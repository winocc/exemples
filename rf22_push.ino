
#include <SPI.h>
#include <RH_RF22.h>

RH_RF22 rf22(SS,9);

uint8_t data[] = {
    0x5A,           /* entête */ 
    0x01,           /* numéro de protocole */
    0x00,           /* numéro de séquence */
    0x00, 0x55,     /* adresse source */
    0x00, 0x02,     /* numéro d'application */
    0x04, 0x42,     /* Luminosité 1 uint8_t */
    0x44, 0x43      /* Pression 1 uint8_t */
};

void setup() 
{
    SPI.setSCK(14);

    Serial.begin(9600);
    delay(5000);
    if (!rf22.init())
        Serial.println("init failed");

    //rf22.setModemConfig(RH_RF22::GFSK_Rb125Fd125);
    rf22.setFrequency(434.0, 0.05);
    rf22.setTxPower(RH_RF22_TXPOW_11DBM);
}

void loop()
{
    rf22.send(data, sizeof(data));
    rf22.waitPacketSent();
    data[2]++;

    delay(5000);
}

