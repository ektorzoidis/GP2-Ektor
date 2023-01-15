#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	// Width, height, and no of components of image
	int width, height, numComponents;
	// Load the image and store the data
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	// Print error if texture failed to load
	if (imageData == NULL)
		std::cerr << "texture load failed" << fileName << std::endl;

	// Number of and address of textures
	glGenTextures(1, &textureHandler);
	// Bind texture - define type 
	glBindTexture(GL_TEXTURE_2D, textureHandler);

	// Wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// Wrap texture outside height
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Linear filtering for magnifcation (texture is larger)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	// Number of and address of textures
	glDeleteTextures(1, &textureHandler);
}

void Texture::Bind(unsigned int unit)
{
	// Check we are working with one of the 32 textures
	assert(unit >= 0 && unit <= 31);

	// Set acitve texture unit
	glActiveTexture(GL_TEXTURE0 + unit);
	// Type of and texture to bind to unit
	glBindTexture(GL_TEXTURE_2D, textureHandler);
}
