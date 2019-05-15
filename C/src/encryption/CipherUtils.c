int xor(unsigned char bytes1[], unsigned char bytes2[], unsigned char result[], unsigned short length) {
	for (int i = 0; i < length; i++) {
		result[i] = bytes1[i] ^ bytes2[i];
	}

	return 0;
}
