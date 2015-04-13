//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef CUSTOMAPPLAYER_H_
#define CUSTOMAPPLAYER_H_

#include <NodeInfo.h>
#include <Vector>
#include <iostream>

class CustomAppLayer
{
    private:
	
        //Cantidad de paquetes enviados
        long numSent;
		
        //Cantidad de paquetes recibidos
        long numReceived;
		
        //ID consecutivo del paquete
        int packageID;
		
        //Distancia total entre el inicio y la meta
        double totalDistance;
		
        //Datos del líder
        double localLeaderAcceleration;
        double localLeaderSpeed;

		  //Información de los nodos vecinos
        std::vector<NodeInfo*> nodeInfoVector;

        //Aceleracion del ultimo platoon
        double lastAccelerationPlatoon;

        //Constantes alpha de CACC
        double alpha1;
        double alpha2;
        double alpha3;
        double alpha4;
        double alpha5;

        //Constante alpha de CACC con el lag
        double alphaLag;

        //Valores para calcular el spacing error
        double length_vehicle_front;
        double desiredSpacing;

        //Frecuencia de envío de paquetes beacon
        double beaconInterval;

        //Frecuencia para calcular aceleración con CACC
        double platoonInterval;

        //Bandera para indicar si el beaconing está habilitado
        bool beaconingEnabled;
		
		 //Velocidad del nodo
		 double mySpeed;
		 
		 //Dirección
		 double myAddress;

    public:
            CustomAppLayer();
            void handleLowerMsg(NodeInfo* nodeInfo);
			 double getAccelerationPlatoon();
			 void setMyAddress(double s);
			 double getMyAddress();
			 void setMySpeed(double s);
			 double getMySpeed();


};

#endif /* CUSTOMAPPLAYER_H_ */
