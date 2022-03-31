#include "speechManager.h"

SpeechManager::SpeechManager()
{
	//初始化容器和属性
	this->initSpeech();
	
	//创建12名选手
	this->createSpeaker();

	//加载往届记录
	this->loadRecord();
}

void SpeechManager::initSpeech()
{
	//轮数置1
	this->m_Index = 1;
	//容器置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();
	this->m_Record.clear();
}

void SpeechManager::createSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		//创建具体选手
		Speaker speaker;
		speaker.m_Name = string("选手") + nameSeed[i];
		for (int j = 0; j < 2; j++)
		{
			speaker.m_Score[j] = 0;
		}

		//创建选手编号，并且放入到v1容器中
		this->v1.push_back(i + 1001);

		//选手编号和选手放入m_Speaker容器
		this->m_Speaker.insert(make_pair(i + 1001, speaker));
	}
}

void SpeechManager::startSpeech()
{
	//第一轮开始比赛
	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示结果
	this->showScore();

	//第二轮开始比赛
	this->m_Index++;
	//1、抽签
	this->speechDraw();

	//2、比赛
	this->speechContest();

	//3、显示结果
	this->showScore();

	//保存分数到文件
	this->saveRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");

	//重置状态
	//初始化容器和属性
	this->initSpeech();

	//创建12名选手
	this->createSpeaker();

	//加载往届记录
	this->loadRecord();
}

void SpeechManager::speechDraw()
{
	cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << endl;
	cout << "-------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;

	if (this->m_Index == 1)
	{
		//第一轮抽签
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮抽签
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	cout << "-------------------------------------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::speechContest()
{
	cout << "-------------- 第" << this->m_Index << "轮比赛正式开始 --------------" << endl;

	multimap<double, int, greater<double>> groupScore;	//临时容器，保存key分数 value 选手编号
	int num = 0;	//计算小组人数
	
	vector<int> vSrc;	//比赛选手容器
	if (this->m_Index == 1)
	{
		vSrc = this->v1;
	}
	else
	{
		vSrc = this->v2;
	}

	//遍历所有选手进行比赛
	for (vector<int>::iterator it = vSrc.begin(); it != vSrc.end(); it++)
	{
		num++;
		//评委打分
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;

		sort(d.begin(), d.end(), greater<double>());	//降序排序
		d.pop_back();	//去除最低分
		d.pop_front();	//去除最高分

		double sum = accumulate(d.begin(), d.end(), 0.0f);		//计算总分
		double avg = sum / (double)d.size();					//平均分

		//将平均分保存至map中
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		//打印平均分
		//cout << "编号：" << *it << " 姓名：" << this->m_Speaker[*it].m_Name << " 平均分：" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;

		groupScore.insert(make_pair(avg, *it));		//保存到小组临时容器
		//每6人一组
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end(); mit++)
			{
				cout << "编号：" << mit->second << " 姓名：" << this->m_Speaker[mit->second].m_Name 
					<< " 平均分：" << this->m_Speaker[mit->second].m_Score[this->m_Index - 1] << endl;
			}
			//取走前3名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end() && count < 3; count++, mit++)
			{
				if (this->m_Index == 1)
				{
					this->v2.push_back(mit->second);
				}
				else
				{
					this->vVictory.push_back(mit->second);
				}
			}
			groupScore.clear();	//清空临时容器
			cout << endl;
		}
	}
	cout << "-------------- 第" << this->m_Index << "轮比赛完毕 --------------" << endl;
	system("pause");
}

void SpeechManager::showScore()
{
	cout << "-------------- 第" << this->m_Index << "轮晋级选手 --------------" << endl;

	vector<int> v;
	if (this->m_Index == 1) v = this->v2;
	else v = this->vVictory;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号：" << *it << " 姓名：" << this->m_Speaker[*it].m_Name << " 得分：" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);	//追加的方式写文件
	//将选手数据写入文件
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	this->fileIsEmpty = false;	//更改文件状态不为空
	cout << "记录已经保存" << endl;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);	//读文件
	//文件不存在
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "文件为空" << endl;
		ifs.close();
		return;
	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);	//将上面读取的单个字符放回文件
	string data;
	int index = 0;	 //记录第几届
	while (ifs >> data)
	{
		index++;
		vector<string> v;	//存储data按","分割的字串
		int pos = -1;	//查到","的位置
		int start = 0;	
		while (true)	//按","分割字符串
		{
			pos = data.find(',', start);
			if (pos == -1) break;
			string temp = data.substr(start, pos - start);
			//cout << temp << endl;
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		v.clear();
	}
	ifs.close();
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在，或文件为空！" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
		{
			cout << "第" << it->first << "届"
				<< " 冠军编号：" << it->second[0] << " 得分：" << it->second[1] << " "
				<< " 亚军编号：" << it->second[2] << " 得分：" << it->second[3] << " "
				<< " 季军编号：" << it->second[4] << " 得分：" << it->second[5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::clearRecord()
{
	cout << "是否确定清空文件？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;

	int choice = 0;
	cin >> choice;
	if (choice == 1)
	{
		//确认清空
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeech();

		//创建12名选手
		this->createSpeaker();

		//加载往届记录
		this->loadRecord();

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	exit(0);
}

SpeechManager::~SpeechManager()
{
}
