#include <iostream>
#include <SDL.h>
#include "Neiron.h"
#include "ClassNeiron.h"
#include "InputNeiron.h"
#include "OutputNeiron.h"

SDL_Window* win;
SDL_Renderer* ren;
SDL_Surface* src;

SDL_Event e;

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("Neiron", 100, 100, 640, 480, SDL_WINDOW_HIDDEN);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
	src = SDL_GetWindowSurface(win);
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

int main(int argc, char* argv)
{
	init();
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

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				return 0;
			}
		}

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

		draw();
		system("pause");
		system("cls");
	}
	quit();
	return 0;
}