#include "NeironNetwork.h"
#include <iostream>
NeironNetwork::NeironNetwork(std::vector<uint16_t> countNe)
{
	net3 = new Neiron**[countNe.size()];
	for (int i = 0; i < countNe.size(); i++)
	{
		net3[i] = new Neiron * [countNe[i]+1];
		for (int j = 0; j < countNe[i]+1; j++)
		{
			net3[i][j] = nullptr;
		}
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
		net3[i][countNe[i]] = new ShiftNeiron(nullptr);
		++countNe[i];
		//for (int j = 0; j < countNe[i]; j++) std::cout << net3[i][j] <<std::endl;

	}
	//for (auto i : countNe)
	//{
	//	std::cout << i << std::endl;
	//}
	size_slize = countNe;
	//for (int j = 0; j < size_slize[3]; j++) std::cout << net3[3][j] << std::endl;
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

void NeironNetwork::NetUpdate(std::vector<double> input, std::vector<double> output, std::vector<double>* NetOut, bool learn = true)
{
	NextUpdate(input, NetOut); // прямое прохождение сигнала
	if (learn) {
		ErrorUpdate(output); // обратное прохождение и определение ошибки
		WeightUpdate(); // корректеровка весов с конца в начало
	}
}

void NeironNetwork::NextUpdate(std::vector<double> input, std::vector<double>* NetOut)
{
	for (int i = 0; i < size_slize.size(); i++) // идем по всем слоям
	{
		//std::cout << "laier" << i << std::endl; // выводим номер слоя
		for (int j = 0; j < size_slize[i]-1; j++) // идем по всем нейронам слоя 
		{
			if (i == 0) // если первый влой(входной)
			{
				static_cast<InputNeiron*>(net3[i][j])->SetResult(input[j]); // записываем на всох сети значение
				continue; // сл итерация
			}
			//std::cout << j << "\n";
			//if (i == 3 && j == 106) 
			//	std::cout << "x";
			net3[i][j]->Calc_Result(); // считаем выход нейрона 
			//std::cout.precision(5); // настройка вывода
			//std::cout << net3[i][j]->GetResult() << "\t"; // выводим значение нейрона и его вес
			if (i == size_slize.size()-1)
			{
				NetOut->push_back(net3[i][j]->GetResult());
			}
		}
		//std::cout << "\n\n";
	}
}

void NeironNetwork::ErrorUpdate(std::vector<double> output)
{
	for (int i = size_slize.size() - 1; i >= 0; i--) // идем по всем слоям с конца в начало, см условие
	{
		for (int j = 0; j < size_slize[i]; j++) // идем по всем нейронам слоя
		{
			//if (size_slize[i]-1 == j)
			//	std::cout << "x";
			if (i == size_slize.size() - 1) // если слой выходной
			{
				 //записываем выход нейросети
				if(size_slize[i] - 1 != j)
					net3[i][j]->CompError(output[j]); // передаем на выходной слой правильный ответ
				continue; // переходим к сл итерации
			}
			net3[i][j]->CompPreError(); // ожибка нейрона
		}
	}
}

void NeironNetwork::WeightUpdate()
{
	for (int i = size_slize.size() - 1; i > 0; i--) // идем по слоям с конца
	{
		for (int j = 0; j < size_slize[i]; j++) // идем по нейронам
		{
			net3[i][j]->CorectWeight(); // корректируем веса
		}
	}
}
