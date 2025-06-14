#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdlib.h>


#define GREEN_LED 11
#define YELLOW_LED 12
#define RED_LED 10


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
//#define OLED_ADDR 0x3C // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT);

const byte rxPin = 4;
const byte txPin = 5;

char c = ' ';
char light = ' ';
String strVoltage = "";

float voltage = 0.00;

// Set up a new SoftwareSerial object
SoftwareSerial BT (rxPin, txPin);


void setup()
{
  // Define pin modes for TX and RX
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    
    Serial.begin(9600);
    BT.begin(38400);
   

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
    display.clearDisplay();

    display.setTextSize(2.0);
    display.setTextColor(WHITE);
    

    //***Serial.println("Ready Setup");
    delay(1000);                       // Last attempt, delay until
    //BT.write("AT\r\n");                // "AT" command is sent over software
   
 }


void loop()
{

  delay(500);                        // serial port. After delay,
  display.clearDisplay();
  
  if (BT.available() > 0) {  
         // do nothing other than report chars
    c = BT.read(); 
    //light = c;
    //Serial.write("Reached here");
    Serial.write(c);                 // anything is available
    strVoltage="";
    
    for (int i = 1; i <= 4; i++)
      { 
        Serial.println("Reached while");            
         strVoltage=strVoltage + c;
         delay(10);
         c = BT.read();    
      }// end while


   Serial.println("Voltage = " +  strVoltage);
   voltage = strVoltage.toFloat();
   Serial.println("Voltage F = " +  String(voltage));

   // OLED display

   display.clearDisplay();
   display.setCursor(5,30);
   //display.println("V=32.26");
   display.println("V=" + strVoltage);
   //display.setCursor(5,50);
   //display.println("C= 9.67");

   // light

   digitalWrite(GREEN_LED, LOW);
   digitalWrite(YELLOW_LED, LOW);
   digitalWrite(RED_LED, LOW);
   
    if(voltage < 2.5){
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(RED_LED, LOW);

        display.setCursor(5,50);
         display.println("C=21.04");
         display.display();
    }

    else
    if(voltage > 2.5 && voltage < 4.0){
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, HIGH);
        digitalWrite(RED_LED, LOW);

        display.setCursor(5,50);
         display.println("C=36.57");
         display.display();

    }
    else
    if(voltage > 4.0){
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(YELLOW_LED, LOW);
        digitalWrite(RED_LED, HIGH);

         display.setCursor(5,50);
         display.println("C=57.42");
         display.display();

    }


  
    
        //Serial.println("Inside loop");
  }

  //delay(500);
  //Serial.println("Ready loop");


 //AT command activate
/*****************************************
  if (BT.available() > 0) {  
         // do nothing other than report chars
    //Serial.print("Reached here BT");
    c = BT.read();                   // from software serial port as long as
    Serial.write(c);                 // anything is available
  }
  if (Serial.available() > 0) {   // Left over from previous code
        c = Serial.read();               // to send ASCII from PC serial monitor
    Serial.write(c);                 // to HC-05 in case we get that far.
    BT.write(c);                     // [Spoiler Alert] We haven't.
  }
******************************************/
 }
