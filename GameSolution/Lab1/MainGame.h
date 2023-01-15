#pragma once
#include <SDL\SDL.h>
#include "Display.h" 
#include "Camera.h"
#include "Skybox.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "SDLAudio.h"
#include "shader.h"
#include <glm/gtc/type_ptr.hpp>

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	// -Methods
	/// <summary>
	/// MainGame constructor.
	/// </summary>
	MainGame();
	/// <summary>
	///  MainGame destructor.
	/// </summary>
	~MainGame();

	/// <summary>
	/// Starts game.
	/// </summary>
	void run();

private:
	// -Fields
	Display _gameDisplay;
	GameState _gameState;
	Mesh mesh1, mesh2, mesh3;
	SkyBox skybox;
	Shader defaultShader, skyboxShader;
	Camera camera;
	SDLAudio gameAudio;

	float counter;
	unsigned int whistle;
	unsigned int backGroundMusic;

	// -Methods
	/// <summary>
	/// Initialises core components.
	/// </summary>
	void initSystems();
	/// <summary>
	/// Tracks and processes events.
	/// </summary>
	void processEvents();
	/// <summary>
	/// Runs while the game plays and contains functions that make the game run.
	/// </summary>
	void gameLoop();
	/// <summary>
	/// Draw game on screen.
	/// </summary>
	void drawGame();
	/// <summary>
	/// Outputs the distance between two objects.
	/// </summary>
	/// <returns>True when collision occurs otherwise false.</returns>
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
};