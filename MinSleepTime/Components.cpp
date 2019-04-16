
#include"Components.h"
#include <vector>
#include<fstream>
#include <iostream>
using namespace std;

string Mobile_Device::revise_name(bool read_write,const string &names) {
	if (read_write == 0) {
		return this->name;
	}
	else if (read_write == 1) {
		this->name = names;
		return "";
	}
}

void Mobile_Device::set_TotalBattery(double value) {
	this->Total_Battery = value;
}

double Mobile_Device::get_TotalBattery()
{
	return this->Total_Battery;
}

int Mobile_Device::revise_price(bool read_write, int money) {
	if (read_write == 0) {
		return this->price;
	}
	else if (read_write == 1) {
		this->price = money;
		
	}
}

double Mobile_Device::revise_Speed(bool read_write,double value) {
	if (read_write == 0) {
		return this->Speed;
	}
	else if (read_write == 1) {
		this->Speed = value;
		
	}
}

void Mobile_Device::set_location(double x, double y) {
	this->location_x = x;
	this->location_y = y;
	
}
double Mobile_Device::get_location(int index) {
	if (index == 0) {
		return this->location_x;
	}
	else if (index == 1) {
		return this->location_y;
	}
}

Mobile_Device::Mobile_Device() {
	
}
double Mobile_Device::revise_Battery(bool read_write , double value )
{
	if (read_write == 0) {
		return this->Battery;
	}
	else if (read_write == 1) {
		this->Battery = value;
	}
	
}

double Mobile_Device::get_Mobile_consumption() {
	return this->Mobile_consumption;
}

void Mobile_Device::Add_QT(Point& point) {
	this->QT.push_back(&point);
}
void Mobile_Device::Add_points(Point& point) {
	this->points.push_back(&point);
}
vector<Point*> Mobile_Device::get_QT() {
	return this->QT;
}

void Mobile_Device::Add_NextEnergy(double Energy)
{
	this->NextEnergy.push_back(Energy);
}






	
double Mobile_Device::Run_Charging(Point &point) {
	double ChargingEnergy = point.get_TotalEnergy() - point.revise_Energy();
	double ChargingTime = ChargingEnergy/point.get_Nodecharge_rate();
	point.revise_Energy(1, point.get_TotalEnergy());
	return ChargingTime;
}

void Mobile_Device::Add_NextTime(double Time)
{
	this->NextTime.push_back(Time);
}

vector<double> Mobile_Device::get_NextTime()
{
	return this->NextTime;
}

void Mobile_Device::reset_QT()
{
	this->QT.clear();
	this->NextTime.clear();
}

double Mobile_Device::get_Charging_rate()
{
	return this->Charging_rate;
}

UAV::UAV(double x, double y)
{
	
	this->revise_name(1,"UAV");
	this->revise_price(1, 40000);
	this->set_TotalBattery(45000);
	this->revise_Battery(1,45000);
	this->revise_Speed(1, 5);
	this->set_location(x, y);

}
WCV::WCV(double x, double y)
{
	this->revise_name(1,"WCV");
	this->revise_price(1, 10000);
	this->set_TotalBattery(180000);
	this->revise_Battery(1,180000);
	this->revise_Speed(1,1);
	this->set_location(x,y);

	
}