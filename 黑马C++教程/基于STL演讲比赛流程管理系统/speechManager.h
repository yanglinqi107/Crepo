#pragma once
#include <map>
#include <deque>
#include <numeric>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "speaker.h"
using namespace std;

//�ݽ�������
class SpeechManager
{
public:
	//���캯��
	SpeechManager();

	//��ʼ����Ա����
	void initSpeech();

	//����12��ѡ��
	void createSpeaker();

	//��ʼ���� �����������̵Ŀ��ƺ���
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�÷�
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ʾ����÷�
	void showRecord();	

	//�˵�����
	void show_Menu();

	//��ռ�¼
	void clearRecord();

	//�˳�ϵͳ
	void exitSystem();

	//��������
	~SpeechManager();

public:
	//��Ա����
	//�����һ�ֱ���ѡ�ֱ��
	vector<int> v1;

	//��һ�ֽ���ѡ�ֱ��
	vector<int> v2;

	//ʤ����ǰ����ѡ�ֱ��
	vector<int> vVictory;

	//��ű�ţ������Ӧѡ��
	map<int, Speaker> m_Speaker;

	//��ű�������
	int m_Index;

	//�ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//��������¼������
	map<int, vector<string>> m_Record;
};

