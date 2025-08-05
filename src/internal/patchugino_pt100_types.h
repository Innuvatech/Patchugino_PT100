/**
* File: patchugino_pt100_types.h
* Created on: 2025-08-05 at 09:49
* Author: Andrea Rantin
* Description: //TODO
*/

#pragma once

#include <Arduino.h>

namespace PatchuginoPT100 {

    /**
    * @brief CS pins usable by the P100 shield board.
    * Selectrable from H9 pin header
    * 
    */
    enum class PT100Cs {
        CS_0 = PC8,
        CS_1 = PD11,
    };

    //Utility constant expressions to ease use of enum class of PT100Cs
    static constexpr PT100Cs PT100_CS_0 = PT100Cs::CS_0;
    static constexpr PT100Cs PT100_CS_1 = PT100Cs::CS_1;

    /**
    * @brief Number of the PT100 of the board.
    * This represents the 2 selectable PT100 connectors of the board
    * (CN1 for PT100_0 and CN3 for PT100_1)
    */
    enum class PT100N {
        PT100_0,
        PT100_1,
    };

    //Utility constant expressions to ease use of enum class of PT100N
    static constexpr PT100N PT100_N_0 = PT100N::PT100_0;
    static constexpr PT100N PT100_N_1 = PT100N::PT100_1;

    /**
    * @brief PT100 types
    * 
    */
    enum class PT100Type {
        PT100_2WIRE,
        PT100_3WIRE,
        PT100_4WIRE,
    };

    //Utility constant expressions to ease use of enum class of PT100Type
    static constexpr PT100Type PT100_2WIRE = PT100Type::PT100_2WIRE;
    static constexpr PT100Type PT100_3WIRE = PT100Type::PT100_3WIRE;
    static constexpr PT100Type PT100_4WIRE = PT100Type::PT100_4WIRE;

    typedef struct {
        bool is3Wire;
        uint32_t configReg;
    }PT100ConfigStruct;

    /**
    * @brief PT100 Filter
    * 
    */
    enum class PT100Filter {
        PT100_FILTER_50Hz = (0x01U << 0),
        PT100_FILTER_60Hz = (0x00U << 0),
    };

    //Utility constant expressions to ease use of enum class of PT100Filter
    static constexpr PT100Filter PT100_FILTER_50Hz = PT100Filter::PT100_FILTER_50Hz;
    static constexpr PT100Filter PT100_FILTER_60Hz = PT100Filter::PT100_FILTER_60Hz;

    /**
    * @brief PT100 Conversion mode
    * 
    */
    enum class PT100ConversionMode {
        PT100_CONVERSION_OFF = (0x00U << 6),
        PT100_CONVERSION_AUTO = (0x01U << 6),
    };

    //Utility constant expressions to ease use of enum class of PT100ConversionMode
    static constexpr PT100ConversionMode PT100_CONVERSION_OFF = PT100ConversionMode::PT100_CONVERSION_OFF;
    static constexpr PT100ConversionMode PT100_CONVERSION_AUTO = PT100ConversionMode::PT100_CONVERSION_AUTO;

    /**
    * @brief PT100 Vbias
    * 
    */
    enum class PT100Vbias {
        PT100_VBIAS_OFF = (0x00U << 7),
        PT100_VBIAS_ON = (0x01U << 7),
    };

    //Utility constant expressions to ease use of enum class of PT100Vbias
    static constexpr PT100Vbias PT100_VBIAS_OFF = PT100Vbias::PT100_VBIAS_OFF;
    static constexpr PT100Vbias PT100_VBIAS_ON = PT100Vbias::PT100_VBIAS_ON;
}

