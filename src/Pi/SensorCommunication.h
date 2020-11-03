#ifndef SensorCommunication_H
#define SensorCommunication_H


#define SLAVE_I2C_ADDRESS 0x03

int initializeConnectSensor();
char* receiveSensorData();
// void closeSensorConnect();
static int getControlBits(int, bool);


#endif