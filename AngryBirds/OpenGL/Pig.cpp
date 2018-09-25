#include "Pig.h"

#include <iostream>

CPig::CPig()
{
	m_fDeathForce = 10.0f;
}

CPig::~CPig()
{

}


void CPig::Init(std::string _sFilepath, glm::vec3 _vecPosition, float _fRotation, glm::vec3 _vecScale, GLuint& _shader, Camera _camera, b2Body* _worldbody)
{
	m_sprite = std::make_unique<CSprite>(_sFilepath, _shader);
	Pawn::Init(_sFilepath, _vecPosition, _fRotation, _vecScale, _shader, _camera);
}

void CPig::Update(float _deltaTime, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _cameraPos)
{
	Pawn::Update(_deltaTime, _view, _projection, _cameraPos);
}

void CPig::Render()
{
	Pawn::Render();
}

void CPig::OnCollisionEnter(Pawn* _other)
{
	//if ((float)_other->GetBody()->GetLinearVelocity().Length() > m_fDeathForce)
	//{
		Death();
	//}
}

void CPig::Death()
{
	m_bIsDead = true;
}