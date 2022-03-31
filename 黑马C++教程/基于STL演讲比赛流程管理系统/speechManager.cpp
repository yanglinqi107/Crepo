#include "speechManager.h"

SpeechManager::SpeechManager()
{
	//��ʼ������������
	this->initSpeech();
	
	//����12��ѡ��
	this->createSpeaker();

	//���������¼
	this->loadRecord();
}

void SpeechManager::initSpeech()
{
	//������1
	this->m_Index = 1;
	//�����ÿ�
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
		//��������ѡ��
		Speaker speaker;
		speaker.m_Name = string("ѡ��") + nameSeed[i];
		for (int j = 0; j < 2; j++)
		{
			speaker.m_Score[j] = 0;
		}

		//����ѡ�ֱ�ţ����ҷ��뵽v1������
		this->v1.push_back(i + 1001);

		//ѡ�ֱ�ź�ѡ�ַ���m_Speaker����
		this->m_Speaker.insert(make_pair(i + 1001, speaker));
	}
}

void SpeechManager::startSpeech()
{
	//��һ�ֿ�ʼ����
	//1����ǩ
	this->speechDraw();

	//2������
	this->speechContest();

	//3����ʾ���
	this->showScore();

	//�ڶ��ֿ�ʼ����
	this->m_Index++;
	//1����ǩ
	this->speechDraw();

	//2������
	this->speechContest();

	//3����ʾ���
	this->showScore();

	//����������ļ�
	this->saveRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");

	//����״̬
	//��ʼ������������
	this->initSpeech();

	//����12��ѡ��
	this->createSpeaker();

	//���������¼
	this->loadRecord();
}

void SpeechManager::speechDraw()
{
	cout << "�� << " << this->m_Index << " >> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "-------------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;

	if (this->m_Index == 1)
	{
		//��һ�ֳ�ǩ
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//�ڶ��ֳ�ǩ
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
	cout << "-------------- ��" << this->m_Index << "�ֱ�����ʽ��ʼ --------------" << endl;

	multimap<double, int, greater<double>> groupScore;	//��ʱ����������key���� value ѡ�ֱ��
	int num = 0;	//����С������
	
	vector<int> vSrc;	//����ѡ������
	if (this->m_Index == 1)
	{
		vSrc = this->v1;
	}
	else
	{
		vSrc = this->v2;
	}

	//��������ѡ�ֽ��б���
	for (vector<int>::iterator it = vSrc.begin(); it != vSrc.end(); it++)
	{
		num++;
		//��ί���
		deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			//cout << score << " ";
			d.push_back(score);
		}
		//cout << endl;

		sort(d.begin(), d.end(), greater<double>());	//��������
		d.pop_back();	//ȥ����ͷ�
		d.pop_front();	//ȥ����߷�

		double sum = accumulate(d.begin(), d.end(), 0.0f);		//�����ܷ�
		double avg = sum / (double)d.size();					//ƽ����

		//��ƽ���ֱ�����map��
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		//��ӡƽ����
		//cout << "��ţ�" << *it << " ������" << this->m_Speaker[*it].m_Name << " ƽ���֣�" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;

		groupScore.insert(make_pair(avg, *it));		//���浽С����ʱ����
		//ÿ6��һ��
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<double>>::iterator mit = groupScore.begin(); mit != groupScore.end(); mit++)
			{
				cout << "��ţ�" << mit->second << " ������" << this->m_Speaker[mit->second].m_Name 
					<< " ƽ���֣�" << this->m_Speaker[mit->second].m_Score[this->m_Index - 1] << endl;
			}
			//ȡ��ǰ3��
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
			groupScore.clear();	//�����ʱ����
			cout << endl;
		}
	}
	cout << "-------------- ��" << this->m_Index << "�ֱ������ --------------" << endl;
	system("pause");
}

void SpeechManager::showScore()
{
	cout << "-------------- ��" << this->m_Index << "�ֽ���ѡ�� --------------" << endl;

	vector<int> v;
	if (this->m_Index == 1) v = this->v2;
	else v = this->vVictory;

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "��ţ�" << *it << " ������" << this->m_Speaker[*it].m_Name << " �÷֣�" << this->m_Speaker[*it].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);	//׷�ӵķ�ʽд�ļ�
	//��ѡ������д���ļ�
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	this->fileIsEmpty = false;	//�����ļ�״̬��Ϊ��
	cout << "��¼�Ѿ�����" << endl;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);	//���ļ�
	//�ļ�������
	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->fileIsEmpty = true;
		//cout << "�ļ�Ϊ��" << endl;
		ifs.close();
		return;
	}
	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);	//�������ȡ�ĵ����ַ��Ż��ļ�
	string data;
	int index = 0;	 //��¼�ڼ���
	while (ifs >> data)
	{
		index++;
		vector<string> v;	//�洢data��","�ָ���ִ�
		int pos = -1;	//�鵽","��λ��
		int start = 0;	
		while (true)	//��","�ָ��ַ���
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
		cout << "�ļ������ڣ����ļ�Ϊ�գ�" << endl;
	}
	else
	{
		for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
		{
			cout << "��" << it->first << "��"
				<< " �ھ���ţ�" << it->second[0] << " �÷֣�" << it->second[1] << " "
				<< " �Ǿ���ţ�" << it->second[2] << " �÷֣�" << it->second[3] << " "
				<< " ������ţ�" << it->second[4] << " �÷֣�" << it->second[5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void SpeechManager::clearRecord()
{
	cout << "�Ƿ�ȷ������ļ���" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int choice = 0;
	cin >> choice;
	if (choice == 1)
	{
		//ȷ�����
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();

		//��ʼ������������
		this->initSpeech();

		//����12��ѡ��
		this->createSpeaker();

		//���������¼
		this->loadRecord();

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	exit(0);
}

SpeechManager::~SpeechManager()
{
}
