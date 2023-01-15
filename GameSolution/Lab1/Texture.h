#pragma once
#include <string>
#include <GL\glew.h>

class Texture
{
public:
	// -Methods
	/// <summary>
	/// Texture constructor.
	/// </summary>
	Texture(const std::string& fileName);

	/// <summary>
	/// Binds upto 32 textures.
	/// </summary>
	void Bind(unsigned int unit);
	/// <summary>
	/// Texture destructor.
	/// </summary>
	~Texture();

private:
	// -Fields
	GLuint textureHandler;
};

