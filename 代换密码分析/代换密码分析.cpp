// test1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

int printLowerLetter(string test);  //小写字母
int shiftLetter(string test, string LKey);  //移位
int frequencyLetter(string test, string CKey);  //统计词频
string changeLetter(string test, char pL, char hL);     //更改字母

int main()
{
    string CapticalKey = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string LowerKey = "abcdefghijklmnopqrstuvwxyz";

    string test = "AHCRCLCTSCIMHUTWCOACEHNILIGOCSEHOCMMONTNEOTLIMMOECRFCNGWTNZHIUOSTGRCTAVOEAIRYMIREHONTSTODTMRCNEHMIRFCRBUSONCSSLCTDCRTSOAWTSRCTLLYAHCMORSAAOFCAHTATEIUNARYSAIIDUPAIAHCLINGTRFJUROSDOEAOINIMAHCUNOACDSATACSONSUEHTWTYAHRIUGHAHCUNRCFOAAONGCMMIRASIMAHCEHONCSCGIVCRNFCNAFCNGMONTLLYRCAURNCDAIHCRHIFCEIUNARYSTMCLYTMACRTLFISAAHRCCYCTRSUNDCRHIUSCTRRCSAONVTNEIUVCRFCNGTRROVCDTASHCNZHCNBTITNONACRNTAOINTLTORPIRAINSTAURDTYNOGHAWHCRCSHCCXPRCSSCDGRTAOAUDCAIAHCEHONCSCGIVCRNFCNAMIRSCEURONGHCRSTMCRCAURN";          /*密文*/
    string test1 = test;                                       
    cout << test << endl;
    char pL = 'C';
    char hL = 'E';
    test1 = changeLetter(test1, pL, hL);                /*C-E替换*/
    cout << test1 << endl;

    pL = 'A';
    hL = 'T';
    test1 = changeLetter(test1, pL, hL);                /*A-T替换*/
    cout << test1 << endl;

    pL = 'I';
    hL = 'O';   
    test1 = changeLetter(test1, pL, hL);                /*I-O替换*/
    cout << test1 << endl;

    pL = 'M';
    hL = 'F';
    test1 = changeLetter(test1, pL, hL);                /*M-F替换*/
    cout << test1 << endl;
    printLowerLetter(test1);
    
    /*
    the release of huawei technologies chief financial officer mengwanzhou is a great victory for china said a french 
    former business leader as it was really the first time that a country stood up to the long arm jurisdiction of 
    the united states in such a way through the unremitting efforts of the chinese government meng finally returned to 
    her home country safely after almost three years under house arrest in vancouver meng arrived at shenzhen baoan 
    international airport on saturday night where she expressed gratitude to the chinese government for securing her 
    safe return
    */

    //frequencyLetter(test, CapticalKey);
    //shiftLetter(test, LowerKey);

    return 0;
}

int printLowerLetter(string test)
{
    int i = 0;
    while (test[i] != '\0')
    {
        int num = test[i] + 32;
        cout << (char)num;
        ++i;
    }
    return 0;
}

int shiftLetter(string test, string LKey)
{
    for (int i = 0; i < 26; ++i)
    {
        int j = 0;
        while (test[j] != '\0')
        {
            int num = test[j] - 'A';
            num = (num + i) % 26;
            cout << LKey[num];
            ++j;
        }
        cout << endl << endl << endl;
    }
    return 0;
}

int frequencyLetter(string test, string CKey)
{
    int fre[26] = {0};
    int i = 0;
    while(test[i] != '\0')
    {
        int num = test[i] - 'A';
        ++fre[num];
        ++i;
    }
    for (int j = 0; j < 26; ++j)
    {
        double frequency = fre[j] / (double)i * 100;
        cout << CKey[j] << "\t" << fre[j] << "\t" << frequency << "%" << endl;
    }
    return 0;
}

string changeLetter(string test, char pL, char hL)
{
    char preLetter = pL;
    char hostLetter = hL;

    int i = 0;
    while (test[i] != '\0')
    {
        if (test[i] == preLetter)
        {
            test[i] = hostLetter;
        }
        else if (test[i] == hostLetter)
        {
            test[i] = preLetter;
        }
        ++i;
    }

    //cout << test << endl;

    return test;
}


