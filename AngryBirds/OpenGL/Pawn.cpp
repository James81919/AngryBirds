#pragma once
#include "Pawn.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"

#include <iostream>

Pawn::Pawn()
{
	m_sprite = std::make_unique<CSprite>();
}

Pawn::~Pawn()
{
}

void Pawn::Init(std::string _sFilepath, glm::vec3 _position, float _fRotation, glm::vec3 _scale, GLuint& _shader, Camera _camera)
{
	m_position = _position;
	m_fRotation = _fRotation;
	m_scale = _scale;

	m_sprite = std::make_unique<CSprite>(_sFilepath, _shader);
	m_sprite->Init();
}

void Pawn::AddPhysics(bool _bIsFixed, EColliderShape _colliderShape, b2World& _world)
{
	b2BodyDef bd;
	if (_bIsFixed)
	{
		bd.type = b2_kinematicBody;
		bd.fixedRotation = true;
	}
	else
	{
		bd.type = b2_dynamicBody;
		bd.fixedRotation = false;
		bd.linearDamping = 0.35f;
	}

	bd.position = b2Vec2(m_position.x, m_position.y);
	bd.angle = glm::radians(m_fRotation);
	m_physicsBody = _world.CreateBody(&bd);

	if (_colliderShape == COLLIDER_CIRCLE)
	{
		m_colliderShape = _colliderShape;
		b2CircleShape objectShape;
		objectShape.m_p.Set(0, 0);
		objectShape.m_radius = m_scale.x;
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &objectShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 1.0f;
		m_physicsBody->CreateFixture(&fixtureDef);
	}
	else if (_colliderShape == COLLIDER_SQUARE)
	{
		m_colliderShape = _colliderShape;
		b2PolygonShape objectShape;
		objectShape.SetAsBox(m_scale.x, m_scale.y);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &objectShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 1.0f;
		m_physicsBody->CreateFixture(&fixtureDef);
	}

	m_physicsBody->SetUserData(this);
}

void Pawn::Update(float _fDeltaTime, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _cameraPos)
{
	if (m_physicsBody != nullptr)
	{
		m_fRotation = glm::degrees(m_physicsBody->GetAngle());
		m_position = glm::vec3(m_physicsBody->GetPosition().x, m_physicsBody->GetPosition().y, 0);
	}

	m_sprite->Update
	(
		_projection,
		_view,
		(
			glm::translate(glm::mat4(), m_position) *
			glm::rotate(glm::mat4(), glm::radians(m_fRotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(), m_scale)
			),
		_cameraPos
	);
}

void Pawn::Render()
{
	m_sprite->Render();
}

void Pawn::applyForce(glm::vec3 _force)
{
	m_vecAcceleration += _force;
}

void Pawn::seek(glm::vec3 _target)
{
	applyForce(limit((glm::normalize(_target - m_position) * m_fMaxspeed) - m_vecVelocity, m_fMaxforce));
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

void Pawn::OnCollisionEnter(Pawn* _other)
{
	
}