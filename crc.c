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
#include "crc.h"

#define FAST_CRC_TABLE_SIZE 256
#define SMALL_CRC_TABLE_SIZE 16
#define LOWEST_BYTE 0xFF
#define LOWEST_NIBBLE 0xF
#define LOWEST_BIT 0x1
#define CRC_WIDTH (8 * sizeof(crc_t))
#define HIGHEST_BYTE (0xFF << (CRC_WIDTH - 8))
#define HIGHEST_NIBBLE 0xF0
#define HIGHEST_BIT (1 << (CRC_WIDTH - 1))

static crc_t fastCRCTable[FAST_CRC_TABLE_SIZE];
static crc_t smallCRCTable[SMALL_CRC_TABLE_SIZE];

void fastCRCInit() {
    uint8_t bit;
    int dividend;
    crc_t remainder;

    for (dividend = 0; dividend < FAST_CRC_TABLE_SIZE; dividend++) {
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
        }

        fastCRCTable[dividend] = remainder;
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

    for (currentByte = 0; currentByte < numBytes; currentByte++) {
#if REVERSE_DATA == TRUE
        tableIdx = (remainder ^ msg[currentByte]) & LOWEST_BYTE;
        remainder = (remainder >> 8) ^ (fastCRCTable[tableIdx]);
#else
        tableIdx = (remainder >> (CRC_WIDTH - 8)) ^ msg[currentByte];
        remainder = (remainder << 8) ^ fastCRCTable[tableIdx]; 
#endif
    }

    return (remainder ^ crcValue) ^ FINAL_XOR_VALUE;
}

void smallCRCInit() {
    uint8_t bit;
    uint8_t dividend;
    crc_t remainder;

    for (dividend = 0; dividend < SMALL_CRC_TABLE_SIZE; dividend++) {
#if REVERSE_DATA == TRUE
        remainder = dividend;
#else
        remainder = dividend << (CRC_WIDTH - 4);
#endif

        for (bit = 0; bit < 4; bit++) {
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
        }

        smallCRCTable[dividend] = remainder;
    }
}

crc_t smallCRC(crc_t crcValue, const uint8_t msg[], uint16_t numBytes) {
    uint8_t tableIdx, currentNibble;
    uint16_t currentByte;
    crc_t remainder = INITIAL_REMAINDER;

    for (currentByte = 0; currentByte < numBytes; currentByte++) {
#if REVERSE_DATA == TRUE
        currentNibble = msg[currentByte];
        tableIdx = (remainder ^ currentNibble) & LOWEST_NIBBLE;
        remainder = smallCRCTable[tableIdx] ^ (remainder >> 4);

        currentNibble >>= 4;
        tableIdx = (remainder ^ currentNibble) & LOWEST_NIBBLE;
        remainder = smallCRCTable[tableIdx] ^ (remainder >> 4);
#else
        currentNibble = msg[currentByte];
        tableIdx = (((remainder >> (CRC_WIDTH - 8)) ^ currentNibble) & HIGHEST_NIBBLE) >> 4;
        remainder = smallCRCTable[tableIdx] ^ (remainder << 4);

        currentNibble <<= 4;
        tableIdx = (((remainder >> (CRC_WIDTH - 8)) ^ currentNibble) & HIGHEST_NIBBLE) >> 4;
        remainder = smallCRCTable[tableIdx] ^ (remainder << 4);
#endif
    }

    return (remainder ^ crcValue) ^ FINAL_XOR_VALUE;
}
