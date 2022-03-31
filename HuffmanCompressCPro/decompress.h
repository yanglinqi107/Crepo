#pragma once
#include"Huffman.h"

int decompress(const char* pFilename);			

string binary_print_int(int x, int n);			//将压缩文件中的字符还原为8位10序列

int SearchHufTree(int snum, int ininum, const HTNode pHT[], char*& pbych, int& pos);		//根据还原的10序列遍历Huffman树，并将叶子存入pbych中

int WriteDecompressFile(const char* pFilename, const char* pbych, int nSize);	//将得到的pbych存入新的文件中得到解压文件
