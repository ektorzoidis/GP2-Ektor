#include "MainGame.h"
#include <string>

MainGame::MainGame()
{
	// Set game state
	_gameState = GameState::PLAY;
	// Create new display
	Display* _gameDisplay = new Display();
}

MainGame::~MainGame()
{
}


void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	// Create game display
	_gameDisplay.initDisplay(); 
	gameAudio.addAudioTrack("..\\res\\Audio\\background.wav");

	// Load obj models
	mesh1.loadModel("..\\res\\Objects\\UFO.obj");
	mesh2.loadModel("..\\res\\Objects\\Moon.obj");
	mesh3.loadModel("..\\res\\Objects\\Astronaut.obj");

	// Initialise skybox
	skybox.init();

	// Initialise camera
	camera.initCamera(glm::vec3(0, 0, -5), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.01f, 1000.0f);

	// Generates Shader objects
	defaultShader.init("default");
	skyboxShader.init("skybox");

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

	defaultShader.Activate();
	glUniform4f(glGetUniformLocation(defaultShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(defaultShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	skyboxShader.Activate();
	glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
	// Enables Cull Facing
	glEnable(GL_CULL_FACE);
	// Uses counter clock-wise standard
	glFrontFace(GL_CCW);

	// Set counter
	counter = 1.0f;
}

void MainGame::gameLoop()
{
	// While game is playing
	while (_gameState != GameState::EXIT)
	{
		// Play music
		gameAudio.playAudioTrack();
		// Process game events
		processEvents();
		// Draw on screen
		drawGame();
		// Detect collision between the 2 meshes
		collision(mesh1.getSpherePos(), mesh1.getSphereRadius(), mesh2.getSpherePos(), mesh2.getSphereRadius());
	}
}

void MainGame::processEvents()
{
	SDL_Event evnt;
	float speed = 0.5f;

	// Get and process events
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				break;
			// On key pressed
			case SDL_KEYDOWN:
				switch (evnt.key.keysym.sym)
				{
					// A pressed
					case SDLK_a:
						camera.MoveRight(speed);
						break;
					// D pressed
					case SDLK_d:
						camera.MoveRight(-speed);
						break;
					// W pressed
					case SDLK_w:
						camera.MoveForward(speed);
						break;
					// S pressed
					case SDLK_s:
						camera.MoveForward(-speed);
						break;
					// E pressed
					case SDLK_e:
						camera.RotateY(-speed / 2);
						break;
					// Q pressed
					case SDLK_q:
						camera.RotateY(speed / 2);
						break;
					// Z pressed
					case SDLK_z:
						camera.Pitch(-speed);
						break;
					// X pressed
					case SDLK_x:
						camera.Pitch(speed);
						break;
				}
				break;
			// On mouse wheel
			case SDL_MOUSEWHEEL:
				// Scroll up
				if (evnt.wheel.y > 0)
				{
					camera.MoveForward(speed);
					break;
				}
				// Scroll down
				else if (evnt.wheel.y < 0)
				{
					camera.MoveForward(-speed);
					break;
				}
				break;
			// On quit
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
}

bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	// Calculate distance
	float distance = ((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));
	
	// If objects collide
	if (distance*distance < (m1Rad + m2Rad))
	{
		// Output distance
		cout << distance << '\n';
		return true;
	}
	else
	{
		return false;
	}
}

void MainGame::drawGame()
{
	// Clear game display
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	// Keep back faces
	glCullFace(GL_BACK);

	// Create transform
	Transform transform;

	// Set transform for mesh 1
	transform.SetPos(glm::vec3(sinf(-counter) * 2.0f, -1.0f, 2.0f));
	transform.SetRot(glm::vec3(0.1f, counter, 0.0f));
	transform.SetScale(glm::vec3(0.6f, 0.6f, 0.6f));

	// Bind shader to mesh 1
	defaultShader.Activate();
	// Update shader
	defaultShader.Update(transform, camera);
	// Load textures for mesh 1
	Texture texture1("..\\res\\Textures\\ufo.png");
	// Bind texture to mesh 1
	texture1.Bind(0);
	// Render mesh 1
	mesh1.draw();
	// Update mesh 1 data
	mesh1.updateSphereData(*transform.GetPos(), 0.6f);

	// Set transform for mesh 2
	transform.SetPos(glm::vec3(3.0f + sinf(counter) * 0.1f, 0.6f, 5.0f));
	transform.SetRot(glm::vec3(0.5f, counter * 0.5f, 0.0f));
	transform.SetScale(glm::vec3(0.7f, 0.7f, 0.7f));

	// Bind shader to mesh 2
	defaultShader.Activate();
	// Update shader
	defaultShader.Update(transform, camera);
	// Load textures for mesh 2
	Texture texture2("..\\res\\Textures\\moon.png");
	// Bind texture to mesh 2
	texture2.Bind(0);
	// Render mesh 2
	mesh2.draw();
	// Update mesh 2 data
	mesh2.updateSphereData(*transform.GetPos(), 0.6f);

	// Set transform for mesh 3
	transform.SetPos(glm::vec3(-0.7f, 0.25f + sinf(counter) * 0.05f, -3.0f));
	transform.SetRot(glm::vec3(0.0f, 9.0f, counter * 0.5f));
	transform.SetScale(glm::vec3(15.0f, 15.0f, 15.0f));

	// Bind shader to mesh 3
	defaultShader.Activate();
	// Update shader
	defaultShader.Update(transform, camera);
	// Load textures for mesh 3
	Texture texture3("..\\res\\Textures\\astronaut.png");
	// Bind texture to mesh 3
	texture3.Bind(0);
	// Render mesh 3
	mesh3.draw();
	// Update mesh 3 data
	mesh3.updateSphereData(*transform.GetPos(), 0.6f);

	// Since the cubemap will always have a depth of 1.0, we need that equal sign so it doesn't get discarded
	glDepthFunc(GL_LEQUAL);

	// Keep front faces
	glCullFace(GL_FRONT);

	skyboxShader.Activate();
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	// We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
	// The last row and column affect the translation of the skybox (which we don't want to affect)
	view = glm::mat4(glm::mat3(glm::lookAt(camera.getPos(), camera.getPos() + camera.getForward(), camera.geUp())));
	projection = glm::perspective(glm::radians(45.0f), (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	// Render skybox
	skybox.draw();

	// Switch back to the normal depth function
	glDepthFunc(GL_LESS);

	// Advance counter
	counter = counter + 0.05f;

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	// Swap buffer
	_gameDisplay.swapBuffer();
} 