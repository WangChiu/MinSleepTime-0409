
#include "Point.h"

#include<iostream>
#include<vector>
using namespace std;

//��l��Point
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

//���o�`�I����
int Point::get_node_Type()
{
	return this->node_Type;
}
//���o�`�I�v��
double Point::get_Wight() {
	return this->Wight;
}

double Point::get_TotalEnergy() {
	return this->Total_Energy;
}
//Ū�g�`�I��q(0->���o,1->��g;��g��)
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

//���o�`�I��q���Ӷq
double Point::get_Energy_consumption() {
	return this->Energy_consumption;
}

//Ū�g�`�I�ͦs�ɶ�(0->���o,1->��g;��g��)
double Point::revise_LifeTime_Time(bool read_write, double value)
{
	if (read_write == 0)
		return this->LifeTime;
	else if (read_write == 1)
		this->LifeTime = value;
}
//���o�`�I�R�q�v
double Point::get_Nodecharge_rate() {
	return this->receive_rate;
}

//���o�`�I�y��
double Point::get_location(int index)
{
	return this->location[index];
}



//Ū�g�`�I�ίv���A(0->���o,1->��g;��g��)
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

//���o�`�I�ŧO
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
