#include <HexToBase64.h>

unsigned char convertNumericToHexChar(unsigned char n);

void hexToBinary(unsigned char* hexString, unsigned short length,
		unsigned char* binaryOut) {

	int i;
	for (i = 0; i < length; i++) {
		unsigned char c = *(hexString);
		hexString++;
		if (c < 48 || c > 102 || (c > 57 && c < 65) || (c > 70 && c < 97)) {
			return;
		}

		if (c >= 97) {
			c -= 32;
		}

		unsigned char b;
		if (c >= 48 && c <= 57) {
			b = c - 48;
		} else {
			b = c - 55;
		}

		if (i % 2 == 0) {
			b <<= 4;
			*(binaryOut) = b;
		} else {
			*(binaryOut) += b;
			binaryOut++;
		}
	}
}

void binaryToHex(unsigned char* binary, unsigned short length,
		unsigned char* hexOut) {
	for (int i = 0; i < length; i++) {
		unsigned char b = *(binary);
		binary++;

		unsigned char higherB = b / 16;
		unsigned char lowerB = b % 16;

		unsigned char h1 = convertNumericToHexChar(higherB);
		unsigned char h2 = convertNumericToHexChar(lowerB);

		*(hexOut) = h1;
		hexOut++;
		*(hexOut) = h2;
		hexOut++;
	}
}

unsigned char convertNumericToHexChar(unsigned char n) {
	if (n < 10) {
		return n + 48;
	} else {
		return n + 55;
	}
}
