#pragma once
#include "Connection.h"
#include <vector>
#include <math.h>
class Neiron
{
public:
	Neiron(std::vector<Neiron*>* inputs);
	virtual void Calc_Result();
	double GetResult() const;
protected:
	double funcActivate(double input);
	std::vector<Connection*> m_inConnections;
	double m_result = 0;
};

