#pragma once
#include "Scene.h"
#include "Dependencies/freeglut/freeglut.h"
#include "Background.h"

Scene::Scene()
{
	m_shader = m_shaderloader.CreateProgram("Resources/Shaders/3D.vs", "Resources/Shaders/3D.fs");
	
	m_camera = std::make_unique<Camera>();
	
	m_label = std::make_unique<TextLabel>("Player Score: " + std::to_string(m_fGametimer), "Resources/Fonts/arial.ttf", glm::vec2(10, 15));

	//m_background = std::make_unique<Background>();

	m_ball = std::make_unique<Pawn>();

	m_vecGameobjects = std::make_unique<std::vector<std::unique_ptr<Pawn>>>();
}

Scene::~Scene()
{
}

void Scene::Init()
{
	//m_background->Init("Resources/Textures/Background.bmp", glm::vec3(10, 5.0f, 1), 0.0f, glm::vec3(10, 10, 1.0f), m_shader);
	//m_vecGameobjects->push_back(std::move(m_background));

	m_ball->Init("Resources/Textures/Ball.png", glm::vec3(10.0f, 5.0f, 1.0f), 0.0f, glm::vec3(10.0f, 10.0f, 1.0f), m_shader);
	m_ball->AddPhysics(false, COLLIDER_CIRCLE, m_world);
	m_vecGameobjects->push_back(std::move(m_ball));

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

	m_fGametimer -= m_fDeltaTime;
	m_label->Update(std::to_string(static_cast<int>(m_fGametimer)));
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
	m_label->Render();
}