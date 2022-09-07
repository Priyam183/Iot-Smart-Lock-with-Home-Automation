#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

//wifi credentials 
const char* ssid     = "Priyam";//Replace with your Wifi Name
const char* password = "87654321";// Replace with your wifi Password

//channel details 
unsigned long channel = 1746702;// ThingSpeak Account Channel ID
const char * myWriteAPIKey = "UIWCKE302UBKTMH3";
//1,2,3 and 4 are channel fields. 
unsigned int Device1 = 1;
unsigned int Device2 = 2;
unsigned int Device3 = 3;
unsigned int SmartLock = 4;

WiFiClient  client;


void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D1, 0);
  digitalWrite(D2, 0);
  digitalWrite(D3, 0);
  digitalWrite(D4, 0);
  // We start by connecting to a WiFi network
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  ThingSpeak.begin(client);

}

void loop() {
 
  //get the last data of the fields
  int Device_1 = ThingSpeak.readFloatField(channel, Device1);
  int Device_2 = ThingSpeak.readFloatField(channel, Device2);
  int Device_3 = ThingSpeak.readFloatField(channel, Device3);
  int Smart_Lock = ThingSpeak.readFloatField(channel, SmartLock);
  if(Device_1 == 1){
    digitalWrite(D1, 1);
    Serial.println("D1 is On..!");
  }
  else if(Device_1 == 0){
    digitalWrite(D1, 0);
    Serial.println("D1 is Off..!");
  }
 
  if(Device_2 == 1){
    digitalWrite(D2, 1);
    Serial.println("D2 is On..!");
  }
  else if(Device_2 == 0){
    digitalWrite(D2, 0);
    Serial.println("D2 is Off..!");
  }
 
  if(Device_3 == 1){
    digitalWrite(D3, 1);
    Serial.println("D3 is On..!");
  }
  else if(Device_3 == 0){
    digitalWrite(D3, 0);
    Serial.println("D3 is Off..!");
  }
  if(Smart_Lock == 1){
    digitalWrite(D4, 1);
    delay(16000);
    ThingSpeak.writeField(channel, SmartLock, 0, myWriteAPIKey);
    digitalWrite(D4, 0);
    Serial.println("D4 is On..!");
  }
  else if(Smart_Lock == 0){
    digitalWrite(D4, 0);
    Serial.println("D4 is Off..!");
  }
    
  Serial.println(Device_1);
  Serial.println(Device_2);
  Serial.println(Device_3);
  Serial.println(Smart_Lock);
  delay(5000);
 
}
