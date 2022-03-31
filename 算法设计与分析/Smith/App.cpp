#include "App.h"

using namespace std;

//��Smith�����㷨��������
int Smith()
{
	int* p = new int;
	int n = 0;
	if (!p)
	{
		return 0;
	}
	//p = NULL;
	//cout << "��������������0������" << endl;
	int i = 0;
	do {
		cin >> p[i];
		++i;
	} while (p[i - 1] != 0);

	--i;
	for (int j = 0; j < i; ++j)
	{
		n = p[j] + 1;
		while (!IsSmith(n))
		{
			++n;
		}
		cout << n << endl;
	}
	if (!p)
	{
		delete p;
	}
	return 0;
}

int Add(int n)
{
	int sum = 0;
	while (n > 0)
	{
		sum += n % 10;
		n /= 10;
	}
	return sum;
}

bool IsSmith(int n)
{
	/*string s = "";
	s = to_string(n);*/
	int sum1 = 0, sum2 = 0;
	sum1 = Add(n);
	int temp = n;
	int i = 2;
	while (i <= temp)
	{
		if (temp % i == 0)
		{
			sum2 += Add(i);
			temp /= i;
			i = 2;
		}
		else
		{
			++i;
		}
		if (i > temp / 2)
		{
			sum2 += Add(temp);
			break;
		}
	}
	if (sum1 == sum2)
	{
		return true;
	}
	return false;
}

//����ӽ������㷨��������
int RecentNumber()
{
	int n;
	cin >> n;
	int* p = new int[n];
	int i = 0;
	while (i < n) {
		cin >> p[i++];
	}

	int small = 100000;
	int temp;

	for (int j = 0; j < n - 1; j++)
	{
		for (int k = j + 1; k < n; k++)
		{
			temp = p[j] - p[k];
			temp = abs(temp);
			if (small > temp)
			{
				small = temp;
			}
		}
	}
	cout << small;
	return 0;
}

//�ַ���ѭ������
int ShiftLeft()
{
	int n, k;
	cin >> n;
	cin >> k;
	char* dp = new char[n];
	char* temp = new char[k];
	cin >> dp;
	int i = 0;
	while (i < k)
	{
		temp[i] = dp[i];
		++i;
	}
	i = k;
	while (i < n)
	{
		dp[i - k] = dp[i];
		++i;
	}
	i = n - k;
	while (i < n)
	{
		dp[i] = temp[i + k - n];
		++i;
	}
	cout << dp;
	if (!dp)
	{
		delete[] dp;
	}
	if (!temp)
	{
		delete[] temp;
	}
	return 0;
}

//����������
int InverseNumber()
{
	int n;
	int num = 0;
	cin >> n;
	int* dp = new int[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> dp[i];
	}
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			if (dp[i] > dp[j])
			{
				++num;
			}
		}
	}
	cout << num;

	delete[] dp;
	return 0;
}

//��ݼ������У����������
int DecreaseOrder()
{
	//���г���
	int n;
	cin >> n;
	if (n > 25)
	{
		return 0;
	}
	
	//���������n�����ݣ���0λ
	double* hNum = new double[n + 1];
	for (int i = 1; i <= n; ++i)
	{
		cin >> hNum[i];
	}

	//L[i]��ʾǰi��������ݼ���������0λ
	int* L = new int[n + 1];

	for (int i = 1; i <= n; ++i)
	{
		int temp = 1;
		for (int k = 1; k < i; ++k)
		{
			if (hNum[k] >= hNum[i])
			{
				if (temp < L[k] + 1)
				{
					temp = L[k] + 1;
				}
			}
		}
		L[i] = temp;
	}
	cout << L[n];

	if (!hNum)
	{
		delete[] hNum;
	}
	return 0;
}

//��󹫹�������
int CommonOrder()
{
	//����������ַ�����
	string s1 = "";
	cin >> s1;
	string s2 = "";
	cin >> s2;
	
	/*cout << s1 << endl;
	cout << s2 << endl;*/

	//�����ַ����еĳ��ȣ����ڽ���
	int m = s1.length();
	int n = s2.length();

	/*cout << m << endl;
	cout << n << endl;*/

	//����m+1��n+1�ľ��󣬿ճ�0��0�У���ֵΪ0�����Ⱦ���
	int** L = new int* [m + 1];
	for (int i = 0; i <= m; ++i)
	{
		L[i] = new int[n + 1];
	}
	//����m+1��n+1�ľ��󣬿ճ�0��0�У���ֵΪ0��״̬����
	//1-��Խ��߻��ݣ�2-������ݣ�3-���ϻ���
	int** S = new int* [m + 1];
	for (int i = 0; i <= m; ++i)
	{
		S[i] = new int[n + 1];
	}

	fill(L[0], L[0] + (n + 1), 0);
	fill(S[0], S[0] + (n + 1), 0);
	for (int i = 0; i <= m; ++i)
	{
		L[i][0] = 0;
		S[i][0] = 0;
	}

	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				L[i][j] = L[i - 1][j - 1] + 1;
				S[i][j] = 1;
			}
			else 
			{
				if (L[i - 1][j] < L[i][j - 1])
				{
					L[i][j] = L[i][j - 1];
					S[i][j] = 2;
				}
				else 
				{
					L[i][j] = L[i - 1][j];
					S[i][j] = 3;
				}
			}
		}
	}
	
	//���Դ��룬���L����
	for (int i = 0; i <= m; ++i)
	{
		for (int j = 0; j <= n; ++j)
		{
			printf_s("%4d", L[i][j]);
		}
		cout << endl;
	}
	cout << endl;
	//���Դ��룬���S����
	for (int i = 0; i <= m; ++i)
	{
		for (int j = 0; j <= n; ++j)
		{
			printf_s("%4d", S[i][j]);
		}
		cout << endl;
	}

	//���������������
	char* s3 = new char;
	//string s3 = "";
	int i = m;
	int j = n;
	int k = 0;
	while (i > 0 && j > 0)
	{
		switch (S[i][j])
		{
			case 1: 
			{
				--i;
				--j;
				//++k;
				s3[k++] = s1[i];
				break;
			}
			case 2:
			{
				//++k; 
				--j;
				//s3[k++] = s2[j];
				break;
			}
			case 3:
			{
				--i;
				//++k;
				//s3[k++] = s1[i];
				break;
			}
			default:
				break;
		}
	}
	do
	{
		--k;
		cout << s3[k];
	} while (k != 0);

	for (int i = 0; i <= m; ++i)
	{
		delete[] L[i];
		delete[] S[i];
	}
	if (!s3)
	{
		delete s3;
	}
	return 0;
}

//����s1��s2���е��������s4
int CommonOrder2()
{
	//����������ַ�����
	string s1 = "";
	cin >> s1;
	string s2 = "";
	cin >> s2;

	//�����ַ����еĳ��ȣ����ڽ���
	int m = s1.length();
	int n = s2.length();

	//����m+1��n+1�ľ��󣬿ճ�0��0�У���ֵΪ0�����Ⱦ���
	int** L = new int* [m + 1];
	for (int i = 0; i <= m; ++i)
	{
		L[i] = new int[n + 1];
	}
	//����m+1��n+1�ľ��󣬿ճ�0��0�У���ֵΪ0��״̬����
	int** S = new int* [m + 1];
	for (int i = 0; i <= m; ++i)
	{
		S[i] = new int[n + 1];
	}

	fill(L[0], L[0] + (n + 1), 0);
	fill(S[0], S[0] + (n + 1), 0);
	for (int i = 0; i <= m; ++i)
	{
		L[i][0] = 0;
		S[i][0] = 0;
	}

	//1-��Խ��߻��ݣ�2-������ݣ�3-���ϻ���
	for (int i = 1; i <= m; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				L[i][j] = L[i - 1][j - 1] + 1;
				S[i][j] = 1;
			}
			else
			{
				if (L[i - 1][j] < L[i][j - 1])
				{
					L[i][j] = L[i][j - 1];
					S[i][j] = 2;
				}
				else
				{
					L[i][j] = L[i - 1][j];
					S[i][j] = 3;
				}
			}
		}
	}
	int len = L[m][n];//����
	//���������������
	char* s3 = new char[len];
	int i = m;
	int j = n;
	int k = 0;
	while (i > 0 && j > 0)
	{
		switch (S[i][j])
		{
		case 1:
		{
			--i;
			--j;
			s3[k++] = s1[i];
			break;
		}
		case 2:
		{
			--j;
			break;
		}
		case 3:
		{
			--i;
			break;
		}
		default:
			break;
		}
	}

	//��s2�е�s3ȥ���������ӵ�s1��
	string s4 = s1;
	j = 0;
	do
	{
		--k;
		if (s3[k] == s2[j])
		{
			++j;
			continue;
		}
		s4 += s2[j];
		++k;
		++j;
	} while (k != 0);
	for (; j < n; ++j)
	{
		s4 += s2[j];
	}
	cout << s4 << endl;
	for (int i = 0; i <= m; ++i)
	{
		delete[] L[i];
		delete[] S[i];
	}
	if (!s3)
	{
		delete[] s3;
	}
	return 0;
}

int Route()
{
	int m;
	cin >> m;
	int n;
	cin >> n;

	//�����ڴ棬��������R[i][j]��ʾ��[0][0]��[i][j]��·����
	int** R = new int* [m];
	for (int i = 0; i < m; i++)
	{
		R[i] = new int[n];
	}
	//��ʼ��[0][0]Ϊ0����һ�к͵�һ��Ϊ1
	R[0][0] = 0;
	fill(R[0] + 1, R[0] + n, 1);
	for (int i = 1; i < m; ++i)
	{
		R[i][0] = 1;
	}
	//���
	for (int i = 1; i < m; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			R[i][j] = R[i - 1][j] + R[i][j - 1];
		}
	}

	cout << R[m - 1][n - 1] << endl;
	return 0;
}

int Similar_01_Back()
{
	//�����������Ӧ�̸������ܼ۸�
	int n, m, d;
	cin >> n >> m >> d;
	//cout << n << m << d << endl;

	//�����ڴ棬W������CΪ��Ӧ�ļ۸�
	int** W = new int* [n + 1];
	int** C = new int* [n + 1];
	for (int i = 1; i <= n; ++i)
	{
		W[i] = new int[m + 1];
		C[i] = new int[m + 1];
	}

	//���������ͼ۸�
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			cin >> W[i][j];
		}
	}
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			cin >> C[i][j];
		}
	}

	/*for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			cout<< W[i][j];
		}
		cout << endl;
	}
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			cout<< C[i][j];
		}
		cout << endl;
	}*/

	int* Result = new int[n + 1];//������������������
	int* ResultNext = new int[n + 1];
	fill(Result, Result + n + 1, 1);
	Result[0] = 10000;
	int deep = 0;//�ݹ�����
	
	Solve_Similar_01_Back(W, C, n, m, deep, Result, ResultNext, d);
	for (int k = 1; k < n; ++k)
	{
		cout << Result[k] << " ";
	}
	cout << Result[n] << endl;
	cout << Result[0] << endl;
	//�ͷ��ڴ�
	for (int i = 0; i <= n; ++i)
	{
		if (!W[i])
		{
			delete[] W[i];
		}
		if (!C[i])
		{
			delete[] C[i];
		}
	}
	if (!Result)
	{
		delete[] Result;
	}
	if (!ResultNext)
	{
		delete[] ResultNext;
	}

	return 0;
}

int Solve_Similar_01_Back( int** W,  int** C,  int n,  int m, int& deep, int* Res, int* ResNext,  int d)
{
	if (deep == n)
	{
		//int Res_Weight = TotalWeight(W, Res, deep);
		int ResNext_Weight = TotalWeight(W, ResNext, deep);
		if (Res[0] > ResNext_Weight)
		{
			for (int k = 1; k <= n; ++k)
			{
				Res[k] = ResNext[k];
			}
			Res[0] = ResNext_Weight;
		}
		return Res[0];
	}
	for (int j = 1; j <= m; ++j)
	{
		++deep;
		ResNext[deep] = j;
		if (OverPrice(C, ResNext, d, deep))
		{
			--deep;
			continue;
		}
		Solve_Similar_01_Back(W, C, n, m, deep, Res, ResNext, d);
		--deep;
	}
	return 0;
}

int OverPrice( int** C,  int* Res,  int d,  int deep)
{
	int price = 0;
	for (int i = 1; i <= deep; ++i)
	{
		int j = Res[i];
		price += C[i][j];
		if (price > d)
		{
			return true;
		}
	}
	return false;
}

int TotalWeight( int** W,  int* Res,  int deep)
{
	int weight = 0;
	for (int i = 1; i <= deep; ++i)
	{
		int j = Res[i];
		weight += W[i][j];
	}
	return weight;
}

int Sum_K()
{
	int N;//�������
	int K;//��
	cin >> N >> K;
	//�����ڴ棬A��������
	int* A = new int[N + 1];
	for (int i = 1; i <= N; ++i)
	{
		cin >> A[i];
	}
	int sum = 0;
	int deep = 0;
	if (Solve_Sum_K(A, N, sum, deep, K))
	{
		cout << "YES" << endl;
	}
	else
	{
		cout << "NO" << endl;
	}

	if (!A)
	{
		delete[] A;
	}
	return 0;
}

int Solve_Sum_K(int* A, int N, int sum, int deep,int K)
{
	if (deep == N)
	{
		return 0;
	}
	++deep;
	if (Solve_Sum_K(A, N, sum, deep, K))
	{
		return 1;
	}
	sum += A[deep];
	if (sum == K)
	{
		return 1;
	}
	if (sum > K)
	{
		return 0;
	}
	if (Solve_Sum_K(A, N, sum, deep, K))
	{
		return 1;
	}
	return 0;
}

int Labyrinth()
{
	int array[5][5];
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cin >> array[i][j];
		}
	}
	//Path��¼�ߵ�·�����ӣ�0,0������
	//1-�����ߣ�2-�����ߣ�3-�����ߣ�4-������
	//�߹��ĵ���Ϊ1
	int* Path = new int[15];
	int* Path_Next = new int[15];
	Path[0] = 0;
	Path_Next[0] = 0;
	Solve_Labyrinth(array, 0, 0, Path, Path_Next);
	int row = 0;
	int col = 0;
	cout << "(0,0)" << endl;
	for (int i = 1; i <= Path[0]; ++i)
	{
		switch (Path[i])
		{
		case 1:++row; break;
		case 2:++col; break;
		case 3:--row; break;
		case 4:--col; break;
		default:break;
		}
		cout << "(" << row << "," << col << ")" << endl;
	}
	if (!Path)
	{
		delete[] Path;
	}
	if (!Path_Next)
	{
		delete[] Path_Next;
	}
	return 0;
}

int Solve_Labyrinth(int array[][5], int row, int col, int*& path, int* pathN)
{
	array[row][col] = 1;
	if (row == 4 && col == 4)
	{
		if (path[0] == 0 || path[0] > pathN[0])
		{
			for (int i = 0; i <= pathN[0]; ++i)
			{
				path[i] = pathN[i];
			}
		}
		return true;
	}
	int k = ++pathN[0];
	//������
	if (row < 4 && array[row + 1][col] == 0)
	{
		pathN[k] = 1;
		Solve_Labyrinth(array, row + 1, col, path, pathN);
	}
	//������
	if (col < 4 && array[row][col + 1] == 0)
	{
		pathN[k] = 2;
		Solve_Labyrinth(array, row, col + 1, path, pathN);
	}
	//������
	if (row > 0 && array[row - 1][col] == 0)
	{
		pathN[k] = 3;
		Solve_Labyrinth(array, row - 1, col, path, pathN);
	}
	//������
	if (col > 0 && array[row][col - 1] == 0)
	{
		pathN[k] = 4;
		Solve_Labyrinth(array, row, col - 1, path, pathN);
	}
	--pathN[0];
	return false;
}

int greedyEventSchedule()
{
	typedef struct EventTime
	{
		int start_Time = 0;
		int end_Time = 0;
	}EventTime;
	int N;
	cin >> N;
	EventTime* e_Time = new EventTime[N];
	for (int i = 0; i < N; ++i)
	{
		cin >> e_Time[i].start_Time >> e_Time[i].end_Time;
	}
	for (int i = 0; i < N - 1; ++i)
	{
		for (int j = i + 1; j < N; ++j)
		{
			if (e_Time[i].end_Time > e_Time[j].end_Time)
			{
				EventTime temp = e_Time[i];
				e_Time[i] = e_Time[j];
				e_Time[j] = temp;
			}
		}
	}
	int greedyNum = 0;
	int endTime = 0;
	for (int i = 0; i < N; ++i)
	{
		if (e_Time[i].start_Time > endTime)
		{
			++greedyNum;
			endTime = e_Time[i].end_Time;
		}
	}
	cout << N - greedyNum + 1 << endl;
	if (!e_Time)
	{
		delete[] e_Time;
	}
	return 0;
}

int SectionCover()
{
	int n, k;
	cin >> n >> k;
	int* xPosition = new int[n];
	for (int i = 0; i < n; ++i)
	{
		cin >> xPosition[i];
	}
	for (int i = 0; i < n - 1; ++i)
	{
		for (int j = i + 1; j < n; ++j)
		{
			if (xPosition[i] > xPosition[j])
			{
				int temp = xPosition[i];
				xPosition[i] = xPosition[j];
				xPosition[j] = temp;
			}
		}
	}
	int SectionNum = 1;
	int Range = xPosition[0] + k;
	for (int i = 1; i < n; ++i)
	{
		if (xPosition[i] > Range)
		{
			++SectionNum;
			Range = xPosition[i] + k;
		}
	}
	cout << SectionNum << endl;

	if (!xPosition)
	{
		delete[] xPosition;
	}
	return 0;
}
