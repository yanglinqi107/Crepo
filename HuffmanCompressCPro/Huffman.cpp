#include<iostream>
#include"Huffman.h"
#include"Compress.h"
using namespace std;

int HuffmanTree(HTNode pHT[], int weight[])			//����Huffman��
{
	int i = 0;
	for (int i = 0; i < 256; ++i)
	{
		pHT[i + 1].weight  = weight[i];
	}
	int child1 = 0;
	int child2 = 0;
	
	for (int i = 256; i < 511;)
	{
		child1 = Select(pHT,i);
		pHT[child1].parent = i + 1;
		child2 = Select(pHT, i);
		pHT[child2].parent = pHT[child1].parent;
		pHT[++i].weight = pHT[child1].weight + pHT[child2].weight;
		pHT[i].lchild = child1;
		pHT[i].rchild = child2;
	}

	//TestHuffman(pHT);
	//cout << endl;
	//TestHufTreeN(511, pHT);
	//cout << endl;
	/*HuffmanCoding(511, pHT, pHC, s);
	cout << endl;
	TestHufCode(511, pHT, pHC);*/

	return 0;
}

void TestHuffman(HTNode pHT[])		//����Huffman��
{
	cout << endl;
	cout << "Byte\tWeight\tParent\tLchild\tRchild" << endl;
	for (int i = 1; i < 512; i++)
	{
		printf("pHT[%d]\t%d\t%d\t%d\t%d\n", i, pHT[i].weight, pHT[i].parent, pHT[i].lchild, pHT[i].rchild);
	}
}

int Select(HTNode pHT[], int nSize)		//��ѡ��С�ڵ㣬����Huffman���Ĺ���
{
	int minValue = 0x7FFFFFFF;//��Сֵ
	int min = 0;//Ԫ�ط���

	//�ҵ���СȨֵ��Ԫ�����
	for (int i = 1; i <= nSize; i++)
	{
		if (pHT[i].parent == 0 && pHT[i].weight < minValue)
		{
			minValue = pHT[i].weight;
			min = i;
		}
	}
	return min;
}

void TestHufTreeN(int root, HTNode pHT[])		//�������Huffman�����Ȩֵ
{
	cout << pHT[root].weight << " ";
	if (pHT[root].lchild != 0)
	{
		TestHufTreeN(pHT[root].lchild, pHT);
	}
	if (pHT[root].rchild != 0)
	{
		TestHufTreeN(pHT[root].rchild, pHT);
	}
}

void HuffmanCoding(int root, HTNode pHT[], string pHC[], string s)		//����Huffman����
{
	int rp = pHT[root].parent;

	if (rp != 0)
	{
		if (pHT[rp].lchild == root)
		{
			s += "0";
		}
		if (pHT[rp].rchild == root)
		{
			s += "1";
		}
	}
	if (pHT[root].lchild != 0)
	{
		HuffmanCoding(pHT[root].lchild, pHT, pHC, s);
	}
	if (pHT[root].rchild != 0)
	{
		HuffmanCoding(pHT[root].rchild, pHT, pHC, s);
	}
	if (pHT[root].lchild == 0 && pHT[root].rchild == 0)
	{
		pHC[root - 1].assign(s);
	}
	
}

void TestHufCode(int root, HTNode pHT[], string pHC[])			//��������ı���
{
	if (pHT[root].lchild == 0 && pHT[root].rchild == 0)
	{
		printf("0x%02X\t%s\n", root - 1, pHC[root - 1].c_str());
	}
	if (pHT[root].lchild)//��������
	{
		TestHufCode(pHT[root].lchild, pHT, pHC);
	}
	if (pHT[root].rchild)//�����Һ���
	{
		TestHufCode(pHT[root].rchild, pHT, pHC);
	}
}