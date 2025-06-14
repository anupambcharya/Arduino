#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "ThingsBoard.h"

#define RELAY 2 //gpio 2 in the esp
#define TOKEN "enteryourtoken" //insert thingsboard token
#define THINGSBOARD_SERVER "demo.thingsboard.io"

const char* wifiSSID = "IBN24-2.4G";
const char* wifiPass = "9873144905";
const char* mqttBroker = "broker.hivemq.com";

WiFiClient client;
PubSubClient mqtt(client);

WiFiClient espClient;
ThingsBoard tb(espClient);


void connectWifi();
void connect_mqtt(); 
void mqttReceive(char *topic, byte*msg, unsigned int msgLength);


void setup()
{
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
    
    pinMode(RELAY, OUTPUT);

    Serial.begin(115200);
    connectWifi();    
    mqtt.setServer(mqttBroker, 1883);
    mqtt.setCallback(mqttReceive);
}

void loop()
{
    if(!mqtt.connected()){
        connect_mqtt();
        Serial.println("MQTT Connected");
    }
    mqtt.loop();
    delay(100);


    if (!tb.connected()) {
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN)) {
      Serial.println("Failed to connect");
      return;
    }
  }

  tb.loop();
}


void connect_mqtt(){
    while (!mqtt.connected())
    {
        Serial.println("Connecting to MQTT...");
        if(mqtt.connect("mqtt_test")){
            mqtt.subscribe("yourtopic"); //match the topic from the previous code
        }
    }
    
}


void connectWifi()
{
    Serial.println("Connecting to WiFi");
    WiFi.begin(wifiSSID, wifiPass);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    
    Serial.println("WiFi Connected");
}


int value; 

void mqttReceive(char *topic, byte*msg, unsigned int msgLength){
        
        String data;
        for(int i = 0; i < msgLength; i++){
            Serial.print(char(msg[i]));
            data += (char)msg[i];
        }
        Serial.println("");

        int value = data.toInt();
        digitalWrite(RELAY, 0);

        switch (value)
        {
        case 0:
            digitalWrite(RELAY, 0);
            break;
        
        case 1:
            digitalWrite(RELAY, 1);
            break;
        }
    
        tb.sendTelemetryInt("lockstatus", value); //send data to thingsboard

    }
