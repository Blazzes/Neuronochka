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
		i->SetWeight(i->GetWeight()+m_k*m_error*i->GetSourse()->GetResult()*funcActProiz(m_result));
		//if (i->GetWeight() > 1) std::cout << i->GetWeight();
	}
}

double Neiron::GetWeight() const
{
	return m_inConnections[0]->GetWeight();
}

double Neiron::GetError() const
{
	return m_error;
}

double Neiron::funcActivate(double input)
{
	if (input > 1)
	{
		return 1 + 0.01 * (input - 1);
	}
	if (input >= 0 && input <= 1)
	{
		return input;
	}
	if (input < 0)
	{
		return input*0.01;
	}
}

double Neiron::funcActProiz(double input)
{
	if (input < 0)
	{
		return 0.01;
	}
	if (input >= 0 && input <= 1)
	{
		return 1;
	}
	if (input > 1)
	{
		return 0.01;
	}
}
