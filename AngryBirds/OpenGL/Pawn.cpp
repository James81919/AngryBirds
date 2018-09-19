#pragma once
#include "Pawn.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"

Pawn::Pawn()
{
	m_mesh = std::make_unique<Mesh>();
}

Pawn::~Pawn()
{
}

void Pawn::Init(std::string _sFilepath, glm::vec3 _vecPosition, float _fRotation, glm::vec3 _vecScale, GLuint& _shader, Camera _camera)
{
	m_vecPosition = _vecPosition;
	m_fRotation = _fRotation;
	m_vecScale = _vecScale;

	m_mesh->Init();
}

void Pawn::AddPhysics(bool _bIsFixed, EColliderShape _colliderShape, b2World& _world)
{
	b2BodyDef bd;
	if (_bIsFixed)
	{
		bd.type = b2_kinematicBody;
	}
	else
	{
		bd.type = b2_dynamicBody;
	}

	bd.position = b2Vec2(m_vecPosition.x, m_vecPosition.y);
	m_physicsBody = _world.CreateBody(&bd);

	if (_colliderShape == COLLIDER_CIRCLE)
	{
		m_colliderShape = _colliderShape;
		b2CircleShape objectShape;
		objectShape.m_p.Set(0, 0);
		objectShape.m_radius = m_vecScale.x;
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &objectShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 1000.0f;
		m_physicsBody->CreateFixture(&fixtureDef);
	}
	else if (_colliderShape == COLLIDER_SQUARE)
	{
		m_colliderShape = _colliderShape;
		b2PolygonShape objectShape;
		objectShape.SetAsBox(m_vecScale.x, m_vecScale.y);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &objectShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 1000.0f;
		m_physicsBody->CreateFixture(&fixtureDef);
	}

	m_physicsBody->SetFixedRotation(true);
}

void Pawn::Update(float _fDeltaTime, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _vecCameraPos)
{
	if (m_physicsBody != nullptr)
	{
		m_fRotation = m_physicsBody->GetAngle();
		m_vecPosition = glm::vec3(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y, 0);
	}

	m_mesh->Update
	(
		_projection,
		_view,
		(
			glm::translate(glm::mat4(), m_vecPosition) *
			glm::rotate(glm::mat4(), glm::radians(m_fRotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(), m_vecScale)
			),
		_vecCameraPos
	);
}

void Pawn::Render()
{
	m_mesh->Render();
}

void Pawn::applyForce(glm::vec3 _force)
{
	m_vecAcceleration += _force;
}

void Pawn::seek(glm::vec3 _target)
{
	applyForce(limit((glm::normalize(_target - m_vecPosition) * m_fMaxspeed) - m_vecVelocity, m_fMaxforce));
}

glm::vec3 Pawn::limit(glm::vec3 _vec, float _max)
{
	float magSq = glm::length(_vec) * glm::length(_vec);

	if (magSq > _max * _max)
	{
		if (_vec != glm::vec3())
		{
			_vec = glm::normalize(_vec);
		}
		_vec *= _max;
	}
	return _vec;
}

b2Body* Pawn::GetBody()
{
	return(m_physicsBody);
}