#include <ConversionUtils.h>
#include <stdio.h>
#include <string.h>

static char hexChars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F' };

int testHex();
int testBase64();
int testChallenge1();

int main() {
	puts("In main");
	puts("Testing hex conversions");
	int result = testHex();

	if (!result) {
		puts("Testing base64 conversions");
		result = testBase64();
	}

	if (!result) {
		puts("Testing set 1, challenge 1");
		result = testChallenge1();
	}
}

int testHex() {
	char hexString[512];

	puts("Populating hexString");
	int i;
	for (i = 0; i < 256; i++) {
		hexString[2 * i] = hexChars[i / 16];
		hexString[(2 * i) + 1] = hexChars[i % 16];
	}

	puts("Calling hexToBinary");
	unsigned char binary[256];
	hexToBinary(hexString, 512, binary);

	puts("Checking results...");
	int result = 0;
	unsigned char c;
	for (c = 0;; c++) {
		if (*(binary + c) != c) {
			printf("Position %d value = %d\n", c, *(binary + c));
			result = 1;
		}
		if (c == 255) {
			break;
		}
	}

	if (result) {
		puts("Ruh-roh!");
		return result;
	}

	char hexOut[512];
	binaryToHex(binary, 256, hexOut);

	for (i = 0; i < 512; i++) {
		if (hexOut[i] != hexString[i]) {
			printf("Position %d, hexOut = %c, hexString = %c\n", i, hexOut[i],
					hexString[i]);
			result = 1;
		}
	}

	if (!result) {
		puts("All good :)");
	} else {
		puts("Ruh-roh!");
	}

	return result;
}

// Not very comprehensive, but it's difficult to automate this without just including the algorithm in the test itself.
int testBase64() {
	unsigned char bytes[13];

	puts("Populating bytes");
	for (unsigned char c = 0; c < 13; c++) {
		bytes[c] = c;
	}

	puts("Calling binaryToBase64");
	char base64[20];
	binaryToBase64(bytes, 13, base64);

	int result = 0;
	char expectedResult[] = "AAECAwQFBgcICQoLDA==";
	for (short i = 0; i < 20; i++) {
		if (expectedResult[i] != (char) base64[i]) {
			result = 1;
			printf("position %d, got %c expected %c\n", i, (char) base64[i],
					expectedResult[i]);
		}
	}

	puts("Calling base64ToBinary");
	unsigned char bytesOut[13];
	base64ToBinary(base64, 20, bytesOut);

	for (short i = 0; i < 13; i++) {
		if (bytesOut[i] != bytes[i]) {
			result = 1;
			printf("position %d, got %x expected %x\n", i, bytesOut[i],
					bytes[i]);
		}
	}

	if (!result) {
		puts("All good :)");
	} else {
		puts("Ruh-roh!");
	}

	return result;
}

int testChallenge1() {
	char testString[] =
			"49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	char expectedResult[] =
			"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

	char base64Out[64];
	hexToBase64(testString, 96, base64Out);

	int result;
	for (short i = 0; i < 64; i++) {
		if (base64Out[i] != expectedResult[i]) {
			result = 1;
			printf("position %d, got %c expected %c\n", i, base64Out[i],
					expectedResult[i]);
		}
	}

	if (!result) {
		puts("All good :)");
	} else {
		puts("Ruh-roh!");
	}

	return result;
}
