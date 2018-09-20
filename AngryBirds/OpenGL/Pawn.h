#pragma once

#include <memory>
#include "Sprite.h"
#include "Utilities.h"
#include "Camera.h"

enum EColliderShape
{
	COLLIDER_SQUARE = 1,
	COLLIDER_CIRCLE = 2
};

class Pawn
{
public:
	Pawn();
	~Pawn();
	virtual void Init(std::string _filepath, glm::vec3 _position, float _rotation, glm::vec3 _scale, GLuint & _shader, Camera _camera);
	void AddPhysics(bool _isFixed, EColliderShape _colliderType, b2World& _world);
	virtual void Update(float _deltaTime, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _cameraPos);
	virtual void Render();

	void applyForce(glm::vec3 _force);
	glm::vec3 limit(glm::vec3 _vec, float _max);
	void seek(glm::vec3 _target);

	glm::vec3 GetLocation() { return m_position; }
	void SetLocation(glm::vec3 _location) { m_position = _location; }

	float GetRotation() { return m_fRotation; }
	void SetRotation(float _rotation) { m_fRotation = _rotation; }

	glm::vec3 GetScale() { return m_scale; }
	void SetScale(glm::vec3 _scale) { m_scale = _scale; }

	b2Body* GetBody();

protected:
	std::unique_ptr<CSprite> m_sprite;

	glm::vec3 m_scale, m_position;
	float m_fRotation;

	glm::vec3 m_vecVelocity;
	glm::vec3 m_vecAcceleration;

	float m_fR;
	float m_fMaxforce;
	float m_fMaxspeed;

	b2Body* m_physicsBody;

	EColliderShape m_colliderShape;
};
