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
    char s[1024];
    struct timeval start, stop;
    crc_t crcOfMsg;
    int i;

    puts("Please enter a message to send!");
    fgets(s, sizeof(s), stdin);
    s[strlen(s) - 1] = '\0';

    crcInit();

    for (i = 0; i < 10; i++) {
        gettimeofday(&start, NULL);
        crcOfMsg = fastCRC(0, (uint8_t *)s, strlen(s));
        gettimeofday(&stop, NULL);

        printf("CRC of message of length %lu = 0x%lX\n", strlen(s), crcOfMsg);
        printf("Calculation of crc took %lu microseconds\n", stop.tv_usec - start.tv_usec);

        gettimeofday(&start, NULL);
        crcOfMsg = fastCRC(crcOfMsg, (uint8_t *)s, strlen(s));
        gettimeofday(&stop, NULL);

        printf("CRC of sent message = 0x%lX\n", crcOfMsg);
        printf("Calculation of crc took %lu microseconds\n", stop.tv_usec - start.tv_usec);
    }

    return 0;
}
