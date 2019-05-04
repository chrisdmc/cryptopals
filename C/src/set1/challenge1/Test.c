#include <HexToBase64.h>
#include <stdio.h>

static char hexChars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F' };

int main() {
	puts("In main...");
	unsigned char hexString[512];

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

	if (!result) {
		puts("All good :)");
	} else {
		puts("Ruh-roh!");
		return result;
	}

	unsigned char hexOut[512];
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
		return result;
	}

	return result;
}
