#include "Pig.h"

CPig::CPig()
{
	
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

void CPig::OnTriggerEnter(Pawn _other)
{
	//if ()
}