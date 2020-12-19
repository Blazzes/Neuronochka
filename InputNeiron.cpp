#include "InputNeiron.h"

InputNeiron::InputNeiron(std::vector<Neiron*>* inputs): Neiron(inputs)
{
}

void InputNeiron::SetResult(double input)
{
	m_result = input;
}
