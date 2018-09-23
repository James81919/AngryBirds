#pragma once
#include "Scene.h"
#include "Dependencies/freeglut/freeglut.h"
#include "Background.h"

Scene::Scene()
{
	m_shader = m_shaderloader.CreateProgram("Resources/Shaders/3D.vs", "Resources/Shaders/3D.fs");
	
	m_camera = std::make_unique<Camera>();
	
	//m_label = std::make_unique<TextLabel>("Player Score: " + std::to_string(m_fGametimer), "Resources/Fonts/arial.ttf", glm::vec2(10, 15));

	m_background = std::make_unique<Background>();
	m_ground = std::make_unique<Pawn>();
	m_ball = std::make_unique<Pawn>();
	m_ball2 = std::make_unique<Pawn>();
	m_bird = std::make_unique<CBird>();
	
	m_vecGameobjects = std::make_unique<std::vector<std::unique_ptr<Pawn>>>();
}

Scene::~Scene()
{
}

void Scene::Init()
{
	// Creating groundbody
	b2BodyDef bd;
	m_world.CreateBody(&bd);


	m_background->Init("Resources/Textures/Background.bmp", glm::vec3(WINDOW_WIDTH/80, WINDOW_HEIGHT/80, 0), 0.0f, glm::vec3(WINDOW_WIDTH/40, WINDOW_HEIGHT/40, 1), m_shader, *m_camera);
	m_vecGameobjects->push_back(std::move(m_background));

	m_ground->Init("Resources/Textures/Box.png", glm::vec3(10, 0.0f, 1.0f), 0, glm::vec3(100, 1, 0.0f), m_shader, *m_camera);
	m_ground->AddPhysics(true, COLLIDER_SQUARE, m_world);
	m_vecGameobjects->push_back(std::move(m_ground));

	m_ball->Init("Resources/Textures/Ball.png", glm::vec3(8.0f, 12.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f), m_shader, *m_camera);
	m_ball->AddPhysics(false, COLLIDER_CIRCLE, m_world);
	

	m_ball2->Init("Resources/Textures/Ball.png", glm::vec3(5.5f, 10.5f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f), m_shader, *m_camera);
	m_ball2->AddPhysics(true, COLLIDER_CIRCLE, m_world);

	m_bird->Init("Resources/Textures/Bird.png", glm::vec3(12.5f, 10.5f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f), m_shader, *m_camera);
	m_bird->AddPhysics(false, COLLIDER_CIRCLE, m_world);
	m_vecGameobjects->push_back(std::move(m_bird));
	
	/*jointDef.Initialize(m_ball->m_physicsBody, m_ball2->m_physicsBody, m_ball->m_physicsBody->GetWorldCenter(), m_ball2->m_physicsBody->GetWorldCenter());
	jointDef.collideConnected = true;
	jointDef.length = 2;*/
	
	
	jointDef.Initialize(m_ball->m_physicsBody, m_ball2->m_physicsBody, m_ball2->m_physicsBody->GetWorldCenter(), worldAxis);
	jointDef.lowerTranslation = -10.0f;
	jointDef.upperTranslation = 2.5f;
	jointDef.enableLimit = true;
	jointDef.maxMotorForce = 5.0f;
	jointDef.motorSpeed = 2.0f;
	jointDef.enableMotor = true;
	m_world.CreateJoint(&jointDef);
	m_world.SetDebugDraw(&m_debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	m_debugDraw.SetFlags(flags);
}

void Scene::Update()
{
	//DeltaTime
	if (m_bIsFirstRun == false)
	{
		m_fPreviousTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
		m_bIsFirstRun = true;
	}
	float currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
	m_fDeltaTime = (currentTime - m_fPreviousTime) * 0.001f;
	m_fPreviousTime = currentTime;

	
	for (auto&& pawn : *m_vecGameobjects)
	{
		if (pawn)
		{
			pawn->Update(m_fDeltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
		}
	}
	m_ball->Update(m_fDeltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
	m_ball2->Update(m_fDeltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
	m_fGametimer -= m_fDeltaTime;
	//m_label->Update(std::to_string(static_cast<int>(m_fGametimer)));
}

void Scene::Render()
{
	m_world.DrawDebugData();

	m_world.Step(m_timeStep, m_velocityInterations, m_positionIterations);

	

	for (auto&& pawn : *m_vecGameobjects)
	{
		if (pawn)
		{
			pawn->Render();
		}
	}

	m_ball->Render();
	m_ball2->Render();
	//m_label->Render();
}