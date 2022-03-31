#pragma once
#include<cstdio>
#include<cstdlib>
#include<random>
#include<time.h>
#include<cmath>
#include"AES-128.h"

void bitDis(int n, string &s, int m);
long int Atoi(string& S, int R);
void text();
void text2();
long myrandom(long n);
int Seed();
bool happened(double probability);
unsigned int AES_seed();


int main()
{
    text();
    return 0;
}

void text()
{
    //srand(Seed());
    srand(AES_seed());
    int Rand_Max = 10000;
    int num[100] = { 0 };
    for (int i = 1; i <= Rand_Max; ++i)
    {
        //int rand_num = rand() % Rand_Max;
        int rand_num = myrandom(100);
        cout << rand_num << "\t";
        num[rand_num]++;
        if (i % 10 == 0)
        {
            cout << endl;
        }
        //Sleep(1000);
    }
    cout << "-------------------------------------------------------------------------" << endl;
    for (int i = 0; i < 100; ++i)
    {
        cout << num[i] << "\t";
        if ((i + 1) % 10 == 0)
        {
            cout << endl;
        }
    }
}

void text2()
{
    for (int i = 1; i <= 100; ++i)
    {
        srand(myrandom(100));
        int rand_num = myrandom(100);
        cout << rand_num << "\t";
        if (i % 10 == 0)
        {
            cout << endl;
        }
    }
}

void bitDis(int n, string &s, int m)
{
    //int m = 12;
    while (m--)
    {
        if (n & (1 << m))
            s += '1';
        //printf("1");
        else
            //printf("0");
            s += '0';
    }
}

long int Atoi(string& S, int R)
{
    long int ans = 0;
    for (int i = 0; i < S.size(); i++)//按权展开
    {
        ans += (S[i] - '0') * pow(R, S.size() - i - 1);
    }
    return ans;
}

long myrandom(long n)   //产生0~n-1之间的等概率随机数
{
    int t = 0;
    if (n <= RAND_MAX)
    {   
        long R = RAND_MAX - (RAND_MAX + 1) % n;//尾数
        t = rand();
        while (t > R)
        {
            t = rand();
        }
        return t % n;
    }
    else
    {
        long r = n % (RAND_MAX + 1);//余数
        if (happened((double)r / n))//取到余数的概率
        {
            return n - r + myrandom(r);
        }
        else
        {
            return rand() + myrandom(n / (RAND_MAX + 1)) * (RAND_MAX + 1);
        }
    }
}

unsigned int AES_seed()
{
    //设置种子
    byte plain[16] = {};
    srand(time(NULL));
    for (int i = 0; i < 16; ++i)
    {
        //cout << hex << rand() % 256 << endl;
        plain[i] = rand() % 256;
        //cout << hex << plain[i].to_ulong() << endl;
    }

    byte key[16] = { 0x2b, 0x7e, 0x15, 0x16,
                    0x28, 0xae, 0xd2, 0xa6,
                    0xab, 0xf7, 0x15, 0x88,
                    0x09, 0xcf, 0x4f, 0x3c };

    word w[4 * (Nr + 1)];
    // 加密种子
    encrypt(plain, w);
    int x = rand() % 16;
    int y = rand() % 16;
    unsigned int seed = plain[x].to_ulong() * plain[y].to_ulong();
    //cout << seed << endl;
    return seed;
}

int Seed()
{
    srand((unsigned)time(NULL));
    long long time_now;
    time_now = time(NULL); //获取当前时间 
    int m = rand() % 15;
    //cout << time_now << endl;
    //cout << sizeof(time_t) << endl;

    string s = "";
    bitDis(time_now, s, m);

    int seed = Atoi(s, 2);
    //cout << seed << "\t";

    return seed;
}

const double MinProb = 1.0 / (RAND_MAX + 1);
bool happened(double probability)//probability 0~1
{
    if (probability <= 0)
    {
        return false;
    }
    if (probability)
    {
        return rand() == 0 && happened(probability * (RAND_MAX + 1));
    }
    if (rand() <= probability * (RAND_MAX + 1))
    {
        return true;
    }
    return false;
}