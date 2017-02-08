#include <Wire.h>
#include <SPI.h>
#include <RH_RF22.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_TSL2561_U.h>
#include <Adafruit_BMP085.h>

RH_RF22 rf22(SS,9);
Adafruit_BMP085 bmp;
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_LOW, 12345);

uint8_t data[] = {
    0x5A,           /* entête */ 
    0x01,           /* numéro de protocole */
    0x00,           /* numéro de séquence */
    0x00, 0x55,     /* adresse source */
    0x00, 0x02,     /* numéro d'application */
    0b10111100, 0x00, 0x00, 0x00, 0x00,
    0b10111101, 0x00, 0x00, 0x00, 0x00,
    0b10111110, 0x00, 0x00, 0x00, 0x00
};

typedef union {
    float f;
    char b[4];
} float_union;

void loadAcceleration(float x, float y, float z)
{
    float_union u;

    u.f = x;
    data[8] = u.b[0];
    data[9] = u.b[1];
    data[10] = u.b[2];
    data[11] = u.b[3];
    u.f = y;
    data[13] = u.b[0];
    data[14] = u.b[1];
    data[15] = u.b[2];
    data[16] = u.b[3];
    u.f = z;
    data[18] = u.b[0];
    data[19] = u.b[1];
    data[20] = u.b[2];
    data[21] = u.b[3];
}

void Err_fatal(char *cause)
{
    Serial.print("FATAL ERROR : ");
    Serial.print(cause);
    while(1);
}

void setup(void) 
{
    Serial.begin(9600);
    delay(1000);

    SPI.setSCK(14);
    if(!rf22.init()) Err_fatal("RF22");
    rf22.setFrequency(434.0, 0.05);
    rf22.setTxPower(RH_RF22_TXPOW_11DBM);
  
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
    loadAcceleration(event.acceleration.x, \
                     event.acceleration.y, \
                     event.acceleration.z);

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

    rf22.send(data, sizeof(data));
    rf22.waitPacketSent();
    data[2]++;

    delay(5000);
}
