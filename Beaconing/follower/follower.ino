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

//Local variables
double myLat; //Mi latitud
double myLng; //Mi longitud
String datos;
int myAddress = 1  ; //Direccion del nodo
int contadorDirecto = 0;
int contadorMultisalto = 0;
double accData [2];
int contadorLider = 0;

void setup()  
{
  Serial.begin(9600); //Local
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
   //readFromGPS();
  
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
    Serial.print(myLat);
    Serial.print(myLng);
    Serial.println();
    
    sendBeacon();
  }

}


/*
Obtener los datos de otros nodos desde XBee
*/
void readFromXBee()
{
  
  double vecinoAddress = 0;
  
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
         
        //Crear arreglo donde estaran los datos
        char datosArray[50];
        datos.toCharArray(datosArray,50);
        
        //Limpiar cadena
        datos = ""; 
        
      //1. Obtener datos del otro nodo
        int index = 0; //Indice del parametro (0-Lat, 1-Lng)
        char *parametro = strtok(datosArray, ";"); //Dividir cuando encuentre un ;
        
        int posData = -1;
        
        while(parametro != 0)
        {
          
          if (index == 0)
          {
            vecinoAddress = atof(parametro);
            if(vecinoAddress == 0)
            {
              posData = 0;
              contadorLider = 0;
              contadorDirecto++;
            }
            else
            {
             posData = 1; 
             contadorMultisalto++;
            }
          }
          else if (index == 1)
          {
            double tempLeaderAcc = 0;
            
            tempLeaderAcc = atof(parametro);
            
            if(tempLeaderAcc != 0 && posData != -1)
            {
              accData[posData] = tempLeaderAcc;              
            }
            
          }


          parametro = strtok(0,";");
          index++; 
        }
        
        Serial.print("Address: ");
        Serial.print(vecinoAddress);
        Serial.print("; Acc 0: ");
        Serial.print(accData[0]);
        Serial.print("; Acc 1: ");
        Serial.print(accData[1]);
        Serial.print(";Directo: ");
        Serial.print(contadorDirecto);
        Serial.print(";Multisalto;");
        Serial.print(contadorMultisalto);
        Serial.println();
        Serial.println("-------------------------------");
        Serial.print('\n');   
        
         // delay(800);
             
         sendBeacon();
        


        
       }

  }


  

}

void sendBeacon()
{
    char leaderAccString[12];

    if(contadorLider >= 20)
    {
          dtostrf(accData[1], 2, 5, leaderAccString);
    }
    else
    {  
          dtostrf(accData[0], 2, 5, leaderAccString);
    }
   
    Serial1.println(String(myAddress)+";"+String(leaderAccString));


}
  



