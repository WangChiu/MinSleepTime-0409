
#include "Point.h"

#include<iostream>
#include<vector>
using namespace std;

//初始化Point
Point::Point(int id_point, vector<double>& values, int node_Type, double wight, double energy,
	double Energy_consumption, double Nodecharge_rate)
{
	this->node_id = id_point;
	total_values = values.size();

	for (int i = 0; i < total_values; i++)
		this->location.push_back(values[i]);

	this->node_Type = node_Type;
	this->Wight = wight;
	this->Total_Energy = energy;
	this->Energy = energy;
	this->Energy_consumption = Energy_consumption;
	this->receive_rate = Nodecharge_rate;
	this->LifeTime = Total_Energy / Energy_consumption;
	this->Rank = this->Energy_consumption;
	this->RemainingTime = Total_Energy / Energy_consumption;



}

//取得節點類型
int Point::get_node_Type()
{
	return this->node_Type;
}
//取得節點權重
double Point::get_Wight() {
	return this->Wight;
}

double Point::get_TotalEnergy() {
	return this->Total_Energy;
}
//讀寫節點能量(0->取得,1->改寫;改寫值)
double Point::revise_Energy(bool read_write, double value)
{
	if (read_write == 0) {
		return this->Energy;
	}
	else if (read_write == 1) {
		this->Energy = value;
		revise_ReminingTime(1);
	}

}

//取得節點能量消耗量
double Point::get_Energy_consumption() {
	return this->Energy_consumption;
}

//讀寫節點生存時間(0->取得,1->改寫;改寫值)
double Point::revise_LifeTime_Time(bool read_write, double value)
{
	if (read_write == 0)
		return this->LifeTime;
	else if (read_write == 1)
		this->LifeTime = value;
}
//取得節點充電率
double Point::get_Nodecharge_rate() {
	return this->receive_rate;
}

//取得節點座標
double Point::get_location(int index)
{
	return this->location[index];
}



//讀寫節點睡眠狀態(0->取得,1->改寫;改寫值)
bool Point::revise_Sleep(bool read_write, bool value)
{
	if (read_write == 0)
		return this->Sleep;
	else if (read_write == 1)
		this->Sleep = value;
}

int Point::getID()
{
	return this->node_id;
}

int Point::getTotalValues()
{
	return this->total_values;
}

//取得節點級別
double Point::get_Rank() {
	return this->Rank;
}
bool Point::revise_task(bool read_write, bool value) {
	if (read_write == 0) {
		return this->task;
	}
	else if (read_write == 1) {
		this->task = value;
	}
}
bool Point::revise_charging(bool read_write, bool value) {
	if (read_write == 0) {
		return this->charging;
	}
	else if (read_write == 1) {
		this->charging = value;
	}
}
double Point::revise_ExistTime(bool read_write, double value)
{
	if (read_write == 0) {
		return this->ExistTime;
	}
	else if(read_write == 1) {
		this->ExistTime += value;
	}
}

double Point::revise_ReminingTime(bool read_write)
{
	if (read_write == 0) {
		return this->RemainingTime;
	}
	else if (read_write == 1) {
		this->RemainingTime = this->Energy/this->Energy_consumption;
	}
}
