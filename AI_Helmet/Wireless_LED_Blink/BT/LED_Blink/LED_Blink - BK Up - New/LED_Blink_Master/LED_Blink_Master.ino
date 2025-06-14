#include <SoftwareSerial.h>

#define BT_Name = "LED_Master"
#define LED_Slave_Address = ""

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
    Serial.println("Master Module");

    BT.print("AT\r\n");
    delay(200);   

    BT.print("AT+RMAAD\r\n");
    delay(200);    

    /*
    BT.print("AT+ROLE=1\r\n");
    delay(200);    

    BT.print("AT+NAME=LED_Master\r\n");
    delay(200);    

    BT.print("AT+PSWD=\"1979\"\r\n");
    delay(200);  

    BT.print("AT+BIND=0021,09,0013A6\r\n");
    delay(200);  

    BT.print("AT+UART=38400,0,0\r\n");
    delay(500);    

    BT.print("AT+UART?\r\n");
    delay(200); */   
 }


void loop()
{

   if (BT.available() > 0) {  
        c = BT.read();                   // from software serial port as long as
        Serial.write(c);                 // anything is available
  }
  if (Serial.available() > 0) {   // Left over from previous code
    c = Serial.read();               // to send ASCII from PC serial monitor
    Serial.write(c);                 // to HC-05 in case we get that far.
    BT.write(c);                     // [Spoiler Alert] We haven't.
  }
}
