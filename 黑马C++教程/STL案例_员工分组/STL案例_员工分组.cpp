#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define CHEHUA 0
#define MEISHU 1
#define YANFA 2

class Worker
{
public:
    string m_Name;
    int m_Salary;
};

void createWorker(vector<Worker>& v)
{
    string nameSeed = "ABCDEFGHIJ"; 
    for (int i = 0; i < 10; i++)
    {
        Worker worker;
        worker.m_Name = string("员工") + nameSeed[i];
        worker.m_Salary = rand() % 10000 + 10000;
        v.push_back(worker);
    }
}

//员工分组
void setGroup(vector<Worker>& v, multimap<int, Worker>& m)
{
    for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++)
    {
        int department = rand() % 3;
        m.insert(make_pair(department, *it));
    }
}

void showWorkerByGroup(multimap<int, Worker>& m)
{
    cout << "策划部门：" << endl;
    multimap<int, Worker>::iterator pos = m.find(CHEHUA);
    int count = m.count(CHEHUA);
    for (int i = 0; pos != m.end() && i < count; i++, pos++)
    {
        cout << "姓名：" << pos->second.m_Name << " 薪水：" << pos->second.m_Salary << endl;
    }

    cout << "----------------------------" << endl;

    cout << "美术部门：" << endl;
    pos = m.find(MEISHU);
    count = m.count(MEISHU);
    for (int i = 0; pos != m.end() && i < count; i++, pos++)
    {
        cout << "姓名：" << pos->second.m_Name << " 薪水：" << pos->second.m_Salary << endl;
    }

    cout << "----------------------------" << endl;

    cout << "研发部门：" << endl;
    pos = m.find(YANFA);
    count = m.count(YANFA);
    for (int i = 0; pos != m.end() && i < count; i++, pos++)
    {
        cout << "姓名：" << pos->second.m_Name << " 薪水：" << pos->second.m_Salary << endl;
    }
}

int main()
{
    srand((unsigned int)time(NULL));

    //1、创建员工
    vector<Worker> vWorker;
    createWorker(vWorker);
    //for (vector<Worker>::iterator it = vWorker.begin(); it != vWorker.end(); it++)
    //{
    //    cout << "姓名：" << it->m_Name << " 薪水：" << it->m_Salary << endl;
    //}
    
    //2、员工分组
    multimap<int, Worker> mWorker;
    setGroup(vWorker, mWorker);

    //3、分组员工显示
    showWorkerByGroup(mWorker);
    return 0;
}


