#pragma once
#include "Background.h"
#include "MeshCube.h"

Background::Background()
{
}

Background::~Background()
{
}

void Background::Init(std::string _sFilepath, glm::vec3 _vecPosition, float _fRotation, glm::vec3 _vecScale, GLuint& _shader)
{
	m_mesh = std::make_unique<MeshCube>(_sFilepath, _shader);
	Pawn::Init(_sFilepath, _vecPosition, _fRotation, _vecScale, _shader);
}

void Background::Update(float _fDeltaTime, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _vecCameraPos)
{
	Update(_fDeltaTime, _view, _projection, _vecCameraPos);
}

void Background::Render()
{
	Pawn::Render();
}