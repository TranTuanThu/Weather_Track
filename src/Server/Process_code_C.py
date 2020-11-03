from ctypes import *
# import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish

communication = CDLL('./libCom.so')

def initializeConnectBroker():
    communication.initializeConnectBroker()
    

def processReceivedData():
    communication.processReceivedData()
    communication.temPt.restype = c_double
    communication.humId.restype = c_double
    communication.warnIng.restype = c_double

    tempt = communication.temPt()
    humid = communication.humId()
    warn = communication.warnIng() 

    if (warn == 0):
        bgcolor = "blue"
        return tempt, humid, bgcolor
    if (warn == 1):
        bgcolor = "red"
        return tempt, humid, bgcolor
    if (warn == 2):
        bgcolor = "green"
        return tempt, humid, bgcolor


def processUpdateThreshold(payload):
    # broker_address = communication.HOST 
    # #broker_address="iot.eclipse.org" #use external broker
    # client = mqtt.Client() #create new instance
    # client.connect(broker_address, 1883, 60) #connect to broker
    # client.publish("UpdateThreshold", payload, 0, False)#publish
    publish.single("UpdateThreshold", payload, 0, False, hostname="192.168.0.168", port=1883, keepalive=60)
    # communication.sendData(payload)


