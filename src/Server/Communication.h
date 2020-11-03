#ifndef Communication_H
#define Communication_H

#define HOST "192.168.0.168"
#define PORT 1883
#define TOPIC_TEMPT_HUMID "TemptHumid"
#define TOPIC_UPDATE_THRESHOLD "UpdateThreshold"
#define KEEPALIVE 60


bool initializeConnectBroker();
static bool initializeConnectBrokerToReceive();
static bool initializeConnectBrokerToSend();
static void closeBrokerConnect();
static void receiveData();
// void sendData(char *);
void processReceivedData();
double temPt();
double humId();


#endif