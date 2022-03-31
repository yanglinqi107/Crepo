#pragma once
#include <string>
using namespace std;
//Huffman���ڵ�
struct HTNode
{
	int weight = 0; //Ȩֵ
	int parent = 0; //���ڵ�
	int lchild = 0; //����
	int rchild = 0; //�Һ���
};

int HuffmanTree(HTNode pHT[], int weight[]);

void TestHuffman(HTNode pHT[]);

int Select(HTNode pHT[], int nSize);

void TestHufTreeN(int root, HTNode pHT[]);

void HuffmanCoding(int root, HTNode pHT[], string pHC[], string s);

void TestHufCode(int root, HTNode pHT[], string pHC[]);


