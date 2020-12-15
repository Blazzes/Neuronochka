#include <iostream>
#include "Neiron.h"
#include "ClassNeiron.h"
#include "InputNeiron.h"
#include "OutputNeiron.h"
int main()
{
	std::vector<Neiron*> Input;
	std::vector<Neiron*> Sl1;
	std::vector<Neiron*> Sl2;
	std::vector<Neiron*> Out;

	for (int i = 0; i < 9; i++)
	{
		Input.push_back(new InputNeiron(nullptr));
	}
	for (int i = 0; i < 14; i++)
	{
		Sl1.push_back(new ClassNeiron(&Input));
	}
	for (int i = 0; i < 5; i++)
	{
		Sl2.push_back(new ClassNeiron(&Sl1));
	}
	for (int i = 0; i < 2; i++)
	{
		Out.push_back(new OutputNeiron(&Sl2));
	}

	while (1)
	{
		std::cout << "\n-----------Input------------" << std::endl;
		for (Neiron* i : Input)
		{
			static_cast<InputNeiron*>(i)->SetResult((rand() % 1000) / 1000.0);
			std::cout << i->GetResult() << "  ";
		}
		std::cout << "\n------Sl1------" << std::endl;
		for (Neiron* i : Sl1)
		{
			i->Calc_Result();
			std::cout << i->GetResult() << "  ";
		}
		std::cout << "\n------Sl2------" << std::endl;
		for (Neiron* i : Sl2) 
		{
			i->Calc_Result(); 
			std::cout << i->GetResult() << "  ";
		}
		std::cout << "\n------OUT------" << std::endl;
		for (Neiron* i : Out)
		{
			i->Calc_Result();
			std::cout << i->GetResult() << "  ";
		}
		system("pause");
		system("cls");
	}

	return 0;
}