#ifndef SINK_H
#define SINK_H
#include "Point.h"
#include"Components.h"
#include<vector>
#include <iostream>

using namespace std;

class Sink
{
private:
	int Sink_id;
	vector<double>location;   //�y��
	int total_values;
	vector<Point*>points; //�P��`�I
	vector<Mobile_Device> Device;//��m�R�q�˸m
	bool AllCharging = 0;//0->�٦��S�R�q�� 1->���R�L
	double Totaltype1_consumption;
	double Totaltype2_consumption;
	vector<Sink*>neighbor;

public:
	Sink(int sink_id,vector<double>& values);
	double get_location(int index);
	vector<Point*> get_points();
	void set_points(Point &point);
	void Add_Device(int &budset, bool uavORwcv);
	double Assign_task(double limit);
	double dist(double x1,double y1,double x2,double y2);
	bool search_Type();
	double cycle_Consumption(vector<Point*>Q,double time);
	double cycle_Charging();
	double cal_other_points_time(double limit);
	bool check_AllCherging();
	double revise_Totaltype1_consumption(bool read_write = 0, double value = 0);
	double revise_Totaltype2_consumption(bool read_write = 0, double value = 0);
	Sink* revise_neighbor(bool read_write,Sink &sinks,int index);
};

#endif