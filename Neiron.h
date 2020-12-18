#pragma once

#include <vector>
#include <math.h>
#include <iostream>
class Connection;
class Neiron
{
public:
	Neiron(std::vector<Neiron*>* inputs);
	virtual void Calc_Result();
	double GetResult() const;
	virtual void CompError(double pre_error);
	void CompPreError();
	void CorectWeight();
	double GetWeight() const;
	double GetError() const;
protected:
	double funcActivate(double input);
	double funcActProiz(double input);
	std::vector<Connection*> m_inConnections;
	double m_result = 0;
	double m_error = 0;
	double m_k = 0.05;
};

