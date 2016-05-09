/*
  Espnet.c - Seven Segment Display library
  Copyright (c) 2016 Sagar Devkota.  All right reserved.
  Email:sagarda7@yahoo.com
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "Arduino.h"
#include "Espnet.h"


Espnet::Espnet(int tx, int rx, int baudRate, const char* ssid,const char *passWord):Modem(tx,rx,baudRate){
	_ssid=ssid;
	_passWord=passWord;
	Serial.begin(9600);
	
}



bool Espnet::ready(){
	char buf[10];
	sendCmd("AT\r\n");
	readBuffer(buf,10,2);
	//Serial.println(buf);

    if(NULL != strstr(buf,"OK")) {
		return true;
	}
	else
	{
		return false;
	}
	
}


void Espnet::reset(){
	//sendCmdAndWaitForResp("AT+CIICR\r\n","OK",DEFAULT_TIMEOUT,CMD);
	sendCmdAndWaitForResp("AT+RST\r\n", "OK", DEFAULT_TIMEOUT,CMD);	
	delay(5000);
}


bool Espnet::isTcpConnected(){
	char buf[32];
	sendCmd("AT+CIPSTATUS\r\n");
	readBuffer(buf,32,2);
	//Serial.println(buf);

    if(NULL != strstr(buf,"STATUS:3")) {
		return true;
	}
	else
	{
		return false;
	}
	
}

bool Espnet::connectWifi(){
	char buf[96];
	sendCmdAndWaitForResp("AT+CWMODE=1\r\n","OK",DEFAULT_TIMEOUT,CMD);
	sprintf(buf, "AT+CWJAP=\"%s\",\"%s\"\r\n",_ssid, _passWord);
	//Serial.println(buf);
	sendCmd(buf);
    cleanBuffer(buf,sizeof(buf));

    readBuffer(buf,sizeof(buf),2*DEFAULT_TIMEOUT);
    //Serial.println(buf);
    if(NULL != strstr(buf,"OK")) { //ALREADY CONNECT or CONNECT OK
        return true;
    }
    return false;//ERROR
	
}


bool Espnet::startTcp(char *host, char port){
	char buf[96];
	sprintf(buf, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n",host, port);
	//Serial.println(buf);
	sendCmd(buf);
    cleanBuffer(buf,sizeof(buf));

    readBuffer(buf,sizeof(buf),3*DEFAULT_TIMEOUT);
    //Serial.println(buf);
    if(NULL != strstr(buf,"CONNECT") && NULL != strstr(buf,"CONNECTED")) { 
        return true;
    }
    return false;//ERROR
}

bool Espnet::disconnectTcp()
{
    sendCmd("AT+CIPCLOSE\r\n");
    delay(1000);
    return true;
}

int Espnet::send(const char *str, int len)
{
   
    char cmd[32];
    char buf[300];
    //delay(1000);
    if(len > 0){
        snprintf(cmd,sizeof(cmd),"AT+CIPSEND=%d\r\n",len);
        //Serial.println(cmd);
        if(0 != sendCmdAndWaitForResp(cmd,">",DEFAULT_TIMEOUT,CMD)) {
            return false;
        }


		//Serial.println(buf);
		sendCmd(str);
	    cleanBuffer(buf,sizeof(buf));

	    readBuffer(buf,sizeof(buf),DEFAULT_TIMEOUT+3);
	    Serial.println(buf);
		
        /*if(0 != sendCmdAndWaitForResp(str,"+IPD",DEFAULT_TIMEOUT+3,CMD)) { //DATA if need to read whole
            return -1;
        }*/
    }
    return len;
}
