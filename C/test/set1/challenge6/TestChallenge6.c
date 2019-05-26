#include <stdio.h>
#include <StringUtils.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int testHammingDistance();

int main() {
    puts("*********** Testing set 1 challenge 6");

    int error = testHammingDistance();
    if (error) {
        printf("Ruh-roh! Failed Hamming distance test (returned distance = %d)", error + 37);
        return 1;
    }

    puts("All good :)");
}

int testHammingDistance() {
    char input1[] = "this is a test";
    char input2[] = "wokka wokka!!!";
    long expected = 37;
    long distance = getHammingSameLength((unsigned char *)input1, (unsigned char *)input2, 14);
    return distance - expected;
}

int findKeySize() {
    long bestHammingDistance = LONG_MAX;

    FILE *testFile = fopen("/home/chris/Documents/git/cryptopals/C/test/set1/challenge6/6.txt", "r");
    char *testData = (char *)malloc(65536);
    char *position = testData;
    char buffer[256] = {0};

    while (fgets(buffer, 255, testFile) != NULL) {
        int lineLength = strlen(buffer);
        memcpy(position, buffer, lineLength);
        position += lineLength;
    }

    position = testData;
    char keySize = 2;
    for (; keySize < 41; keySize++) {
        char blocks[4][keySize + 1];
        memset(blocks, 0, 4*(keySize) + 1);
        for (char i = 0; i < 4; i++) {
            memcpy(blocks[i], position, keySize);
            blocks[i][keySize] = 0;
        }

        long ham = 0;
        for (char i = 0; i < 4; i++) {

        }
    }

    return keySize;
}


