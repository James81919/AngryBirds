#include "Bird.h"

CBird::CBird()
{

}

CBird::~CBird()
{

}

void CBird::SetIsDragable(bool _bValue)
{
	m_bIsDragable = _bValue;
}

bool CBird::IsDragable()
{
	return m_bIsDragable;
}

void CBird::Init(std::string _sFilepath, glm::vec3 _vecPosition, float _fRotation, glm::vec3 _vecScale, GLuint& _shader, Camera _camera)
{
	m_sprite = std::make_unique<CSprite>(_sFilepath, _shader);
	Pawn::Init(_sFilepath, _vecPosition, _fRotation, _vecScale, _shader, _camera);
}

void CBird::Update(float _deltaTime, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _cameraPos)
{
	Pawn::Update(_deltaTime, _view, _projection, _cameraPos);

	if (GetMouseButtonDown(0))
	{
		m_bIsDragable = false;
		m_physicsBody->SetType(b2_kinematicBody);
		
		b2Vec2 diff = b2Vec2(GetMousePosition().x - m_physicsBody->GetPosition().x, GetMousePosition().y - m_physicsBody->GetPosition().y);
		m_physicsBody->SetLinearVelocity(diff);
	}

	if (GetMouseButtonUp(0) && !m_bIsDragable)
	{
		m_bIsDragable = true;
		m_physicsBody->SetType(b2_dynamicBody);
	}
}

void CBird::Render()
{
	Pawn::Render();
}

void CBird::CreateMouseJoint(float _x, float _y)
{
	if (m_physicsBody != nullptr)
	{
		b2MouseJointDef md = b2MouseJointDef();
		
		md.bodyA = m_physicsBody->GetWorld()->GetBodyList();
		md.bodyB = m_physicsBody;

		glm::vec2 mp; // =
		md.target.Set(mp.x, mp.y);

		md.maxForce = 5000.0f * m_physicsBody->GetMass();
		md.frequencyHz = 5;
		md.dampingRatio = 0.9f;

		m_mouseJoint = static_cast<b2MouseJoint*>(m_physicsBody->GetWorld()->CreateJoint(&md));
	}
}