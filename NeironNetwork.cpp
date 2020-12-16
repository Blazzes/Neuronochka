#include "NeironNetwork.h"

NeironNetwork::NeironNetwork(std::vector<uint16_t> countNe)
{
	for (int i = 0; i < countNe.size(); ++i)
	{
		std::vector<Neiron*>* slice = new std::vector<Neiron*>;
		for (int j = 0; j < countNe[i]; j++) {
			if (i == 0)
			{
				slice->push_back(new InputNeiron(nullptr));
				continue;
			}
			if (i == countNe.size() - 1)
			{
				slice->push_back(new OutputNeiron(net.at(i - 1)));
				continue;
			}
			slice->push_back(new ClassNeiron(net.at(i - 1)));
		}
		net.push_back(slice);
	}
	
}

void NeironNetwork::NetUpdate(std::vector<double> input, std::vector<double> output)
{
	NextUpdate(input);
	ErrorUpdate(output);
	WeightUpdate();
}

void NeironNetwork::NextUpdate(std::vector<double> input)
{
	for (int i = 0; i < net.size(); i++)
	{
		for (int j = 0; j < net.at(i)->size(); j++)
		{
			if (i == 0)
			{
				static_cast<InputNeiron*>(net.at(i)->at(j))->SetResult(input[j]);
				continue;
			}
			net.at(i)->at(j)->Calc_Result();
		}
	}
}

void NeironNetwork::ErrorUpdate(std::vector<double> output)
{
	for (int i = net.size() - 1; i > 0; i--)
	{
		for (int j = 0; j < net.at(i)->size(); j++)
		{
			if (i == net.size() - 1)
			{
				net.at(i)->at(j)->CompError(output[j]);
				continue;
			}
			net.at(i)->at(j)->CompPreError();
		}
	}
}

void NeironNetwork::WeightUpdate()
{
	for (int i = net.size() - 1; i > 0; i--)
	{
		for (int j = 0; j < net.at(i)->size(); j++)
		{
			net.at(i)->at(j)->CorectWeight();
		}
	}
}
