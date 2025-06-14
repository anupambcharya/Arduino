#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int value = 0;
float voltage;

#define GREEN_LED 12
#define YELLOW_LED 11
#define RED_LED 10

void setup(){
  Serial.begin(9600);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
}

void loop(){
  value = analogRead(A0);
  voltage = value * 5.0/1023;
  Serial.print("Voltage= ");
  Serial.println(voltage);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);

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
        
   }
  
  delay(1000);
}
