#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef struct sortInfo {
    int sortName = -2;  //小组名
    int sortNum = 0;    //小组元素个数
}sortInfo;

//定义状态转移函数
typedef struct fx {
    string st1="";  //初始状态
    string al="";   //转移条件
    string st2="";  //目标状态
}fx;

struct DFA {
    //状态集合
    vector<string> status;
    //字母表
    vector<string> alphabet;
    //状态转换函数
    vector<fx> f;
    //初态
    string S0;
    //终态
    vector<string> Z;
};

//从文件读取DFA
int read_DFA(DFA &dfa);

//生成状态集
int getStatus(vector<string> &status, string &s);

//生成转换函数
int make_transfer_matrix(vector<fx>& transfer_matrix, string& s);

//从转换函数中获取字母表
int get_alphabet(vector<string> &alphabet, vector<fx> transfer_matrix);

//最小化DFA
int minimize_DFA(DFA &dfa);

//求所有状态接收字母alph的下一个状态，下一状态集合存入next_status
int get_next_status(DFA dfa, vector<int>& next_status, string alph);

//根据传入的状态，返回对应的状态所在的分组
int get_sta_in_group(vector<int>& sta_in_group, vector<int> next_status, int* statusInfo);

//根据下一组状态，对当前组别分组
int div_status(vector<int> sta_in_group, vector<sortInfo>& record, int*& statusInfo, int length);

//根据分组，对状态进行合并
int merge_status(vector<sortInfo> record, int* statusInfo, int length, DFA& dfa);

//获取某一状态在状态集中的下标
int status_sub(vector<string> status, string sta);

//显示DFA
void show_DFA(DFA dfa);

//判断g_int 是否在status中
int find_in_status(vector<int> status, int g_int);

//去除无效状态
int delete_invalid_status(DFA& dfa);

//判断状态s是否在状态集status中
bool s_in_status(vector<string> status, string s);

//删除无效状态，更新dfa状态
void delete_status(vector<string>& dfa_status, vector<string>& dfa_Z, vector<string> invalid_status);

//根据无效状态，删除对应的转移函数
void update_f(vector<fx>& dfa_f, vector<string> invalid_status);

//打印输出
void print_f(DFA dfa);

int main()
{
    DFA dfa;

    read_DFA(dfa);

    minimize_DFA(dfa);

    print_f(dfa);

    return 0;
}

int read_DFA(DFA& dfa)
{
    vector<string> status;
    vector<fx> transfer_matrix;
    vector<string> alphabet;
    string s;

    ifstream infile;
    
    infile.open("DFA输入.txt");
    if (!infile.is_open())
    {
        cout << "文件打开失败" << endl;
        return 0;
    }

    //一行一行读取文件
    while (getline(infile, s))
    {
        getStatus(status, s);
        make_transfer_matrix(transfer_matrix, s);
    }
    infile.close();

    get_alphabet(alphabet, transfer_matrix);

    if (status.size() == 0) cout << "空" << endl;

    dfa.status = status;
    dfa.alphabet = alphabet;
    dfa.f = transfer_matrix;
    dfa.S0="X";
    dfa.Z.push_back("Y");

    return 0;
}

int getStatus(vector<string> &status, string &s)
{
    string sta="";
    int i = 0;
    for (; i < s.length(); ++i)
    {
        if (s[i] == ' ')
        {
            break;
        }
        sta.push_back(s[i]);    //不能sta[i]=s[i]，无法修改
    }
    //去掉s前面的状态
    ++i;
    s = s.substr(i);
    //将状态sta放入状态集中
    status.push_back(sta);
    return 0;
}

int make_transfer_matrix(vector<fx>& transfer_matrix, string& s)
{
    fx temp;
    string stemp = "";
    int index = 0;
    s.push_back(' ');
    
    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] == '>')    continue;
     
        if ((s[i] == '-') || (s[i] == ' ') || (i+1 == s.length()))
        {
            switch (index)
            {
            case 0:temp.st1 = stemp; break;
            case 1:temp.al = stemp; break;
            case 2: 
            {
                temp.st2 = stemp; 
                transfer_matrix.push_back(temp); 
                break;
            }
            default:
                break;
            }
            //cout << "stemp:" << stemp << endl;
            stemp = "";
            index = ++index % 3;
            continue;
        }
        stemp.push_back(s[i]);
    }

    return 0;
}

int get_alphabet(vector<string>& alphabet, vector<fx> transfer_matrix)
{
    string alph = "";
    for (int i = 0; i < transfer_matrix.size(); ++i)
    {
        bool flag = true;
        alph = transfer_matrix[i].al;
        for (int j = 0; j < alphabet.size(); ++j)
        {
            if (alphabet[j] == transfer_matrix[i].al)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            alphabet.push_back(alph);
        }
    }
    return 0;
}

int minimize_DFA(DFA& dfa)
{
    //状态集元素个数，也是temp数组列长度
    int length = dfa.status.size();
    //记录分组信息，sortInfo保存组名和组内元素数量
    vector<sortInfo> record;

    //以状态在vector中的下标对应数组的下标表示，数组对应的值分组组号
    //以数字区别分组，初始均为0；
    int* statusInfo = new int[length];
    for (int i = 0; i < length; ++i)
    {
        statusInfo[i] = 0;
    }

    sortInfo stemp;

    //-1组信息，终态组号为-1，终态数量size()
    stemp.sortName = -1;
    stemp.sortNum = dfa.Z.size();

    //把 -1组 即终态加进去加进去
    record.push_back(stemp);

    //初始化分组，分为终态 -1 和 非终态 0
    for (int j = 0; j < dfa.Z.size(); j++)
    {
        int sub = status_sub(dfa.status, dfa.Z[j]);
        statusInfo[sub] = -1;
    }

    //非终态集信息，组号为0，sortNum为元素数量
    stemp.sortName = 0;
    stemp.sortNum = dfa.status.size() - dfa.Z.size();
    //把 0 组 即非终态集信息加进去
    record.push_back(stemp);

    while (true)
    {
        int add_num = 0;
        for (int j = 0; j < dfa.alphabet.size(); ++j)
        {
            //保存每个状态根据字母表转移下一个状态下标
            vector<int> next_status;
            //对应下一个状态的所在分组的组号
            vector<int> sta_in_group;
            get_next_status(dfa, next_status, dfa.alphabet[j]);

            get_sta_in_group(sta_in_group, next_status, statusInfo);

            add_num += div_status(sta_in_group, record, statusInfo, length);

            //循环前清空下一状态容器
            next_status.clear();
            //清空下一状态对应组号
            sta_in_group.clear();
        }
        if (add_num == 0) break;
    }

    merge_status(record, statusInfo, length, dfa);

    delete_invalid_status(dfa);

    delete[] statusInfo;

    return 0;
}

int get_next_status(DFA dfa, vector<int>& next_status, string alph)
{
    for (int i = 0; i < dfa.status.size(); ++i)
    {
        //保存下一个状态
        string next_sta="";
        for (int j = 0; j < dfa.f.size(); ++j)
        {
            if (dfa.f[j].st1 == dfa.status[i] && dfa.f[j].al == alph)
            {
                next_sta = dfa.f[j].st2;
                break;
            }
        }

        //状态st1不接收字母alph的情况，则置下一状态的下标为-2
        if (next_sta.size() == 0) 
        {
            int flag = status_sub(dfa.alphabet, alph) - dfa.alphabet.size() - 1;
            next_status.push_back(flag);
            continue;
        }

        //获取下一个状态在状态集中的下标
        for (int k = 0; k < dfa.status.size(); ++k)
        {
            if (dfa.status[k] == next_sta)
            {
                next_status.push_back(k);
                break;
            }
        }
    }
    return 0;
}

int get_sta_in_group(vector<int>& sta_in_group, vector<int> next_status, int* statusInfo)
{
    for (int i = 0; i < next_status.size(); ++i)
    {
        //对不接受al的状态，下一状态的分组置为-2
        if (next_status[i] == -2)
        {
            sta_in_group.push_back(next_status[i]);
            continue;
        }
        int sta = next_status[i];
        sta_in_group.push_back(statusInfo[sta]);
    }
    return 0;
}

int div_status(vector<int> sta_in_group, vector<sortInfo>& record, int*& statusInfo, int length)
{
    //保存初始小组数量
    int group_num = record.size();
    int add_group_num = 0;  //新增小组数量

    //每个小组细分
    for (int i = 0; i < record.size(); ++i)
    {   
        //小组数量为1，则不可再分
        if (record[i].sortNum == 1)
        {
            continue;
        }

        vector<int> group;
        vector<int> group_temp;
        //遍历statusInfo存有分组信息的数组，-1,0,1
        for (int j = 0; j < length; ++j)
        {
            if (statusInfo[j] == record[i].sortName)    //判断该状态是否是当前分组
            {
                int g_num = sta_in_group[j];     //当前状态接受字母al的下一状态所在组号
                if (group.size() == 0)          //该组的第一个元素，记下 下一组号
                {
                    group.push_back(g_num);     //存改组的下一状态 所有组号
                    group_temp.push_back(record[i].sortName);    //存该组原组号和新添加的组号
                }
                else                     //不是该组的第一个元素，和记下的组号集group中的组号比对，看是否已存在
                {
                    bool find = false;
                    for (int k = 0; k < group.size(); ++k)  //在所有组号中寻找该组
                    {
                        if (group[k] == g_num)
                        {
                            statusInfo[j] = group_temp[k];
                            find = true;
                            break;
                        }
                    }
                    if (!find)              //如果没找到
                    {
                        group.push_back(g_num);
                        add_group_num++;
                        int max_group_num = record[group_num-1].sortName;
                        statusInfo[j] = max_group_num + add_group_num;  //将statusInfo的所在组设为新的组号
                        group_temp.push_back(statusInfo[j]);
                    }
                }
            }
        }

        group.clear();
        group_temp.clear();
    }

    //如果小组有增加
    if (add_group_num != 0)
    {
        //在record中增加新的组号
        for (int i = 1; i <= add_group_num; ++i)
        {
            sortInfo temp;
            temp.sortName = i + record[group_num-1].sortName;
            record.push_back(temp);
        }
        //对各小组的元素个数重新计数
        for (int i = 0; i < record.size(); ++i)
        {
            int num = 0;
            for (int j = 0; j < length; ++j)
            {
                if (statusInfo[j] == record[i].sortName)
                {
                    num++;
                }
            }
            record[i].sortNum = num;
        }
        return add_group_num;
    }
    return add_group_num;
}

int merge_status(vector<sortInfo> record, int* statusInfo, int length, DFA& dfa)
{
    //每个组的新状态 字符串
    vector<string> status_new;;
    //设置每个组号的状态
    for (int i = 0; i < record.size(); ++i)
    {
        status_new.push_back(to_string(record[i].sortName));
    }

    //初始态在状态集中的下标
    int start_sub = status_sub(dfa.status, dfa.S0);
    
    //初始态所在组号
    int start_group = statusInfo[start_sub];
    //设置初态所在组的状态，不变
    status_new[start_group+1] = dfa.S0;

    //终态在状态集中的下标，
    vector<int> Z_group;
    for (int i = dfa.Z.size() - 1; i >= 0; --i)
    {
        int sub = status_sub(dfa.status, dfa.Z[i]);    //终态在状态集中的位置
        int z_group = statusInfo[sub];      //该终态所在的组
        int find = find_in_status(Z_group, z_group);
        if (!find) Z_group.push_back(z_group);
        //设置终态所在集合的状态名为终态的字符串
        status_new[z_group + 1] = dfa.Z[i];
    }

    //新的终态集
    vector<string> Z_new;
    for (int i = 0; i < Z_group.size(); ++i)
    {
        int sub = Z_group[i] + 1;
        Z_new.push_back(status_new[sub]);
    }

    for (int i = 0; i < dfa.alphabet.size(); ++i)
    {
        //保存每个状态根据字母表转移下一个状态
        vector<int> next_status;
        //对应下一个状态的所在分组的组号
        vector<int> sta_in_group;
        get_next_status(dfa, next_status, dfa.alphabet[i]);
        get_sta_in_group(sta_in_group, next_status, statusInfo);

        //更新状态转移函数
        for (int j = 0; j < dfa.f.size(); ++j)
        {
            //根据字母表逐个字母更新
            if (dfa.f[j].al == dfa.alphabet[i])
            {
                int s_sub = status_sub(dfa.status, dfa.f[j].st1);  //原状态在状态集的下标
                //if (sta_in_group[s_sub] == -2) continue;
                int record_sub = sta_in_group[s_sub] + 1;   //新状态在record的下标
                dfa.f[j].st2 = status_new[record_sub];
            }
        }
        //循环前清空下一状态容器
        next_status.clear();
        //清空下一状态对应组号
        sta_in_group.clear();
    }

    //每个分组只留一个状态，去掉其他状态
    vector<int> s_sub;
    for (int i = 0; i < record.size(); ++i)
    {
        for (int j = 0; j < length; j++)
       {
            if (statusInfo[j] == record[i].sortName)
            {
                s_sub.push_back(j);
                break;
            }
       }
    }

    vector<fx> f_new;
    for (int i = 0; i < dfa.f.size(); ++i)
    {
        int sub = status_sub(dfa.status, dfa.f[i].st1);
        int find = find_in_status(s_sub, sub);
        if (!find)
        {
            continue;
        }
        int s_group = statusInfo[sub];
        dfa.f[i].st1 = status_new[s_group + 1];
        f_new.push_back(dfa.f[i]);
    }

    //新的状态集
    dfa.status = status_new;
    //新的终态集
    dfa.Z = Z_new;
    //新的状态函数
    dfa.f = f_new;

    return 0;
}

int status_sub(vector<string> status, string sta)
{
    for (int i = 0; i < status.size(); ++i)
    {
        if (status[i] == sta)
        {
            return i;
        }
    }
    return -1;
}

void show_DFA(DFA dfa)
{
    cout << "状态集合" << endl;
    for (int i = 0; i < dfa.status.size(); ++i)
    {
        cout << dfa.status[i] << "\t";
    }
    cout << endl;
    cout << "转换函数" << endl;
    for (int i = 0; i < dfa.f.size(); ++i)
    {
        cout << dfa.f[i].st1 << "-" << dfa.f[i].al << "->" << dfa.f[i].st2 << endl;
    }
    cout << "字母表" << endl;
    for (int i = 0; i < dfa.alphabet.size(); ++i)
    {
        cout << dfa.alphabet[i] << "\t";
    }
    cout << endl;
    cout << "初始态" << endl;
    cout << dfa.S0 << endl;
    cout << "终态" << endl;
    for (int i = 0; i < dfa.Z.size(); ++i)
    {
        cout << dfa.Z[i] << "\t";
    }
    cout << endl;
}

int find_in_status(vector<int> status, int g_int)
{
    for (int i = 0; i < status.size(); ++i)
    {
        if (status[i] == g_int)
        {
            return 1;
        }
    }
    return 0;
}

int delete_invalid_status(DFA& dfa)
{
    //判断起始状态不能到达的状态并删除
    
    //先添加起始状态
    vector<string> status;
    status.push_back(dfa.S0);
    vector<string> temp;
    temp.push_back(dfa.S0);

    //找到所有能到达的状态
    while (true)
    {
        vector<string> temp2;
        for (int i = 0; i < temp.size(); ++i)
        {
            for (int j = 0; j < dfa.f.size(); ++j)
            {
                if (temp[i] == dfa.f[j].st1 && !s_in_status(status,dfa.f[j].st2))
                {
                    status.push_back(dfa.f[j].st2);
                    temp2.push_back(dfa.f[j].st2);
                }
            }
        }
        if (temp2.size() == 0) break;
        
        temp.clear();
        temp = temp2;
        temp2.clear();
    }

    //需要删除的状态
    vector<string> invalid_status;
    for (int i = 0; i < dfa.status.size(); ++i)
    {
        if (!s_in_status(status, dfa.status[i]))
        {
            invalid_status.push_back(dfa.status[i]);
        }
    }

    if (invalid_status.size() != 0)
    {
        delete_status(dfa.status, dfa.Z, invalid_status);
        update_f(dfa.f, invalid_status);
    }

    invalid_status.clear();
    status.clear();     //清空
    temp.clear();

    //判断不能到达终态的状态并删除

    //添加终态
    for (int i = 0; i < dfa.Z.size(); ++i)
    {
        status.push_back(dfa.Z[i]);
        temp.push_back(dfa.Z[i]);
    }

    //找到所有能到达终态的状态，从终态反向推
    while (true)
    {
        vector<string> temp2;
        for (int i = 0; i < temp.size(); ++i)
        {
            for (int j = 0; j < dfa.f.size(); ++j)
            {
                if (temp[i] == dfa.f[j].st2 && !s_in_status(status, dfa.f[j].st1))
                {
                    status.push_back(dfa.f[j].st1);
                    temp2.push_back(dfa.f[j].st1);
                }
            }
        }
        if (temp2.size() == 0) break;

        temp.clear();
        temp = temp2;
        temp2.clear();
    }
    //需要删除的状态
    for (int i = 0; i < dfa.status.size(); ++i)
    {
        if (!s_in_status(status, dfa.status[i]))
        {
            invalid_status.push_back(dfa.status[i]);
        }
    }
    //更新状态集合和转移函数
    if (invalid_status.size() != 0)
    {
        delete_status(dfa.status, dfa.Z, invalid_status);
        update_f(dfa.f, invalid_status);
    }
    return 0;
}

bool s_in_status(vector<string> status, string s)
{
    for (int i = 0; i < status.size(); ++i)
    {
        if (status[i] == s) return true;
    }
    return false;
}

void delete_status(vector<string>& dfa_status, vector<string>& dfa_Z, vector<string> invalid_status)
{

    for (int j = 0; j < invalid_status.size(); ++j)
    {
        for (int i = 0; i < dfa_status.size(); ++i)
        {
            if (dfa_status[i] == invalid_status[j])
            {
                dfa_status.erase(dfa_status.begin() + i);
                break;
            }
        }

        for (int i = 0; i < dfa_Z.size(); ++i)
        {
            if (dfa_Z[i] == invalid_status[j])
            {
                dfa_Z.erase(dfa_Z.begin() + i);
                break;
            }
        }
    }
}

void update_f(vector<fx>& dfa_f, vector<string> invalid_status)
{
    for (int i = 0; i < dfa_f.size(); ++i)
    {
        if (s_in_status(invalid_status, dfa_f[i].st1) || s_in_status(invalid_status, dfa_f[i].st2))
        {
            dfa_f.erase(dfa_f.begin() + i); //删除容器f中的第i个元素，后面的元素会前移，所以i要减1
            --i;
        }
    }
}

void print_f(DFA dfa)
{
    for (int i = 0; i < dfa.status.size(); ++i)
    {
        cout << dfa.status[i] << " ";
        for (int j = 0; j < dfa.f.size(); ++j)
        {
            if (dfa.status[i] == dfa.f[j].st1)
            {
                cout << dfa.f[j].st1 << "-" << dfa.f[j].al << "->" << dfa.f[j].st2 <<" ";
            }
        }
        cout << endl;
    }
}

