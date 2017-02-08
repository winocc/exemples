#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_TSL2561_U.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_LOW, 12345);

void Err_fatal(char *cause)
{
    Serial.print("FATAL ERROR : ");
    Serial.print(cause);
    while(1);
}

void setup(void) 
{
    Serial.begin(9600);
    while(!Serial);
  
    if(!accel.begin()) Err_fatal("ACCELEROMETER");

    gyro.enableAutoRange(true); 
    if(!gyro.begin()) Err_fatal("GYROSCOPE");

    mag.enableAutoRange(true); 
    if(!mag.begin()) Err_fatal("MAGNETOMETER");

    if(!tsl.begin()) Err_fatal("LUXMETER");
    tsl.enableAutoRange(true); 
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);

    if(!bmp.begin()) Err_fatal("BMP");
}

void loop(void) 
{
    sensors_event_t event; 

    Serial.println("------------------------------");

    accel.getEvent(&event);
    Serial.print("X:  ");
    Serial.print(event.acceleration.x);
    Serial.print(" ");
    Serial.print("Y:  ");
    Serial.print(event.acceleration.y);
    Serial.print(" ");
    Serial.print("Z:  ");
    Serial.print(event.acceleration.z);
    Serial.print(" ");
    Serial.println("m/s^2 ");

    gyro.getEvent(&event);
    Serial.print("X:  ");
    Serial.print(event.gyro.x);
    Serial.print(" ");
    Serial.print("Y:  ");
    Serial.print(event.gyro.y);
    Serial.print(" ");
    Serial.print("Z:  ");
    Serial.print(event.gyro.z);
    Serial.print(" ");
    Serial.println("rad/s ");

    mag.getEvent(&event);
    Serial.print("X:  ");
    Serial.print(event.magnetic.x);
    Serial.print(" ");
    Serial.print("Y:  ");
    Serial.print(event.magnetic.y);
    Serial.print(" ");
    Serial.print("Z:  ");
    Serial.print(event.magnetic.z);
    Serial.print(" ");
    Serial.println("uT ");

    tsl.getEvent(&event);
    if(event.light)
    {
        Serial.print(event.light);
        Serial.println(" lux");
    }

    delay(1000);
}
