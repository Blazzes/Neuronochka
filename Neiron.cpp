#include "Neiron.h"
#include "Connection.h"
Neiron::Neiron(std::vector<Neiron*>* inputs)
{
	if (!inputs) return;
	for (int i = 0; i < inputs->size(); i++)
	{
		//m_inConnections.push_back(new Connection(inputs->at(i), 0.5));
	}
}

Neiron::Neiron(Neiron** inputs, size_t size)
{
	if (!inputs) return;
	m_inCon = new Connection * [size];
	size_con = size;
	for (int i = 0; i < size; i++)
	{
		m_inCon[i] = new Connection(inputs[i], (rand() % 1000) / 1000.0);
	}
}

void Neiron::Calc_Result() // ������� ����� ������� 
{
	if (!m_inCon) return;
	//std::cout << "\n\n\t\t" << m_error << "\n" << std::endl;
	double sum_r = 0; // ����� ������
	m_error = 0; // ������ �� ����
	for (int i = 0; i < size_con; i++) { // ���� �� ���� ������
		sum_r += m_inCon[i]->Calc_Sum_Out(); // ��������� ��� ������
	}
	m_tmp = sum_r;
	m_result = funcActivate(sum_r); // �������� � ���� ���������
}

double Neiron::GetResult() const // ��������� ��������� �������
{
	return m_result; 
}

void Neiron::CompError(double pre_error)
{
	m_error += pre_error;//��������� ��� ��������� ������
}

void Neiron::CompPreError()
{
	if (!m_inCon) return;
	for (int i = 0; i < size_con; i++)
	{
		m_inCon[i]->GetSourse()->CompError(m_inCon[i]->GetWeight() * m_error); // ����������� ���� ������, �������� ��� ���� ������ ��������� �� ��� ����� ����
	}
}

void Neiron::CorectWeight()
{
	if (!m_inCon) return;
	for (int i = 0; i < size_con; i++) // ����� �� ���� ������
	{
		m_inCon[i]->SetWeight(m_inCon[i]->GetWeight()+m_k*m_error* m_inCon[i]->GetSourse()->GetResult()*(1 - pow(m_result,2)));
		/*
			������������� ��� ����� = ����� + ���� ���� * �� ������� ����� * ������� ���� ���� * ����������� ������� ���������
		*/
		//if (i->GetWeight() > 1) std::cout << i->GetWeight();
	}
}

double Neiron::GetError() const
{
	return m_error;
}

double Neiron::funcActivate(double input)
{
	return (exp(input) - exp(-input)) / (exp(input) + exp(-input));
	//return 1.0 / (1.0 + exp(-input));
	/*if (input > 1)
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
	}*/
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
