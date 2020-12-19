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
	win = SDL_CreateWindow("Neiron", 100, 100, 800, 800, SDL_WINDOW_OPENGL);
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
            inFile.read(color, img->bits/8);
            img->pixel.push_back({ w, h, color[2], color[1], color[0] });
            pos += img->bits/8;
        }
        printf("\nrow: %i pos %08X", h, pos);
        pos += padding;
    }
}

int main(int argv, char* argc[])
{
	init();
    IMG img;
	NeironNetwork net({276,300,300,400});
    loadIMG(&img, (char*)("home.bmp"));
    bool run = true;
    SDL_Rect r;
    int delay = 0;
    std::cout << "\n";

    int a1[20];
    int* a2 = new int[20];
    *a2 = 1;
    std::cout << sizeof(a1) / sizeof(*a1) << std::endl;
    std::cout << sizeof(a2) << " " << sizeof(*a2);
    
    int counter = 1;
    /*while (1)
    {
        std::vector<double> inputData;
        for (int i = 0; i < 296; i++)
        {
            inputData.push_back(img.pixel[i].R / 255.0);
        }
        std::vector<double> outData = { 0.8, 0.2 };
        std::vector<double> out;
        net.NetUpdate(inputData, outData, &out);
        std::cout << out[0] << "\t" << out[1] << std::endl;
        SDL_Delay(1);
        system("cls");
    }*/
    int Px = 0, Py = 0;
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
                    if (delay < 0) delay = 0;
                }
                if (e.key.keysym.sym == SDLK_DOWN)
                {
                    delay += 10;
                    if (delay > 1000) delay = 1000;
                }
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    system("pause");
                }
            }
        }

        //int rand_w = rand() % (img.W - 12) + 1, rand_h = rand() % (img.H - 12) + 1;

        //r.x = 1;
        //r.y = 1;
        //r.w = r.h = 500;
        //SDL_FillRect(src, &r, SDL_MapRGB(src->format, 255,0,0));

        if (++Px > img.W - 26) {
            Px = 0;
            if (++Py > img.H - 26)
            {
                Py = 0;
            }
        }
        int rand_w = Px, rand_h = Py;

        std::vector<double> inputR;
        std::vector<double> outputR;
        std::vector<double> NetOutR;

        std::vector<double> inputG;
        std::vector<double> outputG;
        std::vector<double> NetOutG;

        std::vector<double> inputB;
        std::vector<double> outputB;
        std::vector<double> NetOutB;
        
        for (int y = 0; y < 26; y++)
        {
            for (int x = 0; x < 26; x++)
            {
                int xx = x+rand_w, yy = y+rand_h;
                if (y > 2 && y < 23 && x > 2 && x < 23)
                {
                    outputR.push_back(img.pixel[yy * img.W + xx].R / 255.0);
                    outputG.push_back(img.pixel[yy * img.W + xx].G / 255.0);
                    outputB.push_back(img.pixel[yy * img.W + xx].B / 255.0);
                }
                else {
                    inputR.push_back(img.pixel[yy * img.W + xx].R / 255.0);
                    inputG.push_back(img.pixel[yy * img.W + xx].G / 255.0);
                    inputB.push_back(img.pixel[yy * img.W + xx].B / 255.0);
                }
                r.x = x * 10 + 1;
                r.y = y * 10 + 1;
                r.w = r.h = 10;
                SDL_FillRect(src, &r, SDL_MapRGB(src->format, img.pixel[yy * img.W + xx].R, img.pixel[yy * img.W + xx].G, img.pixel[yy * img.W + xx].B));
                r.x = x * 10 + 301;
                r.y = y * 10 + 1;
                SDL_FillRect(src, &r, SDL_MapRGB(src->format, img.pixel[yy * img.W + xx].R, img.pixel[yy * img.W + xx].G, img.pixel[yy * img.W + xx].B));
            }
        }
        net.NetUpdate(inputR, outputR, &NetOutR);
        net.NetUpdate(inputG, outputG, &NetOutG);
        net.NetUpdate(inputB, outputB, &NetOutB);


        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                r.x = x * 10 + 331;
                r.y = y * 10 + 31;
                r.w = r.h = 10;
                SDL_FillRect(src, &r, SDL_MapRGB(src->format, NetOutR[y * 20 + x], NetOutG[y * 20 + x], NetOutB[y * 20 + x]));
            }
        }
        SDL_UpdateWindowSurface(win);
        SDL_Delay(delay);
        counter++;
    }
	quit();
	return 0;
}