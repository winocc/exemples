#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20_U.h>

Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

void setup(void) 
{
  Serial.begin(9600);
  while(!Serial);  
  Serial.println("Gyroscope Test"); Serial.println("");
  
  gyro.enableAutoRange(true);
  
  if(!gyro.begin())
  {
    Serial.println("Ooops, no L3GD20 detected ... Check your wiring!");
    while(1);
  }
}

void loop(void) 
{
  sensors_event_t event; 
  gyro.getEvent(&event);
 
  Serial.print("X: "); Serial.print(event.gyro.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.gyro.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.gyro.z); Serial.print("  ");
  Serial.println("rad/s ");
  delay(500);
}
