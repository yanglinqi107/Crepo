
#include <iostream>

using namespace std;

//拉格朗日插值
int Lagrange(double* X, double* Y, int n);

//计算插值系数Lk
double Lk(double* X, int k, double x0, int n);

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

	Lagrange(X, Y, n);

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

int Lagrange(double* X, double* Y, int n)
{
	//所求x点
	cout << "输入X：";
	double x0;
	cin >> x0;

	//保存系数Lk
	double* L = new double[n];
	if (!L)
	{
		cerr << "L分配内存失败" << endl;
		return false;
	}

	//调用Lk()计算系数Lk
	for (int i = 0; i < n; ++i)
	{
		L[i] = Lk(X, i, x0, n);
	}

	//计算f(x0)的近似值
	int fx0 = 0;
	for (int i = 0; i < n; ++i)
	{
		fx0 += L[i] * Y[i];
	}
	cout << "f(X)=" << fx0 << endl;

	if (!L)
	{
		delete[] L;
	}

	return true;
}

double Lk(double* X, int k,double x0, int n)
{
	double L = 1;
	for (int i = 0; i < n; ++i)
	{
		if (i == k)continue;
		L *= (x0 - X[i]) / (X[k] - X[i]);
	}
	return L;
}
