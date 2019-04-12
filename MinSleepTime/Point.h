#ifndef POINT_H
#define POINT_H

#include <vector>
#include <iostream>

//#include "Components.h"
using namespace std;
//#include "Sink.h"
class Point
{
private:
	int node_id;
	vector<double> location;    //座標
	int node_Type;
	double Wight;
	double Total_Energy;
	double Energy;
	double Energy_consumption;
	double receive_rate; //接收率
	double LifeTime;    //壽命
	double RemainingTime;
	double ExistTime=0;    //存活時間
	bool Sleep = 0;
	int total_values;
	double Rank;
	bool task = 0; //QT序列中
	bool charging = 0;//充電中
public:
	////初始化Point
	Point(int id_point, vector<double>& values, int node_Type, double wight, double energy,
		double Energy_consumption, double Nodecharge_rate);
	//取得節點編號
	int getID();
	//取得節點座標
	double get_location(int index);
	//取得節點類型
	int get_node_Type();
	//取得節點權重
	double get_Wight();
	double get_TotalEnergy();
	//讀寫節點能量(0->取得,1->改寫;改寫值)
	double revise_Energy(bool read_write = 0, double value = 0);
	//取得節點能量消耗量
	double get_Energy_consumption();
	//取得節點充電率
	double get_Nodecharge_rate();
	//讀寫節點生存時間(0->取得,1->改寫;改寫值)
	double revise_LifeTime_Time(bool read_write=0, double value=0);
	//讀寫節點睡眠狀態(0->取得,1->改寫;改寫值)
	bool revise_Sleep(bool read_write = 0, bool value = 0);
	//讀寫節點更新消耗型別(0->取得,1->改寫;0->WCV,1->UAV,2->no charge,3->sleep)
	int getTotalValues();
	//取得節點級別
	double get_Rank();
	bool revise_task(bool read_write = 0, bool value = 0);
	bool revise_charging(bool read_write=0, bool value=0);
	double revise_ExistTime(bool read_write = 0, double value = 0);
	double revise_ReminingTime(bool read_write=0);
};



#endif
