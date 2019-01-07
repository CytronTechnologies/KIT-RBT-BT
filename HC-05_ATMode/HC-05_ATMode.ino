/*
 * HC-05 AT Mode
 * 
 * To enter the AT Mode of Bluetooth HC-05 
 * 
 * Please make sure that the button on the bluetooth HC-05 is pressed
 * before supply a power to it. You'll notice that the LED on the 
 * bluetooth HC-05 will blink slower than the normal mode. Then release
 * the button.
 * Open the Serial monitor and set the baud rate to 9600 and Both NL and CR.
 * 
 * AT+NAME=....   -> To set the bluetooth name. Example: AT+NAME=CYTRON
 * AT+PSWD="...." -> To set the bluetooth password. Example: AT+PSWD="0000"
 * 
 * For more info: https://docs.google.com/…/1JGKLEX0Jm_0jvSgEAjsCdnhwIo1…/view
 * 
 * 7th January 2019
 * by Suad Anwar
 * 
 */
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(3, 4); // RX | TX

void setup()
{
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);       // HC-05 default speed in AT command more
}

void loop()
{
  if (BTSerial.available()) {   // read from HC-05 and send to Arduino Serial Monitor
    Serial.write(BTSerial.read());
  }

  if (Serial.available()) {    // Keep reading from Arduino Serial Monitor and send to HC-05
    BTSerial.write(Serial.read());
  }
}
