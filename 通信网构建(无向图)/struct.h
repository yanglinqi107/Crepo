#pragma once

#define numMAX 20
#define StrMAX 100
#define MAX 10000

//顶点信息
struct Vex
{
	char Code[StrMAX];
	char Name[StrMAX];

	bool operator==(const Vex& obj) const
	{
		if (strcmp(Code, obj.Code) == 0 && strcmp(Name, obj.Name) == 0)
		{
			return true;
		}
		return false;
	}

};

//边的信息
struct Edge
{
	Vex vex1;
	Vex vex2;
	int weight;

	bool operator==(const Edge& obj) const
	{
		if (vex1 == obj.vex1 && vex2 == obj.vex2 && weight == obj.weight)
		{
			return true;
		}
		return false;
	}
};

