#pragma once
#include "Sprite.h"
#include "Camera.h"
#include "Dependencies/glm/gtc/matrix_transform.hpp"
#include "Dependencies/glm/gtc/type_ptr.hpp"
#include "Dependencies/soil/SOIL.h"
#define _USE_MATH_DEFINES
#include <math.h>

CSprite::CSprite()
{
}

CSprite::CSprite(std::string _filepath, GLuint& _shader)
	: m_sFilePath(_filepath), m_shader(_shader)
{
	Init();
}

CSprite::~CSprite()
{
}

void CSprite::Init()
{
	glGenTextures(1, &m_tex);

	glBindTexture(GL_TEXTURE_2D, m_tex);
	int width, height;
	unsigned char* image = SOIL_load_image(
		m_sFilePath.c_str(),
		&width,
		&height,
		0,
		SOIL_LOAD_RGBA);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_index = sizeof(m_vertices) / sizeof(GLuint);
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

void CSprite::Update(glm::mat4 t_model, glm::mat4 t_view, glm::mat4 t_projection, glm::vec3 t_cameraPos)
{
	m_model = t_model;
	m_view = t_view;
	m_projection = t_projection;
	m_cameraPos = t_cameraPos;
	m_mvp = m_model * m_view * m_projection;
}

void CSprite::Render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(m_shader);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glUniform1i(glGetUniformLocation(m_shader, "tex"), 0);

	GLint MVP = glGetUniformLocation(m_shader, "mvp");
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m_mvp));

	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_index, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDisable(GL_BLEND);
}

void CSprite::SetSprite(std::string _sFilePath)
{
	m_sFilePath = _sFilePath;
}