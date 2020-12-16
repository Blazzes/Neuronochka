#include <iostream>
#include <SDL.h>
#include "Neiron.h"
#include "ClassNeiron.h"
#include "InputNeiron.h"
#include "OutputNeiron.h"
#include <fstream>
#include <string>
#include <cstdio>

SDL_Window* win;
SDL_Renderer* ren;
SDL_Surface* src;

SDL_Event e;


std::vector<std::vector<uint8_t>> data;

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("Neiron", 100, 100, 0, 0, SDL_WINDOW_OPENGL);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
	src = SDL_GetWindowSurface(win);
	
	std::ifstream input("dataSet.csv");
	for (std::string line; std::getline(input, line);)
	{
		std::vector<uint8_t> tmp;
		
		for (int i = 0; i < line.size(); ++i)
		{
			tmp.push_back(line[i]-0x30);
		}
		data.push_back(tmp);
	}
}

void quit()
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void draw()
{

}

int main(int argv, char* argc[])
{
	init();
	std::vector<Neiron*> Input;
	std::vector<Neiron*> Sl1;
	std::vector<Neiron*> Sl2;
	std::vector<Neiron*> Out;
	int pau = 50;
	for (int i = 0; i < 9; i++)
	{
		Input.push_back(new InputNeiron(nullptr));
	}
	for (int i = 0; i < 10; i++)
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

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				return 0;
			}
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					system("pause");
				}
				if (e.key.keysym.sym == SDLK_UP)
				{
					pau -= 10;
					if (pau < 0) pau = 0;
				}
				if (e.key.keysym.sym == SDLK_DOWN)
				{
					pau += 10;
					if (pau > 1000) pau = 1000;
				}
			}
		}
		system("cls");
		std::cout << "\n-----------Input------------" << std::endl;
		int j = 0;
		int random = rand() % 16;
		for (Neiron* i : Input)
		{
			static_cast<InputNeiron*>(i)->SetResult(data[random][j++]);
			std::cout << i->GetResult() << "  ";
		}
		std::cout << "\n------Sl1------" << std::endl;
		for (Neiron* i : Sl1)
		{
			std::cout << i->GetError() << "::";
			i->Calc_Result();
			std::cout << i->GetResult() << "   ";
		}
		std::cout << "\n------Sl2------" << std::endl;
		for (Neiron* i : Sl2) 
		{
			std::cout << i->GetError() << "::";
			i->Calc_Result(); 
			std::cout << i->GetResult() << "  ";
		}
		std::cout << "\n------OUT------" << std::endl;
		for (Neiron* i : Out)
		{
			std::cout << i->GetError() << "::";
			i->Calc_Result();
			std::cout << i->GetResult() << "  ";
		}
		std::cout << "\n";
		for (auto i : Out)
		{
			int x = data[random][j++];
			i->CompError(x);
			std::cout << x << "  ";
			if (i->GetResult() > 0.5 && x == 1)
			{
				std::cout << "True1" << "  ";
			}
			else if(i->GetResult() > 0.5 && x == 0){
				std::cout << "False2" << "  ";
			}
			else if (i->GetResult() < 0.5 && x == 0)
			{
				std::cout << "True3";
			}
			else if(i->GetResult() > 0.5 && x == 1){
				std::cout << "False4" << "  ";
			}
		}
		for (auto i : Sl2)
		{
			i->CompPreError();
		}
		for (auto i : Sl1)
		{
			i->CompPreError();
		}

		for (auto i : Out)
		{
			i->CorectWeight();
		}
		for (auto i : Sl2)
		{
			i->CorectWeight();
		}
		for (auto i : Sl1)
		{
			i->CorectWeight();
		}
		

		draw();
		//system("pause");
		SDL_Delay(pau);
		std::cout << "\n\n" << pau << "\n";
	}
	quit();
	return 0;
}