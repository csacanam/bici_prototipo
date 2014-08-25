#include <Wire.h>
char myChar;
int theSpeed;
int hold; // 1 moving , 0 hold
int myDirection; // 1 ffw, 0 bckw


// Leonardo	2 (SDA), 3 (SCL)
// GP variables
int adc_key_in;
int inputPort = A0;

void setup() {
  Wire.begin();
  Serial.begin(9600); // Start serial communication at 9600 bps
  Serial1.begin(9600);
  theSpeed = 150;
  myDirection = 1;
  hold = 1;
  pinMode(13, OUTPUT);  //we'll use the debug LED to output a heartbeat
  pinMode(inputPort, INPUT);
}


void loop() {
  readGPS();
//  if (Serial.available()) { // If data is available to read,
//    myChar = Serial.read(); // read it and store it in val
//
//    // Cambian direccion
//    if(hold == 1){ // si esta corriendo
//      if(myChar == 'a'){
//        Serial.println("Direction is forward");
//        //        digitalWrite(M1,HIGH);
//        myDirection = 1;
//      }
//      if(myChar == 'b'){
//        Serial.println("Direction is back");
//        //        digitalWrite(M1,LOW);
//        myDirection = 0;  
//      }
//    }
//
//    // arranca el motor
//    if(myChar == 'c'){
//      Serial.println("is going");
//      //     digitalWrite(E1,HIGH);
//      hold = 0;
//    }
//
//    // para el motor
//    if(myChar == 'd'){
//      Serial.println("is stop");
//      hold = 1;
//    }
//
//    // Modifican la velocidad
//    if(myChar == 'e'){
//      Serial.println("speed is 0");
//      theSpeed = 25;
//    }
//    if(myChar == 'f'){
//      Serial.println("speed is 1");
//      theSpeed = 50;
//    }
//    if(myChar == 'g'){
//      Serial.println("speed is 2");
//      theSpeed = 75;
//    }
//    if(myChar == 'h'){
//      Serial.println("speed is 3");
//      theSpeed = 100;
//    }
//    if(myChar == 'i'){
//      Serial.println("speed is 4");
//      theSpeed = 125;
//    }
//    if(myChar == 'j'){
//      Serial.println("speed is 5");
//      theSpeed = 150;
//    }
//    if(myChar == 'k'){
//      Serial.println("speed is 6");
//      theSpeed = 175;
//    }
//    if(myChar == 'l'){
//      Serial.println("speed is 7");
//      theSpeed = 200;
//    }
//    if(myChar == 'm'){
//      Serial.println("speed is 8");
//      theSpeed = 225;
//    }
//    if(myChar == 'n'){
//      Serial.println("speed is 9");
//      theSpeed = 250;
//    }
//  }
//
//  sendData();


  delay(100); // Wait 100 milliseconds for next reading
}

void sendData(){
  // envia datos
  String data = String(theSpeed)+";"+String(myDirection)+";"+ String(hold)+"\n";
  char chars [data.length()+1];
  data.toCharArray(chars, data.length()+1);
  for (int i=0 ; i< sizeof(chars)-1; i++){
    Serial1.write(chars[i]);// Speed, direction, hold
    Serial.print(chars[i]);
  }
}

void readGPS() {
  adc_key_in = analogRead(inputPort);    // read the value from the sensor  
  if (adc_key_in > 0){
    digitalWrite(13, LOW);
  }
  else{
    digitalWrite(13, HIGH);
  }
  // Serial.println(adc_key_in);

  // Necesitamos saber en que direccion se conecta el GPS al bus de datos
  // Por cuales pins esta enviando y recibiendo datos SCL y SDA Confirmar si es por 2 y 3

  Wire.requestFrom(96,100);
  while(Wire.available()){
    char c = Wire.read();
    Serial.print(c);
    Serial1.write(c);
  }
  //Serial.println('_');
  //delay(2000);
}













