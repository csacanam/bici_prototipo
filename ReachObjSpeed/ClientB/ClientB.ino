/*
  RED 3 NODOS - PROYECTO BICICLETAS
  
  CLIENT B

*/

//Variables locales
double mySpeed = 120;
double objSpeed = 0;
String datos;
char floatBuffer[64];
int myAddress = 1;


void setup()
{
  Serial.begin(9600); //Local
  Serial1.begin(9600); //XBee 
}

void loop()
{
  readFromXBee();
  sendBeacon();
}

/*
Obtener la informacion del server
*/
void readFromXBee()
{

  if(Serial1.available())
  {
    char c = Serial1.read();
    
    if(c != '\n')
    {
      datos+=c;
    }
    else
    {
      
      //Convertir de String a double
      datos.toCharArray(floatBuffer, sizeof(floatBuffer));
      objSpeed= atof(floatBuffer);
      
      //Obtener diferencia entre la velocidad actual y la velocidad objetivo
      double difference = objSpeed - mySpeed;
      char differenceString[12];
      dtostrf(difference,2,5,differenceString);
            
      //Imprimir en consola
      Serial.println(differenceString);
      
    }
  }
}

//Enviar informacion cada segundo
void sendBeacon()
{
  
  //Convertir velocidad de double a string
  char mySpeedString[12];
  
  dtostrf(mySpeed,2,5,mySpeedString);
  
  //Enviar datos por XBee
  Serial1.println(String(myAddress) + ";" + mySpeedString);
  
}
