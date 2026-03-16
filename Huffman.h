#pragma once
#include<iostream>
#include<string.h>
typedef struct HFMNode {
	int weight;
	int parent;
	int lchild;
	int rchild;
};
typedef struct HFMCode {
	char Code[256];
	int length;
};
int Select(HFMNode PHT[],int nSize);
void CreatHuffmsnTree(HFMNode PHT[], int nSize, int weight[]);
void TestHufTree(HFMNode PHT[]);
void TestHufTreeN(int root, HFMNode PHT[]);
void HuffmanCoding(int root, HFMNode PHT[], HFMCode codeTable[]);
void TestHufCode(int root, HFMNode PHT[], HFMCode PHC[]);
