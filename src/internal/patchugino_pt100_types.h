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
    static constexpr PT100Type PT100_3WIRE = PT100Type::PT100_2WIRE;
    static constexpr PT100Type PT100_4WIRE = PT100Type::PT100_2WIRE;

    typedef struct {
        bool is3Wire;
        uint32_t configReg;
    }PT100ConfigStruct;
}

