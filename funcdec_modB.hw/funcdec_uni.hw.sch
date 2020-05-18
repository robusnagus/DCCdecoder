EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "DCC function decoder"
Date ""
Rev "1"
Comp "Nagus"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:D_Schottky_ALT D4
U 1 1 5E8B5E38
P 1750 3300
F 0 "D4" H 1800 3400 50  0000 R CNN
F 1 "PMEG4010" H 2050 3200 50  0000 R CNN
F 2 "NGS Elements SMD:SOD323_HS" H 1750 3300 50  0001 C CNN
F 3 "~" H 1750 3300 50  0001 C CNN
	1    1750 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky_ALT D3
U 1 1 5E8B6CEF
P 1750 3000
F 0 "D3" H 1750 3100 50  0000 C CNN
F 1 "PMEG4010" H 1750 2900 50  0000 C CNN
F 2 "NGS Elements SMD:SOD323_HS" H 1750 3000 50  0001 C CNN
F 3 "~" H 1750 3000 50  0001 C CNN
	1    1750 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky_ALT D1
U 1 1 5E8B7744
P 1750 2400
F 0 "D1" H 1750 2500 50  0000 C CNN
F 1 "PMEG4010" H 1750 2300 50  0000 C CNN
F 2 "NGS Elements SMD:SOD323_HS" H 1750 2400 50  0001 C CNN
F 3 "~" H 1750 2400 50  0001 C CNN
	1    1750 2400
	-1   0    0    1   
$EndComp
$Comp
L Device:D_Schottky_ALT D2
U 1 1 5E8B7AE1
P 1750 2700
F 0 "D2" H 1750 2800 50  0000 C CNN
F 1 "PMEG4010" H 1750 2600 50  0000 C CNN
F 2 "NGS Elements SMD:SOD323_HS" H 1750 2700 50  0001 C CNN
F 3 "~" H 1750 2700 50  0001 C CNN
	1    1750 2700
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 5E8B8DC6
P 2550 2700
F 0 "R2" V 2450 2650 50  0000 L CNN
F 1 "150R" V 2650 2600 50  0000 L CNN
F 2 "NGS Elements SMD:SMD_1206_HS" V 2480 2700 50  0001 C CNN
F 3 "~" H 2550 2700 50  0001 C CNN
	1    2550 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5E8B91A1
P 2600 3950
F 0 "R3" V 2500 3900 50  0000 L CNN
F 1 "15k" V 2700 3900 50  0000 L CNN
F 2 "NGS Elements SMD:SMD_0805_HS" V 2530 3950 50  0001 C CNN
F 3 "~" H 2600 3950 50  0001 C CNN
	1    2600 3950
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J1
U 1 1 5E8BAFB0
P 1000 2400
F 0 "J1" H 950 2300 50  0000 L CNN
F 1 "Track2" V 1100 2300 50  0000 L CNN
F 2 "NGS_Connectors_SMD:Array_1-27mm_1X1_SMD" H 1000 2400 50  0001 C CNN
F 3 "~" H 1000 2400 50  0001 C CNN
	1    1000 2400
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 J2
U 1 1 5E8BB639
P 1000 2700
F 0 "J2" H 950 2600 50  0000 L CNN
F 1 "Track1" V 1100 2600 50  0000 L CNN
F 2 "NGS_Connectors_SMD:Array_1-27mm_1X1_SMD" H 1000 2700 50  0001 C CNN
F 3 "~" H 1000 2700 50  0001 C CNN
	1    1000 2700
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x07 J4
U 1 1 5E8BBD46
P 8850 1450
F 0 "J4" H 8800 1850 50  0000 L CNN
F 1 "Functions" V 8950 1250 50  0000 L CNN
F 2 "NGS_Connectors_SMD:Array_1-50mm_1X7_SMD" H 8850 1450 50  0001 C CNN
F 3 "~" H 8850 1450 50  0001 C CNN
	1    8850 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_DUAL_NMOS_G1S2G2D2S1D1 Q2
U 2 1 5E8BDC49
P 6300 1950
F 0 "Q2" H 6150 2100 50  0000 L CNN
F 1 "AP2626" V 6550 1800 50  0000 L CNN
F 2 "NGS Elements SMD:SOT23-6_HS" H 6500 1950 50  0001 C CNN
F 3 "~" H 6500 1950 50  0001 C CNN
	2    6300 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_DUAL_NMOS_G1S2G2D2S1D1 Q2
U 1 1 5E8BEB0D
P 6300 2750
F 0 "Q2" H 6150 2900 50  0000 L CNN
F 1 "AP2626" V 6550 2600 50  0000 L CNN
F 2 "NGS Elements SMD:SOT23-6_HS" H 6500 2750 50  0001 C CNN
F 3 "~" H 6500 2750 50  0001 C CNN
	1    6300 2750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 5E8C0B41
P 4900 5000
F 0 "J3" H 4850 5200 50  0000 L CNN
F 1 "PROG" V 5000 4900 50  0000 L CNN
F 2 "NGS_Connectors_SMD:Array_1-27mm_1X3_SMD" H 4900 5000 50  0001 C CNN
F 3 "~" H 4900 5000 50  0001 C CNN
	1    4900 5000
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5E8C5516
P 5900 2200
F 0 "R5" H 5830 2154 50  0000 R CNN
F 1 "100R" H 5830 2245 50  0000 R CNN
F 2 "NGS Elements SMD:SMD_0805_HS" V 5830 2200 50  0001 C CNN
F 3 "~" H 5900 2200 50  0001 C CNN
	1    5900 2200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 5E8C5DC8
P 6000 3000
F 0 "R6" H 5930 2954 50  0000 R CNN
F 1 "100R" H 5930 3045 50  0000 R CNN
F 2 "NGS Elements SMD:SMD_0805_HS" V 5930 3000 50  0001 C CNN
F 3 "~" H 6000 3000 50  0001 C CNN
	1    6000 3000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5E8C62B4
P 6400 2200
F 0 "#PWR015" H 6400 1950 50  0001 C CNN
F 1 "GND" H 6405 2027 50  0000 C CNN
F 2 "" H 6400 2200 50  0001 C CNN
F 3 "" H 6400 2200 50  0001 C CNN
	1    6400 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5E8C6715
P 6400 3000
F 0 "#PWR016" H 6400 2750 50  0001 C CNN
F 1 "GND" H 6405 2827 50  0000 C CNN
F 2 "" H 6400 3000 50  0001 C CNN
F 3 "" H 6400 3000 50  0001 C CNN
	1    6400 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_DUAL_NMOS_G1S2G2D2S1D1 Q3
U 2 1 5E8DECFD
P 7200 1950
F 0 "Q3" H 7050 2100 50  0000 L CNN
F 1 "AP2626" V 7450 1800 50  0000 L CNN
F 2 "NGS Elements SMD:SOT23-6_HS" H 7400 1950 50  0001 C CNN
F 3 "~" H 7400 1950 50  0001 C CNN
	2    7200 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_DUAL_NMOS_G1S2G2D2S1D1 Q3
U 1 1 5E8DED07
P 7200 2750
F 0 "Q3" H 7050 2900 50  0000 L CNN
F 1 "AP2626" V 7450 2600 50  0000 L CNN
F 2 "NGS Elements SMD:SOT23-6_HS" H 7400 2750 50  0001 C CNN
F 3 "~" H 7400 2750 50  0001 C CNN
	1    7200 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R7
U 1 1 5E8DED11
P 6800 2200
F 0 "R7" H 6730 2154 50  0000 R CNN
F 1 "100R" H 6730 2245 50  0000 R CNN
F 2 "NGS Elements SMD:SMD_0805_HS" V 6730 2200 50  0001 C CNN
F 3 "~" H 6800 2200 50  0001 C CNN
	1    6800 2200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R8
U 1 1 5E8DED1B
P 6900 3000
F 0 "R8" H 6830 2954 50  0000 R CNN
F 1 "100R" H 6830 3045 50  0000 R CNN
F 2 "NGS Elements SMD:SMD_0805_HS" V 6830 3000 50  0001 C CNN
F 3 "~" H 6900 3000 50  0001 C CNN
	1    6900 3000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5E8DED25
P 7300 2200
F 0 "#PWR017" H 7300 1950 50  0001 C CNN
F 1 "GND" H 7305 2027 50  0000 C CNN
F 2 "" H 7300 2200 50  0001 C CNN
F 3 "" H 7300 2200 50  0001 C CNN
	1    7300 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 5E8DED2F
P 7300 3000
F 0 "#PWR018" H 7300 2750 50  0001 C CNN
F 1 "GND" H 7305 2827 50  0000 C CNN
F 2 "" H 7300 3000 50  0001 C CNN
F 3 "" H 7300 3000 50  0001 C CNN
	1    7300 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_DUAL_NMOS_G1S2G2D2S1D1 Q4
U 2 1 5E8E6383
P 8100 1950
F 0 "Q4" H 7950 2100 50  0000 L CNN
F 1 "AP2626" V 8350 1800 50  0000 L CNN
F 2 "NGS Elements SMD:SOT23-6_HS" H 8300 1950 50  0001 C CNN
F 3 "~" H 8300 1950 50  0001 C CNN
	2    8100 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_DUAL_NMOS_G1S2G2D2S1D1 Q4
U 1 1 5E8E638D
P 8100 2750
F 0 "Q4" H 7950 2900 50  0000 L CNN
F 1 "AP2626" V 8350 2600 50  0000 L CNN
F 2 "NGS Elements SMD:SOT23-6_HS" H 8300 2750 50  0001 C CNN
F 3 "~" H 8300 2750 50  0001 C CNN
	1    8100 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5E8E6397
P 7700 2200
F 0 "R9" H 7630 2154 50  0000 R CNN
F 1 "100R" H 7630 2245 50  0000 R CNN
F 2 "NGS Elements SMD:SMD_0805_HS" V 7630 2200 50  0001 C CNN
F 3 "~" H 7700 2200 50  0001 C CNN
	1    7700 2200
	-1   0    0    1   
$EndComp
$Comp
L Device:R R10
U 1 1 5E8E63A1
P 7800 3000
F 0 "R10" H 7870 3046 50  0000 L CNN
F 1 "100R" H 7870 2955 50  0000 L CNN
F 2 "NGS Elements SMD:SMD_0805_HS" V 7730 3000 50  0001 C CNN
F 3 "~" H 7800 3000 50  0001 C CNN
	1    7800 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5E8E63AB
P 8200 2200
F 0 "#PWR019" H 8200 1950 50  0001 C CNN
F 1 "GND" H 8205 2027 50  0000 C CNN
F 2 "" H 8200 2200 50  0001 C CNN
F 3 "" H 8200 2200 50  0001 C CNN
	1    8200 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5E8E63B5
P 8200 3000
F 0 "#PWR020" H 8200 2750 50  0001 C CNN
F 1 "GND" H 8205 2827 50  0000 C CNN
F 2 "" H 8200 3000 50  0001 C CNN
F 3 "" H 8200 3000 50  0001 C CNN
	1    8200 3000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5E8C6819
P 5350 5350
F 0 "#PWR014" H 5350 5100 50  0001 C CNN
F 1 "GND" H 5355 5177 50  0000 C CNN
F 2 "" H 5350 5350 50  0001 C CNN
F 3 "" H 5350 5350 50  0001 C CNN
	1    5350 5350
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR013
U 1 1 5E8C7777
P 5200 4750
F 0 "#PWR013" H 5200 4600 50  0001 C CNN
F 1 "VCC" H 5217 4923 50  0000 C CNN
F 2 "" H 5200 4750 50  0001 C CNN
F 3 "" H 5200 4750 50  0001 C CNN
	1    5200 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5E8E8AB4
P 4250 6800
F 0 "#PWR010" H 4250 6550 50  0001 C CNN
F 1 "GND" H 4255 6627 50  0000 C CNN
F 2 "" H 4250 6800 50  0001 C CNN
F 3 "" H 4250 6800 50  0001 C CNN
	1    4250 6800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5E8ED382
P 5600 5100
F 0 "C3" H 5715 5146 50  0000 L CNN
F 1 "100n" H 5715 5055 50  0000 L CNN
F 2 "NGS Elements SMD:SMD_0805_HS" H 5638 4950 50  0001 C CNN
F 3 "~" H 5600 5100 50  0001 C CNN
	1    5600 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5E8ED846
P 5600 5350
F 0 "#PWR08" H 5600 5100 50  0001 C CNN
F 1 "GND" H 5605 5177 50  0000 C CNN
F 2 "" H 5600 5350 50  0001 C CNN
F 3 "" H 5600 5350 50  0001 C CNN
	1    5600 5350
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR07
U 1 1 5E8EDE39
P 5600 4750
F 0 "#PWR07" H 5600 4600 50  0001 C CNN
F 1 "VCC" H 5617 4923 50  0000 C CNN
F 2 "" H 5600 4750 50  0001 C CNN
F 3 "" H 5600 4750 50  0001 C CNN
	1    5600 4750
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR011
U 1 1 5E8EF845
P 4250 5200
F 0 "#PWR011" H 4250 5050 50  0001 C CNN
F 1 "VCC" H 4267 5373 50  0000 C CNN
F 2 "" H 4250 5200 50  0001 C CNN
F 3 "" H 4250 5200 50  0001 C CNN
	1    4250 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 2150 6400 2200
Wire Wire Line
	7300 2150 7300 2200
Wire Wire Line
	8200 2150 8200 2200
Wire Wire Line
	8200 2950 8200 3000
Wire Wire Line
	7300 2950 7300 3000
Wire Wire Line
	6400 2950 6400 3000
Wire Wire Line
	8650 1650 8200 1650
Wire Wire Line
	8200 1650 8200 1750
Wire Wire Line
	8200 2550 8200 2450
Wire Wire Line
	8200 2450 8550 2450
Wire Wire Line
	8550 2450 8550 1750
Wire Wire Line
	8550 1750 8650 1750
Wire Wire Line
	7700 2050 7700 1950
Wire Wire Line
	7700 1950 7900 1950
Wire Wire Line
	7800 2850 7800 2750
Wire Wire Line
	7800 2750 7900 2750
Wire Wire Line
	6900 2850 6900 2750
Wire Wire Line
	6900 2750 7000 2750
Wire Wire Line
	6800 2050 6800 1950
Wire Wire Line
	6800 1950 7000 1950
Wire Wire Line
	5900 2050 5900 1950
Wire Wire Line
	5900 1950 6100 1950
Wire Wire Line
	6000 2850 6000 2750
Wire Wire Line
	6000 2750 6100 2750
Wire Wire Line
	8650 1450 7300 1450
Wire Wire Line
	7300 1450 7300 1750
Wire Wire Line
	7300 2550 7300 2450
Wire Wire Line
	7300 2450 7550 2450
Wire Wire Line
	7550 2450 7550 1550
Wire Wire Line
	7550 1550 8650 1550
Wire Wire Line
	8650 1250 6400 1250
Wire Wire Line
	6400 1250 6400 1750
Wire Wire Line
	6400 2550 6400 2450
Wire Wire Line
	6400 2450 6700 2450
Wire Wire Line
	6700 2450 6700 1350
Wire Wire Line
	6700 1350 8650 1350
Wire Wire Line
	5100 4900 5200 4900
Wire Wire Line
	5200 4900 5200 4750
Wire Wire Line
	5100 5000 5350 5000
Wire Wire Line
	5350 5000 5350 5350
Wire Wire Line
	5600 5250 5600 5350
Wire Wire Line
	5200 5600 5200 5100
Wire Wire Line
	5200 5100 5100 5100
Wire Wire Line
	1900 2400 2000 2400
Wire Wire Line
	2000 2400 2000 2700
Wire Wire Line
	2000 2700 1900 2700
Wire Wire Line
	1900 3000 2000 3000
Wire Wire Line
	2000 3000 2000 3300
Wire Wire Line
	2000 3300 1900 3300
Wire Wire Line
	1600 3000 1500 3000
Wire Wire Line
	1500 3000 1500 2400
Wire Wire Line
	1500 2400 1600 2400
Wire Wire Line
	1600 2700 1400 2700
Wire Wire Line
	1400 2700 1400 3300
Wire Wire Line
	1400 3300 1600 3300
Wire Wire Line
	1200 2700 1400 2700
Connection ~ 1400 2700
Wire Wire Line
	1200 2400 1500 2400
Connection ~ 1500 2400
$Comp
L Regulator_Linear:AP2204K-5.0 U1
U 1 1 5E92D958
P 4300 2800
F 0 "U1" H 4300 3142 50  0000 C CNN
F 1 "AP2204K-5.0" H 4300 3051 50  0000 C CNN
F 2 "NGS Elements SMD:SOT23-5_HS" H 4300 3125 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/AP2204.pdf" H 4300 2900 50  0001 C CNN
	1    4300 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5E92EAF1
P 3700 2950
F 0 "C1" H 3585 2904 50  0000 R CNN
F 1 "10u" H 3585 2995 50  0000 R CNN
F 2 "NGS Elements SMD:SMD_1206_HS" H 3738 2800 50  0001 C CNN
F 3 "~" H 3700 2950 50  0001 C CNN
	1    3700 2950
	-1   0    0    1   
$EndComp
$Comp
L Device:C C2
U 1 1 5E92F351
P 4800 2950
F 0 "C2" H 4915 2996 50  0000 L CNN
F 1 "22u" H 4915 2905 50  0000 L CNN
F 2 "NGS Elements SMD:SMD_1206_HS" H 4838 2800 50  0001 C CNN
F 3 "~" H 4800 2950 50  0001 C CNN
	1    4800 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5E930CD3
P 3700 3200
F 0 "#PWR02" H 3700 2950 50  0001 C CNN
F 1 "GND" H 3705 3027 50  0000 C CNN
F 2 "" H 3700 3200 50  0001 C CNN
F 3 "" H 3700 3200 50  0001 C CNN
	1    3700 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5E931331
P 4300 3200
F 0 "#PWR03" H 4300 2950 50  0001 C CNN
F 1 "GND" H 4305 3027 50  0000 C CNN
F 2 "" H 4300 3200 50  0001 C CNN
F 3 "" H 4300 3200 50  0001 C CNN
	1    4300 3200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5E93166A
P 4800 3200
F 0 "#PWR04" H 4800 2950 50  0001 C CNN
F 1 "GND" H 4805 3027 50  0000 C CNN
F 2 "" H 4800 3200 50  0001 C CNN
F 3 "" H 4800 3200 50  0001 C CNN
	1    4800 3200
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR05
U 1 1 5E931E8E
P 4900 2600
F 0 "#PWR05" H 4900 2450 50  0001 C CNN
F 1 "VCC" H 4917 2773 50  0000 C CNN
F 2 "" H 4900 2600 50  0001 C CNN
F 3 "" H 4900 2600 50  0001 C CNN
	1    4900 2600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5E8DDB2D
P 2000 3450
F 0 "#PWR01" H 2000 3200 50  0001 C CNN
F 1 "GND" H 2005 3277 50  0000 C CNN
F 2 "" H 2000 3450 50  0001 C CNN
F 3 "" H 2000 3450 50  0001 C CNN
	1    2000 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 3300 2000 3450
Connection ~ 2000 3300
Wire Wire Line
	3700 3100 3700 3200
Wire Wire Line
	4000 2800 3900 2800
Wire Wire Line
	3900 2800 3900 2700
Wire Wire Line
	3900 2700 4000 2700
Wire Wire Line
	3700 2800 3700 2700
Wire Wire Line
	3700 2700 3900 2700
Connection ~ 3900 2700
Wire Wire Line
	4300 3100 4300 3200
Wire Wire Line
	4600 2700 4800 2700
Wire Wire Line
	4800 2700 4800 2800
Wire Wire Line
	4800 3100 4800 3200
Wire Wire Line
	4800 2700 4900 2700
Wire Wire Line
	4900 2700 4900 2600
Connection ~ 4800 2700
Wire Wire Line
	1400 3950 1400 3300
Connection ~ 1400 3300
$Comp
L power:GND #PWR06
U 1 1 5E9C2454
P 2550 3450
F 0 "#PWR06" H 2550 3200 50  0001 C CNN
F 1 "GND" H 2555 3277 50  0000 C CNN
F 2 "" H 2550 3450 50  0001 C CNN
F 3 "" H 2550 3450 50  0001 C CNN
	1    2550 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5E9C2ACB
P 2950 3500
F 0 "R4" H 3020 3546 50  0000 L CNN
F 1 "10k" H 3020 3455 50  0000 L CNN
F 2 "NGS Elements SMD:SMD_0805_HS" V 2880 3500 50  0001 C CNN
F 3 "~" H 2950 3500 50  0001 C CNN
	1    2950 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 2850 2550 2950
Wire Wire Line
	2550 3350 2550 3450
Wire Wire Line
	2850 3150 2950 3150
Wire Wire Line
	2950 3150 2950 3350
$Comp
L Device:R R1
U 1 1 5E924EB7
P 3400 2400
F 0 "R1" V 3193 2400 50  0000 C CNN
F 1 "82R" V 3284 2400 50  0000 C CNN
F 2 "NGS Elements SMD:SMD_1206_HS" V 3330 2400 50  0001 C CNN
F 3 "~" H 3400 2400 50  0001 C CNN
	1    3400 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	2000 2400 2000 1150
Connection ~ 2000 2400
Wire Wire Line
	2000 2400 2550 2400
Wire Wire Line
	3550 2400 3700 2400
Wire Wire Line
	3700 2400 3700 2700
Connection ~ 3700 2700
$Comp
L MCU_Microchip_ATtiny:ATtiny1614-SS U2
U 1 1 5E96765C
P 4250 6000
F 0 "U2" H 4500 6650 50  0000 C CNN
F 1 "ATtiny1614-SS" H 4600 5350 50  0000 C CNN
F 2 "NGS Elements SMD:SOIC14_HS" H 4250 6000 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATtiny1614-data-sheet-40001995A.pdf" H 4250 6000 50  0001 C CNN
	1    4250 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4750 5600 4950
Wire Wire Line
	4250 6800 4250 6700
Wire Wire Line
	4250 5300 4250 5200
Wire Wire Line
	1400 3950 2450 3950
Wire Wire Line
	6000 3150 6000 3250
Wire Wire Line
	6000 3250 5700 3250
Wire Wire Line
	5900 2350 5900 3150
Wire Wire Line
	5900 3150 5700 3150
Wire Wire Line
	6800 2350 6800 3350
Wire Wire Line
	6800 3350 5700 3350
Wire Wire Line
	6900 3150 6900 3450
Wire Wire Line
	6900 3450 5700 3450
Wire Wire Line
	7700 2350 7700 3550
Wire Wire Line
	7700 3550 5700 3550
Wire Wire Line
	7800 3150 7800 3650
Wire Wire Line
	7800 3650 5700 3650
Text Label 5700 3150 2    50   ~ 0
OUT1
Text Label 5700 3250 2    50   ~ 0
OUT2
Text Label 5700 3350 2    50   ~ 0
OUT3
Text Label 5700 3450 2    50   ~ 0
OUT4
Text Label 5700 3550 2    50   ~ 0
OUT5
Text Label 5700 3650 2    50   ~ 0
OUT6
Wire Wire Line
	2000 1150 8650 1150
Wire Wire Line
	2550 2550 2550 2400
Connection ~ 2550 2400
Wire Wire Line
	2550 2400 3250 2400
Wire Wire Line
	2950 3650 2950 3850
Wire Wire Line
	5200 5600 4850 5600
Text Label 3450 5800 2    50   ~ 0
OUT1
Text Label 5050 6100 0    50   ~ 0
OUT2
Wire Wire Line
	4850 6000 5050 6000
Wire Wire Line
	5050 6100 4850 6100
Text Label 5050 6000 0    50   ~ 0
OUT3
Text Label 5050 5900 0    50   ~ 0
OUT4
Text Label 3450 5700 2    50   ~ 0
OUT5
Text Label 3450 5600 2    50   ~ 0
OUT6
Wire Wire Line
	3450 5600 3650 5600
Wire Wire Line
	3650 5700 3450 5700
Wire Wire Line
	3650 5800 3450 5800
Wire Wire Line
	4850 5900 5050 5900
Wire Wire Line
	2950 3850 3250 3850
Wire Wire Line
	2750 3950 3250 3950
Text Label 3250 3950 0    50   ~ 0
DCC
Text Label 3250 3850 0    50   ~ 0
ACK
Text Label 5050 5700 0    50   ~ 0
DCC
Text Label 5050 6200 0    50   ~ 0
ACK
Wire Wire Line
	4850 6200 5050 6200
Wire Wire Line
	5050 5700 4850 5700
$Comp
L Device:Q_NPN_BEC Q1
U 1 1 5EC2F346
P 2650 3150
F 0 "Q1" H 2841 3196 50  0000 L CNN
F 1 "BC847" H 2841 3105 50  0000 L CNN
F 2 "NGS Elements SMD:SOT23_HS" H 2850 3250 50  0001 C CNN
F 3 "~" H 2650 3150 50  0001 C CNN
	1    2650 3150
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
