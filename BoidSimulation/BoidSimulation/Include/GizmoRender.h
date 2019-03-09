#ifndef _GIZMO_RENDER_H__
#define _GIZMO_RENDER_H__

//includes
#include "glm/glm.hpp"
#include "Component.h"

class Entity;

class GizmoRender : public Component
{
public:
	GizmoRender(Entity* pOwnerEntity);
	~GizmoRender();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw(unsigned int a_uProgramID, unsigned int a_uVBO, unsigned int a_uIBO) {};


};


#endif