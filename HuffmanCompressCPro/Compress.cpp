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
	cout << sHead.length << "�ֽ�" << endl;
	HTNode pHT[512];				//Huffman�����ճ���0λ��
	string pHC[256];				//Huffman����
	string s;
	
	//int weight[256] = { 0 };
	//�Զ���������ʽ���ļ�
	/*FILE* in;
	fopen_s(&in, pFilename, "rb");
	if (!in)
	{
		cerr << "���ļ�ʧ�ܣ�" << endl;
		return 1;
	}*/
	//int ch;
	////ɨ���ļ������Ȩ��
	//while ((ch = getc(in)) != EOF)
	//{
	//	sHead.weight[ch]++;
	//}
	////�ر��ļ�
	//fclose(in);
	//cout << sizeof(sHead) << endl;
	HuffmanTree(pHT,sHead.weight);
	HuffmanCoding(511, pHT, pHC, s);
	//TestHufCode(511, pHT, pHC);

	//������뻺������С
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += sHead.weight[i] * pHC[i].length();
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	//cout << nSize << endl;
	//��ԭ�ļ�����ѹ������
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
	cout << len << "�ֽ�" << endl;
	cout << "ѹ��������" << (double)len / sHead.length * 100 << "%" << endl;
	cout << endl;
	//decompress(pFilename, pHT, pHC, len);
	return 0;
}

char Str2byte(const char* pBinStr)
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;//����һλ
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
		cerr << "���ٻ�����ʧ��" << endl;
		return 1;
	}

	//�Զ���������ʽ���ļ�
	FILE* in;
	fopen_s(&in, pFilename, "rb");
	if (!in)
	{
		cerr << "���ļ�ʧ�ܣ�" << endl;
		return 1;
	}
	//string cd = "0";
	char cd[SIZE] = { '\0' };	//������
	int pos = 0; //������ָ��
	int ch;
	//ɨ���ļ�������Huffman����������ѹ����ѹ������ݴ浽��������
	while ((ch = fgetc(in)) != EOF)
	{
		strcat_s(cd, pHC[ch].c_str());//��HC���Ʊ��봮��cd
		//cd.append(pHC[ch + 1]);
		//ѹ������
		while (strlen(cd) >= 8)
		//while (cd.length() >= 8)
		{
			//��ȡ�ַ�����ߵ�8���ַ���������ֽ�
			pBuffer[pos++] = Str2byte(cd);
			

		//	//pBuffer[pos++] = Str2byte(cd);
		//	//Str2byte(cd);
			//�ַ�����������8���ֽ�
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
	//��ʼ���ļ�ͷ
	strcpy_s(sHead.type, "HUF");//�ļ�����
	sHead.length = 0;//ԭ�ļ�����
	//for (int i = 0; i < SIZE; i++)
	//{
	//	sHead.weight[i] = 0;//Ȩֵ
	//}
	//�Զ���������ʽ���ļ�
	FILE* in;
	fopen_s(&in, pFilename, "rb");
	if (!in)
	{
		cerr << "���ļ�ʧ��" << endl;
		return 1;
	}
	int ch;
	int i = 0;
	//ɨ���ļ������Ȩ��
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
	//�����ļ���
	char filename[256] = { 0 };
	strcpy_s(filename, pFilename);
	strcat_s(filename, ".huf");

	//�Զ���������ʽ���ļ�
	FILE* out;
	fopen_s(&out, filename, "wb");
	if (!out)
	{
		cerr << "�ļ���ʧ��" << endl;
		return 1;
	}
	//д�ļ�ͷ
	fwrite(&sHead, sizeof(HEAD), 1, out);
	//дѹ����ı���
	fwrite(pBuffer, sizeof(char), nSize, out);
	//�ر��ļ����ͷ��ļ�ָ��
	fclose(out);
	out = NULL;

	cout << "����ѹ���ļ���" << filename << endl;
	int len = sizeof(HEAD) + nSize;
	//cout << strlen(pFilename) + 1 << endl;
	return len;

}