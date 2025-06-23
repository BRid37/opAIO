import { html } from "https://esm.sh/@arrow-js/core";

export function Modal({
  title,
  message,
  onConfirm,
  onCancel,
  confirmText = "Confirm",
  cancelText = "Cancel",
  confirmClass = "btn-danger"
}) {
  return html`
    <div class="modal-overlay" @click="${(e) => {
      if (e.target.classList.contains('modal-overlay')) {
        onCancel();
      }
    }}">
      <div class="modal">
        <div class="modal-header">${title}</div>
        <div class="modal-body">${message}</div>
        <div class="modal-actions">
          <button class="btn" @click="${onCancel}">${cancelText}</button>
          <button class="btn ${confirmClass}" @click="${onConfirm}">${confirmText}</button>
        </div>
      </div>
    </div>
  `;
}
