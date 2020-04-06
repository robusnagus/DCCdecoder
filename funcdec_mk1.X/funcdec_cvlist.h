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

#ifndef FUNCDEC_CVLIST_H
#define	FUNCDEC_CVLIST_H

#define CFG_DCCD_CVMAX      64

#define CV001_DecAddr       0
#define CV007_Version       6
#define CV008_ManfID        7
#define CV017_DecAddrH      16
#define CV018_DecAddrL      17
#define CV029_Config        28
#define CV033_FuncMap_A1    32
#define CV034_FuncMap_A2    33
#define CV035_FuncMap_B1    34
#define CV036_FuncMap_B2    35
#define CV037_FuncMap_C1    36
#define CV038_FuncMap_C2    37
#define CV039_FuncMap_D1    38
#define CV040_FuncMap_D2    39
#define CV041_FuncMap_E1    40
#define CV042_FuncMap_E2    41
#define CV043_FuncMap_F1    42
#define CV044_FuncMap_F2    43
#define CV045_Deactiv_Fwd1  44
#define CV046_Deactiv_Fwd2  45
#define CV047_Deactiv_Rev1  46
#define CV048_Deactiv_Rev2  47
#define CV049_Dim_A         48
#define CV050_Dim_B         49
#define CV051_Dim_C         50
#define CV052_Dim_D         51
#define CV053_Dim_E         52
#define CV054_Dim_F         53

#define CVDEF_DecAddr       0x03
#define CVDEF_Version       0x02
#define CVDEF_ManfID        0x0D
#define CVDEF_DecAddrH      0xC7
#define CVDEF_DecAddrL      0xD0
#define CVDEF_Config        0x22
#define CVDEF_FuncMap_A1    0x01
#define CVDEF_FuncMap_A2    0x00
#define CVDEF_FuncMap_B1    0x01
#define CVDEF_FuncMap_B2    0x00
#define CVDEF_FuncMap_C1    0x02
#define CVDEF_FuncMap_C2    0x00
#define CVDEF_FuncMap_D1    0x04
#define CVDEF_FuncMap_D2    0x00
#define CVDEF_FuncMap_E1    0x08
#define CVDEF_FuncMap_E2    0x00
#define CVDEF_FuncMap_F1    0x10
#define CVDEF_FuncMap_F2    0x00
#define CVDEF_Deactiv_F1    0x01
#define CVDEF_Deactiv_F2    0x00
#define CVDEF_Deactiv_R1    0x20
#define CVDEF_Deactiv_R2    0x00
#define CVDEF_Dim_X         0x3F

#endif	// FUNCDEC_CVLIST_H
