#include "Neiron.h"

Neiron::Neiron(std::vector<Neiron*>* inputs)
{
	if (!inputs) return;
	for (int i = 0; i < inputs->size(); i++)
	{
		m_inConnections.push_back(new Connection(inputs->at(i), 0.5));
	}
}

void Neiron::Calc_Result()
{
	double sum_r = 0;
	for (int i = 0; i < m_inConnections.size(); i++) {
		sum_r += m_inConnections[i]->Calc_Sum_Out();
	}
	m_result = funcActivate(sum_r);
}

double Neiron::GetResult() const
{
	return m_result;
}

double Neiron::funcActivate(double input)
{
	return 1.0/(1.0+exp(-input));
}
