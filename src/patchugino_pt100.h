/**
* File: patchugino_pt100.h
* Created on: 2025-08-05 at 09:48
* Author: Andrea Rantin
* Description: //TODO
*/

#pragma once

#include "patchugo_core.h"
#include "internal/patchugino_pt100_types.h"
#include <SPI.h>

using namespace PatchuginoPT100;

namespace PatchuginoPT100 {

    class Patchugino_PT100 {
        private:
            uint32_t csUsed; /*!< CS used for SPI communication */
            PT100ConfigStruct pt100_0; /*!< PT100 of connector CN1*/
            PT100ConfigStruct pt100_1; /*!< PT100 of connector CN3*/
            Patchugo_Logger* logger = nullptr;
            /**
            * @brief Converts a member if @ref PT100Cs to
            * its corresponding pin value
            * @param cs Enum value to convert
            * @return uint32_t Pin value
            */
            uint32_t PT100Cs_ToUint(PT100Cs cs);
        public:
            /**
            * @brief Initializes the Patchugino_PT100 board
            * 
            * @param cs Cs used for SPI communication
            * @param serial Serial used for logging of Patchugino_Analog. Defaults to Serial
            * @param logLevel Logging level used for logging of Patchugino_Analog. Defaults to LOG_LEVEL_VERBOSE
            * 
            * @note The serial instance must be initialized by calling Serial.begin before calling this Init function, otherwise logs
            * will not be visible!
            */
            void Init(PT100Cs cs, HardwareSerial& serial = Serial, PatchugoLogLevel logLevel = LOG_LEVEL_VERBOSE);
    };
}
