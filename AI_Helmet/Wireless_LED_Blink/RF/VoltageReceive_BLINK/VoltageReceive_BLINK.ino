#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*#define GREEN_LED 12
#define YELLOW_LED 11
#define RED_LED 10*/

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001"; 
float voltage;


void setup(){
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  /*pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);*/
}

void loop(){
  /*digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);*/

    if (radio.available()) {
      Serial.println("To test");
      char text[32] = {0};
      radio.read(&text, 10);
      Serial.println(text);
      delay(1000);
  }

/*
  if(voltage <= 1){
         digitalWrite(GREEN_LED, LOW);
         digitalWrite(YELLOW_LED, LOW);
         digitalWrite(RED_LED, LOW);
    }
  else
  if(voltage <= 2){
        digitalWrite(GREEN_LED, HIGH);
        delay(1000);
        digitalWrite(GREEN_LED, LOW);
       
    }
   else
   if(voltage <= 4){
        digitalWrite(YELLOW_LED, HIGH);
        delay(1000);
        digitalWrite(YELLOW_LED, LOW);
        
   }
    else
   {
        digitalWrite(RED_LED, HIGH);
        
   }*/
  delay(1000);
  
}
