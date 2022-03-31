#include<iostream>
#include<fstream>

using namespace std;

//数据的输入，输出，调用SearchMid()查找中位数
int Median();
//查找两个序列中位数的具体实现
double SearchMid(double X[], double Y[], int n);

//求两个升序序列的共同中位数
int main()
{
	Median();
	return 0;
}

int Median()
{
	//打开input.txt文件
	ifstream infile("input.txt");
	if (!infile)
	{
		cerr << "input.txt打开失败" << endl;
		return false;
	}

	int n;
	infile >> n;

	//调试代码
	cout << n << endl;

	//创建动态数组储存数据
	double* X = new double[n];
	double* Y = new double[n];
	//获取X序列
	int i = 0;
	while (i < n)
	{
		infile >> X[i];

		//调试代码
		cout << X[i] << endl;

		++i;
	}
	//获取Y序列
	i = 0;
	while (i < n)
	{
		infile >> Y[i];

		//调试代码
		cout << Y[i] << endl;

		++i;
	}
	infile.close();

	//查找中位数
	double MidNum = SearchMid(X, Y, n);

	//调试代码
	cout << MidNum << endl;
	
	//将结果输出到文件
	ofstream outfile("output.txt");
	if (!outfile)
	{
		cerr << "output.txt打开失败" << endl;
		return false;
	}
	outfile << MidNum;
	outfile.close();

	//释放内存
	if (X)
	{
		delete[] X;
	}
	if (Y)
	{
		delete[] Y;
	}
	return true;
}

double SearchMid(double X[], double Y[], int n)
{
	//X,Y序列的初始左右位置
	int xmax = n - 1;
	int ymax = n - 1;
	int xmin = 0;
	int ymin = 0;

	//每个序列的中位数可能为两位
	int xmid1, xmid2;
	int ymid1, ymid2;

	//储存循环过程中X,Y序列的中位数
	double xMid = 0;
	double yMid = 0;

	//循环结束的条件，X,Y序列各剩两个元素
	while (xmin + 1 < xmax && ymin + 1 < ymax)
	{
		//判断 X 中位数是否是两个
		if ((xmax + xmin) % 2 != 0)
		{
			xmid1 = (xmax + xmin) / 2;
			xmid2 = xmid1 + 1;
		}
		else
		{
			xmid1 = (xmax + xmin) / 2;
			xmid2 = xmid1;
		}

		//判断 Y 中位数是否是两个
		if ((ymax + ymin) % 2 != 0)
		{
			ymid1 = (ymax + ymin) / 2;
			ymid2 = ymid1 + 1;
		}
		else
		{
			ymid1 = (ymax + ymin) / 2;
			ymid2 = ymid1;
		}

		xMid = (X[xmid1] + X[xmid2]) / 2;
		yMid = (Y[ymid1] + Y[ymid2]) / 2;
		//相等直接返回
		if (xMid == yMid)
		{
			return xMid;
		}
		//X比Y大,取X左边，Y右边，否则相反
		//注意：取X左边时，要将xmax=xmid2 而不是 xmax = xmid1；取右边为xmin = xmid1；Y一样
		//即在去除序列一边时，要将中位数两个都保存
		if (xMid > yMid)
		{
			xmax = xmid2;
			ymin = ymid1;
		}
		else if (xMid < yMid)
		{
			xmin = xmid1;
			ymax = ymid2;
		}
	}

	//将剩下的四个数排序，取中间两个的均值
	double A[5] = { 0 };
	A[1] = X[xmin];
	A[2] = X[xmax];
	for (int j = 0; j < 2; ++j)
	{
		for (int i = 2 + j; i > 0; --i)
		{
			if (Y[ymin + j] < A[i])
			{
				A[i + 1] = A[i];
				A[i] = Y[ymin + j];
			}
			else
			{
				A[i + 1] = Y[ymin + j];
				break;
			}
		}
	}
	double Mid = (A[2] + A[3]) / 2;
	return Mid;
}