#pragma once
#include"Graph.h"

//��ȡ�ļ���������������ͼ
void CreateGraph(Graph& graph);

//��ѯָ��������Ϣ����ʾ�����ھ���ľ���
void GetSpotInfo(Graph graph);

//����DFSTraverse()������ʵ�����ξ��㵼������
void TravelPath(Graph graph);

//ͨ������FindShortPath(Graph,int,int,Edge)������ѯ�������������·���;���
void FindShortPath(Graph graph);

//ͨ������Graph.cpp�ļ��е�FindMinTree()������ѯ�����·�滮ͼ
void DesignPath(Graph graph);

