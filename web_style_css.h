#pragma once
#include <pgmspace.h>

static const char style_css[] PROGMEM = R"rawliteral(
body {
    font-family: 'Arial', sans-serif;
    background: linear-gradient(to right, #ff7e5f, #feb47b);
    margin: 0;
    padding: 0;
}

.container {
    max-width: 1200px;
    margin: auto;
    box-shadow: 0 4px 12px rgba(0,0,0,0.1);
    padding: 20px;
}

header {
    background: linear-gradient(to right, #2193b0, #6dd5ed);
    color: white;
    padding: 20px;
    text-align: center;
}

section {
    padding: 20px;
    border: 1px solid #ccc;
    margin: 10px 0;
}

.control-group {
    margin-bottom: 15px;
}
.control-group label {
    display: block;
    margin-bottom: 5px;
}
.control-group input {
    width: 100%;
    padding: 10px;
    border: 1px solid #ccc;
}

button {
    padding: 10px 20px;
    border: none;
    border-radius: 5px;
    cursor: pointer;
}

button.primary {
    background-color: #28a745;
    color: white;
}

button.toggle {
    background-color: #007bff;
    color: white;
}

.color-picker {
    width: 100%;
}

select {
    width: 100%;
    padding: 10px;
    border: 1px solid #ccc;
}

input[type='range'] {
    width: 100%;
}

.status-message {
    padding: 10px;
    border-radius: 5px;
}

.status-message.success {
    background-color: #d4edda;
    color: #155724;
}

.status-message.error {
    background-color: #f8d7da;
    color: #721c24;
}

.status-message.info {
    background-color: #d1ecf1;
    color: #0c5460;
}

@media (max-width: 768px) {
    body {
        font-size: 14px;
    }
    .container {
        padding: 10px;
    }
}
)rawliteral";
