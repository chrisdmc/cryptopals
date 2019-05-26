#include <ConversionUtils.h>
#include <BruteForce.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
	puts("*********** Testing set 1 challenge 3");
	char encodedString[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	int len = strlen(encodedString);

	unsigned char encodedBytes[len/2];
	memset(encodedBytes, 0, len/2);
	hexToBinary(encodedString, len, encodedBytes);

	keyScore *result = bruteForceKey(1, encodedBytes, len/2);

	if (result != NULL) {
		printf("Decoded string '%s' with key %x\n", result->decodedText, result->key[0]);
	} else {
		puts("Ruh-roh!");
	}
}


