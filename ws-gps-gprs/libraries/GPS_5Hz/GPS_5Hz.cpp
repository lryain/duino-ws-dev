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
This is our GPS library

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.
BSD license, check license.txt for more information
All text above must be included in any redistribution
****************************************/

#include <GPS_5Hz.h>

// tamaño máximo de los comandos NMEA a analizar
#define MAXLINELENGTH 120

// Se usa un buffer dobleÑ lee una linea y deja una para el programa principal
volatile char line1[MAXLINELENGTH];
volatile char line2[MAXLINELENGTH];
// nuestro indice para llenar la linea actual
volatile uint8_t lineidx=0;
// Apuntadores a los buffers dobles
volatile char *currentline;
volatile char *lastline;
volatile boolean recvdflag;
volatile boolean inStandbyMode;


boolean GPS_5Hz::parse(char *nmea) {
  // hace el checksum

  // revisa si tenemos algun comando
  if (nmea[strlen(nmea)-4] == '*') {
    uint16_t sum = parseHex(nmea[strlen(nmea)-3]) * 16;
    sum += parseHex(nmea[strlen(nmea)-2]);
    
    // checa la checksum 
    for (uint8_t i=1; i < (strlen(nmea)-4); i++) {
      sum ^= nmea[i];
    }
    if (sum != 0) {
      // checksum mala :(
      //return false;  //regresa false
    }
  }

  // busca unas cuantas sentencias comunes
  if (strstr(nmea, "$GPGGA")) {
    // found GGA
    char *p = nmea;
    // get time
    p = strchr(p, ',')+1;
    float timef = atof(p);
    uint32_t time = timef;
    hour = time / 10000;
    minute = (time % 10000) / 100;
    seconds = (time % 100);

    milliseconds = fmod(timef, 1.0) * 1000;

    // analiza la latitud
    p = strchr(p, ',')+1;
    latitude = atof(p);

    p = strchr(p, ',')+1;
    if (p[0] == 'N') lat = 'N';
    else if (p[0] == 'S') lat = 'S';
    else if (p[0] == ',') lat = 0;
    else return false;

    // analiza la longitud
    p = strchr(p, ',')+1;
    longitude = atof(p);

    p = strchr(p, ',')+1;
    if (p[0] == 'W') lon = 'W';
    else if (p[0] == 'E') lon = 'E';
    else if (p[0] == ',') lon = 0;
    else return false;

    p = strchr(p, ',')+1;
    fixquality = atoi(p);

    p = strchr(p, ',')+1;
    satellites = atoi(p);

    p = strchr(p, ',')+1;
    HDOP = atof(p);

    p = strchr(p, ',')+1;
    altitude = atof(p);
    p = strchr(p, ',')+1;
    p = strchr(p, ',')+1;
    geoidheight = atof(p);
    return true;
  }
  if (strstr(nmea, "$GPRMC")) {
   // encontró RMC
    char *p = nmea;

    // obtiene la hora
    p = strchr(p, ',')+1;
    float timef = atof(p);
    uint32_t time = timef;
    hour = time / 10000;
    minute = (time % 10000) / 100;
    seconds = (time % 100);

    milliseconds = fmod(timef, 1.0) * 1000;

    p = strchr(p, ',')+1;
    // Serial.println(p);
    if (p[0] == 'A') 
      fix = true;
    else if (p[0] == 'V')
      fix = false;
    else
      return false;

    // analiza la latitud
    p = strchr(p, ',')+1;
    latitude = atof(p);

    p = strchr(p, ',')+1;
    if (p[0] == 'N') lat = 'N';
    else if (p[0] == 'S') lat = 'S';
    else if (p[0] == ',') lat = 0;
    else return false;

    // analiza la longitud
    p = strchr(p, ',')+1;
    longitude = atof(p);

    p = strchr(p, ',')+1;
    if (p[0] == 'W') lon = 'W';
    else if (p[0] == 'E') lon = 'E';
    else if (p[0] == ',') lon = 0;
    else return false;

    // velocidad
    p = strchr(p, ',')+1;
    speed = atof(p);

    // ángulo
    p = strchr(p, ',')+1;
    angle = atof(p);

    p = strchr(p, ',')+1;
    uint32_t fulldate = atof(p);
    day = fulldate / 10000;
    month = (fulldate % 10000) / 100;
    year = (fulldate % 100);

    // no analizamos el resto, aún!
    return true;
  }

  return false;
}

char GPS_5Hz::read(void) {
  char c = 0;
  
  if (paused) return c;

  if(gpsSwSerial) {
    if(!gpsSwSerial->available()) return c;
    c = gpsSwSerial->read();
  } else {
    if(!gpsHwSerial->available()) return c;
    c = gpsHwSerial->read();
  }

  //Serial.print(c);

  if (c == '$') {
    currentline[lineidx] = 0;
    lineidx = 0;
  }
  if (c == '\n') {
    currentline[lineidx] = 0;

    if (currentline == line1) {
      currentline = line2;
      lastline = line1;
    } else {
      currentline = line1;
      lastline = line2;
    }

    //Serial.println("----");
    //Serial.println((char *)lastline);
    //Serial.println("----");
    lineidx = 0;
    recvdflag = true;
  }

  currentline[lineidx++] = c;
  if (lineidx >= MAXLINELENGTH)
    lineidx = MAXLINELENGTH-1;

  return c;
}

// COnstructor cuando se usa SoftwareSerial o NewSoftSerial
#if ARDUINO >= 100
GPS_5Hz::GPS_5Hz(SoftwareSerial *ser)
#else
GPS_5Hz::GPS_5Hz(NewSoftSerial *ser) 
#endif
{
  common_init();     // inicializa todo comunmente, y luego...
  gpsSwSerial = ser; // ...se modifica gpsSwSerial con el valor pasado.
}

// Constructor cuando se usa HardwareSerial
GPS_5Hz::GPS_5Hz(HardwareSerial *ser) {
  common_init();  // inicializa todo comunmente, y luego...
  gpsHwSerial = ser; // ...se modifica gpsHwSerial con el valor pasado.
}

// Inicialización usada por todos los tipos de constructores
void GPS_5Hz::common_init(void) {
  gpsSwSerial = NULL; // Pone ambos en NULL y luego corrige el correcto
  gpsHwSerial = NULL; // puntero al puerto en el correspondiente constructor
  recvdflag   = false;
  paused      = false;
  lineidx     = 0;
  currentline = line1;
  lastline    = line2;

  hour = minute = seconds = year = month = day =
    fixquality = satellites = 0; // uint8_t
  lat = lon = mag = 0; // char
  fix = false; // boolean
  milliseconds = 0; // uint16_t
  latitude = longitude = geoidheight = altitude =
    speed = angle = magvariation = HDOP = 0.0; // float
}

void GPS_5Hz::begin(uint16_t baud)
{
  if(gpsSwSerial)
  {
	 gpsSwSerial->begin(115200);
	 gpsSwSerial->println("$PMTK220,1000*1F");
     gpsSwSerial->println("$PMTK251,9600*17");
	 gpsSwSerial->begin(baud);
  }
  else
  {
	 gpsHwSerial->begin(115200);
	 gpsHwSerial->println("$PMTK220,1000*1F");
     gpsHwSerial->println("$PMTK251,9600*17");
	 gpsHwSerial->begin(baud);
  }

  delay(10);
}

void GPS_5Hz::sendCommand(char *str) {
  if(gpsSwSerial) gpsSwSerial->println(str);
  else            gpsHwSerial->println(str);
}

boolean GPS_5Hz::newNMEAreceived(void) {
  return recvdflag;
}

void GPS_5Hz::pause(boolean p) {
  paused = p;
}

char *GPS_5Hz::lastNMEA(void) {
  recvdflag = false;
  return (char *)lastline;
}

// lee el valor hexadecimal y regresa el equivalente decimal
uint8_t GPS_5Hz::parseHex(char c) {
    if (c < '0')
      return 0;
    if (c <= '9')
      return c - '0';
    if (c < 'A')
       return 0;
    if (c <= 'F')
       return (c - 'A')+10;
}

boolean GPS_5Hz::waitForSentence(char *wait4me, uint8_t max) {
  char str[20];

  uint8_t i=0;
  while (i < max) {
    if (newNMEAreceived()) { 
      char *nmea = lastNMEA();
      strncpy(str, nmea, 20);
      str[19] = 0;
      i++;

      if (strstr(str, wait4me))
	return true;
    }
  }

  return false;
}

boolean GPS_5Hz::LOCUS_StartLogger(void) {
  sendCommand(PMTK_LOCUS_STARTLOG);
  recvdflag = false;
  return waitForSentence(PMTK_LOCUS_LOGSTARTED);
}

boolean GPS_5Hz::LOCUS_ReadStatus(void) {
  sendCommand(PMTK_LOCUS_QUERY_STATUS);
  
  if (! waitForSentence("$PMTKLOG"))
    return false;

  char *response = lastNMEA();
  uint16_t parsed[10];
  uint8_t i;
  
  for (i=0; i<10; i++) parsed[i] = -1;
  
  response = strchr(response, ',');
  for (i=0; i<10; i++) {
    if (!response || (response[0] == 0) || (response[0] == '*')) 
      break;
    response++;
    parsed[i]=0;
    while ((response[0] != ',') && 
	   (response[0] != '*') && (response[0] != 0)) {
      parsed[i] *= 10;
      char c = response[0];
      if (isDigit(c))
        parsed[i] += c - '0';
      else
        parsed[i] = c;
      response++;
    }
  }
  LOCUS_serial = parsed[0];
  LOCUS_type = parsed[1];
  if (isAlpha(parsed[2])) {
    parsed[2] = parsed[2] - 'a' + 10; 
  }
  LOCUS_mode = parsed[2];
  LOCUS_config = parsed[3];
  LOCUS_interval = parsed[4];
  LOCUS_distance = parsed[5];
  LOCUS_speed = parsed[6];
  LOCUS_status = !parsed[7];
  LOCUS_records = parsed[8];
  LOCUS_percent = parsed[9];

  return true;
}

// Switches de modo standBy
boolean GPS_5Hz::standby(void) {
  if (inStandbyMode) {
    return false;  // Regresa falso si ya se encontraba en modo standBy, para no despertar al GPS al enviarle comandos
  }
  else {
    inStandbyMode = true;
    sendCommand(PMTK_STANDBY);
    //return waitForSentence(PMTK_STANDBY_SUCCESS);  // No parece ser suficientemente rapido para leer el mensaje, o algo mas simplemente no esta funcionando
    return true;
  }
}

boolean GPS_5Hz::wakeup(void) {
  if (inStandbyMode) {
   inStandbyMode = false;
    sendCommand("");  // envía un byte para despertarlo
    return waitForSentence(PMTK_AWAKE);
  }
  else {
      return false;  // Regresa falso si no esta en modo standBy, no hay nada que despertar
  }
}

//5HZ Mods
//0 (MINUTES) para grados y minutos, 1 (DECIMALS) para grados y decimales
void GPS_5Hz::setNotation(boolean type) 
{
	notation = type;
}

//latitud en el formato especificado por notationType(boolean)
float GPS_5Hz::getLatitude()
{
	float latitud = 0;
	if(notation == MINUTES) latitud = latitude;
	else if(notation == DECIMALS) latitud = float(getDegrees(LATITUDE))*100 + getMinutes(LATITUDE)*100/60;
	return latitud;
}

//longitud en el formato especificado por notationType(boolean)
float GPS_5Hz::getLongitude()
{
	float longitud = 0.0;
	if(notation == MINUTES) longitud = longitude;
	else if(notation == DECIMALS) longitud = float(getDegrees(LONGITUDE))*100 + getMinutes(LONGITUDE)*100/60;
	return longitud;
}

//Solo Grados de la latitud/longitud actual 
int GPS_5Hz::getDegrees(boolean axis)
{
	int deg = 0;
	if(axis == LATITUDE) deg = int(latitude) / 100;
	else if(axis == LONGITUDE) deg = int(longitude) / 100;
	return deg;
}

//Solo Minutos de la latitud/longitud actual
float GPS_5Hz::getMinutes(boolean axis)
{
	float min = 0.0;
	if(axis == LATITUDE) min = latitude - getDegrees(LATITUDE) * 100;
	else if(axis == LONGITUDE) min = longitude - getDegrees(LONGITUDE) * 100;
	return min;
}

//Arma una URL para Google Maps con la ubicación actual leída por el GPS (CREDITO POR DESCIFRAR EL URL DE DANIEL ROJAS :D)
void GPS_5Hz::printURL()
{
    Serial.print("https://www.google.com/maps/preview#!q=");
    Serial.print(getDegrees(LATITUDE));
    Serial.print("%C2%B0+");
    Serial.print(getMinutes(LATITUDE), 4);
    Serial.print("'%2C+-");
    Serial.print(getDegrees(LONGITUDE));
    Serial.print("%C2%B0+");
    Serial.print(getMinutes(LONGITUDE), 4);
    Serial.println("'");
}

//fin 5Hz Mods
