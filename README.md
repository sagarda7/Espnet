# SevenSegment
Espnet is an arduino lightweight library which can be used to interface and work with ESP8266 and Arduino Boards

# Install

Clone (or download and unzip) the repository to `/libraries`
which can be found in your arduino installation. currently this library supports only 4 seven segments

# Usage

### Include

```c++
#include <Espnet.h>
```

### Espnet esp(rx, tx, baud, ssid, password);

Constructor to create an Espnet object which takes type parameter.




### Espnet::ready()

Checks if ESP hardware is ready or not. returns boolean

```c++
	void setup(){
		...

		if(esp.ready()) {
			Serial.println(F("Ready"));
		}
		else
		{
			Serial.println(F("Esp Error"));
		}
		...
		 
	}
```

### Espnet::connectWifi()

It connects wifi network and returns true if success
```c++
  void setup(){
		...

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
		...
		 
	}
```

### Espnet::isTcpConnected()

It checks if tcp is connected or not

```c++

  void loop(){
  	...

  	if(!esp.isTcpConnected()) {
      //code to start TCP
      //and send data
    }
    else
    {
       //code to send data here
    }
    
  	...
  }
```

### Espnet::startTcp(host,port)

It starts TCP connection to given host and port number

```c++

  void loop(){
  	...

  	if(!esp.isTcpConnected()) {
      esp.startTcp(HOST,80);
      //code to send data
    }
    else
    {
       //code to send data
    }

  	...
  }
```

### int Espnet::send(const char * str, int len);

Sends data over TCP connection, returns length of data on successful send

```c++
  void send(){
  	  char HOST[]="www.google.com";
  	  char request[100];
	  snprintf(request, sizeof(request), "GET /search?q=esp HTTP/1.1\r\nHost:%s\r\n\r\n",HOST); //Write request
	  Serial.println(esp.send(request,strlen(request)));
  }
```



### Espnet::disconnectTcp()

It disconnects TCP connection
```c++
  void loop(){
  	  esp.disconnectTcp();
  }
```



### Espnet::reset()

It restarts ESP8266

```c++
  void loop(){
  	  esp.reset();
  }
```


### Full Working example of Web Client



```c++
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
```
