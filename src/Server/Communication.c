#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include "Communication.h"

struct mosquitto *mosqsub;
struct mosquitto *mosqpub;
// struct mosquitto_message *dst;


bool initializeConnectBrokerToReceive(){
    int status = 0;
    mosquitto_lib_init();
    mosqsub = mosquitto_new(NULL, true, NULL);

    if(mosqsub)
    {
        status = mosquitto_connect(mosqsub, HOST, PORT, KEEPALIVE);
    }
    mosquitto_subscribe(mosqsub, NULL, TOPIC_TEMPT_HUMID, 0);
    mosquitto_loop_start(mosqsub);

    if(status == MOSQ_ERR_SUCCESS)
    {
        printf("Mosqsub Connect Success!...\n");
        return true;
    }else
    {
        printf("Mosqsub Connect False!>>>\n");
        return false;
    }
}


bool initializeConnectBrokerToSend(){
    int status = 0;
    mosquitto_lib_init();
    mosqpub = mosquitto_new(NULL, true, NULL);

    if(mosqpub)
    {
        status = mosquitto_connect(mosqpub, HOST, PORT, KEEPALIVE);
    }
    mosquitto_loop_start(mosqpub);

    if(status == MOSQ_ERR_SUCCESS)
    {
        printf("Mosqpub Connect Success!...\n");
        return true;
    }else
    {
        printf("Mosqpub Connect False!>>>\n");
        return false;
    }
}


void sendData(char *payload){
    mosquitto_publish(mosqpub, NULL, TOPIC_, strlen(payload), payload, 0, false);
}


void dataCallback(struct mosquitto *mosqsub, void *obj, const struct mosquitto_message *message){
    struct mosquitto_message *dst;
    mosquitto_message_copy(dst, message);
    printf("got message '%.*s' for topic '%s'\n", dst->payloadlen, (char*) dst->payload, dst->topic);
}


void receiveData(){
    mosquitto_message_callback_set(mosqsub, dataCallback);
}


int main(){
    bool status;
    status = initializeConnectBrokerToReceive();

    if (status)
    {
        while (1)
        {
            receiveData();
            // printf("%s/n", dst->payload);
        }
    }
    
    return 0;
}