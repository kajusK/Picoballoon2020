EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "Power supply"
Date "2020-01-13"
Rev "0.2"
Comp "Deadbadger.cz"
Comment1 "Optional boost between solar and supercap for low-light conditions"
Comment2 "2.7 V enable circuit with latch to start second 3v3 boost regulator"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Regulator_Switching:MCP1640CH U8
U 1 1 5E166A45
P 9600 4000
F 0 "U8" H 9600 4467 50  0000 C CNN
F 1 "MCP1640" H 9600 4376 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 9650 3750 50  0001 L CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20002234D.pdf" H 9350 4450 50  0001 C CNN
	1    9600 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:L L3
U 1 1 5E166A4B
P 9600 3450
F 0 "L3" V 9790 3450 50  0000 C CNN
F 1 "SRN2510F-4R7M" V 9699 3450 50  0000 C CNN
F 2 "Inductor_SMD:L_Abracon_ASPI-3012S" H 9600 3450 50  0001 C CNN
F 3 "~" H 9600 3450 50  0001 C CNN
	1    9600 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9750 3450 10050 3450
Wire Wire Line
	10050 3450 10050 3800
Wire Wire Line
	10050 3800 10000 3800
Wire Wire Line
	9450 3450 9150 3450
Wire Wire Line
	9150 3450 9150 3700
Wire Wire Line
	9150 3800 9200 3800
$Comp
L Device:R R19
U 1 1 5E166A57
P 10150 4100
F 0 "R19" H 10220 4146 50  0000 L CNN
F 1 "680k" H 10220 4055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10080 4100 50  0001 C CNN
F 3 "~" H 10150 4100 50  0001 C CNN
	1    10150 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R20
U 1 1 5E166A5D
P 10150 4500
F 0 "R20" H 10220 4546 50  0000 L CNN
F 1 "390k" H 10220 4455 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10080 4500 50  0001 C CNN
F 3 "~" H 10150 4500 50  0001 C CNN
	1    10150 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 4350 10150 4300
Wire Wire Line
	10150 4300 10050 4300
Wire Wire Line
	10050 4300 10050 4100
Wire Wire Line
	10050 4100 10000 4100
Connection ~ 10150 4300
Wire Wire Line
	10150 4300 10150 4250
Wire Wire Line
	10000 3900 10150 3900
Wire Wire Line
	10150 3900 10150 3950
Wire Wire Line
	10150 4700 10150 4650
$Comp
L power:GND #PWR0133
U 1 1 5E166A6C
P 10150 4750
F 0 "#PWR0133" H 10150 4500 50  0001 C CNN
F 1 "GND" H 10155 4577 50  0000 C CNN
F 2 "" H 10150 4750 50  0001 C CNN
F 3 "" H 10150 4750 50  0001 C CNN
	1    10150 4750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C20
U 1 1 5E166A72
P 10500 4300
F 0 "C20" H 10615 4346 50  0000 L CNN
F 1 "100n" H 10615 4255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10538 4150 50  0001 C CNN
F 3 "~" H 10500 4300 50  0001 C CNN
	1    10500 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C21
U 1 1 5E166A78
P 10950 4300
F 0 "C21" H 11065 4346 50  0000 L CNN
F 1 "10u" H 11065 4255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 10988 4150 50  0001 C CNN
F 3 "~" H 10950 4300 50  0001 C CNN
	1    10950 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 3900 10500 3900
Wire Wire Line
	10950 3900 10950 4150
Connection ~ 10150 3900
Wire Wire Line
	10500 4150 10500 3900
Connection ~ 10500 3900
Wire Wire Line
	10500 3900 10950 3900
Wire Wire Line
	10500 4450 10500 4700
Wire Wire Line
	10500 4700 10150 4700
Connection ~ 10150 4700
Wire Wire Line
	10500 4700 10950 4700
Wire Wire Line
	10950 4700 10950 4450
Connection ~ 10500 4700
Wire Wire Line
	10150 4700 10150 4750
$Comp
L Device:CP C18
U 1 1 5E166A93
P 5150 3850
F 0 "C18" H 5268 3896 50  0000 L CNN
F 1 "3F3/3V" H 5268 3805 50  0000 L CNN
F 2 "OptoDevice:R_LDR_5.2x5.2mm_P3.5mm_Horizontal" H 5188 3700 50  0001 C CNN
F 3 "~" H 5150 3850 50  0001 C CNN
	1    5150 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 3450 8650 3450
Connection ~ 9150 3450
$Comp
L Device:C C19
U 1 1 5E1BFF71
P 8650 3700
F 0 "C19" H 8765 3746 50  0000 L CNN
F 1 "10u" H 8765 3655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8688 3550 50  0001 C CNN
F 3 "~" H 8650 3700 50  0001 C CNN
	1    8650 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 3550 8650 3450
$Comp
L power:GND #PWR0134
U 1 1 5E1C8E42
P 8650 3900
F 0 "#PWR0134" H 8650 3650 50  0001 C CNN
F 1 "GND" H 8655 3727 50  0000 C CNN
F 2 "" H 8650 3900 50  0001 C CNN
F 3 "" H 8650 3900 50  0001 C CNN
	1    8650 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 3900 8650 3850
$Comp
L Regulator_Switching:MCP1640CH U6
U 1 1 5E243BE7
P 2500 3550
F 0 "U6" H 2500 4017 50  0000 C CNN
F 1 "MCP1640" H 2500 3926 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 2550 3300 50  0001 L CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20002234D.pdf" H 2250 4000 50  0001 C CNN
	1    2500 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:L L2
U 1 1 5E243BED
P 2500 3000
F 0 "L2" V 2690 3000 50  0000 C CNN
F 1 "SRN2510F-4R7M" V 2599 3000 50  0000 C CNN
F 2 "Inductor_SMD:L_Abracon_ASPI-3012S" H 2500 3000 50  0001 C CNN
F 3 "~" H 2500 3000 50  0001 C CNN
	1    2500 3000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2650 3000 2950 3000
Wire Wire Line
	2950 3000 2950 3350
Wire Wire Line
	2950 3350 2900 3350
Wire Wire Line
	2350 3000 2050 3000
Wire Wire Line
	2050 3000 2050 3350
Wire Wire Line
	2050 3350 2100 3350
$Comp
L Device:R R?
U 1 1 5E243BF9
P 3200 3650
AR Path="/5E243BF9" Ref="R?"  Part="1" 
AR Path="/5E160485/5E243BF9" Ref="R9"  Part="1" 
F 0 "R9" H 3270 3696 50  0000 L CNN
F 1 "510k" H 3270 3605 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3130 3650 50  0001 C CNN
F 3 "~" H 3200 3650 50  0001 C CNN
	1    3200 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5E243BFF
P 3200 4050
AR Path="/5E243BFF" Ref="R?"  Part="1" 
AR Path="/5E160485/5E243BFF" Ref="R10"  Part="1" 
F 0 "R10" H 3270 4096 50  0000 L CNN
F 1 "360k" H 3270 4005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3130 4050 50  0001 C CNN
F 3 "~" H 3200 4050 50  0001 C CNN
	1    3200 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3900 3200 3850
Wire Wire Line
	3200 3850 2950 3850
Wire Wire Line
	2950 3850 2950 3650
Wire Wire Line
	2950 3650 2900 3650
Connection ~ 3200 3850
Wire Wire Line
	3200 3850 3200 3800
Wire Wire Line
	2900 3450 3200 3450
Wire Wire Line
	3200 3450 3200 3500
Wire Wire Line
	3200 4250 3200 4200
$Comp
L power:GND #PWR0135
U 1 1 5E243C0E
P 3200 4300
F 0 "#PWR0135" H 3200 4050 50  0001 C CNN
F 1 "GND" H 3205 4127 50  0000 C CNN
F 2 "" H 3200 4300 50  0001 C CNN
F 3 "" H 3200 4300 50  0001 C CNN
	1    3200 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C16
U 1 1 5E243C14
P 3550 3850
F 0 "C16" H 3665 3896 50  0000 L CNN
F 1 "100n" H 3665 3805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3588 3700 50  0001 C CNN
F 3 "~" H 3550 3850 50  0001 C CNN
	1    3550 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 3450 3550 3450
Connection ~ 3200 3450
Wire Wire Line
	3550 3700 3550 3450
Wire Wire Line
	3550 4000 3550 4250
Wire Wire Line
	3550 4250 3200 4250
Connection ~ 3200 4250
Wire Wire Line
	3200 4250 3200 4300
$Comp
L Device:D_Schottky D2
U 1 1 5E244FF1
P 4350 3450
F 0 "D2" H 4350 3234 50  0000 C CNN
F 1 "BAT20J" H 4350 3325 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" H 4350 3450 50  0001 C CNN
F 3 "~" H 4350 3450 50  0001 C CNN
	1    4350 3450
	-1   0    0    1   
$EndComp
Wire Wire Line
	900  3350 1000 3350
Connection ~ 2050 3350
Wire Wire Line
	2100 3550 2050 3550
Wire Wire Line
	2050 3550 2050 3350
Connection ~ 1000 3350
$Comp
L power:GND #PWR0136
U 1 1 5E24A567
P 1750 3800
F 0 "#PWR0136" H 1750 3550 50  0001 C CNN
F 1 "GND" H 1755 3627 50  0000 C CNN
F 2 "" H 1750 3800 50  0001 C CNN
F 3 "" H 1750 3800 50  0001 C CNN
	1    1750 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0137
U 1 1 5E24A97A
P 2500 3900
F 0 "#PWR0137" H 2500 3650 50  0001 C CNN
F 1 "GND" H 2505 3727 50  0000 C CNN
F 2 "" H 2500 3900 50  0001 C CNN
F 3 "" H 2500 3900 50  0001 C CNN
	1    2500 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 3900 2500 3850
Wire Wire Line
	5150 3700 5150 3450
Wire Wire Line
	5150 4000 5150 4250
Wire Wire Line
	3550 4250 4000 4250
Connection ~ 3550 4250
Connection ~ 8650 3450
Wire Wire Line
	9200 4000 9150 4000
Wire Wire Line
	7800 4800 7800 4700
Connection ~ 7800 4800
Wire Wire Line
	9150 4000 9150 4100
Wire Wire Line
	7800 4900 7800 4800
$Comp
L Device:R R18
U 1 1 5E285C05
P 7800 5050
F 0 "R18" H 7870 5096 50  0000 L CNN
F 1 "680k" H 7870 5005 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7730 5050 50  0001 C CNN
F 3 "~" H 7800 5050 50  0001 C CNN
	1    7800 5050
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC857 Q2
U 1 1 5E284EE6
P 7700 4500
F 0 "Q2" H 7891 4454 50  0000 L CNN
F 1 "BC857" H 7891 4545 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7900 4425 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC856.pdf" H 7700 4500 50  0001 L CNN
	1    7700 4500
	1    0    0    1   
$EndComp
Connection ~ 7800 3450
Wire Wire Line
	7800 3450 8450 3450
$Comp
L power:GND #PWR0138
U 1 1 5E2A4D3D
P 7800 5250
F 0 "#PWR0138" H 7800 5000 50  0001 C CNN
F 1 "GND" H 7805 5077 50  0000 C CNN
F 2 "" H 7800 5250 50  0001 C CNN
F 3 "" H 7800 5250 50  0001 C CNN
	1    7800 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 5250 7800 5200
$Comp
L Transistor_BJT:BC847 Q1
U 1 1 5E2A6E56
P 7000 4800
F 0 "Q1" H 7191 4846 50  0000 L CNN
F 1 "BC847" H 7191 4755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7200 4725 50  0001 L CIN
F 3 "http://www.infineon.com/dgdl/Infineon-BC847SERIES_BC848SERIES_BC849SERIES_BC850SERIES-DS-v01_01-en.pdf?fileId=db3a304314dca389011541d4630a1657" H 7000 4800 50  0001 L CNN
	1    7000 4800
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R16
U 1 1 5E2B662F
P 7250 4500
F 0 "R16" V 7043 4500 50  0000 C CNN
F 1 "100k" V 7134 4500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7180 4500 50  0001 C CNN
F 3 "~" H 7250 4500 50  0001 C CNN
	1    7250 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	7100 4500 6900 4500
Wire Wire Line
	6900 4500 6900 4600
$Comp
L Device:R R17
U 1 1 5E2BC2FC
P 7500 4800
F 0 "R17" V 7293 4800 50  0000 C CNN
F 1 "100k" V 7384 4800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7430 4800 50  0001 C CNN
F 3 "~" H 7500 4800 50  0001 C CNN
	1    7500 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	7650 4800 7800 4800
Wire Wire Line
	7350 4800 7250 4800
$Comp
L power:GND #PWR0139
U 1 1 5E2C6CBE
P 6900 5100
F 0 "#PWR0139" H 6900 4850 50  0001 C CNN
F 1 "GND" H 6905 4927 50  0000 C CNN
F 2 "" H 6900 5100 50  0001 C CNN
F 3 "" H 6900 5100 50  0001 C CNN
	1    6900 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 5100 6900 5000
Wire Wire Line
	7800 4300 7800 4050
Wire Wire Line
	7500 4500 7400 4500
Wire Wire Line
	6900 4400 6900 4500
Connection ~ 6900 4500
Wire Wire Line
	6900 4100 6900 4050
Wire Wire Line
	6900 4050 7800 4050
Connection ~ 7800 4050
Wire Wire Line
	7800 4050 7800 3450
$Comp
L power:GND #PWR0140
U 1 1 5E2FCDDF
P 9600 4350
F 0 "#PWR0140" H 9600 4100 50  0001 C CNN
F 1 "GND" H 9605 4177 50  0000 C CNN
F 2 "" H 9600 4350 50  0001 C CNN
F 3 "" H 9600 4350 50  0001 C CNN
	1    9600 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 4350 9600 4300
Wire Wire Line
	5150 3450 5700 3450
$Comp
L power:GND #PWR0141
U 1 1 5E193AB3
P 6100 4950
F 0 "#PWR0141" H 6100 4700 50  0001 C CNN
F 1 "GND" H 6105 4777 50  0000 C CNN
F 2 "" H 6100 4950 50  0001 C CNN
F 3 "" H 6100 4950 50  0001 C CNN
	1    6100 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 4950 6100 4900
Wire Wire Line
	6100 4100 6100 3450
Connection ~ 6100 3450
Wire Wire Line
	6100 3450 7800 3450
$Comp
L Power_Supervisor:MCP101-270D U7
U 1 1 5E19846B
P 6200 4500
F 0 "U7" H 5971 4546 50  0000 R CNN
F 1 "MCP101-270D" H 5971 4455 50  0000 R CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5800 4650 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/11187f.pdf" H 5900 4750 50  0001 C CNN
	1    6200 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4500 6900 4500
Wire Wire Line
	6550 4500 6500 4500
Text HLabel 900  3350 0    50   Input ~ 0
Vin
Text HLabel 8650 3050 1    50   Output ~ 0
BAT_VOLT
$Comp
L Device:R R12
U 1 1 5E1E0D33
P 8650 3250
F 0 "R12" H 8720 3296 50  0000 L CNN
F 1 "1M" H 8720 3205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 8580 3250 50  0001 C CNN
F 3 "~" H 8650 3250 50  0001 C CNN
	1    8650 3250
	1    0    0    -1  
$EndComp
Connection ~ 5700 3450
Wire Wire Line
	8650 3100 8650 3050
Wire Wire Line
	1000 3350 1000 3250
Text HLabel 1000 2900 1    50   Output ~ 0
SOLAR_VOLT
Wire Wire Line
	1000 2900 1000 2950
$Comp
L Device:R R8
U 1 1 5E1E7317
P 1000 3100
F 0 "R8" H 1070 3146 50  0000 L CNN
F 1 "1M" H 1070 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 930 3100 50  0001 C CNN
F 3 "~" H 1000 3100 50  0001 C CNN
	1    1000 3100
	1    0    0    -1  
$EndComp
Text HLabel 6800 5600 0    50   Input ~ 0
~LATCH_RESET
$Comp
L Device:R R15
U 1 1 5E1F44C2
P 7000 5600
F 0 "R15" V 6793 5600 50  0000 C CNN
F 1 "10k" V 6884 5600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6930 5600 50  0001 C CNN
F 3 "~" H 7000 5600 50  0001 C CNN
	1    7000 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 5600 6850 5600
Wire Wire Line
	7250 5600 7250 4800
Wire Wire Line
	7150 5600 7250 5600
Connection ~ 7250 4800
Wire Wire Line
	7250 4800 7200 4800
$Comp
L Device:R R14
U 1 1 5E2E2C2C
P 6900 4250
F 0 "R14" H 6970 4296 50  0000 L CNN
F 1 "DNP" H 6970 4205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6830 4250 50  0001 C CNN
F 3 "~" H 6900 4250 50  0001 C CNN
	1    6900 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R13
U 1 1 5E1AA426
P 6700 4500
F 0 "R13" V 6493 4500 50  0000 C CNN
F 1 "100k" V 6584 4500 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6630 4500 50  0001 C CNN
F 3 "~" H 6700 4500 50  0001 C CNN
	1    6700 4500
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D3
U 1 1 5E215EAD
P 5700 3850
F 0 "D3" V 5654 3930 50  0000 L CNN
F 1 "3V" V 5745 3930 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323" H 5700 3850 50  0001 C CNN
F 3 "~" H 5700 3850 50  0001 C CNN
	1    5700 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	5700 3700 5700 3450
Wire Wire Line
	5700 4000 5700 4250
Wire Wire Line
	5700 4250 5150 4250
Connection ~ 5150 4250
Wire Wire Line
	5700 3450 6100 3450
$Comp
L Device:C C15
U 1 1 5E239947
P 1750 3600
F 0 "C15" H 1865 3646 50  0000 L CNN
F 1 "10u" H 1865 3555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1788 3450 50  0001 C CNN
F 3 "~" H 1750 3600 50  0001 C CNN
	1    1750 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 3800 1750 3750
$Comp
L Device:R R11
U 1 1 5E2516A9
P 4750 3450
F 0 "R11" V 4543 3450 50  0000 C CNN
F 1 "56" V 4634 3450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 4680 3450 50  0001 C CNN
F 3 "~" H 4750 3450 50  0001 C CNN
	1    4750 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	4500 3450 4600 3450
Wire Wire Line
	4900 3450 5150 3450
Connection ~ 5150 3450
$Comp
L Device:D_Schottky D1
U 1 1 5E2596FE
P 3050 2550
F 0 "D1" H 3050 2333 50  0000 C CNN
F 1 "BAT20J" H 3050 2424 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" H 3050 2550 50  0001 C CNN
F 3 "~" H 3050 2550 50  0001 C CNN
	1    3050 2550
	-1   0    0    1   
$EndComp
Wire Wire Line
	3200 2550 5150 2550
Wire Wire Line
	5150 2550 5150 3450
$Comp
L Device:C C17
U 1 1 5E27E56B
P 4000 3850
F 0 "C17" H 4115 3896 50  0000 L CNN
F 1 "10u" H 4115 3805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4038 3700 50  0001 C CNN
F 3 "~" H 4000 3850 50  0001 C CNN
	1    4000 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3450 4000 3450
Connection ~ 3550 3450
Wire Wire Line
	4000 3700 4000 3450
Connection ~ 4000 3450
Wire Wire Line
	4000 3450 3550 3450
Wire Wire Line
	4000 4000 4000 4250
Connection ~ 4000 4250
Wire Wire Line
	4000 4250 5150 4250
Wire Wire Line
	9150 3350 9150 3450
Text Notes 4350 3650 0    50   ~ 0
Limit current
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5E4262F1
P 7150 800
F 0 "#FLG0101" H 7150 875 50  0001 C CNN
F 1 "PWR_FLAG" H 7150 973 50  0000 C CNN
F 2 "" H 7150 800 50  0001 C CNN
F 3 "~" H 7150 800 50  0001 C CNN
	1    7150 800 
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5E42698F
P 7650 800
F 0 "#FLG0102" H 7650 875 50  0001 C CNN
F 1 "PWR_FLAG" H 7650 973 50  0000 C CNN
F 2 "" H 7650 800 50  0001 C CNN
F 3 "~" H 7650 800 50  0001 C CNN
	1    7650 800 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0145
U 1 1 5E426C6D
P 7150 850
F 0 "#PWR0145" H 7150 600 50  0001 C CNN
F 1 "GND" H 7155 677 50  0000 C CNN
F 2 "" H 7150 850 50  0001 C CNN
F 3 "" H 7150 850 50  0001 C CNN
	1    7150 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 850  7150 800 
Wire Wire Line
	7650 850  7650 800 
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5E43942B
P 1750 3150
F 0 "#FLG0103" H 1750 3225 50  0001 C CNN
F 1 "PWR_FLAG" H 1750 3323 50  0000 C CNN
F 2 "" H 1750 3150 50  0001 C CNN
F 3 "~" H 1750 3150 50  0001 C CNN
	1    1750 3150
	1    0    0    -1  
$EndComp
Wire Notes Line
	1350 4550 1350 2700
Text Notes 4350 2800 0    50   ~ 0
Optional boost
$Comp
L Device:R R21
U 1 1 5E470B8A
P 1550 3350
F 0 "R21" V 1343 3350 50  0000 C CNN
F 1 "0" V 1434 3350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 1480 3350 50  0001 C CNN
F 3 "~" H 1550 3350 50  0001 C CNN
	1    1550 3350
	0    1    1    0   
$EndComp
Wire Wire Line
	1000 3350 1300 3350
Wire Wire Line
	1300 3350 1300 2550
Wire Wire Line
	1300 2550 2900 2550
Wire Wire Line
	1300 3350 1400 3350
Connection ~ 1300 3350
Wire Wire Line
	1700 3350 1750 3350
Wire Wire Line
	1750 3450 1750 3350
Connection ~ 1750 3350
Wire Wire Line
	1750 3350 2050 3350
Wire Notes Line
	1350 2700 5000 2700
Wire Notes Line
	5000 2700 5000 4550
Wire Notes Line
	5000 4550 1350 4550
$Comp
L power:+BATT #PWR0144
U 1 1 5E535B5A
P 9150 3350
F 0 "#PWR0144" H 9150 3200 50  0001 C CNN
F 1 "+BATT" H 9165 3523 50  0000 C CNN
F 2 "" H 9150 3350 50  0001 C CNN
F 3 "" H 9150 3350 50  0001 C CNN
	1    9150 3350
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0146
U 1 1 5E53771A
P 7650 850
F 0 "#PWR0146" H 7650 700 50  0001 C CNN
F 1 "+BATT" H 7665 1023 50  0000 C CNN
F 2 "" H 7650 850 50  0001 C CNN
F 3 "" H 7650 850 50  0001 C CNN
	1    7650 850 
	-1   0    0    1   
$EndComp
Wire Wire Line
	1750 3150 1750 3350
Connection ~ 10950 3900
Wire Wire Line
	10950 3850 10950 3900
$Comp
L power:+3V3 #PWR0142
U 1 1 5E166A8B
P 10950 3850
F 0 "#PWR0142" H 10950 3700 50  0001 C CNN
F 1 "+3V3" H 10965 4023 50  0000 C CNN
F 2 "" H 10950 3850 50  0001 C CNN
F 3 "" H 10950 3850 50  0001 C CNN
	1    10950 3850
	1    0    0    -1  
$EndComp
Wire Notes Line
	8150 2400 8150 6150
Text Notes 8250 2550 0    50   ~ 0
Common for Solar and battery power
Text Notes 7250 2550 0    50   ~ 0
Solar power, cuttable
Wire Wire Line
	8650 3400 8650 3450
$Comp
L Connector_Generic:Conn_01x02 J6
U 1 1 5E23AE32
P 8250 3900
F 0 "J6" H 8168 3575 50  0000 C CNN
F 1 "BAT" H 8168 3666 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8250 3900 50  0001 C CNN
F 3 "~" H 8250 3900 50  0001 C CNN
	1    8250 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	8450 3800 8450 3450
Connection ~ 8450 3450
Wire Wire Line
	8450 3450 8650 3450
Wire Wire Line
	9000 4000 9000 4100
Wire Wire Line
	9000 4100 9150 4100
Connection ~ 9150 4100
Wire Wire Line
	9150 4100 9150 4800
Wire Wire Line
	9000 3800 9000 3700
Wire Wire Line
	9000 3700 9150 3700
Connection ~ 9150 3700
Wire Wire Line
	9150 3700 9150 3800
$Comp
L Device:Jumper_NO_Small JP2
U 1 1 5E33A744
P 9000 3900
F 0 "JP2" V 8954 3948 50  0000 L CNN
F 1 "EN" V 9045 3948 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 9000 3900 50  0001 C CNN
F 3 "~" H 9000 3900 50  0001 C CNN
	1    9000 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 4800 9150 4800
$Comp
L power:GND #PWR0110
U 1 1 5E343835
P 8450 4000
F 0 "#PWR0110" H 8450 3750 50  0001 C CNN
F 1 "GND" H 8455 3827 50  0000 C CNN
F 2 "" H 8450 4000 50  0001 C CNN
F 3 "" H 8450 4000 50  0001 C CNN
	1    8450 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 4000 8450 3900
$EndSCHEMATC
