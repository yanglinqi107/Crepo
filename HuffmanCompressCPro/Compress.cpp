#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include"Compress.h"
#include"Huffman.h"
#include"decompress.h"

int Compress(const char* pFilename)
{
	HEAD sHead;

	InitHead(pFilename, sHead);
	cout << sHead.length << "字节" << endl;
	HTNode pHT[512];				//Huffman树（空出第0位）
	string pHC[256];				//Huffman编码
	string s;
	
	//int weight[256] = { 0 };
	//以二进制流形式打开文件
	/*FILE* in;
	fopen_s(&in, pFilename, "rb");
	if (!in)
	{
		cerr << "打开文件失败！" << endl;
		return 1;
	}*/
	//int ch;
	////扫描文件，获得权重
	//while ((ch = getc(in)) != EOF)
	//{
	//	sHead.weight[ch]++;
	//}
	////关闭文件
	//fclose(in);
	//cout << sizeof(sHead) << endl;
	HuffmanTree(pHT,sHead.weight);
	HuffmanCoding(511, pHT, pHC, s);
	//TestHufCode(511, pHT, pHC);

	//计算编码缓冲区大小
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += sHead.weight[i] * pHC[i].length();
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	//cout << nSize << endl;
	//对原文件进行压缩编码
	char* pBuffer = NULL;
	Encode(pFilename, pHC, pBuffer, nSize);
	if (!pBuffer)
	{
		return 1;
	}

	//cout << endl << pBuffer << endl;
	int len = WriteFile(pFilename, sHead, pBuffer, nSize);

	free(pBuffer);
	if (len < 0)
	{
		return 1;
	}
	//delete pBuffer;
	cout << len << "字节" << endl;
	cout << "压缩比例：" << (double)len / sHead.length * 100 << "%" << endl;
	cout << endl;
	//decompress(pFilename, pHT, pHC, len);
	return 0;
}

char Str2byte(const char* pBinStr)
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;//左移一位
		if (pBinStr[i] == '1') 
		{
			b = b | 0x01;
		}
	}
	
	return b;
}

int Encode(const char* pFilename, string pHC[], char* &pBuffer, const int nSize)
{
	pBuffer = (char*)malloc(nSize * sizeof(char));
	//pBuffer = new char;

	if (!pBuffer)
	{
		cerr << "开辟缓冲区失败" << endl;
		return 1;
	}

	//以二进制流形式打开文件
	FILE* in;
	fopen_s(&in, pFilename, "rb");
	if (!in)
	{
		cerr << "打开文件失败！" << endl;
		return 1;
	}
	//string cd = "0";
	char cd[SIZE] = { '\0' };	//工作区
	int pos = 0; //缓冲区指针
	int ch;
	//扫描文件，根据Huffman编码对其进行压缩，压缩结果暂存到缓冲区。
	while ((ch = fgetc(in)) != EOF)
	{
		strcat_s(cd, pHC[ch].c_str());//从HC复制编码串到cd
		//cd.append(pHC[ch + 1]);
		//压缩编码
		while (strlen(cd) >= 8)
		//while (cd.length() >= 8)
		{
			//截取字符串左边的8个字符，编码成字节
			pBuffer[pos++] = Str2byte(cd);
			

		//	//pBuffer[pos++] = Str2byte(cd);
		//	//Str2byte(cd);
			//字符串整体左移8个字节
		//	cd.assign(cd, 8, cd.length() - 8);
			for (int i = 0; i < SIZE - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
		
	}
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
	//int i = 0;
	//while (cd[i]!='\0')
	//{
	//	pBuffer[pos++] = cd[i++];
	//	//Str2byte(cd);
	//}
	fclose(in);
	return 0;
}

int InitHead(const char* pFilename, HEAD& sHead)
{
	//初始化文件头
	strcpy_s(sHead.type, "HUF");//文件类型
	sHead.length = 0;//原文件长度
	//for (int i = 0; i < SIZE; i++)
	//{
	//	sHead.weight[i] = 0;//权值
	//}
	//以二进制流形式打开文件
	FILE* in;
	fopen_s(&in, pFilename, "rb");
	if (!in)
	{
		cerr << "打开文件失败" << endl;
		return 1;
	}
	int ch;
	int i = 0;
	//扫描文件，获得权重
	while ((ch = fgetc(in)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}
	fclose(in);
	in = NULL;

	return 0;
}

int WriteFile(const char* pFilename, const HEAD sHead, const char* pBuffer, const int nSize)
{
	//生成文件名
	char filename[256] = { 0 };
	strcpy_s(filename, pFilename);
	strcat_s(filename, ".huf");

	//以二进制流形式打开文件
	FILE* out;
	fopen_s(&out, filename, "wb");
	if (!out)
	{
		cerr << "文件打开失败" << endl;
		return 1;
	}
	//写文件头
	fwrite(&sHead, sizeof(HEAD), 1, out);
	//写压缩后的编码
	fwrite(pBuffer, sizeof(char), nSize, out);
	//关闭文件，释放文件指针
	fclose(out);
	out = NULL;

	cout << "生成压缩文件：" << filename << endl;
	int len = sizeof(HEAD) + nSize;
	//cout << strlen(pFilename) + 1 << endl;
	return len;

}