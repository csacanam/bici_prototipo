/*
  RED 3 NODOS - PROYECTO BICICLETAS
 
 CLIENT A
 */

//Dato que se envia al servidor
double mySpeed = 128;
int myAddress = 0;


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
  /*
Circuit is calculated in meters (diameter in inches * 2,54(1 inch in cm)  * pi(3,14))
   this result is en cm, because we want the result in meters, we need to divide the result by 100,
   and we get the 1,52.
   */
}

void loop()
{
  readSpeed();
  sendBeacon();
  //delay(1000);
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


