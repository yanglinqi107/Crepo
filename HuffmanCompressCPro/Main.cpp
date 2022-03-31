#include<iostream>
#include<stdlib.h>
#include"Huffman.h"
#include"Compress.h"
#include"decompress.h"
using namespace std;

int main()
{
	/*char cd[] = "10110010";
	Str2byte(cd);*/
	/*int x = -27;
	binary_print_int(x,8);*/
	cout << "============Huffman文件压缩===============" << endl;
	cout << "请输入文件名：";
	char filename[256] = "";	//记录文件名 Pic.bmp 最好是bmp图片
	cin >> filename;

	

	//显示256中字节的出现的次数
	/*cout << "Byte\t" << "Weight" << endl;
	for (int i = 0; i < 256; i++)
	{
		printf("0x%02X\t%d\n", i, weight[i]);
	}*/

	/*HTNode pHT[512];
	string pHC[256];
	string s;

	HuffmanTree(pHT, weight);*/


	Compress(filename);
	decompress(filename);
	return 0;
}