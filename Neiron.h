#pragma once

#include <vector>
#include <math.h>
#include <iostream>
class Connection;
class Neiron
{
public:
	Neiron(std::vector<Neiron*>* inputs);
	Neiron(Neiron** inputs, size_t size);
	virtual void Calc_Result();
	double GetResult() const;
	virtual void CompError(double pre_error);
	void CompPreError();
	void CorectWeight();
	double GetError() const;
protected:
	double funcActivate(double input);
	double funcActProiz(double input);
	//std::vector<Connection*> m_inConnections;
	Connection** m_inCon = nullptr;
	size_t size_con = 0;
	double m_tmp = 0;
	double m_result = 0;
	double m_error = 0;
	double m_k = 0.1;
};

