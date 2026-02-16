#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

// Replace with your network credentials
const char* ssid = "ENTER YOUR WIFI";
const char* password = "WIFI_PASSWORD";

// Create a web server on port 80
WebServer server(80);

// Define servo pins
const int baseServoPin = 17;
const int shoulderServoPin = 16;
const int armServoPin = 21;
const int wristServoPin = 18;
const int gripServoPin = 15;
const int elbowServoPin = 22;

// Create Servo objects
Servo baseServo;
Servo shoulderServo;
Servo armServo;
Servo wristServo;
Servo gripServo;
Servo elbowServo;

int currentElbowPos = 90;  // Initial elbow position
int pos = 0;

// Include HTML UI
#include "webpage.h"

void setup() {
  Serial.begin(115200);

  // Initialize servos
  baseServo.attach(baseServoPin);
  shoulderServo.attach(shoulderServoPin);
  armServo.attach(armServoPin);
  wristServo.attach(wristServoPin);
  gripServo.attach(gripServoPin);
  elbowServo.attach(elbowServoPin);
  armServo.write(pos);
  elbowServo.write(currentElbowPos);  // Set initial position

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Define routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/base/cw", HTTP_GET, handleBaseCW);
  server.on("/base/ccw", HTTP_GET, handleBaseCCW);
  server.on("/base/stop", HTTP_GET, handleBaseStop);
  server.on("/shoulder/cw", HTTP_GET, handleShoulderCW);
  server.on("/shoulder/ccw", HTTP_GET, handleShoulderCCW);
  server.on("/shoulder/stop", HTTP_GET, handleShoulderStop);
  server.on("/arm/0", HTTP_GET, handleArm0);
  server.on("/arm/45", HTTP_GET, handleArm45);
  server.on("/arm/90", HTTP_GET, handleArm90);
  server.on("/arm/180", HTTP_GET, handleArm180);
  server.on("/wrist/0", HTTP_GET, handleWrist0);
  server.on("/wrist/45", HTTP_GET, handleWrist45);
  server.on("/wrist/90", HTTP_GET, handleWrist90);
  server.on("/wrist/180", HTTP_GET, handleWrist180);
  server.on("/grip/open", HTTP_GET, handleGripOpen);
  server.on("/grip/close", HTTP_GET, handleGripClose);
  server.on("/elbow/0", HTTP_GET, handleElbow0);
  server.on("/elbow/45", HTTP_GET, handleElbow45);
  server.on("/elbow/90", HTTP_GET, handleElbow90);
  server.on("/elbow/180", HTTP_GET, handleElbow180);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  server.send(200, "text/html", PAGE_CONTENT);
}

// Base
void handleBaseCW() {
  baseServo.write(84);
  server.sendHeader("Location", "/");
  Serial.println("Base Clockwise");
  server.send(303);
}
void handleBaseCCW() {
  baseServo.write(100);
  server.sendHeader("Location", "/");
  Serial.println("Base CounterClockwise");
  server.send(303);
}
void handleBaseStop() {
  baseServo.write(92);
  server.sendHeader("Location", "/");
  Serial.println("Base Stop");
  server.send(303);
}

// Shoulder
void handleShoulderCW() {
  shoulderServo.write(87);
  server.sendHeader("Location", "/");
  Serial.println("Shoulder Clockwise");
  server.send(303);
}
void handleShoulderCCW() {
  shoulderServo.write(100);
  server.sendHeader("Location", "/");
  Serial.println("Shoulder CounterClockwise");
  server.send(303);
}
void handleShoulderStop() {
  shoulderServo.write(92);
  server.sendHeader("Location", "/");
  Serial.println("Shoulder Stop");
  server.send(303);
}

// Arm
void handleArm0() {
  armServo.write(0);
  server.sendHeader("Location", "/");
  Serial.println("Arm at 0°");
  server.send(303);
}
void handleArm45() {
  armServo.write(45);
  server.sendHeader("Location", "/");
  Serial.println("Arm at 45°");
  server.send(303);
}
void handleArm90() {
  armServo.write(90);
  server.sendHeader("Location", "/");
  Serial.println("Arm at 90°");
  server.send(303);
}
void handleArm180() {
  armServo.write(180);
  server.sendHeader("Location", "/");
  Serial.println("Arm at 180°");
  server.send(303);
}

// Wrist
void handleWrist0() {
  wristServo.write(0);
  server.sendHeader("Location", "/");
  Serial.println("Wrist at 0°");
  server.send(303);
}
void handleWrist45() {
  wristServo.write(45);
  server.sendHeader("Location", "/");
  Serial.println("Wrist at 45°");
  server.send(303);
}
void handleWrist90() {
  wristServo.write(90);
  server.sendHeader("Location", "/");
  Serial.println("Wrist at 90°");
  server.send(303);
}
void handleWrist180() {
  wristServo.write(180);
  server.sendHeader("Location", "/");
  Serial.println("Wrist at 180°");
  server.send(303);
}

// Grip
void handleGripOpen() {
  Serial.println("Grip Open (0° to 180°)");
  for (int pos = 0; pos <= 180; pos++) {
    gripServo.write(pos);
    delay(10);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}
void handleGripClose() {
  Serial.println("Grip Close (180° to 0°)");
  for (int pos = 180; pos >= 0; pos--) {
    gripServo.write(pos);
    delay(10);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

// Elbow - Smooth Movement
void moveElbowSmooth(int targetAngle) {
  if (targetAngle > currentElbowPos) {
    for (int pos = currentElbowPos; pos <= targetAngle; pos++) {
      elbowServo.write(pos);
      delay(15);  // slower movement
    }
  } else {
    for (int pos = currentElbowPos; pos >= targetAngle; pos--) {
      elbowServo.write(pos);
      delay(15);  // slower movement
    }
  }
  currentElbowPos = targetAngle;
}
void handleElbow0() {
  Serial.println("Elbow to 0°");
  moveElbowSmooth(0);
  server.sendHeader("Location", "/");
  server.send(303);
}
void handleElbow45() {
  Serial.println("Elbow to 45°");
  moveElbowSmooth(45);
  server.sendHeader("Location", "/");
  server.send(303);
}
void handleElbow90() {
  Serial.println("Elbow to 90°");
  moveElbowSmooth(90);
  server.sendHeader("Location", "/");
  server.send(303);
}
void handleElbow180() {
  Serial.println("Elbow to 180°");
  moveElbowSmooth(180);
  server.sendHeader("Location", "/");
  server.send(303);
}
