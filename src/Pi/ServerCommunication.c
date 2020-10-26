#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include "ServerCommunication.h"

struct mosquitto *mosqpub;
struct mosquitto *mosqsub;

int initializeConnectBrokerToSend(){
    int status = 0;
    mosquitto_lib_init();
    mosqpub = mosquitto_new(NULL, true, NULL);

    if(mosqpub)
    {
        status = mosquitto_connect(mosqpub, HOST, PORT, KEEPALIVE);
    }
    mosquitto_loop_start(mosqpub);

    return status;
}


int initializeConnectBrokerToReceive(){
    int status = 0;
    mosquitto_lib_init();
    mosqsub = mosquitto_new(NULL, true, NULL);

    if(mosqsub)
    {
        status = mosquitto_connect(mosqsub, HOST, PORT, KEEPALIVE);
    }
    mosquitto_subscribe(mosqsub, NULL, TOPIC1, 0);
    mosquitto_loop_start(mosqsub);

    return status;
}


void sendSensorData(char *payload){
    mosquitto_publish(mosqpub, NULL, TOPIC_TEMPT_HUMID, strlen(payload), payload, 0, false);

}


void messageCallback(struct mosquitto *mosqsub, void *obj, const struct mosquitto_message *message){

    printf("THTHTHTH\n");

}


void receiveMessageCallback(){
    mosquitto_message_callback_set(mosqsub, messageCallback);
}