#pragma once
#include "Neiron.h"
class Connection
{
public:
	Connection(Neiron* sourse = nullptr, double weight = 0.5);
	double Calc_Sum_Out();
private:
	Neiron* m_sourse;
	double m_weight;
};

