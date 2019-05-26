#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <StringUtils.h>
#include <BruteForce.h>

void copyBytes(unsigned char *from, unsigned char *to, unsigned short len) {
	for (unsigned short i = 0; i < len; i++) {
		*to = *from;
		to++;
		from++;
	}
}

keyScore *bruteForceKey(unsigned char keyLenBytes, unsigned char *encodedBytes,
		unsigned short messageLen) {
	if (keyLenBytes > 8) {
		// Too big to brute force
		return NULL;
	}

	unsigned char currKey[keyLenBytes];
	memset(currKey, 0, keyLenBytes);

	keyScore *best = NULL;
	unsigned char decodedBytes[messageLen + 1];
	memset(decodedBytes, 0, messageLen + 1);

	int done = 0;
	while (!done) {
	    unsigned short currentMessageLen = messageLen;
		unsigned char *encodedBytesTmp = encodedBytes;

		for (unsigned short i = 0; i < currentMessageLen; i++) {
			decodedBytes[i] = *encodedBytesTmp ^ currKey[i % keyLenBytes];
			encodedBytesTmp++;
		}

		// How do we know when we're done? First off, all the characters should be in the printable range.
		if (allPrintableChars(decodedBytes, currentMessageLen)) {
		    trimWhiteSpace(decodedBytes, &currentMessageLen);
			printf(
					"Key %d generated string '%s' which has all printable chars\n",
					currKey[0], decodedBytes);
			// Second, get a score for the text based on character frequencies
			double score = scoreEnglishText(decodedBytes, currentMessageLen);
			keyScore *currentScore = (keyScore*) malloc(sizeof(keyScore));
			copyBytes(encodedBytes, currentScore->encodedText, currentMessageLen);
			copyBytes(currKey, currentScore->key, keyLenBytes);
			copyBytes(decodedBytes, currentScore->decodedText, currentMessageLen + 1);
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

	return best;
}
