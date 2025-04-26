import os
import math
import json
from extra.utils import OSX
import numpy as np
from PIL import Image
import pathlib
import boto3, botocore
from extra.utils import download_file
from tqdm import tqdm
import pandas as pd
import concurrent.futures

BASEDIR = pathlib.Path(__file__).parent / "open-images-v6-mlperf"
BUCKET_NAME = "open-images-dataset"
BBOX_ANNOTATIONS_URL = "https://storage.googleapis.com/openimages/v5/validation-annotations-bbox.csv"
MAP_CLASSES_URL = "https://storage.googleapis.com/openimages/v5/class-descriptions-boxable.csv"
MLPERF_CLASSES = ['Airplane', 'Antelope', 'Apple', 'Backpack', 'Balloon', 'Banana',
  'Barrel', 'Baseball bat', 'Baseball glove', 'Bee', 'Beer', 'Bench', 'Bicycle',
  'Bicycle helmet', 'Bicycle wheel', 'Billboard', 'Book', 'Bookcase', 'Boot',
  'Bottle', 'Bowl', 'Bowling equipment', 'Box', 'Boy', 'Brassiere', 'Bread',
  'Broccoli', 'Bronze sculpture', 'Bull', 'Bus', 'Bust', 'Butterfly', 'Cabinetry',
  'Cake', 'Camel', 'Camera', 'Candle', 'Candy', 'Cannon', 'Canoe', 'Carrot', 'Cart',
  'Castle', 'Cat', 'Cattle', 'Cello', 'Chair', 'Cheese', 'Chest of drawers', 'Chicken',
  'Christmas tree', 'Coat', 'Cocktail', 'Coffee', 'Coffee cup', 'Coffee table', 'Coin',
  'Common sunflower', 'Computer keyboard', 'Computer monitor', 'Convenience store',
  'Cookie', 'Countertop', 'Cowboy hat', 'Crab', 'Crocodile', 'Cucumber', 'Cupboard',
  'Curtain', 'Deer', 'Desk', 'Dinosaur', 'Dog', 'Doll', 'Dolphin', 'Door', 'Dragonfly',
  'Drawer', 'Dress', 'Drum', 'Duck', 'Eagle', 'Earrings', 'Egg (Food)', 'Elephant',
  'Falcon', 'Fedora', 'Flag', 'Flowerpot', 'Football', 'Football helmet', 'Fork',
  'Fountain', 'French fries', 'French horn', 'Frog', 'Giraffe', 'Girl', 'Glasses',
  'Goat', 'Goggles', 'Goldfish', 'Gondola', 'Goose', 'Grape', 'Grapefruit', 'Guitar',
  'Hamburger', 'Handbag', 'Harbor seal', 'Headphones', 'Helicopter', 'High heels',
  'Hiking equipment', 'Horse', 'House', 'Houseplant', 'Human arm', 'Human beard',
  'Human body', 'Human ear', 'Human eye', 'Human face', 'Human foot', 'Human hair',
  'Human hand', 'Human head', 'Human leg', 'Human mouth', 'Human nose', 'Ice cream',
  'Jacket', 'Jeans', 'Jellyfish', 'Juice', 'Kitchen & dining room table', 'Kite',
  'Lamp', 'Lantern', 'Laptop', 'Lavender (Plant)', 'Lemon', 'Light bulb', 'Lighthouse',
  'Lily', 'Lion', 'Lipstick', 'Lizard', 'Man', 'Maple', 'Microphone', 'Mirror',
  'Mixing bowl', 'Mobile phone', 'Monkey', 'Motorcycle', 'Muffin', 'Mug', 'Mule',
  'Mushroom', 'Musical keyboard', 'Necklace', 'Nightstand', 'Office building',
  'Orange', 'Owl', 'Oyster', 'Paddle', 'Palm tree', 'Parachute', 'Parrot', 'Pen',
  'Penguin', 'Personal flotation device', 'Piano', 'Picture frame', 'Pig', 'Pillow',
  'Pizza', 'Plate', 'Platter', 'Porch', 'Poster', 'Pumpkin', 'Rabbit', 'Rifle',
  'Roller skates', 'Rose', 'Salad', 'Sandal', 'Saucer', 'Saxophone', 'Scarf', 'Sea lion',
  'Sea turtle', 'Sheep', 'Shelf', 'Shirt', 'Shorts', 'Shrimp', 'Sink', 'Skateboard',
  'Ski', 'Skull', 'Skyscraper', 'Snake', 'Sock', 'Sofa bed', 'Sparrow', 'Spider', 'Spoon',
  'Sports uniform', 'Squirrel', 'Stairs', 'Stool', 'Strawberry', 'Street light',
  'Studio couch', 'Suit', 'Sun hat', 'Sunglasses', 'Surfboard', 'Sushi', 'Swan',
  'Swimming pool', 'Swimwear', 'Tank', 'Tap', 'Taxi', 'Tea', 'Teddy bear', 'Television',
  'Tent', 'Tie', 'Tiger', 'Tin can', 'Tire', 'Toilet', 'Tomato', 'Tortoise', 'Tower',
  'Traffic light', 'Train', 'Tripod', 'Truck', 'Trumpet', 'Umbrella', 'Van', 'Vase',
  'Vehicle registration plate', 'Violin', 'Wall clock', 'Waste container', 'Watch',
  'Whale', 'Wheel', 'Wheelchair', 'Whiteboard', 'Window', 'Wine', 'Wine glass', 'Woman',
  'Zebra', 'Zucchini',
]

def openimages():
  ann_file = BASEDIR / "validation/labels/openimages-mlperf.json"
  if not ann_file.is_file():
    fetch_openimages(ann_file)
  return ann_file

# this slows down the conversion a lot!
# maybe use https://raw.githubusercontent.com/scardine/image_size/master/get_image_size.py
def extract_dims(path): return Image.open(path).size[::-1]

def export_to_coco(class_map, annotations, image_list, dataset_path, output_path, classes=MLPERF_CLASSES):
  output_path.parent.mkdir(parents=True, exist_ok=True)
  cats = [{"id": i, "name": c, "supercategory": None} for i, c in enumerate(classes)]
  categories_map = pd.DataFrame([(i, c) for i, c in enumerate(classes)], columns=["category_id", "category_name"])
  class_map = class_map.merge(categories_map, left_on="DisplayName", right_on="category_name", how="inner")
  annotations = annotations[np.isin(annotations["ImageID"], image_list)]
  annotations = annotations.merge(class_map, on="LabelName", how="inner")
  annotations["image_id"] = pd.factorize(annotations["ImageID"].tolist())[0]
  annotations[["height", "width"]] = annotations.apply(lambda x: extract_dims(dataset_path / f"{x['ImageID']}.jpg"), axis=1, result_type="expand")

  # Images
  imgs = [{"id": int(id + 1), "file_name": f"{image_id}.jpg", "height": row["height"], "width": row["width"], "license": None, "coco_url": None}
    for (id, image_id), row in (annotations.groupby(["image_id", "ImageID"]).first().iterrows())
  ]

  # Annotations
  annots = []
  for i, row in annotations.iterrows():
    xmin, ymin, xmax, ymax, img_w, img_h = [row[k] for k in ["XMin", "YMin", "XMax", "YMax", "width", "height"]]
    x, y, w, h = xmin * img_w, ymin * img_h, (xmax - xmin) * img_w, (ymax - ymin) * img_h
    coco_annot = {"id": int(i) + 1, "image_id": int(row["image_id"] + 1), "category_id": int(row["category_id"]), "bbox": [x, y, w, h], "area": w * h}
    coco_annot.update({k: row[k] for k in ["IsOccluded", "IsInside", "IsDepiction", "IsTruncated", "IsGroupOf"]})
    coco_annot["iscrowd"] = int(row["IsGroupOf"])
    annots.append(coco_annot)

  info = {"dataset": "openimages_mlperf", "version": "v6"}
  coco_annotations = {"info": info, "licenses": [], "categories": cats, "images": imgs, "annotations": annots}
  with open(output_path, "w") as fp:
    json.dump(coco_annotations, fp)

def get_image_list(class_map, annotations, classes=MLPERF_CLASSES):
  labels = class_map[np.isin(class_map["DisplayName"], classes)]["LabelName"]
  image_ids = annotations[np.isin(annotations["LabelName"], labels)]["ImageID"].unique()
  return image_ids

def download_image(bucket, image_id, data_dir):
  try:
    bucket.download_file(f"validation/{image_id}.jpg", f"{data_dir}/{image_id}.jpg")
  except botocore.exceptions.ClientError as exception:
    sys.exit(f"ERROR when downloading image `validation/{image_id}`: {str(exception)}")

def fetch_openimages(output_fn):
  bucket = boto3.resource("s3", config=botocore.config.Config(signature_version=botocore.UNSIGNED)).Bucket(BUCKET_NAME)

  annotations_dir, data_dir = BASEDIR / "annotations", BASEDIR / "validation/data"
  annotations_dir.mkdir(parents=True, exist_ok=True)
  data_dir.mkdir(parents=True, exist_ok=True)

  annotations_fn = annotations_dir / BBOX_ANNOTATIONS_URL.split('/')[-1]
  download_file(BBOX_ANNOTATIONS_URL, annotations_fn)
  annotations = pd.read_csv(annotations_fn)

  classmap_fn = annotations_dir / MAP_CLASSES_URL.split('/')[-1]
  download_file(MAP_CLASSES_URL, classmap_fn)
  class_map = pd.read_csv(classmap_fn, names=["LabelName", "DisplayName"])

  image_list = get_image_list(class_map, annotations)

  with concurrent.futures.ThreadPoolExecutor() as executor:
    futures = [executor.submit(download_image, bucket, image_id, data_dir) for image_id in image_list]
    for future in (t := tqdm(concurrent.futures.as_completed(futures), total=len(image_list))):
      t.set_description(f"Downloading images")
      future.result()

  print("Converting annotations to COCO format...")
  export_to_coco(class_map, annotations, image_list, data_dir, output_fn)

def image_load(fn):
  img_folder = BASEDIR / "validation/data"
  img = Image.open(img_folder / fn).convert('RGB')
  import torchvision.transforms.functional as F
  ret = F.resize(img, size=(800, 800))
  ret = np.array(ret)
  return ret, img.size[::-1]

def prepare_target(annotations, img_id, img_size):
  boxes = [annot["bbox"] for annot in annotations]
  boxes = np.array(boxes, dtype=np.float32).reshape(-1, 4)
  boxes[:, 2:] += boxes[:, :2]
  boxes[:, 0::2] = boxes[:, 0::2].clip(0, img_size[1])
  boxes[:, 1::2] = boxes[:, 1::2].clip(0, img_size[0])
  keep = (boxes[:, 3] > boxes[:, 1]) & (boxes[:, 2] > boxes[:, 0])
  boxes = boxes[keep]
  classes = [annot["category_id"] for annot in annotations]
  classes = np.array(classes, dtype=np.int64)
  classes = classes[keep]
  return {"boxes": boxes, "labels": classes, "image_id": img_id, "image_size": img_size}

def iterate(coco, bs=8):
  image_ids = sorted(coco.imgs.keys())
  for i in range(0, len(image_ids), bs):
    X, targets  = [], []
    for img_id in image_ids[i:i+bs]:
      x, original_size = image_load(coco.loadImgs(img_id)[0]["file_name"])
      X.append(x)
      annotations = coco.loadAnns(coco.getAnnIds(img_id))
      targets.append(prepare_target(annotations, img_id, original_size))
    yield np.array(X), targets
