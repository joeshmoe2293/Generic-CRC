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

/* 
 * To use a specific version CRC, modify the #define CRC_XXXX in the top of crc.h
 *
 * fastCRC takes 3 parameters, the crc of the message (or 0 if you are calculating it),
 * a pointer to the data, and the number of bytes starting at data to be CRC'd
 * (typecasting just to stop compiler from complaining about mismatched types)
 *
 */
int main() {
    const char *s = "123456789";
    const crc_t crcOfMsg = fastCRC(0, (uint8_t *)s, strlen(s));
    printf("CRC of %s = 0x%lX\n", s, crcOfMsg);
    printf("CRC of sent message = 0x%lX\n", fastCRC(crcOfMsg, (uint8_t *)s, strlen(s)));

    return 0;
}
