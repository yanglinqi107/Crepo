#include <iostream>
#include <climits>

using namespace::std;

int Hash(int key, int H[]);

int SearchHash(int key, int H[]);

int main()
{
	int H[13];
	fill(H, H+13, INT_MIN);
	int key[10];
	cout << "����10��0~99֮���������" << endl;		//��ʾ����
	cin >> key[0] >> key[1] >> key[2] >> key[3] >> key[4] >> key[5] >> key[6] >> key[7] >> key[8] >> key[9];
	/*for (int i = 0; i < 10; i++)
	{
		int judge = false;
		int j = -1;
		do {
			cout << "�����" << i + 1 << "������";
			cin >> j;
			while (getchar() != '\n');
			if (j < 0 || j>99)
			{
				judge = true;
			}
		} while (judge);
		key[i] = j;
	}*/
	for (int i = 0; i < 10; i++)			//����hash��
	{
		Hash(key[i], H);
	}

	cout << "Hash��\n";					//���hash��
	for (int i = 0; i < 13; i++)
		cout << i << "\t";
	cout << endl;
	for (int i = 0; i < 13; i++)
	{
		if (H[i] == INT_MIN)
		{
			cout << "NULL\t";
		}
		else
		{
			cout << H[i] << "\t";
		}
	}
	cout << endl;

	int Key = -1;						  //ͨ���ؼ��ֲ���
	cout << "����Ҫ���ҵĹؼ��֣�";
	cin >> Key;
	int judge = SearchHash(Key, H);
	if (judge == -1)
	{
		cout << "δ�ҵ���";
	}
	else
	{
		cout << judge << "\t" << H[judge];
	}

	return 0;
}

int Hash(int key, int H[])				//���ؼ��ִ��������У�����hash��	
{
	int Key = key;
	key = key % 13;
	while (H[key] != INT_MIN)
	{
		++key;
		key = key % 13;
	}
	H[key] = Key;
	return key;
}

int SearchHash(int key, int H[])		//����hash���еĹؼ���
{
	int Key = key;
	key = key % 13;
	while (H[key] != Key)
	{
		if (H[key] == INT_MIN)
		{
			return -1;
		}
		++key;
		key = key % 13;
	}
	return key;
}