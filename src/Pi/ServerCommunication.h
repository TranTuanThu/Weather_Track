#ifndef ServerCommunication_H
#define ServerCommunication_H

#define USENAME ""
#define PASSWORD ""

#define HOST "localhost"
#define PORT 1883
#define TOPIC_TEMPT_HUMID "TemptHumid"
#define TOPIC_UPDATE_THRESHOLD "UpdateThreshold"
#define TOPIC2 ""
#define KEEPALIVE 60


bool initializeConnectBroker();
static int initializeConnectBrokerToSend();
static int initializeConnectBrokerToReceive();
void sendSensorData(char *);
static void receiveMessageCallback();

void processServerRequest();

#endif