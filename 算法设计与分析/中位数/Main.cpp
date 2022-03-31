#include<iostream>
#include<fstream>

using namespace std;

//���ݵ����룬���������SearchMid()������λ��
int Median();
//��������������λ���ľ���ʵ��
double SearchMid(double X[], double Y[], int n);

//�������������еĹ�ͬ��λ��
int main()
{
	Median();
	return 0;
}

int Median()
{
	//��input.txt�ļ�
	ifstream infile("input.txt");
	if (!infile)
	{
		cerr << "input.txt��ʧ��" << endl;
		return false;
	}

	int n;
	infile >> n;

	//���Դ���
	cout << n << endl;

	//������̬���鴢������
	double* X = new double[n];
	double* Y = new double[n];
	//��ȡX����
	int i = 0;
	while (i < n)
	{
		infile >> X[i];

		//���Դ���
		cout << X[i] << endl;

		++i;
	}
	//��ȡY����
	i = 0;
	while (i < n)
	{
		infile >> Y[i];

		//���Դ���
		cout << Y[i] << endl;

		++i;
	}
	infile.close();

	//������λ��
	double MidNum = SearchMid(X, Y, n);

	//���Դ���
	cout << MidNum << endl;
	
	//�����������ļ�
	ofstream outfile("output.txt");
	if (!outfile)
	{
		cerr << "output.txt��ʧ��" << endl;
		return false;
	}
	outfile << MidNum;
	outfile.close();

	//�ͷ��ڴ�
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
	//X,Y���еĳ�ʼ����λ��
	int xmax = n - 1;
	int ymax = n - 1;
	int xmin = 0;
	int ymin = 0;

	//ÿ�����е���λ������Ϊ��λ
	int xmid1, xmid2;
	int ymid1, ymid2;

	//����ѭ��������X,Y���е���λ��
	double xMid = 0;
	double yMid = 0;

	//ѭ��������������X,Y���и�ʣ����Ԫ��
	while (xmin + 1 < xmax && ymin + 1 < ymax)
	{
		//�ж� X ��λ���Ƿ�������
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

		//�ж� Y ��λ���Ƿ�������
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
		//���ֱ�ӷ���
		if (xMid == yMid)
		{
			return xMid;
		}
		//X��Y��,ȡX��ߣ�Y�ұߣ������෴
		//ע�⣺ȡX���ʱ��Ҫ��xmax=xmid2 ������ xmax = xmid1��ȡ�ұ�Ϊxmin = xmid1��Yһ��
		//����ȥ������һ��ʱ��Ҫ����λ������������
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

	//��ʣ�µ��ĸ�������ȡ�м������ľ�ֵ
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