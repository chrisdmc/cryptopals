void hexToBinary(char* hexString, unsigned short length,
		unsigned char* binaryOut);

void binaryToHex(unsigned char* binary, unsigned short length,
		char* hexOut);

void binaryToBase64(unsigned char* binary, unsigned short length,
		char* base64Out);

void base64ToBinary(char* base64, unsigned short length,
		unsigned char* binaryOut);

void hexToBase64(char* hex, unsigned short length, char* base64Out);

void base64ToHex(char* base64, unsigned short length, char* hexOut);

void transpose(unsigned char *from, unsigned char *to, int numBlocks, int blockLen);
