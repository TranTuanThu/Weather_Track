from ctypes import *

communication = CDLL('./libCom.so')


def processReceivedData():
    communication.processReceivedData()
    communication.temPt.restype = c_double
    communication.humId.restype = c_double

    tempt = communication.temPt()
    humid = communication.humId()
    
    return tempt, humid

