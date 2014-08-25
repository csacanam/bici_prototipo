
void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial1.begin(9600);
  

  Serial.println("Goodnight moon!");


}

void loop() // run over and over
{
  if (Serial1.available())
  {
        Serial.println(Serial1.read());
  }
  else
  {
        Serial.println("no data");
  }
}
