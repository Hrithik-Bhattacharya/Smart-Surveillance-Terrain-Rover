#define IR_SENSOR_PIN 15   // Digital pin connected to IR sensor output
#define LED_PIN 2          // Onboard LED or external LED

void setup() {
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int sensorValue = digitalRead(IR_SENSOR_PIN);

  if (sensorValue == LOW) {  // Obstacle detected
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Obstacle detected!");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("No obstacle.");
  }

  delay(200);  // Small delay for stability
}
