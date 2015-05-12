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
long myLat; //Mi latitud
long myLng; //Mi longitud
int myAddress;
String datos;
double myAcc;

//Datos del lider
double accLeader;


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
  //Asignar direccion al nodo *************
  myAddress = 1;
  
  //Iniciar otras variables en cero
  myLat = 0;
  myLng = 0;
  myAcc = 6;
  
  //Datos del lider
  accLeader = 0;

  
}



void loop() 
{
  //Obtener mi ubicacion desde el GPS
   readFromGPS();
  
  //Obtener datos de los otros nodos desde XBee
  readFromXBee();
  
  //Enviar beacon
  sendBeacon();
  
  
}

/*
Obtener datos del GPS y guardarlos localmente
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
        double vecinoAccLeader=0;
        double vecinoAddress = 0;
        
         
        //Crear arreglo donde estaran los datos
        char datosArray[50];
        datos.toCharArray(datosArray,50);
        
        //Limpiar cadena
        datos = ""; 
        
      //1. Obtener datos del otro nodo
        int index = 0; //Indice del parametro (0-Lat, 1-Lng, 2-AccLeader, 3-Address)
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
          else if (index == 2)
          {
            //Verificar que la aceleracion del lider no es vacia y que no es el nodo lider
            vecinoAccLeader = atof(parametro);
            if(vecinoAccLeader != 0 && myAddress != 0)
             {
                accLeader = vecinoAccLeader;
             } 
          }
          else if (index == 3)
          {
            vecinoAddress = atoi(parametro);
          }  

            parametro = strtok(0,";");
            index++; 
          

        }
        
      //2. Calcular distancia entre el otro nodo y este 
        if(vecinoLat!=0 && vecinoLng!=0 && myLat!=0 && myLng!=0)
        {
          double distanceKm = TinyGPSPlus::distanceBetween(myLat,myLng,vecinoLat,vecinoLng)/1000.0;
          
          Serial.print("Me: ");
          Serial.print("Address: ");
          Serial.print(myAddress);
          Serial.print(";");
          Serial.print(myLat);
          Serial.print(";");
          Serial.print(myLng);
          Serial.print(";");
          Serial.print ("Acc Leader: ");
          Serial.print(accLeader);
          Serial.print(";");
          Serial.print("My Acc: ");
          Serial.print(myAcc);
          Serial.println();
          
          Serial.print("Vecino: ");
          Serial.print("Address:");
          Serial.print(vecinoAddress);
          Serial.print(";");
          Serial.print(vecinoLat);
          Serial.print(";");
          Serial.print(vecinoLng);
          Serial.print(";");
          Serial.print("Acc Leader: ");
          Serial.print(vecinoAccLeader);
          Serial.println();
          Serial.print("Distance in Km: ");
          Serial.print(distanceKm);

          Serial.println();
          Serial.println("-------------------------------");
        }
       }
  }
  

}

void sendBeacon()
{
    char latString[10];
    char lngString[10];
    char accLeaderString[10];
    char myAccString[10];

    
    //Convertir datos de double a char[]
    dtostrf(myLat,3,8,latString);
    dtostrf(myLng,3,8,lngString);
    dtostrf(accLeader,1,0,accLeaderString);
    dtostrf(myAcc,3,8,myAccString);

    String info;

    //Se adjunta toda la informacion que se va a enviar
    if(myAddress != 0)
    {
       info = String(latString)+";"+String(lngString)+";"+String(accLeaderString) + ";" + myAddress;

    }
    else
    {
      info = String(latString)+";"+String(lngString)+";"+String(myAccString) + ";" +  myAddress;

    }
    
    //Enviar datos por XBee
    Serial1.println(info);
    //Serial.println(info);
}

void printData()
{
  Serial1.println("5;6;7;8");
}









