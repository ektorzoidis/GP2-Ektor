#pragma once
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;

class Display
{
public:
	float getWidth();
	float getHeight();

	Display();
	~Display();
	void initDisplay();
	void swapBuffer();
	void clearDisplay(float r, float g, float b, float a);

private:
	SDL_GLContext glContext;
	SDL_Window* sdlWindow;
	float screenWidth;
	float screenHeight;

	void returnError(std::string errorString);
};