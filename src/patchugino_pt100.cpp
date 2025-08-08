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

uint8_t Patchugino_PT100::PT100N_ToCsLevel(PT100N pt100N) {
    switch(pt100N) {
        case PT100_N_0:
            return HIGH;
        case PT100_N_1:
            return LOW;
    }
    return LOW;
}

void Patchugino_PT100::Init(PT100Cs cs, HardwareSerial& serial, PatchugoLogLevel logLevel) {

    //Initialize logger
    static Patchugo_Logger localLogger(serial,logLevel);
    logger = &localLogger;

    logger->Log_Info("Patchugino PT100 Initializing\n");

    csUsed = PT100Cs_ToUint(cs);
    pinMode(csUsed, OUTPUT);
    SPI.end();
    SPI.begin();

    logger->Log_Info("Patchugino PT100 Initialized\n");
}

void Patchugino_PT100::Configure(PT100N pt100N, PT100Type pt100Type) {

    PT100ConfigStruct* target = nullptr;

    switch(pt100N) {
        case PT100_N_0:
            target = &pt100_0;
            break;
        case PT100_N_1:
            target = &pt100_1;
            break;
        default:
            break;
    }

    target->configReg = 0;

    target->configReg |= static_cast<uint8_t>(PT100_FILTER_50Hz);

    //Clear faults
    target->configReg |= static_cast<uint8_t>(0x01U << 1);

    //No fault detection
    target->configReg |= static_cast<uint8_t>(0x00U << 2);

    if(pt100Type == PT100_3WIRE) {
        target->is3Wire = true;
        target->configReg |= static_cast<uint8_t>(0x01U << 4);
    }else {
        target->is3Wire = false;
        target->configReg |= static_cast<uint8_t>(0x00U << 4);
    }

    //One shot
    target->configReg |= static_cast<uint8_t>(0x01U << 5);

    target->configReg |= static_cast<uint8_t>(PT100_CONVERSION_OFF);

    target->configReg |= static_cast<uint8_t>(PT100_VBIAS_ON);

    uint8_t csActiveLevel = PT100N_ToCsLevel(pt100N);

    digitalWrite(csUsed, csActiveLevel);
    SPI.beginTransaction(pt100SpiSettings);
    SPI.transfer(0x80);
    SPI.transfer(target->configReg);
    SPI.endTransaction();
    digitalWrite(csUsed, !csActiveLevel);
}

float Patchugino_PT100::Read(PT100N pt100N) {

    PT100ConfigStruct* target = nullptr;

    switch(pt100N) {
        case PT100_N_0:
            target = &pt100_0;
            break;
        case PT100_N_1:
            target = &pt100_1;
            break;
        default:
            break;
    }

    //Reset one-shot for current read
    target->configReg |= static_cast<uint8_t>(0x01U << 5);

    uint8_t csActiveLevel = PT100N_ToCsLevel(pt100N);

    digitalWrite(csUsed, csActiveLevel);
    SPI.beginTransaction(pt100SpiSettings);
    SPI.transfer(0x80);
    SPI.transfer(target->configReg);
    SPI.endTransaction();
    digitalWrite(csUsed, !csActiveLevel);

    uint8_t msb = 0;
    uint8_t lsb = 0;

    digitalWrite(csUsed, csActiveLevel);
    SPI.beginTransaction(pt100SpiSettings);
    SPI.transfer(0x01);
    msb = SPI.transfer(0x00);
    lsb = SPI.transfer(0x00);
    SPI.endTransaction();
    digitalWrite(csUsed, !csActiveLevel);

    uint16_t rtd_data = ((uint16_t)msb << 8 | lsb) >> 1;
    float resistance = (float)rtd_data * R_REFERENCE / RTD_MAX_VAL;
    float temperature = (resistance - 100.0f) / 0.385f;

    logger->Log_Info("RTD VAL: %d\n", rtd_data);
    return temperature;
}