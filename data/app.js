document.addEventListener('DOMContentLoaded', function () {
    // UI elements
    const sendBtn = document.getElementById('send');
    const statusMsg = document.getElementById('status-message');

    sendBtn.addEventListener('click', function () {
        const ip = document.getElementById('target-ip').value.trim();
        const power = document.getElementById('power').checked;
        const brightness = parseInt(document.getElementById('brightness').value, 10);
        const color = document.getElementById('color').value;
        const pattern = document.getElementById('pattern').value;
        const speed = parseInt(document.getElementById('speed').value, 10);
        const intensity = parseInt(document.getElementById('intensity').value, 10);

        // Simple input validation
        if (!ip) {
            statusMsg.innerText = 'Status: Please enter a target IP/Port.';
            statusMsg.className = 'status-message error';
            return;
        }

        // Assemble control payload
        const payload = {
            power, brightness, color, pattern, speed, intensity
        };

        // Send HTTP POST to the proxy
        fetch(`http://${ip}/api/control`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify(payload),
        })
            .then(response => {
                if (!response.ok) throw new Error('Network/Device Error');
                return response.json().catch(() => ({}));
            })
            .then(result => {
                statusMsg.innerText = 'Status: Command Sent!';
                statusMsg.className = 'status-message success';
            })
            .catch(err => {
                statusMsg.innerText = `Status: Failed to send command (${err.message})`;
                statusMsg.className = 'status-message error';
            });
    });
});