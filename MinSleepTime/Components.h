#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <vector>
#include <iostream>
#include "Point.h"
using namespace std;



class Mobile_Device {
private:
	string name="";
	double location_x, location_y;//初始座標
	int price;//售價
	double Total_Battery;
	double Battery;//攜帶電量
	double Speed;//速度
	double Mobile_consumption=8000;//移動消耗
	double Charging_rate = 7200;  //充電率(J/h)
	vector<Point*>points;//周圍節點
	vector<Point*>QT;//周圍等待節點序列
	vector<double>NextTime;//每段距離序列
	double cycle_Time;
	
public:
	Mobile_Device();
	string revise_name(bool read_write , const string &name="");
	void set_TotalBattery(double value);
	double get_TotalBattery();
	int revise_price(bool read_write = 0,int money=0);
	double revise_Speed(bool read_write = 0, double value = 0);
	void set_location(double x, double y);
	double get_location(int index);
	double revise_Battery(bool read_write = 0, double value = 0);
	double get_Mobile_consumption();
	void Add_points(Point &point);
	void Add_QT(Point &point);
	vector<Point*> get_QT();
	//void reset_QT(bool uav_or_wcv);
	double Run_Charging(Point &point);
	void Add_NextTime(double Time);
	vector<double> get_NextTime();
	void reset_QT();
	double get_Charging_rate();
};

class UAV :public Mobile_Device {

public:
	UAV(double x, double y);
	//void Set_Charging(double Battery);
	
	
};
class WCV :public Mobile_Device {

public:
	WCV(double x, double y);
	//void Set_Charging(double Battery);
};
#endif