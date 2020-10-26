#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include <pigpio.h>
#include "SensorCommunication.h"
#include "ServerCommunication.h"

char threshold = '0';

bool initializeConnectToSend(){
    int scs = initializeConnectSensor();
    int scb = initializeConnectBrokerToSend();

    if(scs >= 0 && scb == MOSQ_ERR_SUCCESS)
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
    // strcat(payload,threshold);
    sendSensorData(payload);
}


void handleServerRequest(){

}


int main(){
    bool status = initializeConnectToSend();
    
    if(status)
    {
        while (1)
        {
            handleSensorData();
        }
    }
    
    return 0;
}