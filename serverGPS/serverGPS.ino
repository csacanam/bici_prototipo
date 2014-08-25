//Importar libreria para usar el protocolo serial I2C
#include <Wire.h>

// GPS variables
int gps_data_in;
int inputPort = A0;

void setup() 
{
  Wire.begin();  //Iniciar protocolo serial I2C para usar el GPS
  Serial.begin(9600); // Empezar comunicacion serial a 9600 (USB)
  Serial1.begin(9600); //Empezar comunicacion serial a 9600 (Comunicacion con XBee)
  initVariables(); //Iniciar variables
  pinMode(inputPort, INPUT); //Configurar pines
}


void loop() 
{
  //Leer ubicacion desde el GPS
  readFromGPS();
  delay(100); // Wait 100 milliseconds for next reading
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
  gps_data_in = analogRead(inputPort);    // Leer dato desde el sensor  

  // Direccion en la cual se conecta el GPS al bus de datos

  Wire.requestFrom(96,100);
  while(Wire.available())
  {
   //Leer dato
    char c = Wire.read();
    //Enviar dato a la XBee
    Serial1.write(c);
  }

}















