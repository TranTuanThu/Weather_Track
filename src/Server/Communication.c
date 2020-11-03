#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mosquitto.h>
#include "Communication.h"

struct mosquitto *mosqsub;
struct mosquitto *mosqpub;

static int count = 0;
static char tempt[5];
static char humid[5];
static char warning[2];

/*---------------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------*/

bool initializeConnectBroker(){
    bool statussuber, statuspuber;

    statussuber = initializeConnectBrokerToReceive();
    statuspuber = initializeConnectBrokerToSend();

    if (statussuber&&statuspuber)
    {
        printf("Mosqpub Connect Success!...\n");
        return true;
    }else
    {
        printf("Mosqpub Connect False!>>>\n");
        return false;
    }
}


static bool initializeConnectBrokerToReceive(){
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
        return true;
    }else
    {
        return false;
    }
}


static bool initializeConnectBrokerToSend(){
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
        return true;
    }else
    {
        return false;
    }
}


// void sendData(char *payload){
//     mosquitto_publish(mosqpub, NULL, TOPIC_UPDATE_THRESHOLD, strlen(payload), payload, 0, false);
// }


static void dataCallback(struct mosquitto *mosqsub, void *obj, const struct mosquitto_message *message){
    struct mosquitto_message dst;

    mosquitto_message_copy(&dst, message);
    (char*) dst.payload;
    
    memcpy(tempt, dst.payload, 4);
    memcpy(humid, dst.payload+4, 4);
    memcpy(warning, dst.payload+8, 1);
    count = 1;
    printf("got message '%.*s' for topic '%s'\n", message->payloadlen, (char*) message->payload, message->topic);
    
}


static void receiveData(){
    mosquitto_message_callback_set(mosqsub, dataCallback);
}


static void closeBrokerConnect(){
    mosquitto_disconnect(mosqsub);
    mosquitto_disconnect(mosqpub);
    mosquitto_destroy(mosqsub);
    mosquitto_destroy(mosqpub);
    mosquitto_lib_cleanup();
}


void processReceivedData(){
    // bool status;
    // status = initializeConnectBroker();

    // if (status)
    // {
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
    // }
}


double temPt(){
    return strtod(tempt, NULL);
}


double humId(){
    return strtod(humid, NULL);
}


double warnIng(){
    return strtod(warning, NULL);
}
