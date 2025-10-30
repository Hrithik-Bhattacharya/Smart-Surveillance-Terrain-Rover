#define IR_SENSOR_PIN 15

void setup() {
  pinMode(IR_SENSOR_PIN, INPUT);
  Serial.begin(115200);
}

void loop() {
  int state = digitalRead(IR_SENSOR_PIN);
  Serial.println(state == LOW ? "Obstacle detected" : "Clear");
  delay(200);
}
