#include <Arduino.h>


#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;

//WIFIF SETUP



//Server
const String host="http://192.168.116.114:4000";


const int d0=16;
const int d1=5;
const int d2=4;



static int db1=0;
static int db2=0;
static int db3=0;


int current_db1;
int current_db2;
int current_db3;




static String url(int db1,int db2,int db3){
  
   String urls=host+"/data?data="+String(db1)+String(db2)+String(db3);
   Serial.println(urls);
   return urls;
}

void setup() {

  Serial.begin(57600);
  // Serial.setDebugOutput(true);

  pinMode(d0,INPUT);
  pinMode(d1,INPUT);
  pinMode(d2,INPUT);

  db1=digitalRead(d0);
  db2=digitalRead(d1);
  db3=digitalRead(d2);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("abc","12345678");

}

//const String not_full="NOT FULL";
//const String full="FULL";

void loop() {
    int current_db1=digitalRead(d0);
    int current_db2=digitalRead(d1);
    int current_db3=digitalRead(d2);
    
    Serial.println("****************************");
    Serial.println("BINARY DUSTBINS STATES");
    Serial.println("Sate of DUSTBIN_1::");
    Serial.println(!current_db1);
    Serial.println("Sate of DUSTBIN_1::");
    Serial.println(!current_db2);
    Serial.println("Sate of DUSTBIN_1::");
    Serial.println(!current_db3);
    
     Serial.println("****************************");

  
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

       Serial.println("wifi connected");
    
      WiFiClient client;

    HTTPClient http;
    

    if(current_db1!=db1 || current_db2!=db2 || current_db3!=db3){
      db1= current_db1;
      db2= current_db2;
      db3= current_db3;
       Serial.println("%d %d %");
   

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, url(db1,db2,db3))) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }
  }
  delay(2000);
  
}