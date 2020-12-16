#pragma once
class Neiron;
class Connection
{
public:
	Connection(Neiron* sourse = nullptr, double weight = 0.5);
	double Calc_Sum_Out();
	Neiron* GetSourse() const;
	double GetWeight() const;
	void SetWeight(double NewWeight);
private:
	Neiron* m_sourse;
	double m_weight;
};

