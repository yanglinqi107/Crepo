#include <iomanip>
#include <iostream>

using namespace std;

//改进Euler法
int RungeKutta4(double x, double y, double h, int N);
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

    RungeKutta4(x0, y0, h, N);

    return 0;
}

int RungeKutta4(double x, double y, double h, int N)
{
    //过渡
    double K1, K2, K3, K4;
   
    double yNext;
    double xNext;
   
    for (int n = 1; n <= N; ++n)
    {
        xNext = x + h;

        K1 = xFy(x, y);
        K2 = xFy(x + h / 2, y + h * K1 / 2);
        K3 = xFy(x + h / 2, y + h * K2 / 2);
        K4 = xFy(xNext, y + h * K3);

        yNext = y + h * (K1 + 2 * K2 + 2 * K3 + K4) / 6;
        cout << xNext << endl;
        cout << setprecision(10) << yNext << endl;
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

