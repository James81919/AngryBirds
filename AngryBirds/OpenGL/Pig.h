#ifndef __PIG_H__
#define __PIG_H__

#include "Pawn.h"

class CPig : public Pawn
{
public:
	CPig();
	~CPig();

	virtual void Init(std::string _sFilepath, glm::vec3 _vecPosition, float _fRotation, glm::vec3 _vecScale, GLuint& _shader, Camera _camera, b2Body* _worldbody);
	virtual void Update(float _deltaTime, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _cameraPos);
	virtual void Render();

private:
	
};

#endif // !__PIG_H__
