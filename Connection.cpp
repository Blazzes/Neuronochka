#include "Connection.h"
#include "Neiron.h"
Connection::Connection(Neiron* sourse, double weight): m_sourse(sourse), m_weight(weight)
{
}

double Connection::Calc_Sum_Out()
{
	return m_sourse->GetResult() * m_weight;
}

Neiron* Connection::GetSourse() const
{
	return m_sourse;
}

double Connection::GetWeight() const
{
	return m_weight;
}

void Connection::SetWeight(double NewWeight)
{
	m_weight = NewWeight;
}
