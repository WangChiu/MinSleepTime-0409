#ifndef CLUSTER_H
#define CLUSTER_H
#include"Sink.h"
#include"Point.h"
class Cluster {
private:
	vector<Sink*>sinks;
	vector<Point*>points;
	double consumption;
public:
	Cluster();
	void merge(Sink &sink);
	
};


#endif
