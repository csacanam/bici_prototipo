#include <XBee.h>

/*
  RED 3 NODOS - PROYECTO BICICLETAS
 
 CLIENT A
 */
 
//XBee
XBee xbee = XBee();
//Arreglo donde se guarda el dato que se envia al lider
uint8_t payload[4] = {0, 0, 0, 0};
//Apuntador para adicionar un float al arreglo payload
uint8_t payloadPointer = 0;

//Direccion del coordinador SH + SL
XBeeAddress64 addr64 = XBeeAddress64(0x0013A200, 0x408BE3EB);
//Informacion (payload + address) para enviar al coordinador
Tx64Request tx = Tx64Request(addr64, payload, sizeof(payload));

//Estado de la respuesta que viene del coordinador
TxStatusResponse txStatus = TxStatusResponse();

// variables for calculate the speed
long previous, time, impulses;
float speedometer, circuit;

void setup()
{
  Serial.begin(9600); //Local
  Serial1.begin(9600); //XBee
  xbee.setSerial(Serial1);
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
  
  //Despues de enviar una solicitud tx se espera una respuesta de estado
  //Se espera hasta 5 segundos por la respuesta 
  if(xbee.readPacket(5000))
  {
    //Debe ser un estado tx de una red ZigBee
    if(xbee.getResponse().getApiId() == TX_STATUS_RESPONSE)
    {
      //Estado exitoso
      if(txStatus.getStatus() == SUCCESS)
      {
      }
      //El coordinador no recibio el paquete
      else
      {
        
      }
    }
  }
  //Error leyendo el paquete
  else if (xbee.getResponse().isError())
  {
    
  }
  //El XBee local no recibio una respuesta de estado tx a tiempo
  //Los radios no estan configurados apropiadamente o estan desconectados
  else
  {
    
  }
  
  delay(1000);
  
}


//Enviar informacion cada segundo
void sendBeacon()
{
  //Agregar dato al payload
  addToPayload(10);
  
  //Enviar datos por XBee
  xbee.send(tx);
  
  //Limpiar payload
  clearPayload();
}


void readSpeed()
{
  //if wheel turns
  if(analogRead(A0)>=300)
  {
    //number of turns++
    impulses++;

    //count turn time
    time=(millis()-previous);

    //count speed
    speedometer=(circuit / time)*3600.0;
    previous=millis();
    delay(100);
  }

  if((millis()-previous) > 2000)
  {
    speedometer = 0;
  }


}

//Permite agregar un valor float a un payload
void addToPayload(float value)
{
  byte * b = (byte *) &value;
  payload[payloadPointer++] = b[0];
  payload[payloadPointer++] = b[1];
  payload[payloadPointer++] = b[2];
  payload[payloadPointer++] = b[3];
}

//Permite eliminar lo que haya en el payload
void clearPayload()
{
   payloadPointer = 0;
   payload[0] = 0;
   payload[1] = 0;
   payload[2] = 0;
   payload[3] = 0; 
}


