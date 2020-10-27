#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mosquitto.h>
#include "Communication.h"

struct mosquitto *mosqsub;
struct mosquitto *mosqpub;

int count = 0;
char tempt[5];
char humid[5];

/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/

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


static void dataCallback(struct mosquitto *mosqsub, void *obj, const struct mosquitto_message *message){
    struct mosquitto_message dst;

    mosquitto_message_copy(&dst, message);
    (char*) dst.payload;
    
    memcpy(tempt, dst.payload, 4);
    memcpy(humid, dst.payload+4, 4);
    count = 1;
    printf("got message '%.*s' for topic '%s'\n", message->payloadlen, (char*) message->payload, message->topic);
    
}


void receiveData(){
    mosquitto_message_callback_set(mosqsub, dataCallback);
}


void closeBrokerConnect(){
    mosquitto_disconnect(mosqsub);
    mosquitto_disconnect(mosqpub);
    mosquitto_destroy(mosqsub);
    mosquitto_destroy(mosqpub);
    mosquitto_lib_cleanup();
}


void processReceivedData(){
    bool status;
    status = initializeConnectBrokerToReceive();

    if (status)
    {
        receiveData();
        while (1)
        {
            if (count == 1)
            {
                count = 0;
                closeBrokerConnect();
                break;
            }
        }
    }
}

double temPt(){
    return strtod(tempt, NULL);
}


double humId(){
    return strtod(humid, NULL);
}

// int main(){
//     bool status;
//     status = initializeConnectBrokerToReceive();

//     if (status)
//     {
//         receiveData();
//         while (1)
//         {   
//             if (count == 1)
//             {
//                 closeBrokerConnect();
//                 break;
//             }
//         }
//         printf("%s, %s\n", tempt, humid);
//     }

//     return 0;
// }