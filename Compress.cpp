#include "Huffman.h"
#include "Compress.h"
int Encoding(const char* pfilename, const HFMCode PHC[], char*& pBuffer, const int nSize);
int WriteCompressedFile(const char* pfilename, const HEAD& head, const char* pBuffer, int nSize);
int initializeHead(HEAD& head, const char* pfilename);
int Compress(const char* pfilename,HFMCode Code[],HFMNode PHT[],int weight[]) {
	FILE* in;
	errno_t err = fopen_s(&in, pfilename, "rb");
	int ch;
	while ((ch = getc(in)) != EOF) {
		weight[ch]++;
	}
	fclose(in);
	CreatHuffmsnTree(PHT, 256, weight);
	HuffmanCoding(510, PHT, Code);
	int nSize = 0;
	for (int i = 0; i < 256; i++) {
		nSize += weight[i] * Code[i].length;
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	char* pBuffer =NULL;
	Encoding(pfilename, Code, pBuffer, nSize);
	if (!pBuffer) {
		std::cerr << "Encoding produced null buffer!" << std::endl;
		return -1;
	}
	HEAD head;
	head.length = 0;
	initializeHead(head, pfilename);
	std::cout << "Original file size: " << head.length * sizeof(char) << " bytes" << std::endl;
	WriteCompressedFile(pfilename, head, pBuffer, nSize);
	return 0;
}
char Str2byte(const char* pBinStr);
int Encoding(const char* pfilename, const HFMCode PHC[], char*& pBuffer, const int nSize) {
	FILE* in;
	errno_t err = fopen_s(&in, pfilename, "rb");
	pBuffer = (char*)malloc(nSize*sizeof(char));
	if(!pBuffer){
		std::cerr << "Memory allocation failed!" << std::endl;
		return -1;
	}
	char cd[256] = { 0 };
	int pos = 0;
	int ch;
	int len;
	while ((ch = fgetc(in)) != EOF) {
		strcat_s(cd, sizeof(cd), PHC[ch].Code);
		//cd[PHC[ch].length] = '\0';
		len = strlen(cd);
		while (len >= 8)
		{
			pBuffer[pos++] = Str2byte(cd);
			for (int i = 0; i < len - 8; i++) {
				cd[i] = cd[i + 8];
			}
			len = len - 8;
			cd[len] = '\0';
		}
	}
	if (strlen(cd) > 0) {
		for (int i = strlen(cd); i < 8; i++) {
			cd[i] = '0';
		}
		cd[8] = '\0';
		pBuffer[pos++] = Str2byte(cd);
	}
	fclose(in);
	return 0;
}
char Str2byte(const char* pBinStr) {
	char byte = 0;
	for (int i = 0; i < 8; i++) {
		byte <<= 1;
		if (pBinStr[i] == '1') {
			byte |= 1;
		}
	}
	return byte;	
}
int initializeHead(HEAD& head, const char* pfilename) {
	FILE* in;
	errno_t err = fopen_s(&in, pfilename, "rb");
	if (err != 0) {
		std::cerr << "Failed to open file: " << pfilename << std::endl;
		return -1;
	}
    const char* suffix = strrchr(pfilename, '.');//读取文件后缀
	strcpy_s(head.type, sizeof(head.type), suffix);
	int ch;
	for (int i = 0; i < 256; i++) {
		head.weight[i] = 0;
	}
	while ((ch = getc(in)) != EOF) {
		head.weight[ch]++;
		head.length++;
	}
	fclose(in);
	return 0;
}
int WriteCompressedFile(const char* pfilename, const HEAD& head, const char* pBuffer, int nSize) {
	char filename[260] = {0};
	strcpy_s(filename, sizeof(filename), pfilename);
	strcat_s(filename, sizeof(filename), ".huf");
	FILE* out;
	errno_t err = fopen_s(&out, filename, "wb");
	if (err != 0) {
		std::cerr << "Failed to open file for writing: " << pfilename << std::endl;
		return -1;
	}
	fwrite(&head, sizeof(HEAD), 1, out);
	fwrite(pBuffer, sizeof(char), nSize, out);
	fclose(out);
	std::cout << "Compressed file written: " << filename << std::endl;
	std::cout << "Compressed file size: " << sizeof(HEAD) + nSize * sizeof(char)+1+strlen(pfilename) << " bytes" << std::endl;
	std::cout << "压缩率: " << ((sizeof(HEAD) + nSize * sizeof(char) + 1 + strlen(pfilename)) / (double)(head.length * sizeof(char))) * 100 << "%" << std::endl;
	int len = strlen(pBuffer);
	return len;
}