#include <iostream>
#include <iomanip>

using namespace std;

//龙贝格算法
int Romberg(double** T,int n);

int main()
{
    int n = 11;
    //分配内存
    double** T = new double*[n];
    for (int i = 0; i < n; i++)
    {
        T[i] = new double[i + 1];
    }
    //初始化数据Tn，第二列为Sn，第三列为Rn，以此类推
    T[0][0] = 0.9207355;
    T[1][0] = 0.9397933;
    T[2][0] = 0.9445135;
    T[3][0] = 0.9456909;
    T[4][0] = 0.9459850;
    T[5][0] = 0.9460596;
    T[6][0] = 0.9460769;
    T[7][0] = 0.9460815;
    T[8][0] = 0.9460827;
    T[9][0] = 0.9460830;
    T[10][0] = 0.9460831;

    Romberg(T, n);

    for (int i = 0; i < n; ++i)
    {
        delete[] T[i];
    }
    return 0;
}

int Romberg(double** T, int n)
{
    //精度
    double precision;
    cout << "输入精度：";
    cin >> precision;
    int k = 3;

    for (int i = 1; i <= k; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            int m = pow(2, j * 2);
            int r = m - 1;
            T[i][j] = m * T[i][j - 1] / r - T[i - 1][j - 1] / r;
        }
    }

    int i;
    bool judge = true;
    for (i = 4; i < n && judge; ++i)
    {
        for (int j = 1; j <= k; ++j)
        {
            int m = pow(2, j * 2);
            int r = m - 1;
            T[i][j] = m * T[i][j - 1] / r - T[i - 1][j - 1] / r;
        }
        judge = fabs(T[i][k] - T[i - 1][k]) >= precision;
    }
    i--;
    cout << setprecision(10) <<T[i][k]<< endl;

    return 0;
}
