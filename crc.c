#include <stdio.h>
#include <string.h>
#include "crc.h"

#define CRC_TABLE_SIZE 256
#define LOWEST_BYTE 0xFF
#define LOWEST_BIT 0x1
#define CRC_WIDTH (8 * sizeof(crc))
#define HIGHEST_BYTE (0xFF << (CRC_WIDTH - 8))
#define HIGHEST_BIT (1 << (CRC_WIDTH - 1))

static void crcInit(crc_t crcTable[]) {
    uint8_t bit;
    int dividend;
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

crc_t fastCRC(crc_t crcValue, const uint8_t msg[], uint16_t numBytes) {
    uint8_t tableIdx;
    static uint8_t tableInit = 0;
    uint16_t currentByte;
    static crc_t crcTable[CRC_TABLE_SIZE];
    crc_t remainder = INITIAL_REMAINDER;

    if (!tableInit) {
        crcInit(crcTable);
        tableInit = 1;
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
