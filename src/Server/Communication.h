#ifndef Communication_H
#define Communication_H

#define HOST "localhost"
#define PORT 1883
#define TOPIC_TEMPT_HUMID "TemptHumid"
#define TOPIC_ ""
#define KEEPALIVE 60

bool initializeConnectBrokerToReceive();
bool initializeConnectBrokerToSend();
void receiveData();
void sendData(char *);


#endif