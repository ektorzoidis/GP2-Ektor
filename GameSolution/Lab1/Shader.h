#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	// -Methods
	/// <summary>
	/// Shader constructor.
	/// </summary>
	Shader();

	/// <summary>
	/// Initialises shader.
	/// </summary>
	void init(std::string fileName);

	/// <summary>
	/// Loads a shader.
	/// </summary>
	std::string LoadShader(const std::string& fileName);
	/// <summary>
	/// Activates the shader program.
	/// </summary>
	void Activate();
	/// <summary>
	/// Updates the shader.
	/// </summary>
	void Update(const Transform& transform, const Camera& camera);
	/// <summary>
	/// Deletes the shader program
	/// </summary>
	void Delete();

	// -Fields
	// Reference ID of the Shader Program
	GLuint ID;
private:
	// -Methods
	/// <summary>
	/// Checks if the different Shaders have compiled properly.
	/// </summary>
	void compileErrors(unsigned int shader, const char* type);

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	// -Fields
	// No of uniform variables
	GLuint uniforms[NUM_UNIFORMS];
};

#endif