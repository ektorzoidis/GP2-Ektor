#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "camera.h"

struct Transform
{
public:
	// -Properties
	/// <returns>Transform position.</returns>
	inline glm::vec3* GetPos() { return &pos; }
	/// <returns>Transform rotation.</returns>
	inline glm::vec3* GetRot() { return &rot; }
	/// <returns>Transform scale.</returns>
	inline glm::vec3* GetScale() { return &scale; }

	/// <summary>
	/// Set transform position.
	/// </summary>
	inline void SetPos(glm::vec3& pos) { this->pos = pos; }
	/// <summary>
	/// Set transform rotation.
	/// </summary>
	inline void SetRot(glm::vec3& rot) { this->rot = rot; }
	/// <summary>
	/// Set transform scale.
	/// </summary>
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }

	// -Methods
	/// <summary>
	/// Transform constructor.
	/// </summary>
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	/// <summary>
	/// Get model transform.
	/// </summary>
	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(pos);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

private:
	// -Fields
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};