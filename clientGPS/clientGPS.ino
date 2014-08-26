
void setup()  
{
  Serial.begin(9600); //Local
  Serial1.begin(9600); //Puerto serial para la comunicacion con XBee
}

void loop() 
{
  while (Serial1.available())
  {
        Serial.write(Serial1.read());
  }

}
