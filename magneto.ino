#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Magnetometer Test"); Serial.println("");
  
  mag.enableAutoRange(true);
  
  if(!mag.begin())
  {
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}

void loop(void) 
{
  sensors_event_t event; 
  mag.getEvent(&event);
 
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");
  delay(500);
}
