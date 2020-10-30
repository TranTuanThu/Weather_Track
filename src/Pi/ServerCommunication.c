#include <stdio.h>
#include <string.h>
#include <mosquitto.h>
#include "ServerCommunication.h"

struct mosquitto *mosqpub;
struct mosquitto *mosqsub;

static char upperthreshold[5];
static char lowerthreshold[5];
static int countsub = 0;
static int countpub = 0;

bool initializeConnectBroker(){
    bool status;
    
    int x = initializeConnectBrokerToSend();
    int y = initializeConnectBrokerToReceive();

    if (x == MOSQ_ERR_SUCCESS&&y == MOSQ_ERR_SUCCESS)
    {
        return true;
    }else
    {
        return false;
    }
} 

static int initializeConnectBrokerToSend(){
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


static int initializeConnectBrokerToReceive(){
    int status = 0;
    mosquitto_lib_init();
    mosqsub = mosquitto_new(NULL, true, NULL);

    if(mosqsub)
    {
        status = mosquitto_connect(mosqsub, HOST, PORT, KEEPALIVE);
    }
    mosquitto_subscribe(mosqsub, NULL, TOPIC_UPDATE_THRESHOLD, 0);
    mosquitto_loop_start(mosqsub);

    return status;
}


void sendSensorData(char *payload){
    char data[9];
    char tempt[5];
    char warning;
    static int count;
    
    memcpy(data, payload, 8);
    memcpy(tempt, payload, 4); tempt[4] = '\0';
    
    if (countpub == 1)
    {
        int comparelow = strcmp(tempt, lowerthreshold);
        int compareup  = strcmp(tempt, upperthreshold);
        
        if (comparelow <= 0)      // canh bao nhiet do thap
        {
            warning = '0';
        }

        if (compareup >= 0)       // canh bao nhiet do cao
        {
            warning = '1';
        }

        if (comparelow > 0&&compareup < 0)  // nhiet do an toan
        {
            warning = '2';
        }
        data[8] = warning;
        countpub = 0;
        count = 1;
    }else if (count == 1)
    {
        int comparelow = strcmp(tempt, lowerthreshold);
        int compareup  = strcmp(tempt, upperthreshold);
        
        if (comparelow <= 0)      // canh bao nhiet do thap
        {
            warning = '0';
        }

        if (compareup >= 0)       // canh bao nhiet do cao
        {
            warning = '1';
        }

        if (comparelow > 0&&compareup < 0)  // nhiet do an toan
        {
            warning = '2';
        }
        data[8] = warning;
    }else
    {
        int comparelow = strcmp(tempt, "20");
        int compareup  = strcmp(tempt, "35");
        
        if (comparelow <= 0)      // canh bao nhiet do thap
        {
            warning = '0';
        }

        if (compareup >= 0)       // canh bao nhiet do cao
        {
            warning = '1';
        }

        if (comparelow > 0&&compareup < 0)  // nhiet do an toan
        {
            warning = '2';
        }
        data[8] = warning;
    }
    mosquitto_publish(mosqpub, NULL, TOPIC_TEMPT_HUMID, sizeof(data), &data, 0, false);
}


static void messageCallback(struct mosquitto *mosqsub, void *obj, const struct mosquitto_message *message){
    // Xu ly cap nhat nguong
    struct mosquitto_message dst;

    mosquitto_message_copy(&dst, message);
    (char*) dst.payload;
    memcpy(lowerthreshold, dst.payload, 4); lowerthreshold[4] = '\0';
    memcpy(upperthreshold, dst.payload+4, 4); upperthreshold[4] = '\0';
    countsub = 1;
    countpub = 1;
}


static void receiveMessageCallback(){
    mosquitto_message_callback_set(mosqsub, messageCallback);
}


void processServerRequest(){
    receiveMessageCallback();
    
    while (1)
    {
        if (countsub == 1)
        {
            countsub = 0;
            break;
        }else
        {
            break;
        }
    }
}
