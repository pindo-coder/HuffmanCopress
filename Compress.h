#pragma once
#include"Compress.h"
#include"Huffman.h"
struct HEAD{
	char type[20];//文件名后缀
	int length;
	int weight[256];
};
int initializeHead(HEAD& head, const char* pfilename);
int Compress(const char* pfilename, HFMCode Code[], HFMNode PHT[], int weight[]);
int WriteCompressedFile(const char* pfilename, const HEAD& head, const char* pBuffer, int nSize);