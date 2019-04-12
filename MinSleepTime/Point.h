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
	vector<double> location;    //�y��
	int node_Type;
	double Wight;
	double Total_Energy;
	double Energy;
	double Energy_consumption;
	double receive_rate; //�����v
	double LifeTime;    //�ةR
	double RemainingTime;
	double ExistTime=0;    //�s���ɶ�
	bool Sleep = 0;
	int total_values;
	double Rank;
	bool task = 0; //QT�ǦC��
	bool charging = 0;//�R�q��
public:
	////��l��Point
	Point(int id_point, vector<double>& values, int node_Type, double wight, double energy,
		double Energy_consumption, double Nodecharge_rate);
	//���o�`�I�s��
	int getID();
	//���o�`�I�y��
	double get_location(int index);
	//���o�`�I����
	int get_node_Type();
	//���o�`�I�v��
	double get_Wight();
	double get_TotalEnergy();
	//Ū�g�`�I��q(0->���o,1->��g;��g��)
	double revise_Energy(bool read_write = 0, double value = 0);
	//���o�`�I��q���Ӷq
	double get_Energy_consumption();
	//���o�`�I�R�q�v
	double get_Nodecharge_rate();
	//Ū�g�`�I�ͦs�ɶ�(0->���o,1->��g;��g��)
	double revise_LifeTime_Time(bool read_write=0, double value=0);
	//Ū�g�`�I�ίv���A(0->���o,1->��g;��g��)
	bool revise_Sleep(bool read_write = 0, bool value = 0);
	//Ū�g�`�I��s���ӫ��O(0->���o,1->��g;0->WCV,1->UAV,2->no charge,3->sleep)
	int getTotalValues();
	//���o�`�I�ŧO
	double get_Rank();
	bool revise_task(bool read_write = 0, bool value = 0);
	bool revise_charging(bool read_write=0, bool value=0);
	double revise_ExistTime(bool read_write = 0, double value = 0);
	double revise_ReminingTime(bool read_write=0);
};



#endif
