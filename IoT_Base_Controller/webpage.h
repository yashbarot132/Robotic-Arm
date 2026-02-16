const char PAGE_CONTENT[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Robotic Arm Control</title>
  <link href="https://fonts.googleapis.com/css2?family=Orbitron:wght@700&display=swap" rel="stylesheet">
  <style>
    body {
      font-family: 'Orbitron', sans-serif;
      text-align: center;
      background: linear-gradient(135deg, #0f2027, #203a43, #2c5364);
      color: #ff0033;
      padding: 20px;
      margin: 0;
      border: 5px solid #00ffff;
      box-shadow: 0 0 20px #00ffff;
      animation: rgbColorChange 6s infinite;
    }

    h1.title-glow {
      font-size: 36px;
      color: #ff0033;
      letter-spacing: 2px;
      text-shadow: 0 0 10px #ff0033;
      margin-bottom: 30px;
      opacity: 0;
      animation: slideInGlow 1.5s ease-out forwards, pulseGlow 2s 1.6s infinite;
    }

    @keyframes slideInGlow {
      0% { transform: translateX(-100%); opacity: 0; }
      100% { transform: translateX(0); opacity: 1; }
    }

    @keyframes pulseGlow {
      0%, 100% { text-shadow: 0 0 10px #ff0033; }
      50% { text-shadow: 0 0 25px #ff0033, 0 0 40px #ff0033; }
    }

    .servo-control {
      margin: 20px auto;
      background: rgba(0, 0, 50, 0.7);
      color: #ffffff;
      font-size: 22px;
      padding: 15px;
      border-radius: 12px;
      max-width: 500px;
      border: 2px solid #00ffff;
      box-shadow: 0 0 15px #00ffff;
    }

    .servo-control h2 {
      color: #00ffff;
      margin-bottom: 15px;
    }

    button {
      padding: 12px 20px;
      margin: 6px;
      font-size: 16px;
      cursor: pointer;
      border: none;
      border-radius: 8px;
      transition: all 0.3s ease;
      font-weight: bold;
      box-shadow: 0 0 8px #ffffff;
    }

    button.green {
      background-color: #00ff99;
      color: #000000;
      box-shadow: 0 0 10px #00ff99;
    }

    button.stop {
      background-color: #ff0033;
      color: white;
      box-shadow: 0 0 10px #ff0033;
    }

    button:hover {
      transform: scale(1.05);
      opacity: 0.9;
    }

    button.blink {
      animation: blink 0.5s infinite;
    }

    @keyframes blink {
      0% { background-color: #00ff99; }
      50% { background-color: #ffffff; }
      100% { background-color: #00ff99; }
    }

    @keyframes rgbColorChange {
      0% { border-color: #ff0033; box-shadow: 0 0 10px #ff0033; }
      50% { border-color: #00ffff; box-shadow: 0 0 20px #00ffff; }
      100% { border-color: #ff0033; box-shadow: 0 0 10px #ff0033; }
    }
  </style>
</head>
<body>
  <h1 class="title-glow">Robotic Arm Control</h1>

  <div class="servo-control">
    <h2>Base Servo</h2>
    <button class="green" onclick="sendCommand('/base/cw')">Rotate Clockwise</button>
    <button class="green" onclick="sendCommand('/base/ccw')">Rotate Anticlockwise</button>
    <button class="stop" onclick="sendCommand('/base/stop')">Stop</button>
  </div>

  <div class="servo-control">
    <h2>Shoulder Servo</h2>
    <button class="green" onclick="sendCommand('/shoulder/cw')">Rotate Clockwise</button>
    <button class="green" onclick="sendCommand('/shoulder/ccw')">Rotate Anticlockwise</button>
    <button class="stop" onclick="sendCommand('/shoulder/stop')">Stop</button>
  </div>

  <div class="servo-control">
    <h2>Arm Servo</h2>
    <button class="green" onclick="sendCommand('/arm/0')">0°</button>
    <button class="green" onclick="sendCommand('/arm/45')">45°</button>
    <button class="green" onclick="sendCommand('/arm/90')">90°</button>
    <button class="green" onclick="sendCommand('/arm/180')">180°</button>
    <button class="stop" onclick="sendCommand('/arm/stop')">Stop</button>
  </div>

  <div class="servo-control">
    <h2>Wrist Servo</h2>
    <button class="green" onclick="sendCommand('/wrist/0')">0°</button>
    <button class="green" onclick="sendCommand('/wrist/45')">45°</button>
    <button class="green" onclick="sendCommand('/wrist/90')">90°</button>
    <button class="green" onclick="sendCommand('/wrist/180')">180°</button>
    <button class="stop" onclick="sendCommand('/wrist/stop')">Stop</button>
  </div>

  <div class="servo-control">
    <h2>Elbow Servo</h2>
    <button class="green" onclick="sendCommand('/elbow/0')">0°</button>
    <button class="green" onclick="sendCommand('/elbow/45')">45°</button>
    <button class="green" onclick="sendCommand('/elbow/90')">90°</button>
    <button class="green" onclick="sendCommand('/elbow/180')">180°</button>
    <button class="stop" onclick="sendCommand('/elbow/stop')">Stop</button>
  </div>

  <div class="servo-control">
    <h2>Grip Servo</h2>
    <button class="green" onclick="sendCommand('/grip/open')">Open</button>
    <button class="green" onclick="sendCommand('/grip/close')">Close</button>
    <button class="stop" onclick="sendCommand('/grip/stop')">Stop</button>
  </div>

  <script>
    let currentActiveButton = null;
    function sendCommand(endpoint) {
      if (currentActiveButton) {
        currentActiveButton.classList.remove('blink');
      }
      const clicked = event.target;
      clicked.classList.add('blink');
      currentActiveButton = clicked;

      fetch(endpoint)
        .then(response => {
          if (!response.ok) {
            console.error("Command failed:", response.statusText);
          }
        })
        .catch(err => console.error("Network error:", err));
    }
  </script>
</body>
</html>
)rawliteral";
