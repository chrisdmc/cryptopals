#include <stdbool.h>

void trimWhiteSpace(unsigned char *text, unsigned short *length);
bool isPrintableChar(char byte);
bool allPrintableChars(unsigned char *stringBytes, unsigned short length);
double scoreEnglishText(unsigned char *stringBytes, unsigned short length);
long getHammingSameLength(unsigned char *string1, unsigned char *string2, int length);
