// web_index_html.h
const char web_index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <link rel="stylesheet" type="text/css" href="/style.css">
</head>
<body>
    <h1>ESP32 WLED Proxy</h1>
    <form id="controlForm">
        <label for="power">Power:</label>
        <input type="checkbox" name="power" id="power"><br>
        <label for="brightness">Brightness:</label>
        <input type="range" name="brightness" id="brightness" min="0" max="255"><br>
        <label for="color">Color:</label>
        <input type="color" name="color" id="color"><br>
        <input type="submit" value="Send">
    </form>
    <script>
        document.getElementById('controlForm').onsubmit = function(e) {
            e.preventDefault();
            fetch('/api/control', {
                method: 'POST',
                body: JSON.stringify({
                    power: document.getElementById('power').checked,
                    brightness: document.getElementById('brightness').value,
                    color: document.getElementById('color').value
                }),
                headers: { 'Content-Type': 'application/json' }
            });
        };
    </script>
</body>
</html>
)rawliteral";

// web_style_css.h
const char web_style_css[] PROGMEM = R"rawliteral(
body {
    font-family: Arial, sans-serif;
}
h1 {
    color: #333;
}
input[type="range"] {
    width: 100%;
}
)rawliteral";