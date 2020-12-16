#include "Neiron.h"
#include "Connection.h"
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
	m_error = 0;
	for (int i = 0; i < m_inConnections.size(); i++) {
		sum_r += m_inConnections[i]->Calc_Sum_Out();
	}
	m_result = funcActivate(sum_r);
}

double Neiron::GetResult() const
{
	return m_result;
}

void Neiron::CompError(double pre_error)
{
	m_error += pre_error;
}

void Neiron::CompPreError()
{
	for (auto i : m_inConnections)
	{
		i->GetSourse()->CompError(i->GetWeight() * m_error);
	}
}

void Neiron::CorectWeight()
{
	for (auto i : m_inConnections)
	{
		i->SetWeight(i->GetWeight()+m_k*m_error*i->GetSourse()->GetResult()*funcActivate(m_result)*(1.0-funcActivate(m_result)));
	}
}

double Neiron::GetWeight() const
{
	return 0.0;
}

double Neiron::GetError() const
{
	return m_error;
}

double Neiron::funcActivate(double input)
{
	return 1.0/(1.0+exp(-input));
}
