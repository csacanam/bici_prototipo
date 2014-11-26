/*
PROTOTIPO PROYECTO BICICLETAS

NODO LIDER

*/

//Libreria para crear puerto Serial virtual
#include <SoftwareSerial.h>


//Variales locales
int myAddress = 0;
double myAcc = 128;
int contador = 0;


void setup() 
{
  Serial.begin(9600); // Local
  Serial1.begin(9600); //XBee
}



void loop() 
{
  sendBeacon();
  delay(1000);
}

void sendBeacon()
{
    //Contador de paquetes
    contador++;
    
    //Convertir aceleracion de double a String
    char myAccString[12];
    
    dtostrf(myAcc,2,5,myAccString);
    
    //Enviar datos por XBee
    Serial1.println(String(myAddress) + ";" + String(myAccString));
    
    //Mostrar datos en consola
    Serial.print(myAddress);
    Serial.print(";");
    Serial.print(myAcc);
    Serial.print(";");
    Serial.print(contador);
    Serial.println();
}











