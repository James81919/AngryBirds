#pragma once
#include <memory>
#include <vector>
#include "Dependencies/glew/glew.h"
#include "ShaderLoader.h"
#include "Camera.h"
#include "Pawn.h"
#include "TextLabel.h"
#include "Bird.h"
#include "Pig.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Init();
	void Update();
	void Render();

private:
	ShaderLoader m_shaderloader;
	GLuint m_shader;

	std::unique_ptr<Camera> m_camera;

	std::unique_ptr<Pawn> m_background, m_ground, m_wall, m_wall2, m_box1, m_box2, m_box3, m_ball3, m_pig1, m_pig2, m_pig3;
	std::unique_ptr<CBird> m_bird;

	std::unique_ptr<std::vector<std::unique_ptr<Pawn>>> m_vecGameobjects;

	//std::unique_ptr<TextLabel> m_label;

	float m_fGametimer = 60;
	bool m_bIsFirstRun = false;
	float m_fDeltaTime = 0;
	float m_fPreviousTime = 0;

	b2World m_world = b2World(b2Vec2(0,-9.81f));
	b2Body* m_worldbody;
	b2PrismaticJoint* joint;
	b2PrismaticJointDef jointDef;
	float motorspeed = 2.0f;
	bool forward = true;
	bool moving = true;
	/*b2DistanceJointDef jointDef;*/

	b2Vec2 worldAxis = b2Vec2(1.0f, 0.0f);
	float32 m_timeStep = 1.0f / 60.0f;
	int32 m_velocityInterations = 6;
	int32 m_positionIterations = 2;
	
	b2GLDraw m_debugDraw;
};
