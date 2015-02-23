/*
  RED 3 NODOS - PROYECTO BICICLETAS
 
 SERVER
 */

//Velocidad objetivo que se recibe del cliente A
double objSpeed = 0;
String datos;
char floatBuffer[64];
float velocidadA, velocidadB;
double vecinoAddress;
int  posData= -1;
double speedData [2];



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
    
    
    //Serial.print(c);

    if(c != '\n')
    {
      datos+=c;
      // guardamos lo que llega por c en la cadena 'datos' hasta encontrar  un salto de linea
      //para seguir
    }
    else
    { 
     
      //Crear arreglo donde estaran los datos
      char datosArray[50];

      //Convertir de String a double (correccion, de String a char array)
     // datos.toCharArray(floatBuffer, sizeof(floatBuffer)); (????)
     datos.toCharArray(datosArray, sizeof(datosArray));
     
     Serial.println(datos);

      //Limpiar cadena
      datos = ""; 

      int index = 0; //Indice del parametro (0-Address, 1-Leader Acceleration)
      char *parametro = strtok(datosArray, ";"); //Dividir cuando encuentre un ;

      posData = -1;

      // Para partir datos en partes

      while(parametro != 0)
      {
        if (index == 0)
        {
          // verificamos el tag del nodo y lo guardamos en posData
          posData = atoi(parametro);
        }
        else if (index == 1)
        {
          double tempSpeed = 0;
          tempSpeed = atof(parametro);
          if(tempSpeed != 0 && posData != -1)
          {
            // speedData[velocidad noda A, velocidad nodo B]
            speedData[posData] = tempSpeed;              
          }
        }
        parametro = strtok(0,";");
        index++; 
      }


      //Imprimir por consola
      Serial.print("Address: ");
      Serial.print(posData);
      Serial.print("; Speed A: ");
      Serial.print(speedData[0]);
      Serial.print("; Speed B: ");
      Serial.print(speedData[1]);
      Serial.println();
      Serial.println("-------------------------------");
      Serial.print('\n'); 


      //***** enviar datos a B por XBee
      Serial1.println(speedData[0]);
/*
      //Imprimir en consola
      Serial.println(speedData[0]);
*/
    }

  }

}










