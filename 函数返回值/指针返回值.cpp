#include <iostream>
#include <math.h>

using namespace std;

double* f_1(double x, double y);

double* f_2(double x, double y);

int main()
{
    double x, y;
    double a, b;
    cout << "输入两个数字：" << endl;
    cin >> x;
    if (x == 0)
    {
        cout << "error" << endl;
        return 1;
    }
    cin >> y;
    a = *f_1(x, y);
    b = *f_2(x, y);
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;

    return 0;
}

double* f_1(double x, double y)
{
    double a;
    //double* p1 = NULL;
    x = x * x;
    y = y * y;
    a = sqrt(x + y);
    //p1 = &a;
    return &a;
}

double* f_2(double x, double y)
{
    double b;
    double* p2 = NULL;
    b = atan(y / x);
    p2 = &b;
    return p2;
}

