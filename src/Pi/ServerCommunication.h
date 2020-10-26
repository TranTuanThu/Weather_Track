#ifndef ServerCommunication_H
#define ServerCommunication_H

#define USENAME ""
#define PASSWORD ""

#define HOST "localhost"
#define PORT 1883
#define TOPIC_TEMPT_HUMID "TemptHumid"
#define TOPIC1 ""
#define TOPIC2 ""
#define KEEPALIVE 60


int initializeConnectBrokerToSend();
int initializeConnectBrokerToReceive();
void sendSensorData(char *);
void receiveMessageCallback();

#endif