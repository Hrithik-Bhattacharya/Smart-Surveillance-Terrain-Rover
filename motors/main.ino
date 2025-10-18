#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "YOUR_SSID"; //Replace with your SSID
const char* password = "YOUR_PASSWORD"; //Replace with your password for the given SSID

// Motor A pins (Left)
const int IN1 = 12;
const int IN2 = 18;
const int ENA = 15;

// Motor B pins (Right)
const int IN3 = 14;
const int IN4 = 27;
const int ENB = 26;

// Web server
WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Set motor pins as output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  stopMotor(); // Ensure motors are stopped at start

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Define web routes
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

// ====== Web UI HTML ======
void handleRoot() {
  server.send(200, "text/html", R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32-CAM Rover Control</title>
  <style>
    body { font-family: Arial; text-align: center; background: #f2f2f2; }
    h1 { color: #333; }
    .btn {
      width: 120px; height: 50px; margin: 10px;
      font-size: 16px; border: none; border-radius: 8px;
      background-color: #4CAF50; color: white;
      cursor: pointer;
    }
    .btn:hover { background-color: #45a049; }
    .control-panel { display: flex; justify-content: center; flex-wrap: wrap; }
  </style>
</head>
<body>
  <h1>ESP32 Rover Control Panel</h1>
  <div class="control-panel">
    <button class="btn" onclick="sendCommand('forward')">Forward</button><br>
    <button class="btn" onclick="sendCommand('left')">Left</button>
    <button class="btn" onclick="sendCommand('stop')">Stop</button>
    <button class="btn" onclick="sendCommand('right')">Right</button><br>
    <button class="btn" onclick="sendCommand('backward')">Backward</button>
  </div>

  <script>
    function sendCommand(cmd) {
      fetch('/' + cmd)
        .then(response => console.log("Command:", cmd))
        .catch(error => console.error("Error:", error));
    }
  </script>
</body>
</html>
  )rawliteral");
}

// ====== Web Command Handlers ======
void handleForward() {
  motorForward();
  server.send(200, "text/plain", "Moving Forward");
}
void handleBackward() {
  motorBackward();
  server.send(200, "text/plain", "Moving Backward");
}
void handleLeft() {
  motorLeft();
  server.send(200, "text/plain", "Turning Left");
}
void handleRight() {
  motorRight();
  server.send(200, "text/plain", "Turning Right");
}
void handleStop() {
  stopMotor();
  server.send(200, "text/plain", "Stopped");
}

// ====== Motor Control Functions ======
void motorForward() {
  Serial.println("Moving Forward");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); // Left motor forward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); // Right motor forward
  analogWrite(ENA, 150); analogWrite(ENB, 150);
}

void motorBackward() {
  Serial.println("Moving Backward");
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); // Left motor backward
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); // Right motor backward
  analogWrite(ENA, 150); analogWrite(ENB, 150);
}

void motorLeft() {
  Serial.println("Turning Left (in place)");
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); // Left motor backward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); // Right motor forward
  analogWrite(ENA, 150); analogWrite(ENB, 150);
}

void motorRight() {
  Serial.println("Turning Right (in place)");
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); // Left motor forward
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); // Right motor backward
  analogWrite(ENA, 150); analogWrite(ENB, 150);
}

void stopMotor() {
  Serial.println("Stopping");
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); analogWrite(ENB, 0);
}
