#pragma once
#include "Scene.h"
#include "Dependencies/freeglut/freeglut.h"
#include "Background.h"
#include "ContactListener.h"
MyContactListener g_myContactListenerInstance;



Scene::Scene()
{
	m_shader = m_shaderloader.CreateProgram("Resources/Shaders/3D.vs", "Resources/Shaders/3D.fs");
	
	m_camera = std::make_unique<Camera>();
	
	//m_label = std::make_unique<TextLabel>("Player Score: " + std::to_string(m_fGametimer), "Resources/Fonts/arial.ttf", glm::vec2(10, 15));

	m_background = std::make_unique<Background>();
	m_ground = std::make_unique<Pawn>();
	m_wall = std::make_unique<Pawn>();
	m_wall2 = std::make_unique<Pawn>();
	m_box1 = std::make_unique<Pawn>();
	m_box2 = std::make_unique<Pawn>();
	m_box3 = std::make_unique<Pawn>();
	m_ball3 = std::make_unique<Pawn>();
	m_pig1 = std::make_unique<CPig>();
	m_pig2 = std::make_unique<CPig>();
	m_pig3 = std::make_unique<CPig>();
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
	m_worldbody = m_world.CreateBody(&bd);
	m_world.SetContactListener(&g_myContactListenerInstance);

	m_background->Init("Resources/Textures/Background.bmp", glm::vec3(WINDOW_WIDTH/40, WINDOW_HEIGHT/40, 0), 0.0f, glm::vec3(WINDOW_WIDTH/40, WINDOW_HEIGHT/40, 1), m_shader, *m_camera);
	m_vecGameobjects->push_back(std::move(m_background));

	m_ground->Init("Resources/Textures/Box.png", glm::vec3(10, 0.0f, 1.0f), 0, glm::vec3(100, 1, 0.0f), m_shader, *m_camera);
	m_ground->AddPhysics(true, COLLIDER_SQUARE, m_world);
	m_vecGameobjects->push_back(std::move(m_ground));

	m_wall->Init("Resources/Textures/Box.png", glm::vec3(20.0f, 10.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f), m_shader, *m_camera);
	m_wall->AddPhysics(false, COLLIDER_SQUARE, m_world);

	m_wall2->Init("Resources/Textures/Box.png", glm::vec3(20.0f, 10.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f), m_shader, *m_camera);
	m_wall2->AddPhysics(true, COLLIDER_SQUARE, m_world);

	m_box1->Init("Resources/Textures/Box.png", glm::vec3(35.5f, 3.0f, 1.0f), 0.0f, glm::vec3(0.5f, 3.0f, 0.0f), m_shader, *m_camera);
	m_box1->AddPhysics(false, COLLIDER_SQUARE, m_world);
	m_vecGameobjects->push_back(std::move(m_box1));

	m_box2->Init("Resources/Textures/Box.png", glm::vec3(40.5f, 3.0f, 1.0f), 0.0f, glm::vec3(0.5f, 3.0f, 0.0f), m_shader, *m_camera);
	m_box2->AddPhysics(false, COLLIDER_SQUARE, m_world);
	m_vecGameobjects->push_back(std::move(m_box2));

	m_box3->Init("Resources/Textures/Box.png", glm::vec3(38.0f, 7.5f, 1.0f), 0.0f, glm::vec3(5.0f, 0.5f, 0.0f), m_shader, *m_camera);
	m_box3->AddPhysics(false, COLLIDER_SQUARE, m_world);
	m_vecGameobjects->push_back(std::move(m_box3));

	m_ball3->Init("Resources/Textures/Ball.png", glm::vec3(33.5f, 2.5f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f), m_shader, *m_camera);
	m_ball3->AddPhysics(false, COLLIDER_CIRCLE, m_world);
	m_vecGameobjects->push_back(std::move(m_ball3));

	m_pig1->Init("Resources/Textures/Pig.png", glm::vec3(38.0f, 1.5f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f), m_shader, *m_camera);
	m_pig1->AddPhysics(false, COLLIDER_CIRCLE, m_world);
	m_vecGameobjects->push_back(std::move(m_pig1));

	m_pig2->Init("Resources/Textures/Pig.png", glm::vec3(35.0f, 9.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f), m_shader, *m_camera);
	m_pig2->AddPhysics(false, COLLIDER_CIRCLE, m_world);
	m_vecGameobjects->push_back(std::move(m_pig2));

	m_pig3->Init("Resources/Textures/Pig.png", glm::vec3(41.0f, 9.0f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f), m_shader, *m_camera);
	m_pig3->AddPhysics(false, COLLIDER_CIRCLE, m_world);
	m_vecGameobjects->push_back(std::move(m_pig3));

	m_bird->Init("Resources/Textures/Bird.png", glm::vec3(10.5f, 10.5f, 1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 0.0f), m_shader, *m_camera, m_worldbody);
	m_bird->AddPhysics(false, COLLIDER_CIRCLE, m_world);

	
	/*jointDef.Initialize(m_ball->m_physicsBody, m_ball2->m_physicsBody, m_ball->m_physicsBody->GetWorldCenter(), m_ball2->m_physicsBody->GetWorldCenter());
	jointDef.collideConnected = true;
	jointDef.length = 2;*/
	
	

	jointDef.Initialize(m_wall->m_physicsBody, m_wall2->m_physicsBody, m_wall->m_physicsBody->GetWorldCenter(), worldAxis);
	jointDef.localAxisA.Set(0, 1);
	jointDef.localAnchorA.Set(-1, 4);
	jointDef.localAnchorB.Set(-1, 4);
	joint = (b2PrismaticJoint*)m_world.CreateJoint(&jointDef);
	joint->SetLimits(0.0f, 2.5f);
	joint->EnableLimit(true);
	joint->SetMaxMotorForce(5.0f);
	joint->SetMotorSpeed(motorspeed);
	joint->EnableMotor(true);
	
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
	if (joint->GetJointTranslation() >= joint->GetUpperLimit()) {
			joint->SetMotorSpeed(-motorspeed);
	}
	else if (joint->GetJointTranslation() <= joint->GetLowerLimit()) {
		joint->SetMotorSpeed(motorspeed);
	}
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
	m_wall->Update(m_fDeltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
	m_wall2->Update(m_fDeltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
	m_bird->Update(m_fDeltaTime, m_camera->GetView(), m_camera->GetProjection(), m_camera->GetLocation());
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

	m_wall->Render();
	m_wall2->Render();
	m_bird->Render();
	//m_label->Render();
}