#include "OutputNeiron.h"
#include <iostream>
OutputNeiron::OutputNeiron(std::vector<Neiron*>* inputs): Neiron(inputs)
{
}

void OutputNeiron::CompError(double comp)
{
	m_error = comp - m_result;
	//std::cout << m_error << "---" << comp << "---" << m_result;
	CompPreError();
}
