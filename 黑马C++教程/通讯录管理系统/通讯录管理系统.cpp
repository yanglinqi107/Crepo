#include <iostream>
#include <string>
using namespace std;

#define MAX 1000


typedef struct Person
{
    string m_Name;  //姓名
    int m_Sex;      //性别， 1 男 2 女
    int m_Age;      //年龄
    string m_Phone; //电话
    string m_Addr;  //地址
};

typedef struct Addressbooks
{
    //通讯录中保存联系人数组
    Person personArray[MAX];
    //通讯录中当前记录的联系人个数
    int m_Size;
};


//显示菜单
void showMenu();

//添加联系人
void addPerson(Addressbooks& abs);

//显示所有联系人
void showPerson(Addressbooks& abs);

//检测联系人是否存在，存在则返回数据下标，不存在返回-1
int isExist(Addressbooks& abs, string name);

//删除联系人
void deletePerson(Addressbooks& abs);

//查找联系人信息
void findPerson(Addressbooks& abs);

//修改指定联系人信息
void modifyPerson(Addressbooks& abs);

//清空联系人
void clearPerson(Addressbooks& abs);

int main()
{
    int select = 0; //用户选择

    //通讯录结构体变量
    Addressbooks abs;
    //初始化通讯录人数
    abs.m_Size = 0;

    while (true)
    {
        showMenu();

        cin >> select;

        switch (select)
        {
        case 1:                 //添加联系人
            addPerson(abs);
            break;
        case 2:                 //显示联系人
            showPerson(abs);
            break;
        case 3:                 //删除联系人
            deletePerson(abs);
            break;
        case 4:                 //查找联系人
            findPerson(abs);
            break;
        case 5:                 //修改联系人
            modifyPerson(abs);
            break;
        case 6:                 //清空联系人
            clearPerson(abs);
            break;
        case 0:                 //退出通讯录
            cout << "欢迎下次使用" << endl;
            system("pause");
            return 0;
            break;
        default:
            cout << "输入错误，请重试" << endl;
        }
    }
}

void showMenu()
{
    cout << "*************************" << endl;
    cout << "***** 1、添加联系人 *****" << endl;
    cout << "***** 2、显示联系人 *****" << endl;
    cout << "***** 3、删除联系人 *****" << endl;
    cout << "***** 4、查找联系人 *****" << endl;
    cout << "***** 5、修改联系人 *****" << endl;
    cout << "***** 6、清空联系人 *****" << endl;
    cout << "***** 0、退出通讯录 *****" << endl;
    cout << "*************************" << endl;
}

void addPerson(Addressbooks& abs)
{
    //判断通讯录是否已满
    if (abs.m_Size == MAX)
    {
        cout << "通讯录已满，无法添加！" << endl;
        return;
    }
    else
    {
        //添加联系人

        //姓名
        string name;
        cout << "请输入姓名：" << endl;
        cin >> name;
        abs.personArray[abs.m_Size].m_Name = name;

        //性别
        int sex = 0;
        cout << "请输入性别：" << endl;
        cout << "1-----男" << endl;
        cout << "2-----女" << endl;

        //如果输入的是1或者2，可以退出循环，
        //如果输入错误，重新输入
        while (true)
        {
            cin >> sex;
            if (sex == 1 || sex == 2)
            {
                abs.personArray[abs.m_Size].m_Sex = sex;
                break;
            }
            cout << "输入错误，请重新输入：" << endl;
        }
        //年龄
        int age;
        cout << "请输入年龄：" << endl;
        while (true)
        {
            cin >> age;
            if (age > 0)
            {
                abs.personArray[abs.m_Size].m_Age = age;
                break;
            }
            cout << "输入错误，请重新输入：" << endl;
        }
        //电话
        cout << "请输入联系电话：" << endl;
        string phone;
        cin >> phone;
        abs.personArray[abs.m_Size].m_Phone = phone;
        //地址
        cout << "请输入家庭地址：" << endl;
        string address;
        cin >> address;
        abs.personArray[abs.m_Size].m_Addr = address;

        abs.m_Size++;

        cout << "添加成功！" << endl;
    }
    //请按任意键继续
    system("pause");
    //清屏操作
    system("cls");
}

void showPerson(Addressbooks& abs)
{
    //判断通讯录中人数是否为0
    if (abs.m_Size == 0)
    {
        cout << "当前记录为空" << endl;
    }
    else
    {
        for (int i = 0; i < abs.m_Size; ++i)
        {
            cout << "姓名：" << abs.personArray[i].m_Name << "\t";
            cout << "性别：" << (abs.personArray[i].m_Sex == 1 ? "男" : "女") << "\t";
            cout << "年龄：" << abs.personArray[i].m_Age << "\t";
            cout << "电话：" << abs.personArray[i].m_Phone << "\t";
            cout << "地址：" << abs.personArray[i].m_Addr << endl;
        }
    }

    system("pause");
    system("cls");
}

int isExist(Addressbooks& abs, string name)
{
    for (int i = 0; i < abs.m_Size; ++i)
    {
        //找到用户输入的姓名
        if (abs.personArray[i].m_Name == name)
        {
            return i;
        }
    }
    return -1;
}

void deletePerson(Addressbooks& abs)
{
    cout << "请输入要删除的联系人" << endl;
    string name;
    cin >> name;

    int result = isExist(abs, name);

    if (result != -1)
    {
        //查到人，进行删除操作
        for (int i = result; i < abs.m_Size - 1; ++i)
        {
            abs.personArray[i] = abs.personArray[i + 1];
        }
        abs.m_Size--;
        cout << "删除成功" << endl;
    }
    else 
    {
        cout << "查无此人" << endl;
    }
    system("pause");
    system("cls");
}

void findPerson(Addressbooks& abs)
{
    cout << "请输入要查找的联系人" << endl;
    string name;
    cin >> name;

    //判断指定的联系人是否在通讯录中
    int result = isExist(abs, name);
    if (result != -1)
    {
        cout << "姓名：" << abs.personArray[result].m_Name << "\t";
        cout << "性别：" << (abs.personArray[result].m_Sex == 1 ? "男" : "女") << "\t";
        cout << "年龄：" << abs.personArray[result].m_Age << "\t";
        cout << "电话：" << abs.personArray[result].m_Phone << "\t";
        cout << "地址：" << abs.personArray[result].m_Addr << endl;
    }
    else
    {
        cout << "查无此人" << endl;
    }
    system("pause");
    system("cls");
}

void modifyPerson(Addressbooks& abs)
{
    cout << "请输入要修改的联系人" << endl;
    string name;
    cin >> name;
    int result = isExist(abs, name);

    if (result != -1)
    {
        //姓名
        string name;
        cout << "请输入姓名：" << endl;
        cin >> name;
        abs.personArray[result].m_Name = name;

        //性别
        cout << "请输入性别：" << endl;
        cout << "1---男" << endl;
        cout << "2---女" << endl;
        int sex = 0;

        while (true)
        {
            cin >> sex;
            if (sex == 1 || sex == 2)
            {
                //输入正确
                abs.personArray[result].m_Sex = sex;
                break;
            }
            else
            {
                cout << "输入错误，请重输：" << endl;
            }
        }

        //年龄
        int age = 0;
        cout << "请输入年龄：" << endl;
        
        while (true)
        {
            cin >> age;
            if (age > 0)
            {
                //输入正确
                abs.personArray[result].m_Age = age;
                break;
            }
            else
            {
                cout << "输入错误，请重输：" << endl;
            }
        }

        //电话
        cout << "请输入电话：" << endl;
        string phone;
        cin >> phone;
        abs.personArray[result].m_Phone = phone;

        //地址
        cout << "请输入地址：" << endl;
        string address;
        cin >> address;
        abs.personArray[result].m_Addr = address;
    }
    else
    {
        cout << "查无此人" << endl;
    }
    system("pause");
    system("cls");
}

void clearPerson(Addressbooks& abs)
{
    int choice = 0;
    cout << "确定清空？" << endl;
    cout << "1--确定  2--取消" << endl;
    cin >> choice;
    if (choice == 1)
    {
        abs.m_Size = 0;

        cout << "通讯录已经清空" << endl;
    }
    system("pause");
    system("cls");
}