//
// Project: DCC decoder proto M3208
// File:    dec08_cvman.h
// Author:  Nagus
// Version: 20200115
//

#ifndef DEC08_CVMAN_H
#define	DEC08_CVMAN_H

#define CFG_DCCD_CVMAX      64

#define DECCFG_DIRREV       0x01
#define DECCFG_FLFUNCG      0x02
#define DECCFG_BIDICOM      0x08
#define DECCFG_LONGADDR     0x20
#define DECCFG_MASK         0x2B

#define CV001_DecAddr       0
#define CV007_Version       6
#define CV008_ManfID        7
#define CV017_DecAddrH      16
#define CV018_DecAddrL      17
#define CV029_Config        28
#define CV033_FMapComp1     32
#define CV034_FMapComp2     33
#define CV035_FMapAisle1    34
#define CV036_FMapAisle2    35
#define CV037_FMapToil1     36
#define CV038_FMapToil2     37
#define CV039_FMapTrEnd1    38
#define CV040_FMapTrEnd2    39
#define CV041_FCompRand1    40
#define CV042_FCompRand2    41
#define CV047_DimComp       46
#define CV048_DimAisle      47
#define CV049_DimToil       48
#define CV050_DimTrEnd      49

#define DEF_DecAddr         0x03
#define DEF_Version         0x02
#define DEF_ManfID          0x0D
#define DEF_DecAddrH        0xC7
#define DEF_DecAddrL        0xD0
#define DEF_Config          0x20
#define DEF_FMapComp1       0x00
#define DEF_FMapComp2       0x00
#define DEF_FMapAisle1      0x00
#define DEF_FMapAisle2      0x00
#define DEF_FMapToil1       0x00
#define DEF_FMapToil2       0x00
#define DEF_FMapTrEnd1      0x00
#define DEF_FMapTrEnd2      0x00
#define DEF_FCompRand1      0x00
#define DEF_FCompRand2      0x00
#define DEF_DimComp         0x10
#define DEF_DimAisle        0x30
#define DEF_DimToil         0x50
#define DEF_DimTrEnd        0x70

void    CV_RestoreDefault(void);
uint8_t CV_GetValue(uint8_t cv);
void    CV_SetValue(uint8_t cv, uint8_t value);

#endif	// DEC08_CVMAN_H
