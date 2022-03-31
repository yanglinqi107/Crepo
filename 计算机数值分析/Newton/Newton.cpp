
#include <iostream>

using namespace std;

//牛顿插值
int Newtown(double* X, double* Y, int n);
//计算基函数
int WX(double x0, double* X, double* wx, int n);
//计算系数
int AX(double* A, double* X, double* Y, int n);

int main()
{
	int n;	//已知点的数目
	cout << "输入f(x)点的个数：";
	cin >> n;
	//cout << n << endl;

	//X保存n个点的x值
	double* X = new double[n];
	if (!X)
	{
		cerr << "X分配内存失败" << endl;
		return 0;
	}
	//Y保存n个点的y值
	double* Y = new double[n];
	if (!Y)
	{
		cerr << "Y分配内存失败" << endl;
		return 0;
	}
	cout << "输入n个点的x值（空格隔开）：" << endl;
	for (int i = 0; i < n; ++i)
	{
		cin >> X[i];
		//cout << X[i] << endl;
	}
	cout << "输入n个点的y值（空格隔开）：" << endl;
	for (int i = 0; i < n; ++i)
	{
		cin >> Y[i];
		//cout << Y[i] << endl;
	}

	Newtown(X, Y, n);

	//回收内存
	if (!X)
	{
		delete[] X;
	}
	if (!Y)
	{
		delete[] Y;
	}
	return 0;
}

int Newtown(double* X, double* Y, int n)
{
	//所求x点
	cout << "输入X：";
	double x0;
	cin >> x0;

	//储存基函数
	double* wx = new double[n];
	if (!wx)
	{
		cerr << "wx内存分配失败" << endl;
		return false;
	}
	WX(x0, X, wx, n);

	//存储系数即差商
	double* A = new double[n];
	if (!A)
	{
		cerr << "A内存分配失败" << endl;
		return false;
	}
	AX(A, X, Y, n);

	double fx = 0;
	for (int i = 0; i < n; ++i)
	{
		fx += A[i] * wx[i];
	}
	cout << "f(X)=" << fx << endl;
	if (!wx)
	{
		delete[] wx;
	}
	if (!A)
	{
		delete[] A;
	}
	return true;
}

int WX(double x0, double* X, double* wx, int n)
{
	wx[0] = 1;
	for (int i = 0; i < n - 1; ++i)
	{
		wx[i + 1] = wx[i] * (x0 - X[i]);
	}
	return 0;
}

int AX(double* A, double* X, double* Y, int n)
{
	//分配内存,差商表
	double** AF = new double* [n];
	for (int i = 0; i < n; ++i)
	{
		AF[i] = new double[i + 1];
	}

	for (int i = 0; i < n; ++i)
	{
		AF[i][0] = Y[i];
	}
	for (int j = 1; j < n; ++j) 
	{
		for (int i = j; i < n; ++i)
		{
			AF[i][j] = (AF[i][j - 1] - AF[i - 1][j - 1]) / (X[i] - X[i - j]);
		}
	}
	for (int i = 0; i < n; ++i)
	{
		A[i] = AF[i][i];
	}
	for (int i = 0; i < n; ++i)
	{
		delete[] AF[i];
	}
	return 0;
}
