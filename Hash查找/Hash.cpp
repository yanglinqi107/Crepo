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
	cout << "输入10个0~99之间的整数：" << endl;		//提示输入
	cin >> key[0] >> key[1] >> key[2] >> key[3] >> key[4] >> key[5] >> key[6] >> key[7] >> key[8] >> key[9];
	/*for (int i = 0; i < 10; i++)
	{
		int judge = false;
		int j = -1;
		do {
			cout << "输入第" << i + 1 << "个数：";
			cin >> j;
			while (getchar() != '\n');
			if (j < 0 || j>99)
			{
				judge = true;
			}
		} while (judge);
		key[i] = j;
	}*/
	for (int i = 0; i < 10; i++)			//创建hash表
	{
		Hash(key[i], H);
	}

	cout << "Hash表：\n";					//输出hash表
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

	int Key = -1;						  //通过关键字查找
	cout << "输入要查找的关键字：";
	cin >> Key;
	int judge = SearchHash(Key, H);
	if (judge == -1)
	{
		cout << "未找到！";
	}
	else
	{
		cout << judge << "\t" << H[judge];
	}

	return 0;
}

int Hash(int key, int H[])				//将关键字存入数组中，创建hash表	
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

int SearchHash(int key, int H[])		//查找hash表中的关键字
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