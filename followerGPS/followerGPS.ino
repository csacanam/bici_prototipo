/*
PROTOTIPO PROYECTO BICICLETAS

NODO SEGUIDOR

*/


//Libreria para crear puerto Serial virtual
#include <SoftwareSerial.h>
//Libreria para obtener los datos de la cadena NMEA
#include <TinyGPS++.h>

// Serial port para el GPS
SoftwareSerial serialGPS(8, 9); // RX, TX

TinyGPSPlus gps;

//Constantes
const float pi = 3.14;
const double earthRadius = 6371.009;

//Local variables
double myLat; //Mi latitud
double myLng; //Mi longitud
String datos;

void setup()  
{
  Serial.begin(4800); //Local
  serialGPS.begin(4800); //GPS
  Serial1.begin(9600); //XBee
  initVariables();
}

/*
Se inician las variables
*/
void initVariables()
{
  myLat = 0;
  myLng = 0;
}

void loop() 
{
  //Obtener mi ubicacion desde el GPS
   readFromGPS();
  
  //Obtener datos de los otros nodos desde XBee
  readFromXBee();
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
  }

}


/*
Obtener los datos de otros nodos desde XBee
*/
void readFromXBee()
{
  //Obtener informacion de otro nodo
  if (Serial1.available())
  {
       char c = Serial1.read();
       
       //Almacenar el caracter en la cadena mientras no sea un fin de linea
       if(c!='\n')
       {
         datos += c;
       }
       //Si encuentra el fin de linea se obtienen los parametros de la cadena
       else
       {
        //Datos otro nodo
        double vecinoLat=0;
        double vecinoLng=0;
         
        //Crear arreglo donde estaran los datos
        char datosArray[50];
        datos.toCharArray(datosArray,50);
        
        //Limpiar cadena
        datos = ""; 
        
      //1. Obtener datos del otro nodo
        int index = 0; //Indice del parametro (0-Lat, 1-Lng)
        char *parametro = strtok(datosArray, ";"); //Dividir cuando encuentre un ;
        while(parametro != 0)
        {
          if(index==0)
          {
           vecinoLat = atof(parametro); 
          }
          else if (index == 1)
          {
           vecinoLng = atof(parametro); 
          }

          parametro = strtok(0,";");
          index++; 
        }
        
      //2. Calcular distancia entre el otro nodo y este 
        if(vecinoLat!=0 && vecinoLng!=0 && myLat!=0 && myLng!=0)
        {
          double distanceKm = TinyGPSPlus::distanceBetween(myLat,myLng,vecinoLat,vecinoLng)/1000.0;
          Serial.print("Me: ");
          Serial.print(myLat);
          Serial.print(";");
          Serial.print(myLng);
          Serial.println();
          Serial.print("Vecino: ");
          Serial.print(vecinoLat);
          Serial.print(";");
          Serial.print(vecinoLng);
          Serial.println();
          Serial.print("Distance in Km: ");
          Serial.print(distanceKm);
          Serial.println();
          Serial.println("-------------------------------");
        }
       }
  }
  

}



