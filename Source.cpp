#include <iostream>
#include <SDL.h>
#include "NeironNetwork.h"
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>

SDL_Window* win;
SDL_Renderer* ren;
SDL_Surface* src;

SDL_Event e;


std::vector<std::vector<uint8_t>> dataIn;
//std::vector;

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
		
		for (int i = 0; i < line.size()-2; ++i)
		{
			tmp.push_back(line[i]-0x30);
		}
		dataIn.push_back(tmp);
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
	NeironNetwork net({9,5,3,2});
	
	quit();
	return 0;
}