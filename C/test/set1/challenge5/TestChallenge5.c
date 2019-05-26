#include <stdio.h>
#include <CipherUtils.h>
#include <ConversionUtils.h>
#include <string.h>

int main() {
    puts("*********** Testing set 1 challenge 5");

    static unsigned char text[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";

    static char expectedResult[] =
            "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

    static unsigned char key[] = "ICE";

    int len = strlen((char *) text);
    unsigned char encryptedBytes[len + 1];
    memset(encryptedBytes, 0, len + 1);

    xorVarLength(text, len, key, 3, encryptedBytes, len);

    char hex[(len * 2) + 1];
    memset(hex, 0, (len * 2) + 1);

    binaryToHex(encryptedBytes, len, hex);

    if (!strcmp(hex, expectedResult)) {
        puts("All good :)");
    } else {
        puts("Ruh-roh!");
    }
}

