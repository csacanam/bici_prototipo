/*
  RED 3 NODOS - PROYECTO BICICLETAS
  
  CLIENT A
*/

//Dato que se envia al servidor
double mySpeed = 128;

void setup()
{
  Serial.begin(9600); //Local
  Serial1.begin(9600); //XBee
}

void loop()
{
  sendBeacon();
  delay(1000);
}


//Enviar informacion cada segundo
void sendBeacon()
{
  
  //Convertir velocidad de double a string
  char mySpeedString[12];
  
  dtostrf(mySpeed,2,5,mySpeedString);
  
  //Enviar datos por XBee
  Serial1.println(mySpeedString);
  
}

