#include<iostream>
#include<stdlib.h>
#include"Huffman.h"
#include"Compress.h"
#include"decompress.h"
using namespace std;
int main(){
	cout << "=========哈夫曼文件压缩=========" << endl;
	int temp1;
	cout << "1.压缩" << endl;
	cout << "2.解压" << endl;
	cin >> temp1;
	if (temp1 == 1) {
		cout << "请输入文件名：";
		char filename[256];
		cin >> filename;
		//压缩文件
		int weight[256] = { 0 };
		HFMNode PHT[512];
		HFMCode Code[511];
		int test = Compress(filename,Code,PHT,weight);
		if (test == 0) {
			cout << "文件压缩成功！" << endl;
		}
		int temp=-1;
		while (temp != 0) {
			cout << "1.打印文件各个字节权值" << endl;
			cout << "2.打印各字节对于的哈夫曼编码" << endl;
			cout << "3.打印形成的哈夫曼数" << endl;
			cout << "4.继续进行解压缩" << endl;
			cout << "0.结束程序" << endl;
			cin >> temp;
			if (temp == 1) {
				cout << "byte" << "weight" << endl;
				//打印字节
				for (int i = 0; i < 256; i++) {
					printf("0x%02X %d\n", i, weight[i]);
				}
			}
			else if (temp == 2) {
				TestHufCode(510, PHT, Code);
			}
			else if (temp == 3) {
				TestHufTree(PHT);
				TestHufTreeN(510, PHT);
			}
			else if (temp == 4) {
				cout << "请输入文件名：";
				char filename[256];
				cin >> filename;
				Decompress(filename);
				cout << "解压成功" << endl;
				return 0;
			}
		}
		return 0;
	}
	else if (temp1 == 2) {
		cout << "请输入文件名：";
		char filename[256];
		cin >> filename;
		Decompress(filename);
		cout << "解压成功" << endl;
		return 0;
	}

}