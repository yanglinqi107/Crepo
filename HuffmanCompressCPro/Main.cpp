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
	cout << "============Huffman�ļ�ѹ��===============" << endl;
	cout << "�������ļ�����";
	char filename[256] = "";	//��¼�ļ��� Pic.bmp �����bmpͼƬ
	cin >> filename;

	

	//��ʾ256���ֽڵĳ��ֵĴ���
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