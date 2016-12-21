/*****************************************
** Librería creada en Electrónica 5Hz                              
** www.5hz-electronica.com                                       
** 
**                                        
**                                                               
** Descripción del código:                                       
**                                                               
** Librería para utilizar con el GPS MTK3339
** compatible con nuestros productos:
** GPS Shield y GPS logger Shield                         
**                                                               
******************************************

Basado en la librería Adafruit_GPS:


/***********************************
This is the Adafruit GPS library - the ultimate GPS library
for the ultimate GPS module!

Tested and works great with the Adafruit Ultimate GPS module
using MTK33x9 chipset
    ------> http://www.adafruit.com/products/746
Pick one up today at the Adafruit electronics shop 
and help support open source hardware & software! -ada

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above must be included in any redistribution
****************************************/

#ifndef _GPS_5HZ
#define _GPS_5HZ

#if ARDUINO >= 100
 #include <SoftwareSerial.h>
#else
 #include <NewSoftSerial.h>
#endif

// diferentes comandos para fijar la taza de refresco desde una vez por segundo hasta 10 veces por segundo (1Hz-10Hz)
#define PMTK_SET_NMEA_UPDATE_1HZ  "$PMTK220,1000*1F"
#define PMTK_SET_NMEA_UPDATE_5HZ  "$PMTK220,200*2C"
#define PMTK_SET_NMEA_UPDATE_10HZ "$PMTK220,100*2F"


#define PMTK_SET_BAUD_57600 "$PMTK251,57600*2C"
#define PMTK_SET_BAUD_9600 "$PMTK251,9600*17"

// Activa solo la segunda secuencia (GPRMC)
#define PMTK_SET_NMEA_OUTPUT_RMCONLY "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
// Activa GPRMC y GGA
#define PMTK_SET_NMEA_OUTPUT_RMCGGA "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
//Activa toda la info

#define PMTK_SET_NMEA_OUTPUT_ALLDATA "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28"
// Desactiva la salida
#define PMTK_SET_NMEA_OUTPUT_OFF "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28"

//Para generar tus propias sentencias, revisa el datasheet de comandos MTK y usa la calculadora de Checksum
// como la grandiosa: http://www.hhhh.org/wiml/proj/nmeaxor.html

#define PMTK_LOCUS_STARTLOG  "$PMTK185,0*22"
#define PMTK_LOCUS_LOGSTARTED "$PMTK001,185,3*3C"
#define PMTK_LOCUS_QUERY_STATUS "$PMTK183*38"
#define PMTK_LOCUS_ERASE_FLASH "$PMTK184,1*22"
#define LOCUS_OVERLAP 0
#define LOCUS_FULLSTOP 1

// comando de standby y mensaje de arranque exitoso
#define PMTK_STANDBY "$PMTK161,0*28"
#define PMTK_STANDBY_SUCCESS "$PMTK001,161,3*3"  // Not needed currently
#define PMTK_AWAKE "$PMTK010,002*2D"

// Pregunta por la versión
#define PMTK_Q_RELEASE "$PMTK605*31"

// Solicita actualizaciones del estado de la antena
#define PGCMD_ANTENNA "$PGCMD,33,1*6C" 
#define PGCMD_NOANTENNA "$PGCMD,33,0*6C" 

// Cuanto tiempo esperar cuando estamos esperando una respuesta
#define MAXWAITSENTENCE 5

#if ARDUINO >= 100
 #include "Arduino.h"
#if !defined(__AVR_ATmega32U4__)
 #include "SoftwareSerial.h"
#endif
#else
 #include "WProgram.h"
 #include "NewSoftSerial.h"
#endif

//5HZ MODS
#define LATITUDE 0
#define LONGITUDE 1

#define MINUTES 0
#define DECIMALS 1
//fin 5HZ MODS
class GPS_5Hz {
 public:
  void begin(uint16_t baud); 

#if ARDUINO >= 100 
  GPS_5Hz(SoftwareSerial *ser); // Constructor cuando usamos SoftwareSerial
#else
  GPS_5Hz(NewSoftSerial  *ser); // Constructor cuando usamos NewSoftSerial
#endif
  GPS_5Hz(HardwareSerial *ser); // Constructor cuando usamos HardwareSerial

  char *lastNMEA(void);
  boolean newNMEAreceived();
  void common_init(void);
  void sendCommand(char *);
  void pause(boolean b);

  boolean parseNMEA(char *response);
  uint8_t parseHex(char c);

  char read(void);
  boolean parse(char *);
  void interruptReads(boolean r);

  boolean wakeup(void);
  boolean standby(void);

  uint8_t hour, minute, seconds, year, month, day;
  uint16_t milliseconds;
  float latitude, longitude; //tienen formato Latitude: DDMM.MMMM, Longitude: DDDMM.MMMM
  float geoidheight, altitude;
  float speed, angle, magvariation, HDOP;
  char lat, lon, mag;
  boolean fix;
  uint8_t fixquality, satellites;

  boolean waitForSentence(char *wait, uint8_t max = MAXWAITSENTENCE);
  boolean LOCUS_StartLogger(void);
  boolean LOCUS_ReadStatus(void);

  uint16_t LOCUS_serial, LOCUS_records;
  uint8_t LOCUS_type, LOCUS_mode, LOCUS_config, LOCUS_interval, LOCUS_distance, LOCUS_speed, LOCUS_status, LOCUS_percent;

  //5Hz Mods:
  void setNotation(boolean type); //0 (MINUTES) para grados y minutos, 1 (DECIMALS) para grados y decimales
  float getLatitude(); //latitud en el formato especificado por notationType(boolean)
  float getLongitude(); //longitud en el formato especificado por notationType(boolean)
  int getDegrees(boolean axis); //Solo Grados de la latitud/longitud actual 
  float getMinutes(boolean axis); //Solo Minutos de la latitud/longitud actual
  void printURL(); //Arma una URL para Google Maps con la ubicación actual leída por el GPS
  //fin 5Hz Mods
 private:
  boolean paused;
  
  uint8_t parseResponse(char *response);
#if ARDUINO >= 100
  SoftwareSerial *gpsSwSerial;
#else
  NewSoftSerial  *gpsSwSerial;
#endif
  HardwareSerial *gpsHwSerial;
  //5hz mods
  boolean notation;
  //fin 5Hz mods
};


#endif
