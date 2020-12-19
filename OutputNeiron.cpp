#include "OutputNeiron.h"
#include <iostream>
OutputNeiron::OutputNeiron(std::vector<Neiron*>* inputs): Neiron(inputs) {}

OutputNeiron::OutputNeiron(Neiron** inputs, size_t size) : Neiron(inputs, size) {}

void OutputNeiron::CompError(double comp)
{
	m_error = comp - m_result; // ошибка выходного слоя 
	//std::cout << m_error << "---" << comp << "---" << m_result;
	CompPreError();//хз
}

