#include <XBee.h>

/*
  RED 3 NODOS - PROYECTO BICICLETAS
 
 SERVER
 */
 
//XBee
XBee xbee = XBee();
XBeeResponse response = XBeeResponse();

//Objetos de respuesta reusables 
Rx16Response rx16 = Rx16Response();
Rx64Response rx64 = Rx64Response();

//Informacion
uint8_t option = 0;
uint8_t data = 0;

//Velocidad objetivo que se recibe del cliente A
float velocidadA = 0;



void setup()
{
  Serial.begin(9600); //Local
  Serial1.begin(9600); //XBee
  xbee.setSerial(Serial1);
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
  xbee.readPacket();

  //Hay datos disponibles
  if(xbee.getResponse().isAvailable())
  {
    //Verificar que proviene de la red ZigBee
    if(xbee.getResponse().getApiId() == RX_16_RESPONSE || xbee.getResponse().getApiId() == RX_64_RESPONSE)
    {
      //Respuesta de 16 bits
      if(xbee.getResponse().getApiId() == RX_16_RESPONSE)
      {
         xbee.getResponse().getRx16Response(rx16);
         option = rx16.getOption();
         data = rx16.getData(0); 
      }
      //Respuesta de 64 bits
      else
      {
         xbee.getResponse().getRx64Response(rx64);
         option = rx64.getOption();
         data = rx64.getData(0);
      }
      
      Serial.println(data);
    }
    //No era informacion que se esperaba
    else 
    {
      
    }

  }
  //Error leyendo el paquete
  else if (xbee.getResponse().isError())
  {
  }

}










