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

//Variales locales

double myLat;
double myLng;
int myAddress = 0;
double myAcc = 128;
int contador = 0;


void setup() 
{
  Serial.begin(9600); // Local
  Serial1.begin(9600); //XBee
  serialGPS.begin(4800); //GPS
  initVariables(); //Iniciar variables 
}



void loop() 
{
  //Leer ubicacion desde el GPS
  //readFromGPS();
  sendBeacon();
  delay(1000);
}


/*
Se inicializan los valores de las variables
*/
void initVariables()
{
myLat = 0;
myLng = 0;
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
    myLat = gps.location.lat();
    myLng = gps.location.lng();

    
    sendBeacon();
    
    /*char latString[10];
    char lngString[10];
    
    //Convertir datos de double a char[]
    dtostrf(gps.location.lat(),3,8,latString);
    dtostrf(gps.location.lng(),3,8,lngString);

    //Se adjunta toda la informacion que se va a enviar
    String info = String(latString)+";"+String(lngString);
    
    //Enviar datos por XBee
    Serial1.println(info);
    Serial.println(info);*/
  }

}


void sendBeacon()
{
  //if(myLat != 0 && myLng != 0)
  //{
    /*Serial1.print(myLat);
    Serial1.print(";");
    Serial1.print(myLng);
    Serial1.println();*/
    
   // char latString[12];
    //char lngString[12];
    
    //Convertir datos de double a char[]
   // dtostrf(myLat,2,7,latString);
    //dtostrf(myLng,2,7,lngString);

    
    //Enviar datos por XBee
    /*Serial1.print(latString);
    Serial1.print(";");
    Serial1.print(lngString);
    Serial1.print(";");*/
    
    contador++;
    
    char myAccString[12];
    
    dtostrf(myAcc,2,5,myAccString);
    
    
    Serial1.println(String(myAddress) + ";" + String(myAccString) + "\n");
    
    Serial.print(myAddress);
    Serial.print(";");
    Serial.print(myAcc);
    Serial.print(";");
    Serial.print(contador);
    Serial.println();
  //}
}











