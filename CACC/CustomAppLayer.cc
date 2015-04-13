#include "CustomAppLayer.h"


using namespace std;

CustomAppLayer::CustomAppLayer()
{
    // 1. Variables generales
    packageID = 0; //ID del paquete
    numSent = 0; // Cantidad de paquetes enviados
    numReceived = 0; // Cantidad de paquetes recibidos
    totalDistance = 0; //Distancia total a la meta
    lastAccelerationPlatoon = 0; // Última aceleración calculada con CACC
    localLeaderAcceleration = 0;
    localLeaderSpeed = 0;

    //2 . Parámetros del Platoon (CACC)
    alpha1 = 0.5;
    alpha2 = 0.5;
    alpha3 = 0.3;
    alpha4 = 0.1;
    alpha5 = 0.04;
    alphaLag = 0.8;
    length_vehicle_front = 2;
    desiredSpacing = 2;
    beaconInterval = 0.1;
    platoonInterval = 1;
    beaconingEnabled = false;

}


double CustomAppLayer::getAccelerationPlatoon()
{
    // 1. PREPARACION

    //Lista sin duplicados
    std::vector<NodeInfo*> noDuplicateInfo;
    double distanceBetweenActualAndFront;

    //Se agrega la informacion a la lista sin duplicados
    for (int i = 0; i < int(nodeInfoVector.size()); i++)
    {
        NodeInfo* nodeInfo = nodeInfoVector.back();

        bool existeInfo = false;

        //Se recorre  la lista sin duplicados
        for (std::vector<NodeInfo*>::iterator it = noDuplicateInfo.begin(); it != noDuplicateInfo.end();
                ++it)
        {
            NodeInfo* n = *it;

            //Si existe algun paquete de la misma fuente no se agrega
            if (n->getSrcAddress() == nodeInfo->getSrcAddress())
            {
                existeInfo = true;
                break;
            }
        }

        //Si nunca se encontrio un paquete de la misma fuente se agrega a la lista
        if (existeInfo == false)
        {
            noDuplicateInfo.push_back(nodeInfo);

        }

        //Se elimina el elemento que se acabo de usar
        nodeInfoVector.pop_back();
    }

    // 2. EMPIEZA EL PLATOON

    //Calcular distancias desde los nodos hacia el actual para determinar el mas cercano
    NodeInfo* nearestNode = NULL;
    NodeInfo* leaderNode = NULL;

    cout << "Node[" << getMyAddress() << "]: Running Platoon Update" << endl;

    if (noDuplicateInfo.size() > 0)
    {

        //a. Determinar nodo mas cercano y nodo lider
        for (std::vector<NodeInfo*>::iterator it = noDuplicateInfo.begin(); it != noDuplicateInfo.end();
                ++it)
        {
            NodeInfo* nodeInfo = *it;

            //Obtener la distancia del nodo del que se recibio el paquete al nodo actual
            int addr_node = nodeInfo->getSrcAddress();
            double distanceToActual = nodeInfo->getDistanceToCurrent();

            //Asignar lider
            if (addr_node == 0)
            {
                leaderNode = *it;
            }

            //Si actualmente no hay un nodo mas cercano y la distancia del nodo al actual es mayor a cero,
            //este es el nodo mas cercano por el momento
            if (distanceToActual > 0 && nearestNode == NULL)
            {
                nearestNode = *it;
            }

            //Si actualmente hay un nodo mas cercano, se compara con el nodo del cual se recibio un paquete
            if (nearestNode != NULL)
            {
                //Comparar con el nodo mas cercano hasta el momento
                double distanceToActual_nearest = nearestNode->getDistanceToCurrent();

                //Se cambia el nodo mas cercano si la distancia es menor a la del mas cercano actual
                if (distanceToActual > 0 && distanceToActual < distanceToActual_nearest)
                {
                    nearestNode = *it;
                }
            }
        }

        //b. Obtener informacion del nodo mas cercano que se encuentre al frente
        double rel_speed_front;

        double spacing_error;
        double nodeFrontAcceleration;

        if (nearestNode != NULL)
        {
            //Velocidad relativa al vehiculo del frente
            rel_speed_front = getMySpeed() - nearestNode->getSpeed();

            //Obtener spacing error
            distanceBetweenActualAndFront = nearestNode->getDistanceToCurrent();
            spacing_error = -distanceBetweenActualAndFront + length_vehicle_front + desiredSpacing;

            nodeFrontAcceleration = nearestNode->getAcceleration();

        }
        else
        {
            rel_speed_front = 0;
            spacing_error = 0;
            nodeFrontAcceleration = 0;
        }

        //c. Obtener la informacion del lider
        double leaderAcceleration;
        double leaderSpeed;

        if (leaderNode == NULL)
        {
            //Se usan los datos del mecanismo beaconing
            if (nearestNode != NULL && beaconingEnabled == true)
            {
				//Se emite cada vez que se usa un paquete que llegó por multisalto
                //emit(leaderInfoMultihopUsedSignal,packageID);

                leaderAcceleration = nearestNode->getLeaderAcceleration();
                leaderSpeed = nearestNode->getLeaderSpeed();
                localLeaderAcceleration = nearestNode->getLeaderAcceleration();
                localLeaderSpeed = nearestNode->getLeaderSpeed();
            }
            else
            {
                leaderAcceleration = 0;
                leaderSpeed = 0;
                localLeaderAcceleration = 0;
                localLeaderSpeed = 0;
            }

        }
        else
        {
            leaderAcceleration = leaderNode->getAcceleration();
            leaderSpeed = leaderNode->getSpeed();
        }

        //Print data for calculation
        cout << "Node[" << getMyAddress() << "]: Platoon parameters" << endl;
        cout << "Distance to Vehicle in Front=" << distanceBetweenActualAndFront << endl;
        cout << "Vehicle in Front Acceleration=" << nodeFrontAcceleration << endl;
        cout << "Leader Acceleration=" << leaderAcceleration << endl;
        cout << "Relative speed vehicule in front=" << rel_speed_front << endl;
        cout << "Leader speed=" << leaderSpeed << endl;
        cout << "My speed=" << getMySpeed() << endl;
        cout << "Spacing Error=" << spacing_error << endl;

        //d. Calcular A_des (Acceleration desired)
        double A_des = alpha1 * nodeFrontAcceleration + alpha2 * leaderAcceleration
                - alpha3 * rel_speed_front - alpha4 * (getMySpeed() - leaderSpeed)
                - alpha5 * spacing_error;

        //e. Calcular la aceleraciÃ³n deseada incluyÃ©ndole el retardo
        double A_des_lag = (alphaLag * A_des) + ((1 - alphaLag) * lastAccelerationPlatoon);

        lastAccelerationPlatoon = A_des_lag;
		

		return A_des_lag;
	}
}


/**
 * Manejar mensajes que llegan desde las capas inferiores
 */
void CustomAppLayer::handleLowerMsg(NodeInfo* nodeInfo)
{
    numReceived++;
	
	//Se emite una señal indicando que llegó un paquete nuevo al nodo
	//emit(receivedSignal, packageID);

	//Obtener información del paquete para reenviar al resto de nodos
	double speed = nodeInfo->getSpeed();
	double acceleration = nodeInfo->getAcceleration();
	int address = nodeInfo->getSrcAddress();

	cout << "Info from: " << address << endl;

	//Guardar aceleración y velocidad si pertenecen al líder
	if (address == 0)
	{
		localLeaderAcceleration = acceleration;
		localLeaderSpeed = speed;

		//Emitir senal que indica la recepcion de un paquete del lider
		//emit(leaderInfoSignal, packageID);
		//Emitir senal que indica la recepcion de un paquete directamente del lider
		//emit(leaderInfoDirectSignal, packageID);

	}
	else if (beaconingEnabled == true)
	{
		//Emitir senal que indica la recepcion de un paquete del lider
		//emit(leaderInfoSignal, packageID);
		//Emitir senal que indica la recepcion de un paquete del lider por multisalto
		//emit(leaderInfoMultihopSignal, packageID);
	}

	//Guardar paquete
	nodeInfoVector.push_back(nodeInfo);


	//Detener el nodo
	/*
	totalDistance = par("totalDistance");
	double distanceToOrigin = getAbsoluteDistance(getModuleXPosition(), getModuleYPosition(),
			getZonaNodo(getModuleXPosition(), getModuleYPosition()));
			
	if (distanceToOrigin >= totalDistance)
	{
		CustomMobilityAccess().get(findHost())->stop();

	}
	*/
	
	return; 
}

void CustomAppLayer::setMyAddress(double newAddress)
{
	myAddress = newAddress;
}

double CustomAppLayer::getMyAddress()
{
	return myAddress;
}

void CustomAppLayer::setMySpeed(double newSpeed)
{
	mySpeed = newSpeed;
}

double CustomAppLayer::getMySpeed()
{
	return mySpeed;
}