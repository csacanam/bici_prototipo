/*
PROTOTIPO PROYECTO BICICLETAS

NODO LIDER

*/

//Libreria para crear puerto Serial virtual
#include <SoftwareSerial.h>
//Libreria para obtener los datos de la cadena NMEA
#include <TinyGPS++.h>

// Serial port to GPS
SoftwareSerial serialGPS(8, 9); // RX, TX

TinyGPSPlus gps;

/////////////// Velocity parameters

#define reed A0 //Pin connected to read switch

int reedVal;
long timer;// Time between one full rotation (in ms)
float mph;
float radius = 13.5;// Tire radius (in inches)
float circumference;

int maxReedCounter = 100;//Min time (in ms) of one rotation (for debouncing)
int reedCounter;
////////////


void setup() 
{
  Serial.begin(4800); // Local
  Serial1.begin(9600); //XBee
  serialGPS.begin(4800); //GPS
  initVariables(); //Iniciar variables 
  setupSpeed(); 
}



void loop() 
{
  //Leer ubicacion desde el GPS
  readFromGPS();
}


/*
Se inicializan los valores de las variables
*/
void initVariables()
{

}

void setupSpeed()
{
   /////////////// velocity code
  reedCounter = maxReedCounter;
  circumference = 2*PI*radius;
  pinMode(reed, INPUT);

  // TIMER SETUP- the timer interrupt allows precise timed measurements of the reed switch
  //for more info about configuration of arduino timers see http://arduino.cc/playground/Code/Timer1
  cli();//stop interrupts

  //set timer1 interrupt at 1kHz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;
  // set timer count for 1khz increments
  OCR1A = 1999;// = (1/1000) / ((1/(16*10^6))*8) - 1
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);   
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupt 
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
    char latString[10];
    char lngString[10];
    char speedString[10];
    
    //Convertir datos de double a char[]
    dtostrf(gps.location.lat(),3,8,latString);
    dtostrf(gps.location.lng(),3,8,lngString);
    dtostrf(mph,3,8,speedString);

    //Se adjunta toda la informacion que se va a enviar
    String info = String(latString)+";"+String(lngString)+";"+String(speedString);
    
    //Enviar datos por XBee
    Serial1.println(info);
    Serial.println(info);
  }

}

ISR(TIMER1_COMPA_vect) {//Interrupt at freq of 1kHz to measure reed switch
  reedVal = digitalRead(reed);//get val of A0
  if (reedVal){//if reed switch is closed
    if (reedCounter == 0){//min time between pulses has passed
      mph = (56.8*float(circumference))/float(timer);//calculate miles per hour
      timer = 0;//reset timer
      reedCounter = maxReedCounter;//reset reedCounter
    }
    else{
      if (reedCounter > 0){//don't let reedCounter go negative
        reedCounter -= 1;//decrement reedCounter
      }
    }
  }
  else{//if reed switch is open
    if (reedCounter > 0){//don't let reedCounter go negative
      reedCounter -= 1;//decrement reedCounter
    }
  }
  if (timer > 2000){
    mph = 0;//if no new pulses from reed switch- tire is still, set mph to 0
  }
  else{
    timer += 1;//increment timer
  } 
}

















