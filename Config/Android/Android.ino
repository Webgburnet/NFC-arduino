/*Pour arduino uno i2c
 * SDA : A4
 * SCL : A5/SCL
 */                    
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>   // The following files are included in the libraries Installed
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);  // Indicates the Shield you are using

void setup() {
    Serial.begin(9600);
    Serial.println("NFC Tag Writer"); // Serial Monitor Message
    nfc.begin();
}

void loop() {
    Serial.println("\nPlace an NFC Tag that you want to Record these Messages on!"); // Command for the Serial Monitor
    if (nfc.tagPresent()) {
        NdefMessage message = NdefMessage();
        message.addTextRecord("TSF : NFC"); // Text Message you want to Record
        message.addUriRecord("http://lyc-hbrisson-vierzon.tice.ac-orleans-tours.fr/"); // Website you want to Record
        message.addTextRecord("BTS SNEC Premiere Année");  // Ednding Message for you to Record
        boolean success = nfc.write(message);
        if (success) {
            Serial.println("Good Job, now read it with your phone!"); // if it works you will see this message 
        } else {
            Serial.println("Write failed"); // If the the rewrite failed you will see this message
        }
    }
    delay(10000);
}
