#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdlib.h>


#define GREEN_LED 12
#define YELLOW_LED 11
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
  //display.clearDisplay();

  // OLED display

   display.clearDisplay();
   display.setCursor(5,20);
   display.println("V=12.62");
  
   display.setCursor(5,40);
   display.println("C= 9.67");
   display.display();
  
}
