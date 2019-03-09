#include "Boid.h"

#include "Entity.h"
#include <GL/glew.h>
#include <glm/ext.hpp>
#include "TransformComponent.h"
#include "ModelComponent.h"

typedef Entity PARENT;


Boid::Boid()
	: m_fScale(0.1f)
{
	//Add new components to the component list
	AddComponent(new TransformComponent(this));
	AddComponent(new ModelComponent(this));
	AddComponent(new BrainComponent(this));
	
	pModelComp = (ModelComponent*)(this->FindComponentOfType(MODEL));
	pModelComp->SetCurrentAnim("idle1");

	pTransformComp = (TransformComponent*)(this->FindComponentOfType(TRANSFORM));
	pBrainComp = (BrainComponent*)(this->FindComponentOfType(BRAIN));
}

Boid::Boid(MD5Model a_m)
	: m_fScale(0.1f)
{
	//Add new components to the component list
	AddComponent(new TransformComponent(this));
	AddComponent(new ModelComponent(this));
	AddComponent(new BrainComponent(this));

	pModelComp = (ModelComponent*)(this->FindComponentOfType(MODEL));
	pModelComp->LoadModel("../resources/Models/imp.md5mesh", 0.1f, a_m);
	pModelComp->SetCurrentAnim("idle1");

	pTransformComp = (TransformComponent*)(this->FindComponentOfType(TRANSFORM));

	pBrainComp = (BrainComponent*)(this->FindComponentOfType(BRAIN));
	pBrainComp->SetBehaviour(SEEK);
}


Boid::~Boid()
{
}


void Boid::Update(float a_fDeltaTime)
{
	PARENT::Update(a_fDeltaTime);
}

void Boid::Draw(unsigned int a_uiProgramID, unsigned int a_uiVBO, unsigned int a_uiIBO)
{
	PARENT::Draw(a_uiProgramID, a_uiVBO, a_uiIBO);
}

