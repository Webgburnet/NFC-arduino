// Erases a NFC tag by writing an empty NDEF message 
/*Pour arduino uno spi
 * SCK : 13
 * MISO : 12
 * MOSI : 11
 * SSEL : 10
 */
#if 1
#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);
#else
/*Pour arduino uno i2c
 * SDA : A4
 * SCL : A5/SCL
 */ 
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
#endif

void setup(void) {
    Serial.begin(9600);
    Serial.println("NFC Tag Eraser");
    nfc.begin();
}

void loop(void) {
    Serial.println("\nPlace a tag on the NFC reader to erase.");

    if (nfc.tagPresent()) {

        bool success = nfc.erase();
        if (success) {
            Serial.println("\nSuccess, tag contains an empty record.");        
        } else {
            Serial.println("\nUnable to erase tag.");
        }

    }
    delay(5000);
}
