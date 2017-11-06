/******************************************************************************
SparkFunESP8266UDPClient.cpp
ESP8266 WiFi Shield Library Client Source File
Jim Lindblom @ SparkFun Electronics
Original Creation Date: June 20, 2015
http://github.com/sparkfun/SparkFun_ESP8266_AT_Arduino_Library

!!! Description Here !!!

Development environment specifics:
	IDE: Arduino 1.6.5
	Hardware Platform: Arduino Uno
	ESP8266 WiFi Shield Version: 1.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#include "SparkFunESP8266WiFi.h"
#include <Arduino.h>
#include "util/ESP8266_AT.h"
#include "SparkFunESP8266UDPClient.h"

ESP8266UDPClient::ESP8266UDPClient()
{
}

ESP8266UDPClient::ESP8266UDPClient(uint8_t sock)
{
	_socket = sock;
}

uint8_t ESP8266UDPClient::status()
{
	return esp8266.status();
}
	
int ESP8266UDPClient::connect(IPAddress ip, uint16_t port)
{
	return connect(ip, port, 0);
}

int ESP8266UDPClient::connect(const char *host, uint16_t port)
{
	return connect(host, port, 0);
}

int ESP8266UDPClient::connect(String host, uint16_t port, uint32_t keepAlive)
{
	return connect(host.c_str(), port, keepAlive);
}
	
int ESP8266UDPClient::connect(IPAddress ip, uint16_t port, uint32_t keepAlive) 
{
	char ipAddress[16];
	sprintf(ipAddress, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
	
	return connect((const char *)ipAddress, port, keepAlive);
}
	
int ESP8266UDPClient::connect(const char* host, uint16_t port, uint32_t keepAlive) 
{
	_socket = getFirstSocket();
	
    if (_socket != ESP8266_SOCK_NOT_AVAIL)
    {
		esp8266._state[_socket] = TAKEN;
		int16_t rsp = esp8266.tcpConnect(_socket, host, port, keepAlive, ESP8266_UDP);
		
		return rsp;
	}
}

size_t ESP8266UDPClient::write(uint8_t c)
{
	return write(&c, 1);
}

size_t ESP8266UDPClient::write(const uint8_t *buf, size_t size)
{
	return esp8266.tcpSend(_socket, buf, size);
}

int ESP8266UDPClient::available()
{
	int available = esp8266.available();
	if (available == 0)
	{
		// Delay for the amount of time it'd take to receive one character
		delayMicroseconds((1 / esp8266._baud) * 10 * 1E6);
		// Check again just to be sure:
		available = esp8266.available();
	}
	return esp8266.available();
}

int ESP8266UDPClient::read()
{
	return esp8266.read();
}

int ESP8266UDPClient::read(uint8_t *buf, size_t size)
{
	if (esp8266.available() < size)
		return 0;
	
	for (int i=0; i<size; i++)
	{
		buf[i] = esp8266.read();
	}
	
	return 1;
}

int ESP8266UDPClient::peek()
{
	return esp8266.peek();
}

void ESP8266UDPClient::flush()
{
	esp8266.flush();
}

void ESP8266UDPClient::stop()
{
	esp8266.close(_socket);
	esp8266._state[_socket] = AVAILABLE;
}

uint8_t ESP8266UDPClient::connected()
{
	// If data is available, assume we're connected. Otherwise,
	// we'll try to send the status query, and will probably end 
	// up timing out if data is still coming in.
	if (_socket == ESP8266_SOCK_NOT_AVAIL)
		return 0;
	else if (available() > 0)
		return 1;
	else if (status() == ESP8266_STATUS_CONNECTED)
		return 1;
	
	return 0;
}

ESP8266UDPClient::operator bool()
{
	return connected();
}

// Private Methods
uint8_t ESP8266UDPClient::getFirstSocket()
{
	/*
	for (int i = 0; i < ESP8266_MAX_SOCK_NUM; i++) 
	{
		if (esp8266._state[i] == AVAILABLE)
		{
			return i;
		}
	}
	return ESP8266_SOCK_NOT_AVAIL;
	*/
	esp8266.updateStatus();
	for (int i = 0; i < ESP8266_MAX_SOCK_NUM; i++) 
	{
		if (esp8266._status.ipstatus[i].linkID == 255)
		{
			return i;
		}
	}
	return ESP8266_SOCK_NOT_AVAIL;
}
