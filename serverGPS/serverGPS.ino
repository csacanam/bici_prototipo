//Libreria para crear puerto Serial virtual
#include <SoftwareSerial.h>
//Libreria para obtener los datos de la cadena NMEA
#include <TinyGPS++.h>

// Serial port to GPS
SoftwareSerial serialGPS(8, 9); // RX, TX

TinyGPSPlus gps;


void setup() 
{
  Serial.begin(4800); // Empezar comunicacion serial a 4800 (USB)
  serialGPS.begin(4800); //Empezar comunicacion serial a 4800 (Comunicacion con GPS)
  initVariables(); //Iniciar variables  
}



void loop() 
{
  //Leer ubicacion desde el GPS
  readFromGPS();
}


/*
Se inicializan los valores de las variables
*/
void initVariables()
{

}


/*
Obtener datos del GPS y enviarlos en modo broadcast
*/
void readFromGPS() 
{
  while(serialGPS.available())
  {
    gps.encode(serialGPS.read());
  }
  
  if(gps.location.isUpdated() && gps.speed.isUpdated())
  {
    Serial.print("LAT="); Serial.println(gps.location.lat());
    Serial.print("LONG="); Serial.println(gps.location.lng());
    //Serial.print("SPEED="); Serial.println(gps.speed.kmph());
    Serial.println("___________________________________");
  }

}

















