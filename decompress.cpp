#include"decompress.h"
#include "Compress.h"
#include "Huffman.h"
int Decompress(const char* pfilename) {
	FILE* in;
	FILE* out;
	errno_t err = fopen_s(&in, pfilename, "rb");
	if (err != 0) {
		std::cout << "fail to open" << std::endl;
	}
	HEAD head;
	int n;
	n = fread(&head, sizeof(HEAD), 1, in);
	if (n != 1) {
		printf("读取文件头失败\n");
		return 1;
	}
	HFMNode PHT[511];
	CreatHuffmsnTree(PHT, 256, head.weight);
	HFMCode Code[511];
	HuffmanCoding(510, PHT, Code);
	char filename[260] = { 0 };
	strcpy_s(filename, sizeof(filename), pfilename);
	strcat_s(filename, sizeof(filename), head.type);
	errno_t err1 = fopen_s(&out, filename, "wb");
	char* deBuffer = (char*)malloc(sizeof(char) * head.length);
	if (!deBuffer) {
		std::cerr << "Memory allocation failed!" << std::endl;
		return -1;
	}
	int pos = 510;
	int ch;
	int count = 0;
	while (!feof(in)) {
		ch = getc(in);
		if (feof(in)) break;
		for (int i = 7; i >= 0; i--) {
			if (((ch >> i) & 1) == 1) {
				pos = PHT[pos].lchild;
			}
			else { 
				pos = PHT[pos].rchild;
			}
			if (pos < 256) {
				deBuffer[count++] = (char)(pos);
				pos = 510;
			}
		}
		//if (count >= head.length) break;
	}
	std::cout << "解压后长度=" << count << "解压前长度" << head.length;
	fwrite(deBuffer, 1, head.length, out);
	fclose(in);
	fclose(out);
	if (count != head.length) {
		std::cerr << "Warning: decompressed size (" << count << ") != original size (" << head.length << ")" << std::endl;
		return -1;
	}
	std::cout << "Decompressed to: " << filename << " (" << count << " bytes)" << std::endl;
	free(deBuffer);
	return 0;
}