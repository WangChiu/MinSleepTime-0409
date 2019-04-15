#include"Cluster.h"

Cluster::Cluster(vector<Sink*>&group,bool Type1_Type2,int WCVnum,int UAVnum)
{
	
	for (int i = 0; i < group.size(); i++) {
		this->sinks.push_back(group.at(i));
		if (Type1_Type2 == 0) {
				this->consumption += group.at(i)->revise_Totaltype1_consumption();
			}
			else if (Type1_Type2 == 1) {
				this->consumption += group.at(i)->revise_Totaltype2_consumption();
			}
			
			for (int k = 0; k < group.at(i)->get_points().size(); k++) {
				if (Type1_Type2 == 0) {
					if (group.at(i)->get_point(k)->get_node_Type() == 1) {
						this->points.push_back(group.at(i)->get_point(k));
					}
					
				}
				else if (Type1_Type2 == 1) {
					if (group.at(i)->get_point(k)->get_node_Type() == 2) {
						this->points.push_back(group.at(i)->get_point(k));
					}
					
				}
			}	
	}
	if (Type1_Type2 == 0) {
		
		int temp = sinks.size()-1;
		this->location_x = sinks.at(temp)->get_location(0);
		this->location_y = sinks.at(temp)->get_location(1);
		if (WCVnum != 0) {
			WCV wcv(sinks.at(temp)->get_location(0), sinks.at(temp)->get_location(1));
			this->set_vehicle(wcv);
			set_points(points);
		}
		
	}
	else if (Type1_Type2 == 1) {
		int temp = sinks.size() - 1;
		this->location_x = sinks.at(temp)->get_location(0);
		this->location_y = sinks.at(temp)->get_location(1);
		if (UAVnum != 0) {
			UAV uav(sinks.at(temp)->get_location(0), sinks.at(temp)->get_location(1));
			this->set_vehicle(uav);
			set_points(points);
		}
		
	}
}

vector<Sink*> Cluster::get_sinks()
{
	return this->sinks;
}

vector<Point*> Cluster::get_points()
{
	return this->points;
}

void Cluster::set_vehicle(Mobile_Device vehicle)
{
	this->vehicle.push_back(vehicle);
}
void Cluster::set_points(vector<Point*> &points)
{
	for (int i = 0; i < points.size(); i++) {
		this->vehicle.at(0).Add_points(*points.at(i));
	}
}
double Cluster::Assign_task(double limit) {
	
	double Task_time = 0;
	double SleepTime = 0;
	double Tonextdistance = 0;
	//double TonextEnergy = 0;
	double TonextTime = 0;
	double TOnextEnergy = 0;
	double TonextChargeTime = 0;
	double TonextChargeEnergy = 0;
	//double TonextChargeE = 0;
	double filnalTime = 0;
	double TonextLifeTime = 0;
	for (int i = 0; i < vehicle.size(); i++) {
		double cycle_time = 0, cycle_energy = 0;
		double MobileEnergy = vehicle.at(i).revise_Battery();
		double temp_x = this->location_x;
		double temp_y = this->location_y;
		bool count = 0;
		count = check_AllCherging();
		for (int j = 0; j < points.size(); j++) {
			if (points.at(j)->revise_task() == 1) {
				continue;
			}
			if (points.at(j)->revise_charging() == 1) {
				continue;
			}
			if (j == 0 || j == points.size() - 1) {
				temp_x = vehicle.at(i).get_location(0);
				temp_y = vehicle.at(i).get_location(1);
			}
			Tonextdistance = dist(temp_x, temp_y, points.at(j)->get_location(0), points.at(j)->get_location(1));
			TonextTime = Tonextdistance / vehicle.at(i).revise_Speed(0);
			TOnextEnergy = TonextTime * this->vehicle.at(i).get_Mobile_consumption();
			temp_x = points.at(j)->get_location(0);
			temp_y = points.at(j)->get_location(1);
			double NextPointReminTime = points.at(j)->revise_ReminingTime(0);
			NextPointReminTime -= cycle_time;
			cycle_time += TonextTime + TonextChargeTime;
			if (cycle_time < NextPointReminTime && cycle_time <= limit && (MobileEnergy-TOnextEnergy-TonextChargeEnergy) <= 0) {
				
			}
			
		}
	}
	/*for (int i = 0; i < vehicle.size(); i++) {
		
		double cycle_time = 0, cycle_energy = 0;
		double temp_x = this->location_x;
		double temp_y = this->location_y;
		double DeviceEnergy = vehicle.at(i).revise_Battery();
		bool count = 0;
		count = check_AllCherging();
		
		for (int j = 0; j < points.size(); j++) {

			if (points.at(j)->revise_task() == 1) {
				continue;
			}
			if (points.at(j)->revise_charging() == 1) {
				continue;
			}
			if (vehicle.at(i).revise_name(0) == "WCV") {
				if (points.at(j)->get_node_Type() != 1) {
					continue;
				}
			}
			if (vehicle.at(i).revise_name(0) == "UAV") {
				if (points.at(j)->get_node_Type() == 1) {
					continue;
				}
			}
			if (j == 0 || j == points.size() - 1) {
				temp_x = vehicle.at(i).get_location(0);
				temp_y = vehicle.at(i).get_location(1);
			}
			Tonextdistance = dist(temp_x, temp_y, points.at(j)->get_location(0), points.at(j)->get_location(1));
			TonextTime = Tonextdistance / vehicle.at(i).revise_Speed(0);
			temp_x = points.at(j)->get_location(0);
			temp_y = points.at(j)->get_location(1);

			cycle_time += TonextTime + TonextChargeTime;
			double NextPointReminTime = points.at(j)->revise_ReminingTime(0);
			NextPointReminTime -= cycle_time;
			
			if ((cycle_time < NextPointReminTime && cycle_time+ filnalTime <= limit)) {
				double Energy = points.at(i)->revise_Energy();
				Energy = Energy - (cycle_time*points.at(j)->get_Energy_consumption());
				points.at(j)->revise_Energy(1,Energy);
				for (int z = 0; z < points.size(); z++) {
					cout << points.at(z)->getID() << "\t" << points.at(z)->revise_Energy() << "\t" << points.at(z)->revise_ReminingTime() << "\t" << cycle_time << endl;
				}
				cout << "------------------------------------------" << endl;
				TonextChargeTime = ((points.at(i)->get_TotalEnergy() - Energy) / points.at(i)->get_Nodecharge_rate());
				filnalTime = dist(points.at(j)->get_location(0), points.at(j)->get_location(1), vehicle.at(i).get_location(0), vehicle.at(i).get_location(1)) / vehicle.at(i).revise_Speed();
				vehicle.at(i).Add_QT(*points.at(j));
				points.at(j)->revise_task(1, 1);
				vehicle.at(i).Add_NextTime(TonextTime + TonextChargeTime);
			}
			else {

				vehicle.at(i).Add_NextTime(filnalTime);
				break;
			}

		}
		SleepTime += cycle_Charging();
		return SleepTime;
	}*/
}
double Cluster::cycle_Charging()
{
	double SleepTime = 0;
	double Time = 0;
	for (int i = 0; i < this->vehicle.size(); i++) {
		double ChargingTime = 0;
		double time = 0;
		for (int j = 0; j < this->vehicle.at(i).get_QT().size(); j++) {
			vehicle.at(i).get_QT().at(j)->revise_Energy(1, vehicle.at(i).get_QT().at(j)->get_TotalEnergy());
			for (int z = 0; z < points.size(); z++) {
				cout << points.at(z)->getID() << "\t" << points.at(z)->revise_Energy() << "\t" << points.at(z)->revise_ReminingTime() << endl;
			}
			vehicle.at(i).get_QT().at(j)->revise_charging(1, 1);
			vehicle.at(i).get_QT().at(j)->revise_task(1, 0);
			double TravelTime = vehicle.at(i).get_NextTime().at(j);
		}
		vehicle.at(i).reset_QT();
	}
	return SleepTime;
}

double Cluster::cal_other_points_time(double limit)
{
	double SleepTime = 0;
	vector<Point*>Temp;
	for (int i = 0; i < points.size(); i++) {
		if (points.at(i)->revise_charging(0) == 0 ){
			if(points.at(i)->revise_task(0) == 0) {
				Temp.push_back(points.at(i));
			}
			else {
				continue;
			}
		}
		else {
			continue;
		}
	}
	if (Temp.empty() == 1) {
		return SleepTime;
	}
	SleepTime += cycle_Consumption(Temp, limit);
	return SleepTime;
}
double Cluster::dist(double x1, double y1, double x2, double y2) {
	return sqrt(((x1 - x2)*(x1 - x2)) + ((y1 - y2)*(y1 - y2)));
}
bool Cluster::check_AllCherging() {
	bool temp = 1;
	for (int j = 0; j < points.size(); j++) {
		if (points.at(j)->revise_charging() != 1)
			temp = 0;
	}
	return temp;
}
double Cluster::cycle_Consumption(vector<Point*> Q, double time)
{
	double Sleeptime = 0;
	for (int i = 0; i < Q.size(); i++) {
		double Energy = Q.at(i)->revise_Energy(0);
		if (Energy - (Q.at(i)->get_Energy_consumption()*time) < 0) {
			Energy -= (Q.at(i)->get_Energy_consumption()*time);
			double temp = 0 - Energy;
			Q.at(i)->revise_Energy(1, 0);
			Sleeptime += temp;
		}
		else {
			Energy -= (Q.at(i)->get_Energy_consumption()*time);
			Q.at(i)->revise_Energy(1, Energy);
		}
	}
	return Sleeptime;
}


