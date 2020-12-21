#include <iostream>
#include <SDL.h>
#include "NeironNetwork.h"
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <thread>
#include <ctime>
SDL_Window* win;
SDL_Renderer* ren;
SDL_Surface* src;
SDL_Surface* image;

SDL_Event e;

std::vector<double> inputR;
std::vector<double> outputR;
std::vector<double> NetOutR;

std::vector<double> inputG;
std::vector<double> outputG;
std::vector<double> NetOutG;

std::vector<double> inputB;
std::vector<double> outputB;
std::vector<double> NetOutB;

std::vector<std::vector<uint8_t>> dataIn;

std::vector<uint16_t> network = { 80,500,500,64 };

NeironNetwork net(network);
NeironNetwork net2(network);
NeironNetwork net3(network);

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

typedef struct {
    size_t x, y;
    uint8_t R, G, B;
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
            img->pixel.push_back({ w, h, (uint8_t)color[2], (uint8_t)color[1], (uint8_t)color[0] });
            pos += img->bits/8;
        }
        printf("\nrow: %i pos %08X", h, pos);
        pos += padding;
    }
}

void tr1(std::vector<double> input, std::vector<double> output, std::vector<double> &NetOut)
{
    //net.NetUpdate(input, output, &NetOut);
}

void tr2(std::vector<double> input, std::vector<double> output, std::vector<double>& NetOut)
{
    //net2.NetUpdate(input, output, &NetOut);
}

void tr3(std::vector<double> input, std::vector<double> output, std::vector<double>& NetOut)
{
    //net3.NetUpdate(input, output, &NetOut);
}


int main(int argv, char* argc[])
{
	init();
    IMG img;
	
    loadIMG(&img, (char*)("home.bmp"));
    bool run = true;
    SDL_Rect r;
    r.w = r.h = 10;
    int delay = 0;
    std::cout << "\n";
    bool learn = true;
    

    
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
    int Px = 20, Py = 200;
   while (run)
    {
        //uint64_t time = clock();
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
                if (e.key.keysym.sym == SDLK_w)
                {
                    Py--;
                }
                if (e.key.keysym.sym == SDLK_s)
                {
                    Py++;
                }
                if (e.key.keysym.sym == SDLK_a)
                {
                    Px--;
                }
                if (e.key.keysym.sym == SDLK_d)
                {
                    Px++;
                }
                if (e.key.keysym.sym == SDLK_e)
                {
                    learn = !learn;
                }
            }
        }
        
        //int rand_w = rand() % (img.W - 12) + 1, rand_h = rand() % (img.H - 12) + 1;

        //r.x = 1;
        //r.y = 1;
        //r.w = r.h = 500;
        //SDL_FillRect(src, &r, SDL_MapRGB(src->format, 255,0,0));

        if (Px > img.W - 26) {
            Px = 0;
            if (Py > img.H - 26)
            {
                Py = 0;
            }
        }
        int rand_w = Px, rand_h = Py;

        inputR.clear();
        outputR.clear();
        NetOutR.clear();

        inputG.clear();
        outputG.clear();
        NetOutG.clear();

        inputB.clear();
        outputB.clear();
        NetOutB.clear();
        
        for (int y = 0; y < 12; y++)
        {
            for (int x = 0; x < 12; x++)
            {
                int xx = x+rand_w, yy = y+rand_h;
                if (y > 1 && y < 10 && x > 1 && x < 10)
                {
                    outputR.push_back(img.pixel[yy * img.W + xx].R / 255.0);
                    outputG.push_back(img.pixel[yy * img.W + xx].G / 255.0);
                    outputB.push_back(img.pixel[yy * img.W + xx].B / 255.0);
                }
                else {
                    inputR.push_back(img.pixel[yy * img.W + xx].R / 255.0);
                    inputG.push_back(img.pixel[yy * img.W + xx].G / 255.0);
                    inputB.push_back(img.pixel[yy * img.W + xx].B / 255.0);
                    //inputR.push_back(0.001);
                    //inputG.push_back(0.002);
                    //inputB.push_back(0.003);
                }
                if (1) {
                    r.x = x * 10 + 1;
                    r.y = y * 10 + 1;
                    SDL_FillRect(src, &r, SDL_MapRGB(src->format, img.pixel[yy * img.W + xx].R, img.pixel[yy * img.W + xx].G, img.pixel[yy * img.W + xx].B));
                    r.x = x * 10 + 301;
                    r.y = y * 10 + 1;
                    SDL_FillRect(src, &r, SDL_MapRGB(src->format, img.pixel[yy * img.W + xx].R, img.pixel[yy * img.W + xx].G, img.pixel[yy * img.W + xx].B));
                }
            }
        }
        //std::cout << clock() - time << std::endl;
        /*std::thread tr11(tr1, inputR, outputR, std::ref(NetOutR));
        std::thread tr12(tr2, inputG, outputG, std::ref(NetOutG));
        std::thread tr13(tr3, inputB, outputB, std::ref(NetOutB));

        tr11.join();
        tr12.join();
        tr13.join();*/
        net.NetUpdate(inputR, outputR, & NetOutR, learn);
        net.NetUpdate(inputB, outputG, & NetOutG, learn);
        net.NetUpdate(inputG, outputB, & NetOutB, learn);
        //std::cout << clock() - time << std::endl;
        
        int cor = 8;
        if (1) {
            for (int y = 0; y < cor; y++)
            {
                for (int x = 0; x < cor; x++)
                {
                    r.x = x * 10 + 321;
                    r.y = y * 10 + 21;
                    //SDL_FillRect(src, &r, SDL_MapRGB(src->format, ((NetOutR[y * cor + x] * 255) > 255 ? 255: (NetOutR[y * cor + x] * 255)),
                    //    ((NetOutG[y * cor + x] * 255) > 255 ? 255 : (NetOutG[y * cor + x] * 255)),
                    //    ((NetOutB[y * cor + x] * 255) > 255 ? 255 : (NetOutB[y * cor + x] * 255))));
                    SDL_FillRect(src, &r, SDL_MapRGB(src->format, NetOutR[y * cor + x] * 255, NetOutG[y * cor + x] * 255, NetOutB[y * cor + x] * 255));
                }
            }
        }
        r.x = 1;
        r.y = 300;
        SDL_FillRect(src, &r, SDL_MapRGB(src->format, counter % 2 == 0 ? 255:0 , 0, 0));
        
        if (counter % 50 == 0)
        {
            Px = rand() % (img.W - 20);
            Py = rand() % (img.H - 20);
        }

        //std::cout << clock() - time << std::endl;
        SDL_UpdateWindowSurface(win);
        SDL_Delay(delay);
        //system("cls");
        counter++;
        //std::cout << clock() - time << std::endl;
    }
	quit();
	return 0;
}

