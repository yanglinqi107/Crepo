#include <iostream>
#include <iomanip>

using namespace std;

//雅可比迭代公式
int Jacobi(int nRow, int nCol, double** A, int N, double precision);

int main()
{
    int nRow, nCol;
    cout << "输入线性方程组的行数：";
    cin >> nRow;
    cout << "输入线性方程组的列数：";
    cin >> nCol;

    if (nRow <= 0 || nCol <= 0 || nRow + 1 != nCol)
    {
        cout << "行或列错误！" << endl;
        return false;
    }

    //分配内存保存矩阵
    double** A = new double* [nRow + 1];
    for (int i = 1; i <= nRow; ++i)
    {
        A[i] = new double[nCol + 1];
    }

    for (int i = 1; i <= nRow; ++i)
    {
        cout << "输入第" << i << "行数据(空格隔开)：" << endl;
        for (int j = 1; j <= nCol; ++j)
        {
            cin >> A[i][j];
        }
        if (A[i][i] == 0)
        {
            cout << "对角线上的系数不能为0！" << endl;
            return false;
        }
    }

    cout << "输入最大迭代次数：";
    int N;
    cin >> N;

    if (N <= 0)
    {
        cout << "次数错误！" << endl;
        return false;
    }

    cout << "输入精度：";
    double precision;
    cin >> precision;

    if (precision <= 0)
    {
        cout << "精度错误！" << endl;
        return false;
    }

    Jacobi(nRow, nCol, A, N, precision);

    for (int i = 1; i <= nRow; ++i)
    {
        delete[] A[i];
    }
    return 0;
}

int Jacobi(int nRow, int nCol, double** A, int N, double precision)
{
    //分配内存，保存解
    double* X = new double[nRow + 1];
    fill(X, X + nRow + 1, 0);
    double* XNext = new double[nRow + 1];

    double ax = 0;
    bool judge = true;

    for (int k = 1; k <= N; ++k)
    {
        judge = false;
        for (int i = 1; i <= nRow; ++i)
        {
            ax = 0;
            for (int j = 1; j < nCol; ++j)
            {
                if (j == i)
                {
                    continue;
                }
                ax += A[i][j] * X[j];
            }
            XNext[i] = (A[i][nCol] - ax) / A[i][i];
        }

        for (int i = 1; i <= nRow; ++i)
        {
            if (fabs(XNext[i] - X[i]) > precision)
            {
                judge = true;
                break;
            }
        }

        if (!judge)
        {
            break;
        }

        for (int i = 1; i <= nRow; ++i)
        {
            X[i] = XNext[i];
        }
    }

    if (judge)
    {
        cout << "迭代失败，未达到精度要求！" << endl;
        return false;
    }

    for (int i = 1; i <= nRow; ++i)
    {
        cout << "X" << i << "=" << XNext[i] << endl;
    }

    if (!X)
    {
        delete[] X;
    }
    if (!XNext)
    {
        delete[] XNext;
    }
    return 0;
}
