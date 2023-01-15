#pragma once
#include <GL/glew.h>
#include <string>
#include <iostream>
#include "stb_image.h"
using namespace std;

class SkyBox
{
public:
    // -Methods
    /// <summary>
    /// SkyBox constructor.
    /// </summary>
    SkyBox();
    /// <summary>
    /// SkyBox destructor.
    /// </summary>
    ~SkyBox();
    /// <summary>
    /// Initialises the skybox.
    /// </summary>
    void init();
    /// <summary>
    /// Initialises the cubemap.
    /// </summary>
    void initCubemap();
    /// <summary>
    /// Loads the cubemap.
    /// </summary>
    void loadCubemap();
    /// <summary>
    /// Draws the skybox.
    /// </summary>
    void draw();

private:
    // -Fields
    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    unsigned int cubemapTexture;
};