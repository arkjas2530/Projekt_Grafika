#include "BaseSDL.h"
#include<iostream>
#include "CompAlg.h"
#include<SDL.h>

using namespace std;

SDL_Window* window;
SDL_Surface* screen; //to co bêdzie widoczne
SDL_Surface* img;//zdjecie 

BaseSDL::BaseSDL()
{
	window = nullptr;
	screen = nullptr;
	img = nullptr;
	
	if (!Init())
	{
		cout << "AGAIN WRONG ERROR" << SDL_GetError();
		system("pause");
		exit(1);
	}

	bool exit = false;
	/*
	Cokolwiek klikne bêdzie wykryte przez program
	*/
	SDL_Event e;
	/*
	Tworzenie koloru
	*/
	Uint32 bgColor = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
	while (!exit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			/*
			Sprawdzamy czy bylo klikniete x albo esc
			*/
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			if (!loadImage())
			{
				cout << "Nie mozna otworzyc obrazu";
				system("pause");
			}
			else
			{
				/*
				Wype³nianie kolorem
				*/
				SDL_FillRect(screen, NULL, bgColor);
				/*
				Wype³nianie obrazem
				*/
				SDL_BlitSurface(img, NULL, screen, NULL);
			}
		}


		/*
		Aktualizowanie okna
		*/
		SDL_UpdateWindowSurface(window);
	}
	Close();
}

BaseSDL::~BaseSDL()
{
}

bool BaseSDL::Init()
{
	/*
	Inicjuje Video jeœli mniejsze od 0 to nie uda³o sie
	*/
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not be init, ERROR: " << SDL_GetError() << endl;
		return false;
	}
	/*
	Tworzenie okna Parametry:
	1. Tytul, 2. Pozycja gora dol, 3. Pozycja lewo prawo, 4. Szerokosc okna,
	5. Wysokoœæ okna,6. Typ okna Shown z ramka, borderless bez ramki
	SDL_WINDOWPOS_UNDEFINED - wyœrodkowuje
	*/
	window = SDL_CreateWindow("BITMAPY PROBA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	/*
	B³¹d zapewne sterownika lub urz¹dzenia
	*/
	if (window == NULL)
	{
		cout << "WINDOW COULDNT BE CREATE ERORR: " << SDL_GetError();
	}
	/*
	Przypisuje przestrzen do okna, w tym wypadku t³o
	*/
	screen = SDL_GetWindowSurface(window);
	return true;
}
bool BaseSDL::loadImage()
{
	img = SDL_LoadBMP("img_fjords.bmp");
	if (!img)
	{
		cout << "BLAD: " << SDL_GetError();
		return false;
	}
	return true;
}
void BaseSDL::Close()
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_FreeSurface(screen);
	SDL_FreeSurface(img);
	SDL_Quit();
}