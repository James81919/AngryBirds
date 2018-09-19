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

void Background::Render()
{
	Pawn::Render();
}