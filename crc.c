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

#include "crc.h"
#include <stdio.h>

#define CRC_TABLE_SIZE 256
#define LOWEST_BYTE 0xFF
#define LOWEST_BIT 0x1
#define CRC_WIDTH (8 * sizeof(crc_t))
#define HIGHEST_BYTE (0xFF << (CRC_WIDTH - 8))
#define HIGHEST_BIT (1 << (CRC_WIDTH - 1))

static crc_t crcTable[CRC_TABLE_SIZE];

void crcInit() {
    uint8_t bit;
    uint16_t dividend;
    crc_t remainder;

    for (dividend = 0; dividend < CRC_TABLE_SIZE; dividend++) {
#if REVERSE_DATA == TRUE
        remainder = dividend;
#else
        remainder = dividend << (CRC_WIDTH - 8);
#endif

        for (bit = 0; bit < 8; bit++) {
#if REVERSE_DATA == TRUE
            if (remainder & LOWEST_BIT) {
                remainder = (remainder >> 1) ^ REVERSED_POLYNOMIAL;
            }
            else {
                remainder >>= 1;
            }
#else
            if (remainder & HIGHEST_BIT) {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else {
                remainder <<= 1;
            }
#endif
            crcTable[dividend] = remainder;
        }
    }
}

/* 
* fastCRC takes 3 parameters, the crc of the message (or 0 if you are calculating it),
* a pointer to the data, and the number of bytes starting at data to be CRC'd
* (typecasting just to stop compiler from complaining about mismatched types)
*
*/
crc_t fastCRC(crc_t crcValue, const uint8_t msg[], uint16_t numBytes) {
    uint8_t tableIdx;
    uint16_t currentByte;
    crc_t remainder = INITIAL_REMAINDER;

    if (crcTable[1] == 0) {
        crcInit(crcTable);
    }

    for (currentByte = 0; currentByte < numBytes; currentByte++) {
#if REVERSE_DATA == TRUE
        tableIdx = (remainder & LOWEST_BYTE) ^ msg[currentByte];
        remainder = (remainder >> 8) ^ (crcTable[tableIdx]);
#else
        tableIdx = msg[currentByte] ^ (remainder >> (CRC_WIDTH - 8));
        remainder = (remainder << 8) ^ crcTable[tableIdx]; 
#endif
    }

    return (remainder ^ crcValue) ^ FINAL_XOR_VALUE;
}

crc_t calcCRC(crc_t crcValue, const uint8_t *msg, uint16_t numBytes)
{
    crc_t remainder = INITIAL_REMAINDER;

    for (int currentByte = 0; currentByte < numBytes; currentByte++) {
#if REVERSE_DATA
        remainder ^= msg[currentByte];

        for (int bit = 7; bit >= 0; bit--) {
            if (remainder & LOWEST_BIT) {
                remainder = (remainder >> 1) ^ REVERSED_POLYNOMIAL;
            } else {
                remainder = remainder >> 1;
            }
        }
#else 
        remainder ^= (msg[currentByte] << (CRC_WIDTH - 8));

        for (int bit = 7; bit >= 0; bit--) {
            if (remainder & HIGHEST_BIT) {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            } else {
                remainder = remainder << 1;
            }
        }
#endif
    }

    return remainder ^ FINAL_XOR_VALUE;
}
