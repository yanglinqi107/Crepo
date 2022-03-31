#include <iomanip>
#include <iostream>

using namespace std;

//改进Euler法
int improEuler(double x,double y,double h,int N);
//x和y的函数
double xFy(double x, double y);

int main()
{
    cout << "输入X初值：";
    double x0;
    cin >> x0;
    cout << "输入Y初值：";
    double y0;
    cin >> y0;
    cout << "输入h步长：";
    double h;
    cin >> h;
    cout << "输入N步数：";
    int N;
    cin >> N;
    cout << endl;
    improEuler(x0, y0, h, N);

    return 0;
}

int improEuler(double x, double y, double h, int N)
{
    //预报值
    double yp;
    //校正值
    double yNext;
    double xNext;
    //过渡
    double yc;
    for (int n = 1; n <= N; ++n)
    {
        xNext = x + h;
        yp = y + h * xFy(x, y);
        cout << "X=" << xNext << endl;
        cout << "预报值：" << setprecision(10) << yp << endl;
        yc = y + h * xFy(xNext, yp);
        yNext = (yp + yc) / 2;
        cout << "校正值：" << setprecision(10) << yNext << endl;
        cout << endl;
        x = xNext;
        y = yNext;
    }

    return 0;
}

double xFy(double x, double y)
{
    double fy;
    fy = y - 2 * x / y;
    return fy;
}
