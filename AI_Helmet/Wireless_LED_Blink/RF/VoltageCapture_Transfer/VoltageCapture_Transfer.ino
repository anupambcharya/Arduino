#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

int value = 0;
float voltage;

RF24 radio(7, 8); // CE, CSN

const byte address[5] = "00001";


void setup(){
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop(){
  /*value = analogRead(A0);
 // voltage = value * 5.0/1023;
  //Serial.print("Voltage= ");
  //Serial.println(voltage);*/

  const char text[] = "1";
  if (radio.available()) {
      radio.write(&text, sizeof(text));
      Serial.println(text);
  }
  delay(1000);
 
}
