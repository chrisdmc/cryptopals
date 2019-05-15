#include <ConversionUtils.h>
#include <CipherUtils.h>
#include <BruteForce.h>
#include <stdio.h>
#include <stdbool.h>

int main() {
	puts("*********** Testing set 1 challenge 3");
	char encodedString[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

	unsigned char encodedBytes[34];
	hexToBinary(encodedString, 68, encodedBytes);

	unsigned char decodedBytes[34];
	unsigned char key[1];
	bool result = bruteForceKey(1, encodedBytes, decodedBytes, 34, key);

	if (result) {
		printf("Decoded string '%s' with key %d (%c)\n", decodedBytes, key[0], key[0]);
	} else {
		puts("Ruh-roh!");
	}
}


