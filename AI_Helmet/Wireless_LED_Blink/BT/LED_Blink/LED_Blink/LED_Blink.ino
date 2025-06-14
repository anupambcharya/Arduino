#include <SoftwareSerial.h>

const byte rxPin = 4;
const byte txPin = 5;

char c = ' ';

// Set up a new SoftwareSerial object
SoftwareSerial BT (rxPin, txPin);


void setup()
{
  // Define pin modes for TX and RX
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    
    Serial.begin(9600);
    BT.begin(38400);
    Serial.println("Ready");

    delay(1000);                       // Last attempt, delay until
    BT.write("AT\r\n");                // "AT" command is sent over software
 }


void loop()
{

  /**
    if (Bluetooth.available())
  {
    Serial.println("Reached BT");
     delay(1000);  
    Serial.println(Bluetooth.read());
    
  }

   if (Serial.available())
  {
    
    Serial.println("Reached Serial");
     delay(2000);  
     c = Serial.read();
    Serial.println(c);
    Serial.println(Serial.read());
  }
 **/

  
  delay(100);                        // serial port. After delay,
  if (BT.available() > 0) {  
         // do nothing other than report chars
    c = BT.read();                   // from software serial port as long as
    Serial.write(c);                 // anything is available
  }
  if (Serial.available() > 0) {   // Left over from previous code
    
    c = Serial.read();               // to send ASCII from PC serial monitor
    Serial.write(c);                 // to HC-05 in case we get that far.
    BT.write(c);                     // [Spoiler Alert] We haven't.
  }
}
