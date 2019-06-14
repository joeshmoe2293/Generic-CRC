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
#include <sys/time.h>
#include "crc.h"

/* 
 * To use a specific version CRC, modify the #define CRC_XXXX in the top of crc.h
 * (Also make sure to call (small/fast)CRCinit before trying to calculate a CRC)
 * (small/fast)CRC takes 3 parameters, the crc of the message (or 0 if you are calculating it),
 * a pointer to the data, and the number of bytes starting at data to be CRC'd
 * (typecasting just to stop compiler from complaining about mismatched types)
 *
 */
int main() {
    const char *s = "123456789";
    fastCRCInit();
    smallCRCInit();
    crc_t crcOfMsg = fastCRC(0, (uint8_t *)s, strlen(s));
    crc_t crcOfMsg2 = smallCRC(0, (uint8_t *)s, strlen(s));

    printf("Expected CRC of %s = 0x%lX\n", s, crcOfMsg);
    printf("New CRC of %s = 0x%lX\n", s, crcOfMsg2);

    crcOfMsg2 = smallCRC(crcOfMsg2, (uint8_t *)s, strlen(s));

    printf("CRC of sent message = 0x%lX\n", crcOfMsg2);

    return 0;
}
