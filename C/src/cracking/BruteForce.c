#include <stdio.h>
#include <stdlib.h>
#include <CipherUtils.h>
#include <StringUtils.h>

typedef struct KeyAndScore {
	unsigned char key[8];
	unsigned char keyLen;
	unsigned char decodedText[65536];
	unsigned short textLen;
	double score;
} keyScore;

void copyBytes(unsigned char *from, unsigned char *to, unsigned short len) {
	for (unsigned short i = 0; i < len; i++) {
		*to = *from;
		to++;
		from++;
	}
}

bool bruteForceKey(unsigned char keyLenBytes, unsigned char *encodedBytes,
		unsigned char *decodedBytes, unsigned short messageLen,
		unsigned char *foundKey) {
	if (keyLenBytes > 8) {
		// Too big to brute force
		return false;
	}

	unsigned char currKey[keyLenBytes];

	keyScore *best = NULL;

	int done = 0;
	while (!done) {
		unsigned char *encodedBytesTmp = encodedBytes;
		unsigned char *decodedBytesTmp = decodedBytes;

		for (unsigned short i = 0; i < messageLen; i++) {
			*decodedBytesTmp = *encodedBytesTmp ^ currKey[i % keyLenBytes];
			decodedBytesTmp++;
			encodedBytesTmp++;
		}

		// How do we know when we're done? First off, all the characters should be in the printable range.
		if (allPrintableChars(decodedBytes, messageLen)) {
			printf(
					"Key %d generated string '%s' which has all printable chars\n",
					currKey[0], decodedBytes);
			// Second, get a score for the text based on character frequencies
			double score = scoreEnglishText(decodedBytes, messageLen);
			printf("String '%s' scored %f\n", decodedBytes, score);
			keyScore *currentScore = (keyScore*) malloc(sizeof(keyScore));
			copyBytes(currKey, currentScore->key, keyLenBytes);
			currentScore->keyLen = keyLenBytes;
			copyBytes(decodedBytes, currentScore->decodedText, messageLen);
			currentScore->textLen = messageLen;
			currentScore->score = score;
			if (best == NULL || currentScore->score < best->score) {
				printf("New best = %p, score = %f, key = %d, text = '%s'\n",
						currentScore, currentScore->score, currentScore->key[0],
						currentScore->decodedText);
				best = currentScore;
			}
		}

		for (unsigned char i = keyLenBytes - 1; i >= 0; i--) {
			currKey[i]++;
			if (currKey[i] > 0) {
				break;
			}
			if (i == 0) {
				done = 1;
				break;
			}
		}
	}

	if (best != NULL) {
		for (unsigned char i = 0; i < keyLenBytes; i++) {
			*foundKey = best->key[i];
			foundKey++;
		}
		for (unsigned short i = 0; i < messageLen; i++) {
			*decodedBytes = best->decodedText[i];
			decodedBytes++;
		}
		return true;
	}

	return false;
}
