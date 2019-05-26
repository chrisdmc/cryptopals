#include <stdbool.h>

typedef struct KeyAndScore {
    unsigned char encodedText[64];
	unsigned char key[8];
	unsigned char decodedText[64];
	double score;
} keyScore;

keyScore *bruteForceKey(unsigned char keyLenBytes, unsigned char *encodedBytes,
		unsigned short messageLen);
