#include <pigpio.h>
#include <stdio.h>
#include <stdbool.h>
#include "SensorCommunication.h"


bsc_xfer_t xfer;

int initializeConnectSensor(){
    gpioInitialise();
    printf("Initializeed GPIO\n");
    // Close old device (if any)
    xfer.control = getControlBits(SLAVE_I2C_ADDRESS, false);

    bscXfer(&xfer);
    // Set I2C slave Address to 0x03
    xfer.control = getControlBits(SLAVE_I2C_ADDRESS, true);
    int status = bscXfer(&xfer); // Should now be visible in I2C-Scanner

    return status;
}


char* receiveSensorData(){
    char *payload;

    printf("Opened slave\n");
    xfer.rxCnt = 0;
    payload = &xfer.rxBuf[0];

    while(1){
        bscXfer(&xfer);
        if(xfer.rxCnt > 0)
        {
            printf("Receiving Data ... %s\n", xfer.rxBuf);
            break;
        }
    }
    
    return payload;
}



void closeSensorConnect(){
    gpioInitialise();
    // cout << "Initialized GPIOs\n";
    printf("Initialized GPIOs\n");

    xfer.control = getControlBits(SLAVE_I2C_ADDRESS, false);
    bscXfer(&xfer);
    // cout << "Closed slave.\n";
    printf("Closed slave.\n");

    gpioTerminate();
    // cout << "Terminated GPIOs.\n";
    printf("Terminated GPIOs.\n");
}



int getControlBits(int address /* max 127 */, bool open) {
    /*
    Excerpt from http://abyz.me.uk/rpi/pigpio/cif.html#bscXfer regarding the control bits:

    22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00
    a  a  a  a  a  a  a  -  -  IT HC TF IR RE TE BK EC ES PL PH I2 SP EN

    Bits 0-13 are copied unchanged to the BSC CR register. See pages 163-165 of the Broadcom 
    peripherals document for full details. 

    aaaaaaa defines the I2C slave address (only relevant in I2C mode)
    IT  invert transmit status flags
    HC  enable host control
    TF  enable test FIFO
    IR  invert receive status flags
    RE  enable receive
    TE  enable transmit
    BK  abort operation and clear FIFOs
    EC  send control register as first I2C byte
    ES  send status register as first I2C byte
    PL  set SPI polarity high
    PH  set SPI phase high
    I2  enable I2C mode
    SP  enable SPI mode
    EN  enable BSC peripheral
    */

    // Flags like this: 0b/*IT:*/0/*HC:*/0/*TF:*/0/*IR:*/0/*RE:*/0/*TE:*/0/*BK:*/0/*EC:*/0/*ES:*/0/*PL:*/0/*PH:*/0/*I2:*/0/*SP:*/0/*EN:*/0;

    int flags;
    if(open)
        flags = /*RE:*/ (1 << 9) | /*TE:*/ (1 << 8) | /*I2:*/ (1 << 2) | /*EN:*/ (1 << 0);
    else // Close/Abort
        flags = /*BK:*/ (1 << 7) | /*I2:*/ (0 << 2) | /*EN:*/ (0 << 0);

    return (address << 16 /*= to the start of significant bits*/) | flags;
}
