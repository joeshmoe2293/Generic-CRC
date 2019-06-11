#include <stdio.h>
#include <string.h>
#include "crc.h"

int main() {
    const char *s = "123456789";
    const crc_t crcOfMsg = fastCRC(0, (uint8_t *)s, strlen(s));
    printf("CRC of %s = 0x%lX\n", s, crcOfMsg);
    printf("CRC of sent message = 0x%lX\n", fastCRC(crcOfMsg, (uint8_t *)s, strlen(s)));

    return 0;
}
