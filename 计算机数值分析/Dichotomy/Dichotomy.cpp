#include <iostream>

using namespace std;

//二分法求根
int Dichotomy(double a, double fa, double b, double fb, double precision);
//X与Y的函数，返回F(X)
double xFy(double x);

int main()
{
    cout << "输入Xa：";
    double a;
    cin >> a;
    cout << "输入f(a)：";
    double fa;
    cin >> fa;

    cout << "输入Xb：";
    double b;
    cin >> b;
    cout << "输入f(b)：";
    double fb;
    cin >> fb;

    if (fa * fb > 0)
    {
        cout << "算法失效！" << endl;
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
    Dichotomy(a, fa, b, fb, precision);
    return 0;
}

int Dichotomy(double a, double fa, double b, double fb, double precision)
{
    double min;
    double fmin;
    do 
    {
        min = (a + b) / 2;
        fmin = xFy(min);
        if (fa * fmin < 0)
        {
            b = min;
            fb = fmin;
        }
        if (fb * fmin < 0)
        {
            a = min;
            fa = fmin;
        }
        if (fmin == 0)
        {
            cout << "近似解：" << min << endl;
            cout << "近似值：" << fmin << endl;
            return 0;
        }
    } while (fabs(b - a) > precision && fabs(fmin) > precision);

    cout << "近似解：" << min << endl;
    cout << "近似值：" << fmin << endl;
    return true;
}

double xFy(double x)
{
    double fy;
    fy = x * x - x - 3;
    return fy;
}
