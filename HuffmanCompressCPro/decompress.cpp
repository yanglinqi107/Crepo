#include<fstream>
#include"Compress.h"
#include"decompress.h"
#include"Huffman.h"
using namespace std;

int decompress(const char* pFilename)
{
	HTNode pHT[512];				//Huffman�����ճ���0λ��
	//string pHC[256];				//Huffman����
	HEAD sHead;						//�����ļ�ͷ
	int Length = 0;					//
	char* pbych = NULL;				//
	int ch;				

	string pBuffer;
	//char* pBuffer = NULL;
	//pBuffer = new char;

	char filename[256] = { 0 };
	strcpy_s(filename, pFilename);
	strcat_s(filename, ".huf");

	FILE* in;
	fopen_s(&in, filename, "rb");
	if (!in)
	{
		cerr << filename << "�ļ���ʧ��" << endl;
		return 1;
	}
	while ((ch = fgetc(in)) != EOF)
	{
		Length++;
	}
	//cout << Length << endl;
	fseek(in, 0L, SEEK_SET);
	fread(&sHead, sizeof(HEAD), 1, in);
	//cout << sizeof(HEAD) << endl;
	//cout << sizeof(sHead) << endl;

	string s;
	HuffmanTree(pHT, sHead.weight);
	//HuffmanCoding(511, pHT, pHC, s);

	cout << "ԭ�ļ���С��" << sHead.length << "�ֽ�" << endl;
	cout << "ѹ���ļ���С��" << Length << "�ֽ�" << endl;
	cout << "ѹ���ļ����ͣ�" << sHead.type << endl;
	/*for (int i = 0; i < 256; i++)
	{
		cout << sHead.weight[i] << " ";
	}*/

	//������뻺������С
	int nSize = 0;
	nSize = Length - sizeof(HEAD);
	//cout << nSize << endl;

	int ininum = 511;
	int snum;
	int pos = 0;
	int i = 0;
	/*while (pBuffer[i] != '\0')
	{
		string pb = "";
		pb.assign(binary_print_int(pBuffer[i], 8));
		int j = 0;
		while (j < 8)
		{
			snum = pBuffer[j++] - 48;
			ininum = SearchHufTree(snum, ininum, pHT, pbych, pos);
		}
		i++;
	}*/
	////while (fread_s(pBuffer,1000000, sizeof(char), 100000, in));
	//int i = 0;
	//int ch;
	//int ininum = 511;
	//int snum;
	//int pos = 0;
	//string bistr;
	pbych = (char*)malloc(sizeof(char) * nSize * 8);
	while ((ch = fgetc(in)) != EOF)
	{
		i = 0;
		pBuffer.assign(binary_print_int(ch, 8));
		/*binary_print_int(ch, 8, bistr);
		pBuffer.assign(bistr);*/
		while (i < 8)
		{
			snum = pBuffer[i++] - 48;
			ininum = SearchHufTree(snum, ininum, pHT, pbych, pos);
		};
	}

	//cout << pBuffer;
	//cout << pbych[0] <<pbych[1]<<pbych[2]<< endl;
	
	fclose(in);

	WriteDecompressFile(pFilename, pbych, pos);
	cout << "��ѹ�ļ���С��" << pos << "�ֽ�" << endl;
	free(pbych);
	return 0;

	//cout << pbych;
	/*fstream table;
	table.open(pFilename, ios::binary | ios::in);
	if (!table)
	{
		cerr << "wenjiandakaishibai" << endl;
		return 1;
	}
	while (!table.eof())
	{
		table.read(pBuffer, len);
	}
	cout << pBuffer;
	delete pBuffer;
	table.close();*/
	
}

string binary_print_int(int x, int n)
{
	string bistr;
	//cout << "bits: ";
	for (int i = n - 1; i >= 0; --i)
	{
		if (x & (1 << i))
			bistr += '1';
		else
			bistr += '0';
	}
	return bistr;
}

int SearchHufTree(int snum, int ininum, const HTNode pHT[], char*& pbych, int& pos)
{
	if (snum == 0)
	{
		ininum = pHT[ininum].lchild;
	}
	if (snum == 1)
	{
		ininum = pHT[ininum].rchild;
	}
	if (pHT[ininum].lchild == 0 && pHT[ininum].rchild == 0)
	{
		pbych[pos++] = ininum - 1;
		//cout << pos << endl;
		ininum = 511;
	}
	return ininum;
}

int WriteDecompressFile(const char* pFilename, const char* pbych, int nSize)
{
	char filename[256] = "";//= "E:\\Pic1.bmp";
	int i = 0;
	while (pFilename[i] != '.')
	{
		filename[i] = pFilename[i];
		++i;
	}
	filename[i] = '1';
	while (pFilename[i] != '\0')
	{
		filename[i + 1] = pFilename[i];
		++i;
	}
	
	//�Զ���������ʽ���ļ�
	FILE* out;
	fopen_s(&out, filename, "wb");
	if (!out)
	{
		cerr << "�ļ���ʧ��" << endl;
		return 1;
	}
	fwrite(pbych, sizeof(char), nSize, out);
	fclose(out);
	return 0;
}
