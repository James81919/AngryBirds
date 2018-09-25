#ifndef __BIRD_H__
#define __BIRD_H__

#include "Pawn.h"

class CBird : public Pawn
{
public:
	CBird();
	~CBird();

	virtual void Init(std::string _sFilepath, glm::vec3 _vecPosition, float _fRotation, glm::vec3 _vecScale, GLuint& _shader, Camera _camera, b2World* _worldbody, b2Body* _body);
	virtual void Update(float _deltaTime, glm::mat4 _view, glm::mat4 _projection, glm::vec3 _cameraPos);
	virtual void Render();

	void SetIsDragable(bool _bValue);
	bool IsDragable();

	void CreateMouseJoint(float _x, float _y);

private:
	bool m_bIsDragable = false;
	b2MouseJoint* m_mouseJoint;
	b2World* m_world;
	b2DistanceJointDef jointdef;
	b2DistanceJoint* joint;
	b2Body* m_shotbody;
};

#endif // !__BIRD_H__
