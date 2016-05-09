#include <SoftwareSerial.h>
#include <Espnet.h>

char HOST[]="www.google.com";

//SSID, password
Espnet esp(2, 3, 9600, "ssid","pass");

void setup() {
  Serial.begin(9600);

  if(esp.ready()) {
    Serial.println(F("Ready"));
    if(esp.connectWifi()) {
      Serial.println(F("Wifi connected"));
    }
    else
    {
      Serial.println(F("Wifi error"));
    }
  }
  else
  {
    Serial.println(F("Esp Error"));
  }

}

void loop() {
    if(!esp.isTcpConnected()) {
      esp.startTcp(HOST,80);
      getData();
    }
    else
    {
       getData();
    }
  
    delay(10000);

}

void getData() {
  char request[100];
  snprintf(request, sizeof(request), "GET /search?q=sagar+devkota HTTP/1.1\r\nHost:%s\r\n\r\n",HOST); //Write request
  Serial.println(request);
  Serial.println(strlen(request));
  Serial.println(esp.send(request,strlen(request)));
}