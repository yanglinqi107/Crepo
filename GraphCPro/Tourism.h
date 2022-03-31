#pragma once
#include"Graph.h"

//读取文件，创建景区景点图
void CreateGraph(Graph& graph);

//查询指定景点信息，显示到相邻景点的距离
void GetSpotInfo(Graph graph);

//调用DFSTraverse()函数，实现旅游景点导航功能
void TravelPath(Graph graph);

//通过调用FindShortPath(Graph,int,int,Edge)函数查询两个景点间的最短路径和距离
void FindShortPath(Graph graph);

//通过调用Graph.cpp文件中的FindMinTree()方法查询铺设电路规划图
void DesignPath(Graph graph);

