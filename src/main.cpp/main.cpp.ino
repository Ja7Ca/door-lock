#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "Enroll.h"
#include "Scan.h"


//Fingerprint scanner Pins
#define Finger_Rx 14 //D5
#define Finger_Tx 12 //D6

const char* ssid = "nodemcu";
const char* password = "00000000";

ESP8266WebServer server(80);

SoftwareSerial mySerial(Finger_Rx, Finger_Tx);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int FingerID = 0;     // The Fingerprint ID from the scanner 
uint8_t id;
bool isenroll = true;
bool lampu_on = true;
void setup(){
  Serial.begin(115200);
   pinMode(LED_BUILTIN, OUTPUT);
    // set the data rate for the sensor serial port
  finger.begin(57600);
  Serial.println("\n\nAdafruit finger detect test");
  digitalWrite(LED_BUILTIN, HIGH); 
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
 WiFi.mode(WIFI_AP);  
 WiFi.softAP(ssid, password);
 IPAddress myIP = WiFi.softAPIP();
 
   Serial.print(myIP);


 
  // Start the server
  
  server.on("/", [](){
    server.send(200, "text/html", "Home Fingerprint FOSTI<br><br>"
    "<a type='button' href='/enrollmodeon'>Enroll</a>");
    digitalWrite(LED_BUILTIN, HIGH); 
  });
    server.on("/enrollmodeon", [](){
      server.send(200, "text/html", "MODE ENROLL ON<br><br>"
      "<a type='button' href='/enrollmodeoff'>Enroll Off</a><br><br>"
      "<a type='button' href='/'>Back</a><br>");
      isenroll = true;
      digitalWrite(LED_BUILTIN, LOW);

    
  });
    server.on("/enrollmodeoff", [](){
      server.send(200, "text/html", "MODE ENROLL OFF<br><br>"
      "<a type='button' href='/'>Back</a>");
      isenroll = false;
      digitalWrite(LED_BUILTIN, HIGH);


    
  });
  server.begin();
  Serial.println("Server started");


}

//void loop()                     // run over and over again
//{
//  server.handleClient();
//  //getFingerprintID();
//  delay(50);            //don't ned to run this at full speed.
//}
  
uint8_t readnumber(void) {
  uint8_t num = 0;

  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  } 
  return num;
}



void scanFinger(){
  getFingerprintID(finger);
}




void loop()                     // run over and over again
{
  server.handleClient();
  while (! getFingerprintEnroll(finger, id) );
/*   while(true){
      if (isenroll == true){
             Serial.println("Ready to enroll a fingerprint!");
              Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
              id = readnumber();
              if (id == 0) {// ID #0 not allowed, try again!
                return;
              }
              Serial.print("Enrolling ID #");
              Serial.println(id);
        }else{
          scanFinger();
        }
  } */

  
}
