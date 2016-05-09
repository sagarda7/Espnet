#ifndef SevenSeg_h
/*
  Espnet.h - Arduino Esp8266 Library
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
#define Espnet_h

#include "Arduino.h"
#include "modem.h"
#define DEFAULT_WAIT_RESP_TIMEOUT 500

class Espnet: public Modem
{
	public:
		/** Constructor
		 *  @param tx mbed pin to use for tx line of Serial interface
		 *  @param rx mbed pin to use for rx line of Serial interface
		 *  @param baudRate serial communicate baud rate
		 *  @param ssid name of the gateway for GPRS to connect to the network
		 *  @param passWord wifi password, usually is NULL
		 */
		Espnet(int tx, int rx, int baudRate, const char* ssid,const char *passWord = NULL);
		bool ready();
		void reset();
		bool isTcpConnected();
		bool connectWifi();
		bool startTcp(char *host, char port);
		bool disconnectTcp();
		int send(const char * str, int len);


    

	protected:
		const char* _ssid;
		const char* _passWord;
		
		
	
		
};

#endif