#include <iostream>
#include <iomanip>

using namespace std;

//二分法求根
int Newton(double x0, int N, double precision);
//X与Y的函数，返回F(X)
double xFy(double x);
//Y的一阶导
double xFFy(double x);

int main()
{
    cout << "输入X0：";
    double x0;
    cin >> x0;

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
    Newton(x0, N, precision);
    return 0;
}

int Newton(double x0, int N, double precision)
{
    //函数值
    double fx;
    //导数值
    double ffx;

    double xNow = x0;
    double xNext;
    double yNext;

    for (int k = 1; k <= N; ++k)
    {
        if (xFFy(xNow) == 0)
        {
            cout << "函数失效！" << endl;
            return false;
        }
        fx = xFy(xNow);
        ffx = xFFy(xNow);
        xNext = xNow - fx / ffx;
        yNext = xFy(xNext);

        if (fabs(xNext - xNow) < precision || fabs(yNext) < precision)
        {
            cout << "近似解：" << xNext << endl;
            cout << "近似值：" << setprecision(10) << yNext << endl;
            return 0;
        }
        xNow = xNext;
    }
    cout << "失败，未找到解！" << endl;
    return 0;
}

double xFy(double x)
{
    double fy;
    fy = x * x - 115;
    return fy;
}

double xFFy(double x)
{
    double ffy;
    ffy = 2 * x;
    return ffy;
}
