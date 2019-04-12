#include"Cluster.h"

Cluster::Cluster()
{
}

void Cluster::merge(Sink &sink)
{
	this->sinks.push_back(&sink);
}
