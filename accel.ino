#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");
  
  if(!accel.begin())
  {
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}

void loop(void) 
{
  sensors_event_t event; 
  accel.getEvent(&event);
 
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  delay(500);
}
