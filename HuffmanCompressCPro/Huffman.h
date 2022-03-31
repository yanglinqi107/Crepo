#pragma once
#include <string>
using namespace std;
//Huffman树节点
struct HTNode
{
	int weight = 0; //权值
	int parent = 0; //父节点
	int lchild = 0; //左孩子
	int rchild = 0; //右孩子
};

int HuffmanTree(HTNode pHT[], int weight[]);

void TestHuffman(HTNode pHT[]);

int Select(HTNode pHT[], int nSize);

void TestHufTreeN(int root, HTNode pHT[]);

void HuffmanCoding(int root, HTNode pHT[], string pHC[], string s);

void TestHufCode(int root, HTNode pHT[], string pHC[]);


