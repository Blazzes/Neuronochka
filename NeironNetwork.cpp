#include "NeironNetwork.h"
#include <iostream>
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

void NeironNetwork::NetUpdate(std::vector<double> input, std::vector<double> output, std::vector<double>* NetOut)
{
	NextUpdate(input);
	ErrorUpdate(output, NetOut);
	WeightUpdate();
}

void NeironNetwork::NextUpdate(std::vector<double> input)
{
	for (int i = 0; i < net.size(); i++)
	{
		std::cout << "laier" << i << std::endl;
		for (int j = 0; j < net.at(i)->size(); j++)
		{
			if (i == 0)
			{
				static_cast<InputNeiron*>(net.at(i)->at(j))->SetResult(input[j]);
				continue;
			}
			net.at(i)->at(j)->Calc_Result();
			std::cout.precision(5);
			std::cout << net.at(i)->at(j)->GetResult() << ":" << net.at(i)->at(j)->GetWeight() << "\t";
		}
		std::cout << "\n\n";
	}
}

void NeironNetwork::ErrorUpdate(std::vector<double> output, std::vector<double>* NetOut)
{
	for (int i = net.size() - 1; i > 0; i--)
	{
		for (int j = 0; j < net.at(i)->size(); j++)
		{
			if (i == net.size() - 1)
			{
				NetOut->push_back(net.at(i)->at(j)->GetResult());
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
