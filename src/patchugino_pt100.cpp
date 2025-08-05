/**
* File: patchugino_pt100.cpp
* Created on: 2025-08-05 at 09:48
* Author: Andrea Rantin
* Description: Implementation file for patchugino_pt100.h
*/

#include "patchugino_pt100.h"

static SPISettings pt100SpiSettings(1000000, MSBFIRST, SPI_MODE1);

uint32_t Patchugino_PT100::PT100Cs_ToUint(PT100Cs cs) {
    switch(cs) {
        case PT100Cs::CS_0:
            return PC8;
        case PT100Cs::CS_1:
            return PD11;
        default:
            break;
    }
    return 0;
}

void Patchugino_PT100::Init(PT100Cs cs, HardwareSerial& serial, PatchugoLogLevel logLevel) {

    //Initialize logger
    static Patchugo_Logger localLogger(serial,logLevel);
    logger = &localLogger;

    logger->Log_Info("Patchugino PT100 Initializing\n");

    csUsed = PT100Cs_ToUint(cs);
    SPI.end();
    SPI.begin();

    logger->Log_Info("Patchugino PT100 Initialized\n");
}