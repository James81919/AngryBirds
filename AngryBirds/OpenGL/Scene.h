#pragma once
#include <memory>
#include <vector>
#include "Dependencies/glew/glew.h"
#include "ShaderLoader.h"
#include "Camera.h"
#include "Pawn.h"
#include "TextLabel.h"

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

	//std::unique_ptr<Pawn> m_background;
	std::unique_ptr<Pawn> m_ball;

	std::unique_ptr<std::vector<std::unique_ptr<Pawn>>> m_vecGameobjects;

	std::unique_ptr<TextLabel> m_label;

	float m_fGametimer = 60;
	bool m_bIsFirstRun = false;
	float m_fDeltaTime = 0;
	float m_fPreviousTime = 0;

	b2World m_world = b2World(b2Vec2(0,0));

	float32 m_timeStep = 1.0f / 60.0f;
	int32 m_velocityInterations = 6;
	int32 m_positionIterations = 2;

	b2GLDraw m_debugDraw;
};
