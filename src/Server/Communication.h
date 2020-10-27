#ifndef Communication_H
#define Communication_H

#define HOST "192.168.0.155"
#define PORT 1883
#define TOPIC_TEMPT_HUMID "TemptHumid"
#define TOPIC_ ""
#define KEEPALIVE 60

// extern int count = 0;
// extern char tempt[5];
// extern char humid[5];

bool initializeConnectBrokerToReceive();
bool initializeConnectBrokerToSend();
void closeBrokerConnect();
void receiveData();
void sendData(char *);
void processReceivedData();
double temPt();
double humId();


#endif