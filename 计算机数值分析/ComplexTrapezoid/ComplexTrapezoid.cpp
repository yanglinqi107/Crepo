#include <iostream>
#include <iomanip>
using namespace std;
//复化梯形递推求积分
int ComTn(double* X, double* Y, int n);

int main()
{
	int n;	//已知点的数目
	cout << "输入f(x)点的个数：";
	cin >> n;
	//cout << n << endl;

	//X保存n个点的x值
	double* X = new double[n + 1];
	if (!X)
	{
		cerr << "X分配内存失败" << endl;
		return 0;
	}
	//Y保存n个点的y值
	double* Y = new double[n + 1];
	if (!Y)
	{
		cerr << "Y分配内存失败" << endl;
		return 0;
	}
	cout << "输入n个点的x值（空格隔开）：" << endl;
	for (int i = 1; i <= n; ++i)
	{
		cin >> X[i];
		//cout << X[i] << endl;
	}
	cout << "输入n个点的y值（空格隔开）：" << endl;
	for (int i = 1; i <= n; ++i)
	{
		cin >> Y[i];
		//cout << Y[i] << endl;
	}

	ComTn(X, Y, n);

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

int ComTn(double* X, double* Y, int n)
{
	//精度
	double precision;
	cout << "精度：";
	cin >> precision;
	//递推过程的T值
	double* T = new double[n];
	//初始步长
	double h = 1;
	int h0 = n - 1;
	//等分
	int i = 1;
	//等分点的个数
	int num = i + 1;

	T[1] = Y[n] / 2.0 + Y[1] / 2.0;
	do
	{
		i *= 2;
		num = i + 1;
		double fadd = 0;
		for (int k = 0; k < i / 2; ++k)
		{
			int index = (int)(1 + (k + 0.5) * h0);
			fadd += Y[index];
		}
		T[i] = T[i / 2] / 2.0 + h * fadd / 2.0;
		h = h / 2;
		h0 = h0 / 2;
	} while (fabs(T[i] - T[i / 2]) >= precision && num < n);
	cout << setprecision(10) << T[i] << endl;

	if (!T)
	{
		delete[] T;
	}
	return 0;
}
