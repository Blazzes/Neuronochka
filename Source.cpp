#include <iostream>
#include <SDL.h>
#include "NeironNetwork.h"
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <iomanip>
SDL_Window* win;
SDL_Renderer* ren;
SDL_Surface* src;
SDL_Surface* image;

SDL_Event e;


std::vector<std::vector<uint8_t>> dataIn;

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("Neiron", 100, 100, 640, 480, SDL_WINDOW_OPENGL);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
    src = SDL_GetWindowSurface(win);
	//src = SDL_CreateRGBSurface(0,)
	image = SDL_LoadBMP("1234.bmp");
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

typedef struct {
    size_t x, y;
    char R, G, B;
}Pixel;

typedef struct {
    uint16_t W, H;
    std::vector<Pixel> pixel;
    uint8_t bits;
} IMG;

struct header {
    char header[2]; //0x00-0x01
    char fSize[4]; //0x02-0x05
    char skip_1[4]; //0x06-0x09
    char pixelStartPos[4]; //0x0A-0x0D
    char rInfoSize[4]; //0x0E-0x11
    char width[4]; //0x12-0x15
    char height[4]; //0x16-0x19
    char skip_2[2]; //0x1A-0x1B
    char bitCount[2]; //0x1C-0x1D
    char compresion[4];//0x1E-0x21
    char pixelSizes[4];//0x22-0x25
};

void loadIMG(IMG* img, char* path) {
    std::ifstream inFile;
    inFile.open(path, std::ios::in | std::ios::binary);

    if (!inFile.is_open()) return;
    header head;
    inFile.seekg(0x00);
    inFile.read((char*)&head, sizeof(header));
    if (*((uint16_t*)(head.header)) != 19778) return;
    if (*((uint32_t*)head.compresion)) return;

    img->W = *((uint32_t*)head.width);
    img->H = *((uint32_t*)head.height);
    img->bits = *((uint32_t*)head.bitCount);

    //считывание набора цветов
    size_t pos = *((uint32_t*)head.pixelStartPos);
    uint8_t padding = (img->W * (img->bits / 8)) % 4;
    for (size_t h = 0; h < img->H; h++) {
        for (size_t w = 0; w < img->W; w++) {
            char color[4];
            inFile.seekg(pos);
            inFile.read(color, 4);
            img->pixel.push_back({ w, h, color[2], color[1], color[0] });
            pos += 4;
        }
        printf("\nrow: %i pos %08X", h, pos);
        pos += padding;
    }
}

int main(int argv, char* argc[])
{
	init();
    IMG img;
	NeironNetwork net({96,100,100,50,25});
    loadIMG(&img, (char*)("12345.bmp"));
    bool run = true;
    SDL_Rect r;
    int delay = 1;
    std::cout << "\n";
    while (run)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                run = false;
            }
            if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_UP)
                {
                    delay -= 10;
                    if (delay < 1) delay = 1;
                }
                if (e.key.keysym.sym == SDLK_DOWN)
                {
                    delay += 10;
                    if (delay > 1000) delay = 100;
                }
            }
        }

        int rand_w = rand() % (img.W - 12) + 1, rand_h = rand() % (img.H - 12) + 1;

        r.x = 1;
        r.y = 1;
        r.w = r.h = 300;
        SDL_FillRect(src, &r, SDL_MapRGB(src->format, 255,0,0));

        //int rand_w = 10, rand_h = 10;

        std::vector<double> input;
        std::vector<double> output;
        std::vector<double> NetOut;
        int counter = 0;
        for (int y = rand_h; y < 11+rand_h; y++)
        {
            for (int x = rand_w; x < 11 + rand_w; x++)
            {
                if (x > 2 + rand_w && x < 8 + rand_w && y > 2 + rand_h && y < 8 + rand_h)
                {
                    output.push_back(img.pixel[y * img.W + x].R / 255.0);
                }
                else {
                    input.push_back(img.pixel[y * img.W + x].R / 255.0);
                    counter++;
                }
                r.x = (x % rand_w) * 10 + 100;
                r.y = (y % rand_h) * 10 + 100;
                r.w = r.h = 10;
                SDL_FillRect(src, &r, SDL_MapRGB(src->format, img.pixel[y * img.W + x].R,
                    img.pixel[y * img.W + x].G, img.pixel[y * img.W + x].B));
            }
        }
        
        net.NetUpdate(input, output, &NetOut);

        for (int y = 0; y < 5; y++)
        {
            for (int x = 0; x < 5; x++)
            {
                r.x = x * 10 + 253;
                r.y = y * 10 + 103;
                r.w = r.h = 10;
                SDL_FillRect(src, &r, SDL_MapRGB(src->format, NetOut[y * 5 + x] * 255, NetOut[y * 5 + x] * 255, NetOut[y * 5 + x] * 255));
            }
        }

        /*for (int y = 0; y < 12; y++)
        {
            for (int x = 0; x < 12; x++)
            {
                if (x > 3 && x < 9 && y > 3 && y < 9)
                {
                    continue;
                }
                else {
                    r.x = x * 10 + 253;
                    r.y = y * 10 + 103;
                    r.w = r.h = 10;
                    SDL_FillRect(src, &r, SDL_MapRGB(src->format, input[y * 11 + x] * 255, input[y * 11 + x] * 255, input[y * 11 + x] * 255));
                }
            }
        }*/
        std::cout << counter << "\n\n";
        SDL_UpdateWindowSurface(win);
        SDL_Delay(delay);
    }
	quit();
	return 0;
}