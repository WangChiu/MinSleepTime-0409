#ifndef CLUSTER_H
#define CLUSTER_H
#include"Sink.h"
#include"Point.h"
class Cluster {
private:
	double consumption;
	double location_x;
	double location_y;
	vector<Sink*>sinks;
	vector<Point*>points;
	vector<Mobile_Device>vehicle;
	
public:
	Cluster(vector<Sink*>&group, bool Type1_Type2, int WCVnum, int UAVnum);
	vector<Sink*> get_sinks();
	vector<Point*>get_points();
	void set_vehicle(Mobile_Device vehicle);
	void set_points(vector<Point*>&points);
	double Assign_task(double limit);
	double cycle_Charging();
	double cal_other_points_time(double limit);
	double dist(double x1, double y1, double x2, double y2);
	bool check_AllCherging();
	double cycle_Consumption(vector<Point*> Q, double time);
};


#endif
