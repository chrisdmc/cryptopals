#include <ConversionUtils.h>
#include <stdio.h>

char convertNumericToHexChar(unsigned char n);
unsigned char convertFirstVariantToBase64(unsigned char byte);
unsigned char convertFirstVariantFromBase64(unsigned char value0,
		unsigned char value1);
unsigned char convertSecondVariantToBase64(unsigned char byte1,
		unsigned char byte2);
unsigned char convertSecondVariantFromBase64(unsigned char value1,
		unsigned char value2);
unsigned char convertThirdVariantToBase64(unsigned char byte1,
		unsigned char byte2);
unsigned char convertThirdVariantFromBase64(unsigned char value2,
		unsigned char value3);
unsigned char convertFourthVariantToBase64(unsigned char byte);
void appendBase64Char(char* base64Out, unsigned char base64Value);
char getBase64Char(unsigned char base64Value);
char convertNumericToHexChar(unsigned char n);
unsigned char getBase64Value(char base64Char);

const unsigned char HIGHER_SIX_BIT_MASK = 0xFC;
const unsigned char LOWER_SIX_BIT_MASK = 0x3F;
const unsigned char HIGHER_TWO_BIT_MASK = 0xC0;
const unsigned char LOWER_TWO_BIT_MASK = 0x03;
const unsigned char HIGHER_FOUR_BIT_MASK = 0xF0;
const unsigned char LOWER_FOUR_BIT_MASK = 0x0F;
const unsigned char BITS_TWO_AND_THREE_BIT_MASK = 0x30;
const unsigned char MIDDLE_FOUR_BIT_MASK = 0x3C;
const unsigned char PADDING_BYTE = 0xFF;

void hexToBinary(char* hexString, unsigned short length,
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

void binaryToHex(unsigned char* binary, unsigned short length, char* hexOut) {
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

void binaryToBase64(unsigned char* binary, unsigned short length,
		char* base64Out) {
	int iterations = length / 3;
	for (int i = 0; i < iterations; i++) {
		unsigned char byte0 = *binary;
		unsigned char byte1 = *(binary + 1);
		unsigned char byte2 = *(binary + 2);

		unsigned char base64Value = convertFirstVariantToBase64(byte0);
		appendBase64Char(base64Out++, base64Value);

		base64Value = convertSecondVariantToBase64(byte0, byte1);
		appendBase64Char(base64Out++, base64Value);

		base64Value = convertThirdVariantToBase64(byte1, byte2);
		appendBase64Char(base64Out++, base64Value);

		base64Value = convertFourthVariantToBase64(byte2);
		appendBase64Char(base64Out++, base64Value);

		binary += 3;
	}

	int r = length % 3;
	if (r > 0) {
		unsigned char byte0 = *binary;
		unsigned char byte1 = r > 1 ? *(binary + 1) : 0x00;
		unsigned char byte2 = 0x00;

		unsigned char base64Value = convertFirstVariantToBase64(byte0);
		appendBase64Char(base64Out++, base64Value);

		base64Value = convertSecondVariantToBase64(byte0, byte1);
		appendBase64Char(base64Out++, base64Value);

		base64Value =
				r > 1 ? convertThirdVariantToBase64(byte1, byte2) : PADDING_BYTE;
		appendBase64Char(base64Out++, base64Value);
		appendBase64Char(base64Out++, PADDING_BYTE);
	}
}

void base64ToBinary(char* base64, unsigned short length,
		unsigned char* binaryOut) {
	for (int i = 0; i < length / 4; i++) {
		char c0 = *base64;
		char c1 = *(base64 + 1);
		char c2 = *(base64 + 2);
		char c3 = *(base64 + 3);

		unsigned char value0 = getBase64Value(c0);
		unsigned char value1 = getBase64Value(c1);
		unsigned char value2 = getBase64Value(c2);
		unsigned char value3 = getBase64Value(c3);

		unsigned char byte0 = convertFirstVariantFromBase64(value0, value1);
		unsigned char byte1 = convertSecondVariantFromBase64(value1, value2);
		unsigned char byte2 = convertThirdVariantFromBase64(value2, value3);

		*(binaryOut) = byte0;
		*(binaryOut + 1) = byte1;
		*(binaryOut + 2) = byte2;

		base64 += 4;
		binaryOut += 3;
	}
}

void hexToBase64(char* hex, unsigned short length, char* base64Out) {
	unsigned short binaryLen = length / 2;
	unsigned char binary[binaryLen];
	hexToBinary(hex, length, binary);
	binaryToBase64(binary, binaryLen, base64Out);
}

void base64ToHex(char* base64, unsigned short length, char* hexOut) {
	unsigned short binaryLen = (length / 4) * 3;
	unsigned char binary[binaryLen];
	base64ToBinary(base64, length, binary);
	binaryToHex(binary, binaryLen, hexOut);
}

unsigned char convertFirstVariantToBase64(unsigned char byte) {
	return (byte & HIGHER_SIX_BIT_MASK) >> 2;
}

unsigned char convertFirstVariantFromBase64(unsigned char value0,
		unsigned char value1) {
	return (value0 << 2) + ((value1 & BITS_TWO_AND_THREE_BIT_MASK) >> 4);
}

unsigned char convertSecondVariantToBase64(unsigned char byte1,
		unsigned char byte2) {
	return ((byte1 & LOWER_TWO_BIT_MASK) << 4)
			+ ((byte2 & HIGHER_FOUR_BIT_MASK) >> 4);
}

unsigned char convertSecondVariantFromBase64(unsigned char value1,
		unsigned char value2) {
	return ((value1 & LOWER_FOUR_BIT_MASK) << 4)
			+ ((value2 & MIDDLE_FOUR_BIT_MASK) >> 2);
}

unsigned char convertThirdVariantToBase64(unsigned char byte1,
		unsigned char byte2) {
	return ((byte1 & LOWER_FOUR_BIT_MASK) << 2)
			+ ((byte2 & HIGHER_TWO_BIT_MASK) >> 6);
}

unsigned char convertThirdVariantFromBase64(unsigned char value2,
		unsigned char value3) {
	return ((value2 & LOWER_TWO_BIT_MASK) << 6) + (value3 & LOWER_SIX_BIT_MASK);
}

unsigned char convertFourthVariantToBase64(unsigned char byte) {
	return byte & LOWER_SIX_BIT_MASK;
}

void appendBase64Char(char* base64Out, unsigned char base64Value) {
	char base64Char = getBase64Char(base64Value);
	*base64Out = base64Char;
}

unsigned char getBase64Value(char base64Char) {
	if (base64Char == '+') {
		return 62;
	} else if (base64Char == '/') {
		return 63;
	} else if (base64Char == '=') {
		return 0;
	} else if (base64Char < 58) {
		return base64Char + 4;
	} else if (base64Char < 91) {
		return base64Char - 65;
	} else { // if (base64Char < 123)
		return base64Char - 71;
	}
}

char getBase64Char(unsigned char base64Value) {
	if (base64Value < 26) {
		return base64Value + 65;
	} else if (base64Value < 52) {
		return base64Value + 71;
	} else if (base64Value < 62) {
		return base64Value - 4;
	} else if (base64Value == 62) {
		return '+';
	} else if (base64Value == 63) {
		return '/';
	} else {
		return '=';
	}
}

char convertNumericToHexChar(unsigned char n) {
	if (n < 10) {
		return n + 48;
	} else {
		return n + 55;
	}
}
