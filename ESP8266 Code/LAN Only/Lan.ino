#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);

/* WIFI settings */
const char* ssid = "Priyam";   //WIFI SSID
const char* password = "87654321";    //WIFI PASSWORD

/* data received from application */
String  data =""; 

unsigned int Device1 = 1;
unsigned int Device2 = 2;
unsigned int Device3 = 3;
unsigned int SmartLock = 4;


void setup()
{
  /* initialize pins as output */
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT); 
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);

  digitalWrite(D1,LOW);
  digitalWrite(D2,LOW);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
  
  /* start server communication */
  Serial.begin(115200);
  connectWiFi();
  server.begin();
}

void loop()
{
    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) return; 
    data = checkClient ();
Serial.print(data);
/************************ Run function according to incoming data from application *************************/

    
    if (data == "Relay1ON")
    { 
      digitalWrite(D1,HIGH);
      }
    
    else if (data == "Relay1OFF")
    {
      digitalWrite(D1,LOW);
      }

    else if (data == "Relay2ON")
    {
      digitalWrite(D2,HIGH);
      }
      
    else if (data == "Relay2OFF")
    {
      digitalWrite(D2,LOW);
      }
      
    else if (data == "Relay3ON")
    {
      digitalWrite(D3,HIGH);
      }
      
    else if (data == "Relay3OFF")
    {
      digitalWrite(D3,LOW);
      }
      
    else if (data == "RELAY4SUCCESS")//checking for password
    {
      digitalWrite(D4,HIGH);
      delay(3000);
      digitalWrite(D4,LOW);
      }
      
} 

void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}
/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
