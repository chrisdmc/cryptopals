#include <ConversionUtils.h>
#include <CipherUtils.h>
#include <BruteForce.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
	puts("*********** Testing set 1 challenge 4");

	FILE *fp = fopen("/home/chris/Documents/git/cryptopals/C/test/set1/challenge4/4.txt", "r");
	if (fp == NULL) {
		puts("fopen returned null");
		return 1;
	}

	char line[64] = {0};
	int lineNum = 0;
	int bestLineNum = 0;
	int len;
	keyScore *best = NULL;
	while (fgets(line, 64, (FILE *)fp) != NULL) {
	    len = strlen(line);
		// Cut the newline char
	    if (line[len-1] == 0x0a) {
	        line[--len] = 0x0;
	    }
		printf("Checking line %d, length %d, ('%s')\n", lineNum++, len, line);
		unsigned char bytes[len/2];
		memset(bytes, 0, len/2);
		hexToBinary(line, len, bytes);

		keyScore *score = bruteForceKey(1, bytes, len/2);
		if (score == NULL) {
			continue;
		}
		if (best == NULL || score->score < best->score) {
			best = score;
			bestLineNum = lineNum - 1;
			printf("New best score (%f) found for line '%s'\n", best->score, line);
		}
	}

	if (best != NULL) {
		printf("Decoded line %d: '%s' to string '%s' with key %d (%c)\n", bestLineNum, best->encodedText, best->decodedText,
				best->key[0], best->key[0]);
	} else {
		puts("Ruh-roh!");
	}
}
