
#include <iostream>

using namespace std;

//直线拟合
int FitStraightLine(double* X, double* Y, int n);

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

	FitStraightLine(X, Y, n);

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

int FitStraightLine(double* X, double* Y, int n)
{
	//X的总和
	double xSum = 0;
	//Y的总和
	double ySum = 0;
	//X的平方和
	double xSquSum = 0;
	//X和Y的乘积和
	double xMulySum = 0;

	for (int i = 0; i < n; ++i)
	{
		xSum += X[i];
		ySum += Y[i];
		xSquSum += X[i] * X[i];
		xMulySum += X[i] * Y[i];
	}

	double a, b;

	double a0 = n * xSum;
	double a1 = xSum * xSum;
	double a2 = ySum * xSum;
	double b0 = xSum * n;
	double b1 = xSquSum * n;
	double b2 = xMulySum * n;

	b = (b2 - a2) / (b1 - a1);
	a = (a2 - b * a1) / a0;
	cout << "y=" << a << "+(" << b << ")x" << endl;
	return 0;
}
