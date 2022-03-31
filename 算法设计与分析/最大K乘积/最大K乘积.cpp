#include <iostream>
#include <fstream>
using namespace std;

//输入和输出数据，调用K()取得最优值
int MaxKPro();
//实现最大K乘积的具体算法
int K(int** m, int** s, int I, int n, int k);

int main()
{
    MaxKPro();
    return 0;
}

int MaxKPro()
{
    //打开input1.txt文件
    ifstream infile("input.txt");
    if (!infile)
    {
        cerr << "input.txt打开失败" << endl;
        return false;
    }
    //读取整数I，位数n，k段
    int n, k, I;
    infile >> n;
    infile >> k;
    infile >> I;
    infile.close();

    //测试代码
    //cout << n << "\t" << k << "\t" << I << endl;
    
    //创建动态二维数组，求表
    int** m = new int*[n + 1];
    for (int i = 0; i < n + 1; ++i)
    {
        m[i] = new int[n + 1];
    }
    //创建动态二维数组，保存路径
    int** s = new int* [n + 1];
    for (int i = 0; i < n + 1; ++i)
    {
        s[i] = new int[n + 1];
    }

    int maxPro = K(m, s, I, n, k);

    //写入到output1.txt文件中
    ofstream output("output1.txt");
    if (!output)
    {
        cerr << "output打开失败" << endl;
        return false;
    }
    output << maxPro;
    output.close();
    //调试代码
    //cout << maxPro << endl;
    return true;
}

int K(int** m, int** s, int I, int n, int k)
{
    //将I的每一位保存到Num数组中
    int* Num = new int[n + 1];
    if (!Num)
    {
        cerr << "Num分配内存失败" << endl;
        return 0;
    }
    int I1 = I;
    for (int i = n; i > 0; --i)
    {
        Num[i] = I1 % 10;
        I1 = I1 / 10;

        //测试代码
        //cout << Num[i] << endl;
    }
    //m[i,j]保存将前i位分成j段的最大值
    m[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        m[i][1] = I/pow(10,n-i);
        m[i][i] = m[i - 1][i - 1] * Num[i];

        //测试代码
        //cout << m[i][1] << "\t" << m[i][i] << endl;
    }

    for (int i = 3; i <= n; ++i)
    {
        for (int j = 2; j < i; ++j)
        {
            int k = i - 1;
            m[i][j] = m[k][j - 1] * m[i][i] / m[k][k];
            while (k > j)
            {
                --k;
                int t = m[k][j - 1] * m[i][i] / m[k][k];
                if (t > m[i][j])
                {
                    m[i][j] = t;
                }
            } 
        }
    }
    return m[n][k];
}