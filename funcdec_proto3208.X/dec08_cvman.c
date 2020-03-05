//
// Project: DCC decoder proto M3208
// File:    dec08_cvman.c
// Author:  Nagus
// Version: 20200118
//

#include <avr/eeprom.h>

#include "dec08_board.h"
#include "dec08_cvman.h"

extern uint8_t decAddr;
extern uint8_t decAddrH;
extern uint8_t decAddrL;
extern uint8_t decConf;

const uint8_t defaultConfig[] = {
    // 1
    DEF_DecAddr, 0xFF, 0xFF, 0xFF,
    // 5
    0xFF, 0xFF, DEF_Version, DEF_ManfID,
    // 9
    0xFF, 0xFF, 0xFF, 0xFF,
    // 13
    0xFF, 0xFF, 0xFF, 0xFF,
    // 17
    DEF_DecAddrH, DEF_DecAddrL, 0xFF, 0xFF,
    // 21
    0xFF, 0xFF, 0xFF, 0xFF,
    // 25
    0xFF, 0xFF, 0xFF, 0xFF,
    // 29
    DEF_Config, 0xFF, 0xFF, 0xFF,
    // 33
    DEF_FMapComp1, DEF_FMapComp2, DEF_FMapAisle1, DEF_FMapAisle2,
    // 37
    DEF_FMapToil1, DEF_FMapToil2, DEF_FMapTrEnd1, DEF_FMapTrEnd2,
    // 41
    DEF_FCompRand1, DEF_FCompRand2, 0xFF, 0xFF,
    // 45
    0xFF, 0xFF, DEF_DimComp, DEF_DimAisle,
    // 49
    DEF_DimToil, DEF_DimTrEnd, 0xFF, 0xFF,
    // 53
    0xFF, 0xFF, 0xFF, 0xFF,
    // 57
    0xFF, 0xFF, 0xFF, 0xFF,
    // 61
    0xFF, 0xFF, 0xFF, 0xFF,
    
}; // defaultConfig

uint8_t decConfig[CFG_DCCD_CVMAX] EEMEM;

void CV_RestoreDefault(void)
{   
    uint8_t idx;
    for (idx = 0; idx < CFG_DCCD_CVMAX; idx++) {
        eeprom_busy_wait();
        eeprom_write_byte(&(decConfig[idx]), defaultConfig[idx]);
    }
    decAddr  = DEF_DecAddr;
    decAddrH = DEF_DecAddrH;
    decAddrL = DEF_DecAddrL;
    decConf  = DEF_Config;

} // CV_RestoreDefault

uint8_t CV_GetValue(uint8_t cv)
{
    if (cv < CFG_DCCD_CVMAX) {
        eeprom_busy_wait();
        return eeprom_read_byte(&(decConfig[cv]));
    }   
    return 0;
    
} // CV_GetValue

void CV_SetValue(uint8_t cv, uint8_t value)
{
    if (cv >= CFG_DCCD_CVMAX) {
        return;
    }
        
    // sprawdzenie zawartości
    switch (cv) {
        case CV001_DecAddr:
            if ((value < 1) || (value > 127))
                value = DEF_DecAddr;
            decAddr = value;
            break;
        case CV007_Version:
            return;
        case CV008_ManfID:
            if (value == 32)
                CV_RestoreDefault();
            return;
        case CV017_DecAddrH:
            if ((value < 192) && (value > 232))
                value = DEF_DecAddrH;
            decAddrH = value;
            break;
        case CV018_DecAddrL:
            decAddrL = value;
            break;
        case CV029_Config:
            value = value & DECCFG_MASK;
            decConf = value;
            break;
        case CV047_DimComp:
            if ((value > 63) || (value == 0))
                value = 63;
            break;
        case CV048_DimAisle:
            if ((value > 63) || (value == 0))
                value = 63;
            break;
        case CV049_DimToil:
            if ((value > 63) || (value == 0))
                value = 63;
            break;
        case CV050_DimTrEnd:
            if ((value > 63) || (value == 0))
                value = 63;
            break;
        default: // nie podlega weryfikacji
            break;
    } // switch cv
    
    eeprom_busy_wait();
    eeprom_write_byte(&(decConfig[cv]), value);
    
} // CV_SetValue

// EOF dec08_cvman.c
