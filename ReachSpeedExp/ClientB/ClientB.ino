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

// variables for calculate the speed

long previous, time, impulses;
float speedometer, circuit;


void setup()
{
  Serial.begin(9600); //Local
  Serial1.begin(9600); //XBee
  
    /*
  Set A0 analog port, wish is where the speed sensor
   is read. Is set has input of data. The sensor will
   send 0 to 10, when is no data and will send 1024,
   when is data or the switch is activated.
   */
  pinMode(A0, INPUT);
  
  circuit = 1,52;
}

void loop()
{
  readSpeed();
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
  
  dtostrf(speedometer,2,5,mySpeedString);
  
  //Enviar datos por XBee
  Serial1.println(String(myAddress) + ";" + mySpeedString);
  
}

void readSpeed(){
  //if wheel turns
  if(analogRead(A0)>=300){
    //number of turns++
    impulses++;

    //count turn time
    time=(millis()-previous);

    //count speed
    speedometer=(circuit / time)*3600.0;
    previous=millis();
    delay(100);
  }

  if((millis()-previous) > 2000){
    speedometer = 0;
  }


}

