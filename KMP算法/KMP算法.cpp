#include <iostream>
using namespace std;

// T是模式串，tLen是T的长度
void getnext(char T[], int next[], int tLen)
{
	int j = 0, k = -1;
	next[0] = -1;
	while (j < tLen - 1)	// 第j个数决定j+1，所以tLen减1
	{
		if (k == -1 || T[j] == T[k]) {
			++k; ++j;
			next[j] = k;
		}
		else {
			k = next[k];
		}
	}
}

int KMP(char S[], char T[], int next[], int sLen, int tLen)
{
	int i = 0, j = 0;
	while (i < sLen && j < tLen)
	{
		if (j == -1 || S[i] == T[j]) {
			++i; ++j;
		}
		else {
			j = next[j];
		}
	}
	if (j == tLen) return i - j;
	else return -1;
}

int main()
{
	char T[] = "abaababc";
	char S[] = "abacabaababcabc";
	int tLen = sizeof(T) / sizeof(char) - 1;
	int sLen = sizeof(S) / sizeof(char) - 1;
	int* next = new int[tLen];
	getnext(T, next, tLen);
	/*for (int i = 0; i < 8; ++i) {
		cout << next[i] << " ";
	}
	cout << endl;*/
	int pos = KMP(S, T, next, sLen, tLen);
	cout << pos << endl;
	delete[] next;
	return 0;
}