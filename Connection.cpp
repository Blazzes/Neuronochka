#include "Connection.h"
#include "Neiron.h"
Connection::Connection(Neiron* sourse, double weight): m_sourse(sourse), m_weight(weight)
{
}

double Connection::Calc_Sum_Out()
{
	return m_sourse->GetResult() * m_weight;
}
