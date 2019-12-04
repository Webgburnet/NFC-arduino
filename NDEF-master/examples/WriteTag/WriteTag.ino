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
/*Pour arduino uno i2c
 * SDA : A4
 * SCL : A5/SCL
 */       
#else

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
#endif

void setup() {
      Serial.begin(9600);
      Serial.println("NDEF Writer");
      nfc.begin();
}

void loop() {
    Serial.println("\nPlace a formatted Mifare Classic or Ultralight NFC tag on the reader.");
    if (nfc.tagPresent()) {
        NdefMessage message = NdefMessage();
        message.addTextRecord("TSF : NFC"); // Text Message you want to Record
        message.addUriRecord("http://lyc-hbrisson-vierzon.tice.ac-orleans-tours.fr/"); // Website you want to Record
        message.addTextRecord("BTS SNEC Premiere Année, Année 2016-2017, LPO Henri BRISSON");  // Ednding Message for you to Record

        bool success = nfc.write(message);
        if (success) {
          Serial.println("Success. Try reading this tag with your phone.");        
        } else {
          Serial.println("Write failed.");
        }
    }
    delay(5000);
}
