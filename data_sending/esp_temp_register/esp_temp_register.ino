
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

//For Wifi and connections
char* networkName = "network (2.4GHz)";
char* networkPassword = "network password";

char* url = "http://network ip:8000/sensorvalues/";

//For temperature sensor
const float lineRegulation = 0.01;
int delayRequest = 3000;
 
int sensor = A0;

//For concurrency algorithm
unsigned long lastTime = 0;
unsigned long actualTime = 0;
unsigned long waitTime = 20000;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();

  //Connecting to WiFi network
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
    //Veriyfing if ESP8266 is connected to WiFi
    if(WiFi.status()== WL_CONNECTED) {
      int readSensor = analogRead(sensor);
      //Serial.println(readSensor);
      float voltage = readSensor * (3.2 / 1023.0);
      //Serial.println(voltage);
      float temperature = voltage / lineRegulation;
      //Serial.println(temperature);
      httpDataPostRequest(temperature);
      
      lastTime = actualTime;
    }
  
  }
  
}

void httpDataPostRequest(float temperatureValue) {
  WiFiClient client;  
  HTTPClient http;

  String jsonResult;
  int response;

  //Starting a http client with the url defined at the beginning and the object of WiFiClient
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");

  //Serializing values to a json format
  DynamicJsonDocument doc(1024);
  doc["sensor"] = 1;
  doc["value"] = roundingTempValue(temperatureValue);
  serializeJson(doc, jsonResult);

  Serial.println(jsonResult);

  //Making a http post request
  response = http.POST(jsonResult);

  //Checking if the response is a 200 code. 
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

//Function to round the float value obtained by the sensor
double roundingTempValue(double value) {
   return (int)(value * 100 + 0.5) / 100.0;
}