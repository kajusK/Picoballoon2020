#!/usr/bin/env python3
#
# Generate frequency configs for rfm95 module
#

# each region should have 8 channels
regions = {
    'au': [916.8, 917.0, 917.2, 917.4, 917.6, 917.8, 918.0, 918.2],
    'eu': [868.1, 868.3, 868.5, 867.1, 867.3, 867.5, 867.7, 867.9],
    'us': [903.9, 904.1, 904.3, 904.5, 904.7, 904.9, 905.1, 905.3],
    'as': [923.2, 923.4, 922.2, 922.4, 922.6, 922.8, 923.0, 922.0],
}

for region, freqs in regions.items():
    print("static const uint8_t rfmi_lora_region_%s[RFM_CHANNELS][3] = {"
          % (region))

    for freq in freqs:
        res = round(freq*1e6/61.035)
        digits = "%06X" % (res)
        print("    {0x%s, 0x%s, 0x%s},  /* %.1f MHz */"
              % (digits[0:2], digits[2:4], digits[4:6], freq))
    print("};\n")
