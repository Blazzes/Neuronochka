#include "InputNeiron.h"

InputNeiron::InputNeiron(std::vector<Neiron*>* inputs): Neiron(nullptr)
{
}

void InputNeiron::SetResult(double input)
{
	m_result = input;
}
