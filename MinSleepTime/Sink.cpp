
#include "Sink.h"
#include<time.h>
#include<iostream>
#include<vector>
using namespace std;

Sink::Sink(int sink_id,vector<double>& values)
{
	total_values = values.size();
	Sink_id = sink_id;
	for (int i = 0; i < total_values; i++)
		this->location.push_back(values.at(i));	
}

double Sink::get_location(int index) {
	return this->location[index];
}

vector<Point*> Sink::get_points() {
	return this->points;
}
void Sink::set_points(Point &point) {
	points.push_back(&point);
}
Point * Sink::get_point(int index)
{
	return this->points.at(index);
}
void Sink::Add_Device(int &budget,bool uavORwcv) {
	
	double x = this->get_location(0);
	double y = this->get_location(1);
	if (uavORwcv == 0) {
		WCV wcv(x, y);
		if (budget - wcv.revise_price() >= 0)
		{
			budget -= wcv.revise_price();
			this->Device.push_back(wcv);
		}
		else  return;
	}
	else if (uavORwcv == 1) {
		UAV uav(x, y);
		if (budget - uav.revise_price() >=0)
		{
			budget -= uav.revise_price();
			this->Device.push_back(uav);
		}
		else  return;
		
	}
	
}
bool Sink::search_Type() {
	bool flag = 0;

	for (int i = 0; i < points.size(); i++) {
		if (points.at(i)->get_node_Type() != 1) {
			flag = 1;
		}
	}
	return flag;
}
double Sink::cycle_Consumption(vector<Point*> Q, double time)
{
	double Sleeptime = 0;
	for (int i = 0; i < Q.size(); i++) {
		double Energy = Q.at(i)->revise_Energy(0);
		if (Energy - (Q.at(i)->get_Energy_consumption()*time) < 0) {
			Energy -=(Q.at(i)->get_Energy_consumption()*time);
			double temp = 0 - Energy;
			Q.at(i)->revise_Energy(1,0);
			Sleeptime += temp;
		}
		else {
			Energy -= (Q.at(i)->get_Energy_consumption()*time);
			Q.at(i)->revise_Energy(1, Energy);
		}
	}
	return Sleeptime;
}
bool Sink::check_AllCherging() {
	bool temp = 1;
	for (int j = 0; j < points.size(); j++) {
		if (points.at(j)->revise_charging() != 1)
			temp = 0;
	}
	return temp;
}

double Sink::revise_Totaltype1_consumption(bool read_write, double value)
{
	if (read_write == 0) {
		return this->Totaltype1_consumption;
	}
	else if (read_write == 1) {
		this->Totaltype1_consumption = value;
	}
}
double Sink::revise_Totaltype2_consumption(bool read_write, double value)
{
	if (read_write == 0) {
		return this->Totaltype2_consumption;
	}
	else if (read_write == 1) {
		this->Totaltype2_consumption = value;
	}
}

Sink* Sink::revise_neighbor(bool read_write,Sink &sinks,int index)
{
	if (read_write == 0) {
		return this->neighbor.at(index);
	}
	else if (read_write == 1) {
		this->neighbor.push_back(&sinks);

	}
}


double Sink::dist(double x1, double y1, double x2, double y2) {
	return sqrt(((x1 - x2)*(x1 - x2)) + ((y1 - y2)*(y1 - y2)));
}
double Sink::Assign_task(double limit) {
	double Task_time = 0;
	double SleepTime = 0;
	double Tonextdistance = 0;
	//double TonextEnergy = 0;
	double TonextTime = 0;
	double TonextChargeTime = 0;
	//double TonextChargeE = 0;
	double filnalTime = 0;	
	double TonextLifeTime = 0;
	for (int i = 0; i < Device.size(); i++) {
		double cycle_time = 0, cycle_energy = 0;
		double temp_x = this->get_location(0);
		double temp_y = this->get_location(1);
		double DeviceEnergy = Device.at(i).revise_Battery();
		bool count = 0;
		count=check_AllCherging();
		if (count == 1) {
			cout << "全部充完" << endl;
		}
		/*if (count == 1) {
			for (int j = 0; j < points.size(); j++) {
				points.at(j)->revise_charging(1, 0);
			}
			count = 0;
		}*/
		for (int j = 0; j < points.size(); j++) {
			//Point* tt;
			if (points.at(j)->revise_task() == 1) {
				continue;
			}
			if (points.at(j)->revise_charging() == 1) {
				continue;
			}
			if (Device.at(i).revise_name(0) == "WCV") {
				if (points.at(j)->get_node_Type() != 1) {
					continue;
				}
			}
			if (Device.at(i).revise_name(0) == "UAV") {
				if (points.at(j)->get_node_Type() == 1) {
					continue;
				}
			}
			if (j == 0 || j == points.size() - 1) {
				temp_x = Device.at(i).get_location(0);
				temp_y = Device.at(i).get_location(1);
			}
			Tonextdistance=dist(temp_x, temp_y, points.at(j)->get_location(0), points.at(j)->get_location(1));
			TonextTime = Tonextdistance / Device.at(i).revise_Speed(0);
			temp_x = points.at(j)->get_location(0);
			temp_y = points.at(j)->get_location(1);
			
			cycle_time += TonextTime + TonextChargeTime;
			double NextPointReminTime=points.at(j)->revise_ReminingTime(0);
			NextPointReminTime -= cycle_time;
			if (cycle_time < NextPointReminTime && cycle_time<= limit) {
				double Energy = points.at(i)->revise_Energy();
				//points.at(i)->revise_Energy(1, Energy - (TonextTime*points.at(i)->get_Energy_consumption()));
				Energy = Energy - (cycle_time*points.at(j)->get_Energy_consumption());
				//points.at(i)->revise_Energy(1, Energy);
				TonextChargeTime = ((points.at(i)->get_TotalEnergy() - Energy) / points.at(i)->get_Nodecharge_rate());
				
				filnalTime = dist(points.at(j)->get_location(0), points.at(j)->get_location(1), Device.at(i).get_location(0), Device.at(i).get_location(1)) / Device.at(i).revise_Speed();
				Device.at(i).Add_QT(*points.at(j));
				points.at(j)->revise_task(1,1);
				Device.at(i).Add_NextTime(TonextTime + TonextChargeTime);
			}
			else {
				//filnalTime= dist(points.at(j)->get_location(0), points.at(j)->get_location(1), Device.at(i).get_location(0), Device.at(i).get_location(1))/Device.at(i).revise_Speed();
				Device.at(i).Add_NextTime(filnalTime);
				break;
			}
			/*for (int e = 0; e < Device.at(i).get_QT().size(); e++) {
				cout << "Device " << i << "  QT有:" << Device.at(i).get_QT().at(e)->getID() << endl;
			}
			cout << "Device " << i << " 時間:  " << cycle_time << endl;*/
		}
		if (Device.at(i).get_QT().empty() == 1) {
			cout << "Device: " << i << " QT是空的" << endl;
			for (int i = 0; i < points.size(); i++) {
				cout << "points " << i << " Tyep: " << points.at(i)->get_node_Type() << "charging_Typy: " << points.at(i)->revise_charging() << " task: " << points.at(i)->revise_task() << endl;;
			}
			system("pause");
		}
	}
	SleepTime += cycle_Charging();
	return SleepTime;

}
double Sink::cycle_Charging()
{
	double SleepTime = 0;
	double Time = 0;

	//Assign_task();
	
	for (int i = 0; i < this->Device.size(); i++) {
		double ChargingTime = 0;
		double time = 0;
		for (int j = 0; j < this->Device.at(i).get_QT().size(); j++) {
			ChargingTime = Device.at(i).Run_Charging(*Device.at(i).get_QT().at(j));
			Device.at(i).get_QT().at(j)->revise_charging(1, 1);
			Device.at(i).get_QT().at(j)->revise_task(1, 0);
			double TravelTime = Device.at(i).get_NextTime().at(j);
		}
		Device.at(i).reset_QT();		
	}
	return SleepTime;
}

double Sink::cal_other_points_time(double limit)
{
	double SleepTime=0;
	vector<Point*>Temp;
	for (int i = 0; i < points.size(); i++) {
		if (points.at(i)->revise_charging(0) == 0 && points.at(i)->revise_task(0) == 0) {
			Temp.push_back(points.at(i));
		}
	}
	if (Temp.empty() == 1) {
		return SleepTime;
	}
	SleepTime += cycle_Consumption(Temp, limit);
	return SleepTime;
}
