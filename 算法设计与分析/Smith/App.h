#pragma once
#include<iostream>

//求Smith数，算法设计与分析
int Smith();
int Add(int n);
bool IsSmith(int n);

//求最接近数，算法设计与分析
int RecentNumber();

//字符串循环左移
int ShiftLeft();

//逆序数个数，算法设计与分析
int InverseNumber();

//递减子序列
int DecreaseOrder();

//最大公共子序列
int CommonOrder();
//包含s1和s2序列的最短序列s4
int CommonOrder2();

//一个机器人只能向下和向右移动，每次只能移动一步，设计一个算法求机器人从（1,1）到（m，n）有多少条路径
int Route();

/*
设某一机器由n个部件组成,部件编号为1~n，每一种部件都可以从m个不同的供应商处购得，供应商编号为1~m。设wij是从供应商j处购得的部件i的
重量,cij是相应的价格。对于给定的机器部件重量和机器部件价格，计算总价格不超过d的最小重量机器设计。
*/
int Similar_01_Back();
int Solve_Similar_01_Back(int** W, int** C, int n, int m, int& deep, int* Res, int* ResNext, int d);
int OverPrice(int** C, int* Res, int d, int deep);
int TotalWeight( int** W,  int* Res,  int deep);

/*
给出N个正整数组成的数组A，求能否从中选出若干个，使他们的和为K。如果可以，输出："YES"，否则输出"NO"
第1行：2个数N、K, N为数组的长度, K为需要判断的和(2 ≤N ≤ 20，1 ≤ K ≤ 10^9)
第2 到第 N + 1行：每行1个数，对应数组的元素A[i] (1 ≤ A[i]≤ 10^6)
*/
int Sum_K();
int Solve_Sum_K(int* A, int N, int sum, int deep, int K);

/*
一个5 × 5的二维数组，表示一个迷宫。数据保证有唯一最短路径。
其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的最短路线。
*/
int Labyrinth();
int Solve_Labyrinth(int array[][5], int row, int col, int*& path, int* pathN);

/*
有n头牛（1<=n<=50,000)要挤奶。给定每头牛挤奶的时间区间[A,B](1<=A<=B<=1,000,000，A,B为整数)。
牛需要呆在畜栏里才能挤奶。一个畜栏同一时间只能容纳一头牛。问至少需要多少个畜栏，
才能完成全部挤奶工作，以及每头牛都放哪个畜栏里？注意：在同一个畜栏的两头牛，它们挤奶时间区间不能在端点重合
*/
int greedyEventSchedule();

/*
设x1,x2,... ,xn是实直线上的n个点。用固定长度的闭区间覆盖这n个点，
至少需要多少个这样的固定长度闭区间?设计求解此问题的有效算法。
对于给定的实直线上的n个点和闭区间的长度k，编程计算覆盖点集的最少区间数。
*/
int SectionCover();

