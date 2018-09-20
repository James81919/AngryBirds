#pragma once
#include "Pawn.h"

#include "Dependencies/glm/vec3.hpp"
#include <string>
#include "Dependencies/glew/glew.h"

class Camera;

class Background : public Pawn
{
public:
	Background();
	~Background();
	virtual void Init(std::string _sFilepath, glm::vec3 _vecPosition, float _fRotation, glm::vec3 _vecScale, GLuint& _shader, Camera _camera);
	virtual void Update(float _deltaTime, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _cameraPos);
	virtual void Render();
};
