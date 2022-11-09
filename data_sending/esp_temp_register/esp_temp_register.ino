#include <ESP8266HTTPClient.h>

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

//For Wifi and connections
char* networkName = "network";
char* networkPassword = "password";

char* url = "http://ipaddress:port/sensorvalues/";

//For temperature sensor
int pinAlertRequest = D2;
int sensor = A0;

float temperature;
float voltage;

//For concurrency algorithm
unsigned long lastTime = 0;
unsigned long actualTime = 0;
unsigned long waitTime = 300000;

WiFiServer server(80);

void setup() {
  pinMode(pinAlertRequest, OUTPUT);

  Serial.begin(115200);
  Serial.println();
  
  WiFi.begin(networkName, networkPassword);
  
  Serial.println("Connecting");
  
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }

  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  
  actualTime = millis();

  if(actualTime - lastTime >= waitTime){
    if(WiFi.status()== WL_CONNECTED) {

      WiFiClient client;  
      HTTPClient http;
    
      String jsonResult;
      int response;
    
      
      DynamicJsonDocument doc(1024);
      doc["sensor"] = 1;
      doc["value"] = 2.50;
      serializeJson(doc, jsonResult);
    
      http.begin(client, url);
      http.addHeader("Content-Type", "application/json");
    
      Serial.println(jsonResult);
      
      response = http.POST(jsonResult);
    
      if(response > 0){
        Serial.println("Status code: " + String(response));
    
        if(response == 200){
          String reponse = http.getString();
          Serial.println(response);
        }
      } else {
        Serial.println(response);
      }
    
      http.end();
    }
  
  
  }
  /*
  analogRead(sensor);
  
  voltage = sensor * (5.0 / 1023.0);
  temperature = voltage * 100;

  Serial.println(temperature);
  delay(1000);
  */
}

/*
void httpDataPostRequest() {
  WiFiClient client;  
  HTTPClient http;

  String jsonResult;
  int response;

  String url = "http://127.0.0.1:8000/sensorvalues/";

  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");

  DynamicJsonDocument doc(1024);
  doc["sensor"] = 1;
  doc["value"] = 18.50;
  serializeJson(doc, jsonResult);

  //Serial.println(jsonResult);
  
  response = http.POST(jsonResult);

  if(response > 0){
    Serial.println("Status code: " + String(response));

    if(response == 200){
      String reponse = http.getString();
      Serial.println(response);
    }
  } else {
    Serial.println(response);
  }

  http.end();
  
  
}*/
