#include <ConversionUtils.h>
#include <CipherUtils.h>
#include <stdio.h>

int main() {
	puts("********** Challenge 2 Tests");

	char input[] = "1c0111001f010100061a024b53535009181c";
	char key[] = "686974207468652062756c6c277320657965";
	char expectedResult[] = "746865206b696420646f6e277420706c6179";

	unsigned char inputBinary[18];
	hexToBinary(input, 36, inputBinary);

	unsigned char keyBinary[18];
	hexToBinary(key, 36, keyBinary);

	unsigned char expectedResultBinary[18];
	hexToBinary(expectedResult, 36, expectedResultBinary);

	unsigned char actual[18];
	xorFixedLength(inputBinary, keyBinary, actual, 18);

	int result = 0;
	for (int i = 0; i < 18; i++) {
		if (actual[i] != expectedResultBinary[i]) {
			result++;
			printf("position %d, expected %c (%d), but got %c (%d)\n", i, expectedResult[i], expectedResult[i], actual[i], actual[i]);
		}
	}

	if (result) {
		puts("Ruh-roh!");
	} else {
		puts("All good :)");
	}

	return result;
}

