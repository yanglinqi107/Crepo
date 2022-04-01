#include <iostream>
#include <string>
#include <bitset>
#include <unordered_map>
using namespace std;

string to_base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//输入字符串 并转化为 二进制序列 存入字符串bits
void strToBits(string& bits)
{
    string str;
    cin >> str;
    for (char c : str)
    {
        bitset<8> bs(c);
        bits += bs.to_string();
    }
}

//6位一组进行分组，转化为base64编码
void group(string& bits, string& encryptStr)
{
    //若bits长度不是6的倍速，补0
    int sur = bits.size() % 6;
    if (sur != 0)
    {
        bits += string(6 - sur, '0');
    }
    //将bits中的二进制每6位一个字符转化位base64编码字符，存入字符串encryptStr中
    int pos = 6;
    while (pos <= bits.size())
    {
        bitset<6> bs(bits.substr(pos - 6, pos));
        int temp = bs.to_ulong();
        encryptStr += to_base64[temp];
        pos += 6;
    }
    //若得到的encryptStr不是4的倍数，补=
    sur = encryptStr.size() % 4;
    if (sur != 0)
    {
        encryptStr += string(4 - sur, '=');
    }
}

int main() {
    string bits;
    strToBits(bits);
    string encryptStr;
    group(bits, encryptStr);
    cout << encryptStr << endl;
    return 0;
}