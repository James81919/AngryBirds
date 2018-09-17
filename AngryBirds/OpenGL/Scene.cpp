#pragma once
#include "Scene.h"
#include "Dependencies/freeglut/freeglut.h"
#include "Background.h"

Scene::Scene()
{
	shader =
		shaderloader.CreateProgram("Resources/Shaders/3D.vs", "Resources/Shaders/3D.fs");
	camera =
		std::make_unique<Camera>();

	label =
		std::make_unique<TextLabel>("Player Score: " + std::to_string(gametimer), "Resources/Fonts/arial.ttf", glm::vec2(10, 15));
	//background =
	//	std::make_shared<Background>();

	gameobjects =
		std::make_unique<std::vector<std::unique_ptr<Pawn>>>();
}

Scene::~Scene()
{
}

void Scene::Init()
{
	//background->Init("Resources/Textures/Background.bmp",	glm::vec3(10, 5.0f, 1),			0.0f,			glm::vec3(10, 10, 1.0f), shader, m_world);
	//gameobjects->push_back(background);

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
	if (firstrun == false)
	{
		previousTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
		firstrun = true;
	}
	float currentTime = static_cast<float>(glutGet(GLUT_ELAPSED_TIME));
	deltaTime = (currentTime - previousTime) * 0.001f;
	previousTime = currentTime;

	for (auto&& pawn : *gameobjects)
	{
		if (pawn)
		{
			pawn->Update(deltaTime, camera->GetView(), camera->GetProjection(), camera->GetLocation());
		}
	}

	gametimer -= deltaTime;
	label->Update(std::to_string(static_cast<int>(gametimer)));
}

void Scene::Render()
{
	m_world.DrawDebugData();

	m_world.Step(m_timeStep, m_velocityInterations, m_positionIterations);

	for (auto&& pawn : *gameobjects)
	{
		if (pawn)
		{
			pawn->Render();
		}
	}
	label->Render();
}