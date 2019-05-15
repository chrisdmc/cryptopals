#include <StringUtils.h>
#include <stdio.h>
#include <math.h>

static double FREQUENCY_LIST[26] = { 0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228,
		0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929,
		0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.0236, 0.0015, 0.01974, 0.00074 };

bool isPrintableChar(unsigned char byte) {
	return (byte >= 32 && byte <= 126);
}

bool isAlphaChar(unsigned char c) {
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

unsigned char normalizeChar(unsigned char c) {
	if (c >= 97) {
		return c - 97;
	} else {
		return c - 65;
	}
}

bool allPrintableChars(unsigned char *stringBytes, unsigned short length) {
	unsigned char *stringStart = stringBytes;
	for (unsigned char c = *stringBytes; stringBytes - stringStart < length; c =
			*(++stringBytes)) {
		if (!isPrintableChar(c)) {
			return false;
		}
	}

	return true;
}

double scoreEnglishText(unsigned char *stringBytes, unsigned short length) {
	double score = 0.0;
	unsigned short charFrequencies[26];
	int alphaCharCount = 0;

	unsigned char *stringStart = stringBytes;
	for (unsigned char c = *stringBytes; stringBytes - stringStart < length; c =
			*(++stringBytes)) {
		if (isAlphaChar(c)) {
			charFrequencies[normalizeChar(c)]++;
			alphaCharCount++;
		}
	}

	double variance = 0.0;
	for (unsigned char i = 0; i < 26; i++) {
		unsigned short charFrequency = charFrequencies[i];
		variance += pow(((charFrequency / alphaCharCount) - FREQUENCY_LIST[i]),
				2.0);
	}

	score = sqrt(variance / 26);

	return score;
}
