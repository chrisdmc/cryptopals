int xorFixedLength(unsigned char bytes1[], unsigned char bytes2[], unsigned char result[], unsigned short length) {
    for (int i = 0; i < length; i++) {
        result[i] = bytes1[i] ^ bytes2[i];
    }

    return 0;
}

int xorVarLength(unsigned char bytes1[], unsigned short bytes1Len, unsigned char bytes2[], unsigned short bytes2Len,
        unsigned char result[], unsigned short resultLength) {
    for (int i = 0; i < resultLength; i++) {
        result[i] = bytes1[i % bytes1Len] ^ bytes2[i % bytes2Len];
    }

    return 0;
}
