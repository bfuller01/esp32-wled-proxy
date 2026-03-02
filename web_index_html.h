#pragma once
#include <pgmspace.h>

static const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WLED Control Interface</title>
    <link rel="stylesheet" href="/style.css">
</head>
<body>
    <div class="container">
        <h1>WLED Control Interface</h1>
        <div class="control-group">
            <label for="target-ip">Target IP/Port:</label>
            <input type="text" id="target-ip" placeholder="192.168.1.100:80" />
        </div>
        <div class="control-group">
            <label for="power">Power:</label>
            <input type="checkbox" id="power" />
        </div>
        <div class="control-group">
            <label for="brightness">Brightness:</label>
            <input type="range" id="brightness" min="0" max="255" value="255" />
        </div>
        <div class="control-group">
            <label for="color">Color:</label>
            <input type="color" id="color" value="#ffffff" />
        </div>
        <div class="control-group">
            <label for="pattern">Pattern:</label>
            <select id="pattern">
                <option value="1">Solid</option>
                <option value="2">Blink</option>
                <option value="3">Pulse</option>
                <option value="4">Rainbow</option>
                <option value="5">Theater Chase</option>
            </select>
        </div>
        <div class="control-group">
            <label for="speed">Speed:</label>
            <input type="range" id="speed" min="1" max="100" value="50" />
        </div>
        <div class="control-group">
            <label for="intensity">Intensity:</label>
            <input type="range" id="intensity" min="1" max="100" value="100" />
        </div>
        <div class="control-group">
            <button class="primary" id="send">Send Command</button>
        </div>
        <div>
            <p id="status-message" class="status-message">Status: Ready</p>
        </div>
    </div>

    <script>
    document.addEventListener('DOMContentLoaded', function () {
        const sendBtn = document.getElementById('send');
        const statusMsg = document.getElementById('status-message');

        sendBtn.addEventListener('click', function () {
            const target = document.getElementById('target-ip').value.trim();
            const power = document.getElementById('power').checked;
            const brightness = parseInt(document.getElementById('brightness').value, 10);
            const color = document.getElementById('color').value;
            const pattern = document.getElementById('pattern').value;
            const speed = parseInt(document.getElementById('speed').value, 10);
            const intensity = parseInt(document.getElementById('intensity').value, 10);

            if (!target) {
                statusMsg.innerText = 'Status: Please enter a target IP/Port.';
                statusMsg.className = 'status-message error';
                return;
            }

            const payload = { target, power, brightness, color, pattern, speed, intensity };

            fetch('/api/control', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(payload),
            })
            .then(function (response) {
                if (!response.ok) throw new Error('Network/Device Error');
                return response.json().catch(function () { return {}; });
            })
            .then(function () {
                statusMsg.innerText = 'Status: Command Sent!';
                statusMsg.className = 'status-message success';
            })
            .catch(function (err) {
                statusMsg.innerText = 'Status: Failed to send command (' + err.message + ')';
                statusMsg.className = 'status-message error';
            });
        });
    });
    </script>
</body>
</html>
)rawliteral";
