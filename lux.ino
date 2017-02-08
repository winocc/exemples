#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_LOW, 12345);

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("Light Sensor Test"); Serial.println("");
  
  if(!tsl.begin())
  {
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  tsl.enableAutoRange(true); 
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
}

void loop(void) 
{  
  sensors_event_t event;
  tsl.getEvent(&event);
 
  if (event.light)
  {
    Serial.print(event.light); Serial.println(" lux");
  }
  else
  {
    Serial.println("Sensor overload");
  }
  delay(250);
}
