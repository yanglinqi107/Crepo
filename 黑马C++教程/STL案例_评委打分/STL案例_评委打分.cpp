#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

//选手类
class Person
{
public:
    Person(string name, int score)
    {
        this->m_Name = name;
        this->m_Score = score;
    }
    string m_Name;  //姓名
    int m_Score;    //分数
};

//创建选手
void createPerson(vector<Person>& v)
{
    string nameSeed = "ABCDE";
    for (int i = 0; i < 5; i++)
    {
        string name = "选手";
        name += nameSeed[i];
        int score = 0;
        Person p(name, score);
        //将创建的对象存入容器
        v.push_back(p);
    }
}

//打分
void setScore(vector<Person>& v)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < v.size(); i++)
    {
        deque<int> d;
        //评委打分
        for (int j = 0; j < 10; j++)
        {
            int score = rand() % 41 + 60;
            d.push_back(score);
        }

        //cout << "选手：" << v[i].m_Name << "打分：" << endl;
        //for (deque<int>::iterator it = d.begin(); it != d.end(); it++)
        //{
        //    cout << *it << " ";
        //}
        //cout << endl;

        //分数排序
        sort(d.begin(), d.end());

        //去掉最高和最低分
        d.pop_back();
        d.pop_front();

        //计算平均分
        int sum = 0;
        for (deque<int>::iterator it = d.begin(); it != d.end(); it++)
        {
            sum += *it;
        }
        int avg = sum / d.size();
        v[i].m_Score = avg;
    }
}

void showScore(vector<Person>& v)
{
    for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "姓名：" << it->m_Name << " 平均分：" << it->m_Score << endl;
    }
}

int main()
{
    //1、创建5名选手
    vector<Person> v;   //存放选手的容器
    createPerson(v);

    //测试
    //for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    //{
    //    cout << "姓名：" << it->m_Name << " 分数：" << it->m_Score << endl;
    //}

    //2、给5名选手打分
    setScore(v);

    //3、显示最后得分
    showScore(v);

    return 0;
}
