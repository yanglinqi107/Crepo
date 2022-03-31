#pragma once
#include<iostream>
#include <string>
#define SIZE 256
using namespace std;

struct HEAD
{
	char type[4];	//�ļ�����
	int length = 0;		//ԭ�ļ�����
	int weight[256] = { 0 };//Ȩֵ����
};

int Compress(const char* pFilename);

char Str2byte(const char* pBinStr);

int Encode(const char* pFilename, string pHC[], char* &pBuffer, const int nSize);

int InitHead(const char* pFilename, HEAD& sHead);

int WriteFile(const char* pFilename, const HEAD sHead, const char* pBuffer, const int nSize);