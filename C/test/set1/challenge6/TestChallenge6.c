#include <stdio.h>
#include <StringUtils.h>
#include <ConversionUtils.h>
#include <limits.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>

int testHammingDistance();
char findKeySize(unsigned char* bytePosition);
int decrypt();
int testTranspose();

int main() {
    puts("*********** Testing set 1 challenge 6");

    puts("Testing hamming distance");
    int error = testHammingDistance();
    if (error) {
        printf("Ruh-roh! Failed Hamming distance test (returned distance = %d)", error + 37);
        return 1;
    }

    puts("Testing transpose");
    error = testTranspose();
    if (error) {
        return 1;
    }

    puts("Testing decrypt");
    int foundKeySize = decrypt();
    if (foundKeySize == -1) {
        puts("Ruh-roh! Didn't find a key size");
        return 1;
    } else {
        printf("Found key size = %d\n", foundKeySize);
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

int testTranspose() {
    unsigned char input[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    unsigned char expectedResult[12] = {1, 4, 7, 10, 2, 5, 8, 11, 3, 6, 9, 12};
    unsigned char actual[12];
    memset(actual, 0, 12);

    transpose(input, actual, 4, 3);

    int error = 0;
    for (int i = 0; i < 12; i++) {
        if (actual[i] != expectedResult[i]) {
            printf("%d Ruh-roh! Expected %d, actual %d\n", i, expectedResult[i], actual[i]);
            error = 1;
        }
    }

    return error;
}

char findKeySize(unsigned char* bytePosition) {
    char foundKeySize = -1;
    double bestHammingDistance = DBL_MAX;
    for (char keySize = 2; keySize < 41; keySize++) {
        unsigned char blocks[4][keySize + 1];
        memset(blocks, 0, 4 * (keySize + 1));
        for (unsigned char i = 0; i < 4; i++) {
            memcpy(blocks[i], bytePosition + i * keySize, keySize);
        }
        double ham = 0.0;
        ham += getHammingSameLength(blocks[0], blocks[1], keySize) / (double) keySize;
        ham += getHammingSameLength(blocks[0], blocks[2], keySize) / (double) keySize;
        ham += getHammingSameLength(blocks[0], blocks[3], keySize) / (double) keySize;
        ham += getHammingSameLength(blocks[1], blocks[2], keySize) / (double) keySize;
        ham += getHammingSameLength(blocks[1], blocks[3], keySize) / (double) keySize;
        ham += getHammingSameLength(blocks[2], blocks[3], keySize) / (double) keySize;
        ham /= 6;
        if (ham < bestHammingDistance) {
            bestHammingDistance = ham;
            foundKeySize = keySize;
        }
    }
    return foundKeySize;
}

int decrypt() {
    char foundKeySize = -1;

    FILE *testFile = fopen("/home/chris/Documents/git/cryptopals/C/test/set1/challenge6/6.txt", "r");
    char *testData = (char *)malloc(65536);
    memset(testData, 0, 65536);

    char *position = testData;
    char buffer[256] = {0};

    while (fgets(buffer, 255, testFile) != NULL) {
        int lineLength = strlen(buffer);
        if (buffer[lineLength-1] == 0x0A) {
            // Trim new line
            buffer[--lineLength] = 0x0;
        }
        memcpy(position, buffer, lineLength);
        position += lineLength;
    }

    int docLength = position - testData;
    if (docLength % 4 != 0) {
        return foundKeySize;
    }

    int docLengthBytes = (docLength/4)*3;
    unsigned char decodedBytes[docLengthBytes];
    memset(decodedBytes, 0, docLengthBytes);
    base64ToBinary(testData, docLength, decodedBytes);

    foundKeySize = findKeySize(decodedBytes);
    int numBlocks = (docLengthBytes/foundKeySize)+1;
    int lastBlockNumBytes = docLengthBytes % foundKeySize;
    unsigned char blocks[numBlocks * foundKeySize];
    memset(blocks, 0, numBlocks*foundKeySize);
    memcpy(blocks, decodedBytes, docLengthBytes);

    unsigned char transposedBlocks[numBlocks * foundKeySize];
    memset(transposedBlocks, 0, numBlocks*foundKeySize);
    transpose(blocks, transposedBlocks, numBlocks, foundKeySize);



    return (int)foundKeySize;
}


