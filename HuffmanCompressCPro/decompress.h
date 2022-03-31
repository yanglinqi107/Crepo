#pragma once
#include"Huffman.h"

int decompress(const char* pFilename);			

string binary_print_int(int x, int n);			//��ѹ���ļ��е��ַ���ԭΪ8λ10����

int SearchHufTree(int snum, int ininum, const HTNode pHT[], char*& pbych, int& pos);		//���ݻ�ԭ��10���б���Huffman��������Ҷ�Ӵ���pbych��

int WriteDecompressFile(const char* pFilename, const char* pbych, int nSize);	//���õ���pbych�����µ��ļ��еõ���ѹ�ļ�
