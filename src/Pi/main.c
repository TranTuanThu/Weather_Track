#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include <pigpio.h>
#include "SensorCommunication.h"
#include "ServerCommunication.h"


bool initializeConnect(){
    int scs = initializeConnectSensor();
    bool scb = initializeConnectBroker();

    if(scs >= 0 && scb)
    {
        printf("Connect Success!...\n");
        return true;
    }else
    {
        printf("Connect false!>>>\n");
        return false;
    }
    
}


void handleSensorData(){
    char *payload;

    payload = receiveSensorData();
    sendSensorData(payload);
}


void handleServerRequest(){
    processServerRequest();
}


int main(){
    bool status = initializeConnect();

    while (status)
    {
        handleServerRequest();
        handleSensorData();
    }
    
    return 0;
}