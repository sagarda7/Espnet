/*
 * modem.cpp
 *
*/

#include "modem.h"

char Modem::readByte(void)
{
    return serialModem.read();
}

bool Modem::readable()
{
    return serialModem.available();
}

#if 0

void Modem::flush(void)
{
    while(serialModem.available()){
        char c = serialModem.read();
    }
}
#endif

int Modem::readBuffer(char *buffer,int count, unsigned int timeOut)
{
    int i = 0;
    unsigned long timerStart,timerEnd;
    timerStart = millis();
    timerEnd = 1000*timeOut + timerStart;
    while(1) {
        while (serialModem.available()) {
            char c = serialModem.read();
            buffer[i++] = c;
            if(i >= count)break;
        }
        if(i >= count)break;
        if(millis() > timerEnd) {
            break;
        }
    }
    return 0;
}

void Modem::cleanBuffer(char *buffer, int count)
{
    for(int i=0; i < count; i++) {
        buffer[i] = '\0';
    }
}

void Modem::sendCmd(const char* cmd)
{
    serialModem.write(cmd);
}

void Modem::sendATTest(void)
{
    sendCmdAndWaitForResp("AT\r\n","OK",DEFAULT_TIMEOUT,CMD);
}

bool Modem::respCmp(const char *resp, unsigned int len, unsigned int timeout)
{
    int sum=0;
    unsigned long timerStart,timerEnd;
    timerStart = millis();
    timerEnd = 1000*timeout + timerStart;
    while(1) {
        if(serialModem.available()) {
            char c = serialModem.read();
            sum = (c==resp[sum]) ? sum+1 : 0;
            if(sum == len)break;
        }
        if(millis() > timerEnd) {
            return false;
        }
    }

    return true;
}

int Modem::waitForResp(const char *resp, unsigned int timeout,DataType type)
{
    int len = strlen(resp);
    int sum = 0;
    unsigned long timerStart,timerEnd;
    timerStart = millis();
    timerEnd = 1000*timeout + timerStart;
    while(1) {
        if(serialModem.available()) {
            char c = serialModem.read();
			//Serial.print(c);
            sum = (c==resp[sum]) ? sum+1 : 0;
            if(sum == len)break;
        }
        if(millis() > timerEnd) {
            return -1;
        }
    }

    if(type == CMD) {
        while(serialModem.available()) {
            char c = serialModem.read();
        }
    }

    return 0;
}

int Modem::sendCmdAndWaitForResp(const char* data, const char *resp, unsigned timeout,DataType type)
{
    sendCmd(data);
    return waitForResp(resp,timeout,type);
}
