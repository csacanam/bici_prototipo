/*
PROTOTIPO PROYECTO BICICLETAS

NODO LIDER

*/

//Libreria para crear puerto Serial virtual
#include <SoftwareSerial.h>
//Libreria para obtener los datos de la cadena NMEA
#include <TinyGPS++.h>

// Serial port to GPS
SoftwareSerial serialGPS(8, 9); // RX, TX

TinyGPSPlus gps;


void setup() 
{
  Serial.begin(4800); // Local
  Serial1.begin(9600); //XBee
  serialGPS.begin(4800); //GPS
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
  
  if(gps.location.isUpdated())
  {
    char latString[10];
    char lngString[10];
    
    //Convertir datos de double a char[]
    dtostrf(gps.location.lat(),2,2,latString);
    dtostrf(gps.location.lng(),2,2,lngString);

    //Se adjunta toda la informacion que se va a enviar
    String info = String(latString)+";"+String(lngString);
    
    //Enviar datos por XBee
    Serial1.println(info);
  }

}

















