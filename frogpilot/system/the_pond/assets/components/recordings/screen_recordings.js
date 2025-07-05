import { html, reactive } from "https://esm.sh/@arrow-js/core"
import { Modal } from "../modal.js";

const state = reactive({
  loading: true,
  error: null,
  recordings: [],
  selectedRecording: null,
  showDeleteModal: false,
  recordingToDelete: null,
  progress: 0,
  total: 0,
})

function getOrdinalSuffix(n) {
  const s = ["th", "st", "nd", "rd"];
  const v = n % 100;
  return s[(v - 20) % 10] || s[v] || s[0];
}

function formatScreenRecordingDate(dateString) {
  const date = new Date(dateString);
  const month = date.toLocaleString('en-US', { month: 'long' });
  const day = date.getDate();
  const year = date.getFullYear();
  let hour = date.getHours();
  const minute = date.getMinutes();
  const ampm = hour >= 12 ? 'pm' : 'am';
  hour = hour % 12;
  hour = hour ? hour : 12;
  const minuteStr = minute < 10 ? '0' + minute : minute;
  return `${month} ${day}${getOrdinalSuffix(day)}, ${year} - ${hour}:${minuteStr}${ampm}`;
}


async function fetchRecordings() {
  try {
    const response = await fetch("/api/screen_recordings/list");
    if (!response.ok) throw new Error();

    const reader = response.body.getReader();
    const decoder = new TextDecoder();

    while (true) {
      const { value, done } = await reader.read();
      if (done) break;

      const chunk = decoder.decode(value);
      const lines = chunk.split('\n\n');

      for (const line of lines) {
        if (line.startsWith('data: ')) {
          const data = JSON.parse(line.substring(6));
          if (data.progress !== undefined && data.total !== undefined) {
            state.progress = data.progress;
            state.total = data.total;
          }
          if (data.recordings) {
            state.recordings = data.recordings;
          }
        }
      }
    }
  } catch (_) {
    state.error = "Couldn't load recordings. Please try again later."
  } finally {
    state.loading = false
  }
}

fetchRecordings()

function refresh() {
  state.loading = true
  fetchRecordings()
}

let overlay = null

function openDialog(htmlStr) {
  const o = document.createElement("div")
  o.className = "dialog-overlay"
  o.innerHTML = htmlStr
  document.body.appendChild(o)
  return o
}

function closeDialog(o) { if (o) o.remove() }

async function renameFile(rec) {
  const base = rec.filename.replace(/\.mp4$/i, "")
  const dlg = openDialog(`
    <div class="dialog-box">
      <p>Rename “${rec.filename}”</p>
      <input class="rn-input" value="${base}" />
      <div class="dialog-buttons">
        <button class="btn-cancel">Cancel</button>
        <button class="btn-save">Save</button>
      </div>
    </div>`)
  dlg.querySelector(".btn-cancel").onclick = () => closeDialog(dlg)
  dlg.querySelector(".btn-save").onclick = async () => {
    const val = dlg.querySelector(".rn-input").value.trim()
    if (!val) return
    const res = await fetch("/api/screen_recordings/rename", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ old: rec.filename, new: val + ".mp4" }),
    })
    if (res.ok) { closeDialog(dlg); closeOverlay(); refresh() }
    else showSnackbar("Rename failed", "error")
  }
}

function confirmDeleteFile(rec) {
    state.recordingToDelete = rec;
    state.showDeleteModal = true;
}

async function deleteFile() {
  if (!state.recordingToDelete) return;
  const rec = state.recordingToDelete;

  const res = await fetch(`/api/screen_recordings/delete/${encodeURIComponent(rec.filename)}`, { method: "DELETE" })
  if (res.ok) {
      closeOverlay();
      refresh();
      showSnackbar("Recording deleted!");
  } else {
      showSnackbar("Delete failed", "error");
  }

  state.showDeleteModal = false;
  state.recordingToDelete = null;
}

function openOverlay(rec) {
  if (overlay) return
  overlay = document.createElement("div")
  overlay.className = "media-player-overlay"
  overlay.innerHTML = `
    <div class="media-player-content">
      <div class="media-player-title">${formatScreenRecordingDate(rec.timestamp)}</div>
      <video controls autoplay muted>
        <source src="/api/screen_recordings/download/${rec.filename}" type="video/mp4">
      </video>
      <div class="button-row">
        <button class="close-button action-close">Close</button>
        <button class="close-button action-rename">Rename</button>
        <a href="/api/screen_recordings/download/${rec.filename}" download="${rec.filename}" class="close-button action-download">Download</a>
        <button class="close-button action-delete">Delete</button>
      </div>
    </div>`
  overlay.addEventListener("click", e => { if (e.target === overlay) closeOverlay() })
  overlay.querySelector(".action-close").onclick = closeOverlay
  overlay.querySelector(".action-rename").onclick = () => renameFile(rec)
  overlay.querySelector(".action-delete").onclick = () => confirmDeleteFile(rec)
  document.body.appendChild(overlay)
}

function closeOverlay() {
  if (!overlay) return
  overlay.remove()
  overlay = null
  state.selectedRecording = null
}

export function ScreenRecordings() {
  if (state.selectedRecording && !overlay) openOverlay(state.selectedRecording)

  return html`
    <div class="screen-recordings-wrapper">
      <div class="screen-recordings-widget">
        <div class="screen-recordings-title">Screen Recordings</div>

        ${() => {
          if (state.loading) {
            if (state.total > 0) {
              return html`<p class="screen-recordings-message">Processing Recordings: ${state.progress} of ${state.total}</p>`
            }
            return html`<p class="screen-recordings-message">Loading…</p>`
          }
          if (state.error) return html`<p class="screen-recordings-message">${state.error}</p>`
          if (!state.recordings.length) return html`<p class="screen-recordings-message">No screen recordings found.</p>`
          return html`
            <div class="screen-recordings-grid">
              ${state.recordings.map(rec => html`
                <div
                  class="recording-card"
                  @mouseenter="${e => {
                    if (!state.selectedRecording) {
                      const c = e.currentTarget
                      c.querySelector(".recording-preview-png").style.display = "none"
                      c.querySelector(".recording-preview-gif").style.display = "block"
                    }
                  }}"
                  @mouseleave="${e => {
                    const c = e.currentTarget
                    c.querySelector(".recording-preview-png").style.display = "block"
                    c.querySelector(".recording-preview-gif").style.display = "none"
                  }}"
                  @click="${() => { state.selectedRecording = rec }}"
                >
                  <div class="recording-preview-container">
                    <img src="${rec.png}" class="recording-preview recording-preview-png" style="display:block;">
                    <img src="${rec.gif}" class="recording-preview recording-preview-gif" style="display:none;">
                  </div>
                  <p class="recording-filename">${formatScreenRecordingDate(rec.timestamp)}</p>
                </div>
              `)}
            </div>
          `
        }}
      </div>
      ${() => state.showDeleteModal ? Modal({
          title: "Confirm Delete",
          message: `Are you sure you want to delete <strong>${state.recordingToDelete.filename}</strong>?`,
          onConfirm: deleteFile,
          onCancel: () => { state.showDeleteModal = false; state.recordingToDelete = null; },
          confirmText: "Delete"
      }) : ""}
    </div>
  `
}
