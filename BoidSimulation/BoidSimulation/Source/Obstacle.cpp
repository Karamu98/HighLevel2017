#include "Boid.h"

#include "Gizmos.h"
#include "Entity.h"
#include "Obstacle.h"
#include "TransformComponent.h"

typedef Entity PARENT;


Obstacle::Obstacle() : m_fScale(0.1f)
{
	//Add new components to the component list
	AddComponent(new TransformComponent(this));

}

void Obstacle::Update(float a_fDeltaTime)
{
	PARENT::Update(a_fDeltaTime);
}

void Obstacle::Draw(unsigned int a_uiProgramID, unsigned int a_uiVBO, unsigned int a_uiIBO)
{
	PARENT::Draw(a_uiProgramID, a_uiVBO, a_uiIBO);
}
