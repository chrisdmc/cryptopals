#include <StringUtils.h>
#include <stdio.h>
#include <math.h>

static double FREQUENCY_LIST2[27] = { 0.0651738, 0.0124248, 0.0217339, 0.0349835, 0.1041442, 0.0197881, 0.0158610,
        0.0492888, 0.0558094, 0.0009033, 0.0050529, 0.0331490, 0.0202124, 0.0564513, 0.0596302, 0.0137645, 0.0008606,
        0.0497563, 0.0515760, 0.0729357, 0.0225134, 0.0082903, 0.0171272, 0.0013692, 0.0145984, 0.0007836, 0.1918182 };

long getHammingByte(unsigned char c1, unsigned char c2);

bool isWhiteSpace(char c) {
    return (c == 0x20 || c == 0x9 || c == 0xa || c == 0xd);
}

void trimWhiteSpace(unsigned char *text, unsigned short *length) {
    for (unsigned char *curr = text + (*length - 1); curr != text; curr--) {
        if (!isWhiteSpace(*curr)) {
            return;
        }

        *curr = 0x0;
        (*length)--;
    }
}

bool isPrintableChar(char byte) {
    return (byte == 0xa || byte == 0xd || (byte >= 32 && byte <= 126));
}

bool isAlphaCharOrSpace(char c) {
    return ((c == 32) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

unsigned char normalizeChar(unsigned char c) {
    if (c == 32) {
        return 27;
    } else if (c >= 97) {
        return c - 97;
    } else {
        return c - 65;
    }
}

bool allPrintableChars(unsigned char *stringBytes, unsigned short length) {
    for (int i = 0; i < length; i++) {
        if (!isPrintableChar(*stringBytes)) {
            return false;
        }
        stringBytes++;
    }

    return true;
}

double scoreEnglishText(unsigned char *stringBytes, unsigned short length) {
    double score = 0.0;
    unsigned short charFrequencies[27] = { 0 };
    int alphaAndSpaceCharCount = 0;

    unsigned char *iter = stringBytes;
    for (unsigned char c = *iter; iter - stringBytes < length; c = *(++iter)) {
        if (isAlphaCharOrSpace(c)) {
            charFrequencies[normalizeChar(c)]++;
            alphaAndSpaceCharCount++;
        }
    }

    double variance = 0.0;
    for (unsigned char i = 0; i < 27; i++) {
        unsigned short charFrequency = charFrequencies[i];
        double relativeFrequency = (double) charFrequency/alphaAndSpaceCharCount;
        double charVariance = relativeFrequency - FREQUENCY_LIST2[i];

        variance += pow(charVariance, 2.0);
    }

    score = sqrt(variance/26.0);

    return score;
}

long getHammingSameLength(unsigned char *string1, unsigned char *string2, int length) {
    long ham = 0;

    for (int i = 0; i < length; i++) {
        unsigned char c1 = string1[i];
        unsigned char c2 = string2[i];

        ham += getHammingByte(c1, c2);
    }

    return ham;
}

long getHammingByte(unsigned char c1, unsigned char c2) {
    long bytesDiff = 0;
    unsigned char diff = c1 ^ c2;

    while(diff > 0) {
        if (diff & 1) {
            bytesDiff++;
        }
        diff >>= 1;
    }

    return bytesDiff;
}
