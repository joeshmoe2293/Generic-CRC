/*
 * Written by Paul Vohs
 * Use as you'd like, and feel free to remove this notice if you'd like!
 *
 * Heavily inspired from:
 * http://ross.net/crc/download/crc_v3.txt
 * https://barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code
 * http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "crc.h"

/* 
 * To use a specific version CRC, modify the #define CRC_XXXX in the top of crc.h
 *
 * fastCRC takes 3 parameters, the crc of the message (or 0 if you are calculating it),
 * a pointer to the data, and the number of bytes starting at data to be CRC'd
 * (typecasting just to stop compiler from complaining about mismatched types)
 *
 */
int main() {
    crc_t crcOfMsg;

    crcInit();

    uint8_t data[] = {1, 2, 3, 4};

    printf("For the %s type of CRC:\n", CRC_STRING);

    crcOfMsg = fastCRC(0, data, sizeof(data));
    printf("CRC (using table lookups) is: 0x%X\n", crcOfMsg);
    crcOfMsg = fastCRC(crcOfMsg, data, sizeof(data));
    printf("Remainder after applying calculated CRC: 0x%X\n", crcOfMsg);

    crcOfMsg = calcCRC(0, data, sizeof(data));
    printf("CRC without lookups is: 0x%X\n", crcOfMsg);
    crcOfMsg = calcCRC(crcOfMsg, data, sizeof(data));
    printf("Remainder after applying calculated CRC: 0x%X\n", crcOfMsg);

    return 0;
}
