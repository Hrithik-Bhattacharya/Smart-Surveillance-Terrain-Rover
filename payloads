#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  
  Wire.begin(22, 21); 

  Serial.begin(9600);
  
  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX90614. Check wiring.");
    while (1);
  }

  Serial.println("MLX90614 Sensor Initialized.");
}

void loop() {
  float tempC = mlx.readObjectTempC();
  Serial.println(tempC); 
  delay(1000);           
}
