This is my personal fork of [FrogPilot](https://github.com/FrogAi/FrogPilot). **This fork contains lots of code changes considered "unsafe" by comma.ai and will get your device banned from their servers if uploading is enabled. Uploads are disabled by default, however logging is still enabled. Be sure to delete all logs before switching to another fork or enabling uploads to avoid getting your device banned.** While the base FrogPilot fork that this is built on top of is primarily geared toward Toyota/Lexus, this is primarily geared toward HKG CAN-FD vehicles, more specifically my Kia EV6.

**This fork is purely a personal project and is not affiliated with FrogAi or FrogPilot in any way. Use at your own risk.**

Having said that, in addition to the features and improvements included from [FrogAi/FrogPilot](https://github.com/FrogAi/FrogPilot), here are some added highlights:

 - Customizable steering torque values
 - Customizable offline and live lateral tuning values (stock torque controller only, does not apply if using [twilsonco's NNFF](https://github.com/twilsonco/openpilot))
 - Toggles to turn off driver monitoring, door open alerts, and seatbelt unlatched alerts
 - Toggle to add a "target locked" animation to the lead car in the on road UI (credit goes to [programanichiro](https://github.com/programanichiro/openpilot))
 - Opweb - access routes, modify parameters, and apply updates via web browser (credit goes to [Jacob Pfeifer](https://github.com/pfeiferj/pfeifer-pilot-patches))
 - Various small tweaks and improvements: use the more fine-grained MDPS steering angle sensor for HKG CAN-FD vehicles, less sensitive steer saturated alerts, faster auto tune for the stock torque controller, display the current branch in the startup alert, ability to set more aggressive follow distances for the driving personalities

Licensing
------

openpilot is released under the MIT license. Some parts of the software are released under other licenses as specified.

Any user of this software shall indemnify and hold harmless Comma.ai, Inc. and its directors, officers, employees, agents, stockholders, affiliates, subcontractors and customers from and against all allegations, claims, actions, suits, demands, damages, liabilities, obligations, losses, settlements, judgments, costs and expenses (including without limitation attorneys’ fees and costs) which arise out of, relate to or result from any use of this software by user.

**THIS IS ALPHA QUALITY SOFTWARE FOR RESEARCH PURPOSES ONLY. THIS IS NOT A PRODUCT.
YOU ARE RESPONSIBLE FOR COMPLYING WITH LOCAL LAWS AND REGULATIONS.
NO WARRANTY EXPRESSED OR IMPLIED.**

---

<img src="https://d1qb2nb5cznatu.cloudfront.net/startups/i/1061157-bc7e9bf3b246ece7322e6ffe653f6af8-medium_jpg.jpg?buster=1458363130" width="75"></img> <img src="https://cdn-images-1.medium.com/max/1600/1*C87EjxGeMPrkTuVRVWVg4w.png" width="225"></img>

![openpilot tests](https://github.com/commaai/openpilot/actions/workflows/selfdrive_tests.yaml/badge.svg)
[![codecov](https://codecov.io/gh/commaai/openpilot/branch/master/graph/badge.svg)](https://codecov.io/gh/commaai/openpilot)
