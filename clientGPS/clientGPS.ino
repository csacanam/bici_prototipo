//Importar libreria para usar el protocolo serial I2C
#include <Wire.h>

//Constantes
const float pi = 3.14;
const double earthRadius = 6371.009;

// GPS variables
int gps_data_in;
int inputPort = A0;

//Local variables
double myLat; //My latitude
double myLong; //My longitude

void setup()  
{
  Wire.begin();  //Iniciar protocolo serial I2C para usar el GPS
  Serial.begin(9600); //Local
  Serial1.begin(9600); //Puerto serial para la comunicacion con XBee
  pinMode(inputPort, INPUT); //Configurar pines

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
  gps_data_in = analogRead(inputPort);    // Leer dato desde el sensor  

  Wire.requestFrom(96,100); // Direccion en la cual se conecta el GPS al bus de datos
  
  while(Wire.available())
  {
   //1. Leer datos del GPS
    char c = Wire.read();
   //2. Guardar mi ubicacion
    myLat = 0;
    myLong = 0;
    //3. Enviar datos a los otros nodos - XBee
    Serial.write(c);
    Serial1.write(c);
  }

}


/*
Obtener los datos de otros nodos desde XBee
*/
void readFromXBee()
{
  //Obtener informacion de otro nodo
  while (Serial1.available())
  {
      //1. Obtener ubicacion de otro nodo
      Serial.write(Serial1.read());
      
      //2. Calcular distancia entre el otro nodo y este nodo
      //double distanceBetweenNodes = distanceBetweenGeoPoints(lat1,long1,lat2,long2);
      
  }
}


/*
Calcular distancia entre dos puntos geograficos usando la Flat-surface formula (Spherical Earth projected to a plane)
*/
double distanceBetweenGeoPoints(double lat1, double long1, double lat2, double long2)
{  
  //Convertir de grados a radianes
  double latRad1 = lat1 * (pi/180);
  double longRad1 = long1 * (pi/180);
  double latRad2 = lat2 * (pi/180);
  double longRad2 = long2 * (pi/180);
  
  //Obtener datos
  double deltaLat = latRad2 - latRad1; //phi
  double deltaLong = longRad2 - longRad1; //lambda
  double meanLat = (latRad1 + latRad2)/2;
  
  //Calcular distancia
  double d = earthRadius * sqrt(pow(deltaLat,2) + pow(deltaLong*cos(meanLat),2));
  return d;
}

