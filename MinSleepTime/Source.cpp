#include <iostream>
#include <vector>
#include<string>
#include <time.h>
#include <algorithm>
#include<math.h>
#include <list>
#include<fstream>
#include<time.h>
#include"Components.h"
#include"Point.h"
#include"Sink.h"
#include"Cluster.h"

using namespace std;
int total_points, total_values;


class Main {
private:
	vector<Point*>points;
	vector<Sink*>sinks;
	vector<vector<Sink*>>groups1;
	vector<vector<Sink*>>groups2;
	vector<Cluster>clusters1;
	vector<Cluster>clusters2;
	int WCVnum = 0;
	int UAVnum = 0;
	double SleepTime;
	int *budget;
public:
	Main(const char *argv, const char *argv2) {
		int temp = 30000;
		double test = 0;
		double limit = 6;
		this->budget = &temp;
		read_TopofileNode(argv2);
		sort(points.begin(), points.end(), cmp);
		read_TopofileSink(argv);
		BUY_Device(*budget, limit);
		merge();
				
		//Consumption(1);
		
		for (int k = 0; k < 360; k++) {
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < clusters1.size(); i++) {			
					SleepTime += clusters1.at(i).Assign_task(limit);
					SleepTime += clusters1.at(i).cal_other_points_time(limit);
				};
				for (int i = 0; i < clusters2.size(); i++) {
					SleepTime += clusters2.at(i).Assign_task(limit);
					SleepTime += clusters2.at(i).cal_other_points_time(limit);	
				};
			};
			cout << k << "¤Ñµ²§ô¡ASleetTime:" << SleepTime << endl;
		};
	
	cout << "SleepTime: "<<(SleepTime/24) << endl;
	system("pause");
	}
	static bool cmp(Point* a, Point* b) {
		return a->get_Rank() > b->get_Rank();
	}
	static bool sort_consumption1(Sink* a, Sink* b) {
		return a->revise_Totaltype1_consumption() < b->revise_Totaltype1_consumption();
	}
	static bool sort_consumption2(Sink* a, Sink* b) {
		return a->revise_Totaltype2_consumption() < b->revise_Totaltype2_consumption();
	}
	static bool sort_groups1(vector<Sink*>a,vector<Sink*>b) {
		double temp = 0;
		double temp_s = 0;
		for (int i = 0; i < a.size(); i++) {
			temp += a.at(i)->revise_Totaltype1_consumption();
		}
		for (int i = 0; i < b.size(); i++) {
			temp_s += b.at(i)->revise_Totaltype1_consumption();
		}
		return temp < temp_s;
	}
	static bool sort_groups2(vector<Sink*>a, vector<Sink*>b) {
		double temp = 0;
		double temp_s = 0;
		for (int i = 0; i < a.size(); i++) {
			temp += a.at(i)->revise_Totaltype2_consumption();
		}
		for (int i = 0; i < b.size(); i++) {
			temp_s += b.at(i)->revise_Totaltype2_consumption();
		}
		return temp < temp_s;
	}
	void merge() {
		
		sort(sinks.begin(), sinks.end(), sort_consumption1);

		for (int i = 0; i < sinks.size(); i++) {
			vector<Sink*>temp;
			temp.push_back(sinks.at(i));
			groups1.push_back(temp);
		}
		while (groups1.size() > WCVnum) {
			if (groups1.size()== 1)break;
			if (groups1.size() <= WCVnum)break;
			//if (WCVnum = 0)break;
			Sink* closeSink = groups1.at(0).at(0);
			double temp = 10e10;
			int count = 0;
			for (int j = 1; j < groups1.size(); j++) {
				double temp_s = sqrt(pow(groups1.at(0).at(0)->get_location(0) - groups1.at(j).at(0)->get_location(0), 2) + pow(groups1.at(0).at(0)->get_location(1) - groups1.at(j).at(0)->get_location(1), 2));
				if (temp_s < temp) {
					temp = temp_s;
					closeSink = groups1.at(j).at(0);
					count = j;
				}
			}
			for (int i = 0; i < groups1.at(count).size(); i++) {
				groups1.at(0).push_back(groups1.at(count).at(i));
			}
			
			groups1.erase(groups1.begin() + count);
			sort(groups1.begin(), groups1.end(), sort_groups1);
		}

		sort(sinks.begin(), sinks.end(), sort_consumption2);
		for (int i = 0; i < sinks.size(); i++) {
			vector<Sink*>temp;
			temp.push_back(sinks.at(i));
			groups2.push_back(temp);
		}
		while (groups2.size() > UAVnum) {
			if (groups2.size() == 1)break;
			if (groups2.size() <= UAVnum)break;
			//if (UAVnum = 0)break;
			Sink* closeSink = groups2.at(0).at(0);
			double temp = 10e10;
			int count = 0;
			for (int j = 1; j < groups2.size(); j++) {
				double temp_s = sqrt(pow(groups2.at(0).at(0)->get_location(0) - groups2.at(j).at(0)->get_location(0), 2) + pow(groups2.at(0).at(0)->get_location(1) - groups2.at(j).at(0)->get_location(1), 2));
				if (temp_s < temp) {
					temp = temp_s;
					closeSink = groups2.at(j).at(0);
					count = j;
				}
			}
			for (int i = 0; i < groups2.at(count).size(); i++) {
				groups2.at(0).push_back(groups2.at(count).at(i));
			}
			groups2.erase(groups2.begin() + count);
			sort(groups2.begin(), groups2.end(), sort_groups2);
		}

		for (int i = 0; i < groups1.size(); i++) {
			for (int j = 0; j < groups1.size(); j++) {
				if (i == j)
					continue;

				double dist = sqrt(pow(sinks.at(i)->get_location(0) - sinks.at(j)->get_location(0), 2) + pow(sinks.at(i)->get_location(1) - sinks.at(j)->get_location(1), 2));

			}
		}
		for (int i = 0; i < groups1.size(); i++) {
			Cluster Type1(groups1.at(i), 0,WCVnum,UAVnum);
			clusters1.push_back(Type1);
		}
		for (int i = 0; i < groups2.size(); i++) {
			Cluster Type2(groups2.at(i), 1, WCVnum, UAVnum);
			clusters2.push_back(Type2);
		}
	}
	void belong() {
		for (int i = 0; i < points.size(); i++) {
			double temp = sqrt(pow(points.at(i)->get_location(0) - sinks.at(0)->get_location(0), 2) + pow(points.at(i)->get_location(1) - sinks.at(0)->get_location(1), 2));
			Sink* temp_s = sinks.at(0);
			int count = 0;
			for (int j = 1; j < sinks.size(); j++) {
				double disc = sqrt(pow(points.at(i)->get_location(0) - sinks.at(j)->get_location(0), 2) + pow(points.at(i)->get_location(1) - sinks.at(j)->get_location(1), 2));
				if (disc < temp) {
					temp = disc;
					temp_s = sinks.at(j);
					count = j;
				}
			}
			sinks.at(count)->set_points(*points.at(i));
			if (points.at(i)->get_node_Type() == 1) {
				double consumption = sinks.at(count)->revise_Totaltype1_consumption(0);
				consumption += points.at(i)->get_Energy_consumption();
				sinks.at(count)->revise_Totaltype1_consumption(1, consumption);
			}
			else if (points.at(i)->get_node_Type() == 2) {
				double consumption = sinks.at(count)->revise_Totaltype2_consumption(0);
				consumption += points.at(i)->get_Energy_consumption();
				sinks.at(count)->revise_Totaltype2_consumption(1, consumption);
			}
			
		}
	}
		
	void BUY_Device(int& budget,int limitTime) {
		int temp = 0;
		double Type_1 = 0;
		double Type_2 = 0;
		UAV uav(0,0);
		WCV wcv(0,0);
		for (int i = 0; i < points.size(); i++) {
			if (points.at(i)->get_node_Type() == 1) {
				Type_1 += points.at(i)->get_Energy_consumption();
			}
			else if (points.at(i)->get_node_Type() == 2) {
				Type_2 += points.at(i)->get_Energy_consumption();
			}
		}
		int UAV_num = ceil((Type_2/(uav.get_Charging_rate())*limitTime));
		int WCV_num = ceil((Type_1 / (wcv.get_Charging_rate())*limitTime));
		for (int i = 0; i < UAV_num; i++) {
			if (budget - uav.revise_price() >=0) {
				budget -= uav.revise_price();
				UAVnum++;
			}
			else  break;	
		}
		while (budget >=wcv.revise_price()) {
			budget -= wcv.revise_price();
			WCVnum++;
		}
			
	
	}
	void read_TopofileSink(const char *fileName1) {
		//vector<Sink*>temp;
		if (fileName1 == NULL) {
			fileName1 = "Sink_Topolist.txt";
		}
		
		ifstream ReadTopo_Sink;
		string SinkTopoName = fileName1;// "Sink_Topolist.txt";
		ReadTopo_Sink.open(SinkTopoName.c_str(), ios::in);
		ReadTopo_Sink >> total_points >> total_values;
		Sink *temp;
		for (int i = 0; i < total_points; i++)
		{
			int sink_id;
			ReadTopo_Sink >> sink_id;
			vector<double> values;
			for (int j = 0; j < total_values; j++)
			{
				double value;
				ReadTopo_Sink >> value;
				values.push_back(value);
			}
			//Sink n(values);
			temp = new Sink(sink_id,values);
			sinks.push_back(temp);
		}
		ReadTopo_Sink.close();
		belong();
		
	
		//return temp;
	}
	//vector<Point*> 
	void read_TopofileNode(const char *fileName2) {
		if (fileName2 == NULL) {
			fileName2 = "Node_Topolist.txt";
		}
		ifstream ReadTopo_Node;
		string NodeTopoName = fileName2;// "Node_Topolist.txt";
		ReadTopo_Node.open(NodeTopoName.c_str(), ios::in);
		ReadTopo_Node >> total_points >> total_values;
		Point *temp;
		for (int i = 0; i < total_points; i++)
		{
			int node_id;
			ReadTopo_Node >> node_id;
			vector<double> values;
			for (int j = 0; j < total_values; j++)
			{
				double value;
				ReadTopo_Node >> value;
				values.push_back(value);
			}

			int node_Type;
			double energy, Energy_consumption, Nodecharge_rate, wight;
			ReadTopo_Node >> node_Type >> wight >> energy >> Energy_consumption >> Nodecharge_rate;
			temp = new Point(node_id, values, node_Type, wight, energy, Energy_consumption, Nodecharge_rate);

			points.push_back(temp);
		}
		ReadTopo_Node.close();
		//return temp;

	}

	void Consumption(double time) {

		for (int i = 0; i < points.size(); i++) {
			double temp=points.at(i)->revise_ExistTime();
			points.at(i)->revise_ExistTime(1,time);
			double Energy = points.at(i)->revise_Energy(0, 0);
			Energy -= (points.at(i)->get_Energy_consumption()*time);
			if (Energy <= 0) {
				double temp = 0 - Energy;
				points.at(i)->revise_Energy(1, 0);
				this->SleepTime += temp / points.at(i)->get_Energy_consumption();
			}
			else {
				points.at(i)->revise_Energy(1, Energy);

			}

		}
	}
};

int main(int argc,char *argv[])
{
	char* filename1 = NULL;
	char* filename2 = NULL;
	if (argc == 3) {
		filename1 = argv[1];//Sink
		filename2 = argv[2];//Node
	}
	Main mo(filename1, filename2);
	
	return 0;

}
