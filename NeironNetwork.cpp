#include "NeironNetwork.h"
#include <iostream>
NeironNetwork::NeironNetwork(std::vector<uint16_t> countNe)
{
	net3 = new Neiron**[countNe.size()];
	for (int i = 0; i < countNe.size(); i++)
	{
		net3[i] = new Neiron * [countNe[i]];
		for (int j = 0; j < countNe[i]; j++)
		{
			if (i == 0) 
			{
				net3[i][j] = new InputNeiron(nullptr);
				continue;
			}
			if (i == countNe.size() - 1)
			{
				net3[i][j] = new OutputNeiron(net3[i - 1],countNe[i - 1]);
				continue;
			}
			net3[i][j] = new ClassNeiron(net3[i - 1], countNe[i - 1]);
		}
	}
	size_slize = countNe;
	/*for (int i = 0; i < countNe.size(); ++i)
	{
		std::vector<Neiron*> slice;
		for (int j = 0; j < countNe[i]; j++) {
			if (i == 0)
			{
				slice.push_back(new InputNeiron(nullptr));
				continue;
			}
			if (i == countNe.size() - 1)
			{
				slice.push_back(new OutputNeiron(&net[i - 1]));
				continue;
			}
			slice.push_back(new ClassNeiron(&net[i - 1]));
		}
		net.push_back(slice);
	}*/
	
}

void NeironNetwork::NetUpdate(std::vector<double> input, std::vector<double> output, std::vector<double>* NetOut)
{
	NextUpdate(input); // пр€мое прохождение сигнала
	ErrorUpdate(output, NetOut); // обратное прохождение и определение ошибки
	WeightUpdate(); // корректеровка весов с конца в начало
}

void NeironNetwork::NextUpdate(std::vector<double> input)
{
	for (int i = 0; i < size_slize.size(); i++) // идем по всем сло€м
	{
		//std::cout << "laier" << i << std::endl; // выводим номер сло€
		for (int j = 0; j < size_slize[i]; j++) // идем по всем нейронам сло€ 
		{
			if (i == 0) // если первый влой(входной)
			{
				static_cast<InputNeiron*>(net3[i][j])->SetResult(input[j]); // записываем на всох сети значение
				continue; // сл итераци€
			}
			net3[i][j]->Calc_Result(); // считаем выход нейрона 
			//std::cout.precision(30); // настройка вывода
			//std::cout << net3[i][j]->GetResult() << "\t"; // выводим значение нейрона и его вес
		}
		//std::cout << "\n\n";
	}
}

void NeironNetwork::ErrorUpdate(std::vector<double> output, std::vector<double>* NetOut)
{
	for (int i = size_slize.size() - 1; i >= 0; i--) // идем по всем сло€м с конца в начало, см условие
	{
		for (int j = 0; j < size_slize[i]; j++) // идем по всем нейронам сло€
		{
			if (i == size_slize.size() - 1) // если слой выходной
			{
				NetOut->push_back(net3[i][j]->GetResult()); //записываем выход нейросети
				net3[i][j]->CompError(output[j]); // передаем на выходной слой правильный ответ
				continue; // переходим к сл итерации
			}
			net3[i][j]->CompPreError(); // ожибка сло€
		}
	}
}

void NeironNetwork::WeightUpdate()
{
	for (int i = size_slize.size() - 1; i > 0; i--) // идем по сло€м с конца
	{
		for (int j = 0; j < size_slize[i]; j++) // идем по нейронам
		{
			net3[i][j]->CorectWeight(); // корректируем веса
		}
	}
}
