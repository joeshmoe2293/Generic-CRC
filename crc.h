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

#ifndef CRC_H
#define CRC_H

#include <stdint.h>

/*
 * Change this define to use a different CRC!
 * At the time of writing, CRC8, CRC16 (IBM standard), 
 * CRC-CCITT (0xFFFF), and CRC32 (Ethernet standard)
 * are implemented and verified 
 *
 */
#define CRC_32

#define TRUE 1
#define FALSE 0

/*
 * At the time of writing this, I have not needed to use REFLECT_REMAINDER
 * for anything, so you don't need to include it or define it for everything
 * to function properly. If you add a CRC that reflects either the data
 * or remainder but not the other and stuff doesn't work, let me know!
 *
 */

#if defined(CRC_8)
typedef uint8_t crc_t;
#define POLYNOMIAL 0xD5
#define REFLECT_DATA FALSE
#define REFLECT_REMAINDER FALSE
#define INITIAL_REMAINDER 0x00
#define FINAL_XOR_VALUE 0x00
#endif

#if defined(CRC_16)
typedef uint16_t crc_t;
#define POLYNOMIAL 0x8005
#define REVERSED_POLYNOMIAL 0xA001
#define REVERSE_DATA TRUE
#define REVERSE_REMAINDER TRUE
#define INITIAL_REMAINDER 0x0000
#define FINAL_XOR_VALUE 0x0000
#endif

#if defined(CRC_CCITT)
typedef uint16_t crc_t;
#define POLYNOMIAL 0x1021
#define REVERSE_DATA FALSE
#define REVERSE_REMAINDER FALSE
#define INITIAL_REMAINDER 0xFFFF
#define FINAL_XOR_VALUE 0x0000
#endif

#if defined(CRC_32)
typedef uint32_t crc_t;
#define POLYNOMIAL 0x04C11DB7
#define REVERSED_POLYNOMIAL 0xEDB88320 
#define REVERSE_DATA TRUE
#define REVRSE_REMAINDER TRUE
#define INITIAL_REMAINDER 0xFFFFFFFF
#define FINAL_XOR_VALUE 0xFFFFFFFF
#endif

/*
 * Parameters are: crc of the message (or 0 if you are calculating it),
 * a pointer to the data, and the number of bytes starting at data to be CRC'd
 */
crc_t fastCRC(crc_t crcValue, const uint8_t msg[], uint16_t numBytes);

#endif
