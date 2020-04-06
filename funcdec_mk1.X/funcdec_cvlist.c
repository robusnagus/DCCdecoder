//
// DCC function decoder
//
// Copyright 2020 Robert Nagowski
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// See gpl-3.0.md file for details.
//

#include <avr/io.h>
#include <avr/eeprom.h>

#include "funcdec_cvlist.h"

void CV_RestoreDefault(uint8_t *config);
uint8_t CV_validate(uint8_t cv, uint8_t value);

const uint8_t defaultConfig[CFG_DCCD_CVMAX] = {
    // 1
    CVDEF_DecAddr, 0xFF, 0xFF, 0xFF,
    // 5
    0xFF, 0xFF, CVDEF_Version, CVDEF_ManfID,
    // 9
    0xFF, 0xFF, 0xFF, 0xFF,
    // 13
    0xFF, 0xFF, 0xFF, 0xFF,
    // 17
    CVDEF_DecAddrH, CVDEF_DecAddrL, 0xFF, 0xFF,
    // 21
    0xFF, 0xFF, 0xFF, 0xFF,
    // 25
    0xFF, 0xFF, 0xFF, 0xFF,
    // 29
    CVDEF_Config, 0xFF, 0xFF, 0xFF,
    // 33
    CVDEF_FuncMap_A1, CVDEF_FuncMap_A2, CVDEF_FuncMap_B1, CVDEF_FuncMap_B2,
    // 37
    CVDEF_FuncMap_C1, CVDEF_FuncMap_C2, CVDEF_FuncMap_D1, CVDEF_FuncMap_D2,
    // 41
    CVDEF_FuncMap_E1, CVDEF_FuncMap_E2, CVDEF_FuncMap_F1, CVDEF_FuncMap_F2,
    // 45
    CVDEF_Deactiv_F1, CVDEF_Deactiv_F2, CVDEF_Deactiv_R1, CVDEF_Deactiv_R2,
    // 49
    CVDEF_Dim_X, CVDEF_Dim_X, CVDEF_Dim_X, CVDEF_Dim_X,
    // 53
    CVDEF_Dim_X, CVDEF_Dim_X, 0xFF, 0xFF,
    // 57
    0xFF, 0xFF, 0xFF, 0xFF,
    // 61
    0xFF, 0xFF, 0xFF, 0xFF,
    
}; // defaultConfig

// przywrócenie domyślnej konfiguracji
// param: brak
// zwrot: brak
void CV_RestoreDefault(uint8_t *config)
{
    uint8_t idx;
    for (idx = 0; idx < CFG_DCCD_CVMAX; idx++) {
        eeprom_busy_wait();
        eeprom_write_byte(&(config[idx]), defaultConfig[idx]);
    }
    
} // CV_RestoreDefault

// sprawdzenie zawartości CV (użytkownika)
// cv:    cv do sprawdzenia
// value: proponowana wartość
// zwrot: prawidłowo wartość, skorygowana w razie potrzeby
uint8_t CV_validate(uint8_t cv, uint8_t value)
{
    if ((cv >= CV049_Dim_A) && (cv <= CV054_Dim_F)) {
        if (value > 63)
            value = 63;
    }
    
    return value;
    
} // CV_validate

// EOF funcdec_cvlist.c
