#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "ShaderLoader.h"
#include "Utilities.h"

class CSprite
{
public:
	CSprite();
	CSprite(std::string _filepath, GLuint& _shader);
	~CSprite();
	virtual void Init();
	virtual void Update(glm::mat4 _model, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _cameraPos);
	virtual void Render();

	void SetSprite(std::string _sFilePath);

protected:
	std::string
		m_sFilePath;
	GLuint
		m_vbo,
		m_vao,
		m_ebo,
		m_tex,
		m_index,
		m_shader;
	glm::mat4
		m_model,
		m_view,
		m_projection,
		m_mvp;
	glm::vec3
		m_cameraPos;

	GLfloat m_vertices[32] = {
		// Position				// Colour			// Tex Coords
		-1.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,		1.0f, 1.0f, 1.0f,	0.0f, 1.0f
	};

	GLuint m_indices[6] = {
		0, 1, 2, // First Triangle
		0, 2, 3  // Second Triangle
	};
};

#endif // !__SPRITE_H__
