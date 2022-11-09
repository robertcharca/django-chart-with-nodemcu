#include <ESP8266HTTPClient.h>

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>

//About Wifi
char* networkName = "MARY CLARO";
char* networkPassword = "charcafamilyWMRJM50";

char* url = "http://192.168.0.10:8000/sensorvalues/";

//Stuff for temperature sensor
int pinAlertRequest = D2;
int sensor = A0;

float temperature;
float voltage;

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
  // wait for WiFi connection
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
  delay(60000);
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
