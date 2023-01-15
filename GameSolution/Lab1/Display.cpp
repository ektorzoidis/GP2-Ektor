#include "Display.h"

Display::Display()
{
	// Initialise to generate null access violation for debugging.
	sdlWindow = nullptr;
	// Set screen resolution
	screenWidth = 1024.0f;
	screenHeight = 768.0f; 
}

Display::~Display()
{
	// Delete context
	SDL_GL_DeleteContext(glContext);
	// Delete window
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

float Display::getWidth() { return screenWidth; }
float Display::getHeight() { return screenHeight; }

void Display::returnError(std::string errorString)
{
	// Output error text
	std::cout << errorString << std::endl;
	// Output quit text and wait for user input
	std::cout << "press any key to quit...";
	int in;
	std::cin >> in;
	// Quit
	SDL_Quit();
}

void Display::swapBuffer()
{
	// Swap buffers
	SDL_GL_SwapWindow(sdlWindow);
}

void Display::clearDisplay(float r, float g, float b, float a)
{
	// Clear colour and depth buffer - set colour to colour defined in glClearColor
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::initDisplay()
{
	// Initalise everything
	SDL_Init(SDL_INIT_EVERYTHING);
	// Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	// Set up z-buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	// Set up double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create window
	sdlWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screenWidth, (int)screenHeight, SDL_WINDOW_OPENGL);
	// Return error if failed to create
	if (sdlWindow == nullptr)
		returnError("window failed to create");

	// Create context
	glContext = SDL_GL_CreateContext(sdlWindow);
	// Return error if failed to create
	if (glContext == nullptr)
		returnError("SDL_GL context failed to create");

	// Initialise glew
	GLenum error = glewInit();
	// Return error if failed to initialise
	if (error != GLEW_OK)
		returnError("GLEW failed to initialise");

	// Enable z-buffering 
	glEnable(GL_DEPTH_TEST);
	// Dont draw faces that are not pointing at the camera
	glEnable(GL_CULL_FACE);

	// Reset color
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}