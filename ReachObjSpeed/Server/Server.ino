/*
  RED 3 NODOS - PROYECTO BICICLETAS
  
  SERVER
*/

//Velocidad objetivo que se recibe del cliente A
double objSpeed = 0;
String datos;
char floatBuffer[64];


void setup()
{
  Serial.begin(9600); //Local
  Serial1.begin(9600); //XBee
}

void loop()
{
  readFromXBee();
}


/*
Obtener la informacion Client A
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
      
      //Enviar por XBee
      Serial1.println(objSpeed);
            
      //Imprimir en consola
      Serial.println(objSpeed);
      
    }
    
  }
  
}

