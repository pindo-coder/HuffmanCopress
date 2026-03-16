#include "Huffman.h"
int Select(HFMNode PHT[], int nSize) {
	int minValue = 0x7FFFFFFF;
	int min = -1;
	for (int i = 0; i < nSize; i++) {
		if (PHT[i].weight < minValue && PHT[i].parent == -1) {
			min = i;
			minValue = PHT[i].weight;
		}
	}
	return min;
}
void CreatHuffmsnTree(HFMNode PHT[], int nSize, int weight[]) {
	for (int i = 0; i < nSize; i++) {
		PHT[i].weight = weight[i];
		PHT[i].parent = -1;
		PHT[i].lchild = -1;
		PHT[i].rchild = -1;
	}
	int Max = nSize * 2 - 1;
	for (int i = nSize; i < Max; i++) {
		PHT[i].weight = 0;
		PHT[i].parent = -1;
		PHT[i].lchild = -1;
		PHT[i].rchild = -1;
	}
	for (int i = nSize; i < Max; i++) {
		int min1, min2;
		min1 = Select(PHT, i);
		PHT[min1].parent = i;
		min2 = Select(PHT, i);
		PHT[min2].parent = i;
		PHT[i].weight = PHT[min1].weight + PHT[min2].weight;
		PHT[i].lchild = min1;
		PHT[i].rchild = min2;
		PHT[i].parent = -1;
	}
}
void TestHufTree( HFMNode PHT[]) {
	for (int i = 0; i < 511; i++) {
		printf("PHT[%3d]\tweight=%d\tparent=%d\tlchild=%d\trchild=%d\n", i, PHT[i].weight, PHT[i].parent, PHT[i].lchild, PHT[i].rchild);
	}
}
void TestHufTreeN(int root, HFMNode PHT[]) {
	std::cout << PHT[root].weight << " ";
	if (PHT[root].lchild != -1) {
		TestHufTreeN(PHT[root].lchild, PHT);
	}
	if (PHT[root].rchild != -1) {
		TestHufTreeN(PHT[root].rchild, PHT);
	}
}
void HuffmanCoding(int root, HFMNode PHT[], HFMCode codeTable[]) {
	if (root < 0) return;
	int parent = PHT[root].parent;
	// 如果没有父节点（根），确保有安全的初始值
	if (parent == -1) {
		codeTable[root].length = 0;
		codeTable[root].Code[0] = '\0';
	} else {
		// 只在 parent 有效时访问 parent 信息
		if (parent >= 0) {
			if (PHT[parent].lchild == root) {
				char newbit = '1';
				int len = codeTable[parent].length + 1;
				strcpy_s(codeTable[root].Code, sizeof(codeTable[root].Code), codeTable[parent].Code); // 先复制父节点的编码
				codeTable[root].Code[len - 1] = newbit;
				codeTable[root].Code[len] = '\0';
				codeTable[root].length = len;
			}
			else {
				char newbit = '0';
				int len = codeTable[parent].length + 1;
				strcpy_s(codeTable[root].Code, sizeof(codeTable[root].Code), codeTable[parent].Code);
				codeTable[root].Code[len - 1] = newbit;
				codeTable[root].Code[len] = '\0';
				codeTable[root].length = len;
			}
		} else {
			// 防护：非法 parent
			codeTable[root].length = 0;
			codeTable[root].Code[0] = '\0';
		}
	}
	if (PHT[root].lchild != -1) {
		HuffmanCoding(PHT[root].lchild, PHT, codeTable);
	}
	if (PHT[root].rchild != -1) {
		HuffmanCoding(PHT[root].rchild, PHT, codeTable);
	}
}
void TestHufCode(int root, HFMNode PHT[], HFMCode PHC[]) {
	if (root < 0)return;
	if (PHT[root].rchild == -1 && PHT[root].lchild == -1) {
		printf("0x%02X %s\n", root, PHC[root].Code);
	}
	if (PHT[root].lchild!=-1) {
		TestHufCode(PHT[root].lchild, PHT, PHC);
	}
	if (PHT[root].rchild!=-1) {
		TestHufCode(PHT[root].rchild, PHT, PHC);
	}
}

