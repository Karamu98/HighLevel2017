// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Boid.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Boid.h"

#include <GL/glew.h>
#include <glm/ext.hpp>
#include "BrainComponent.h"
#include "ModelComponent.h"
#include "CameraComponent.h"
#include "BoxColliderComponent.h"

#include <iostream>

typedef Entity PARENT;


/// <summary>
/// Initializes a new instance of the <see cref="Boid"/> class.
/// </summary>
Boid::Boid()
	: m_fScale(0.1f)
{
	//Add new components to the component list
	AddComponent(new ModelComponent(this));
	AddComponent(new BrainComponent(this));
	AddComponent(new CameraComponent(this));
	AddComponent(new BoxColliderComponent(this));
	
	pModelComp = (ModelComponent*)(this->FindComponentOfType(MODEL));
	pBrainComp = (BrainComponent*)(this->FindComponentOfType(BRAIN));
	pCameraComp = (CameraComponent*)(this->FindComponentOfType(CAMERA));
	pBoxColliderComp = (BoxColliderComponent*)(this->FindComponentOfType(BOXCOLLIDER));

	pCameraComp->m_bActive = false;
	pCameraComp->SetPossesed(false);

	pBoxColliderComp->SetDimentions(10, 10, 10);
	SetName(std::string("Boid ") += std::to_string(GetEntityID()));
}

/// <summary>
/// Initializes a new instance of the <see cref="Boid"/> class.
/// </summary>
/// <param name="a_m">a m.</param>
Boid::Boid(MD5Model* a_m)
	: m_fScale(0.1f)
{
	//Add new components to the component list
	AddComponent(new ModelComponent(this));
	AddComponent(new BrainComponent(this));
	AddComponent(new CameraComponent(this));
	AddComponent(new BoxColliderComponent(this));

	pBoxColliderComp = (BoxColliderComponent*)(this->FindComponentOfType(BOXCOLLIDER));

	pModelComp = static_cast<ModelComponent*>(this->FindComponentOfType(MODEL));
	pModelComp->SetModel(a_m);
	pModelComp->SetCurrentAnim("idle1");

	pBrainComp = static_cast<BrainComponent*>(this->FindComponentOfType(BRAIN));
	pCameraComp = (CameraComponent*)(this->FindComponentOfType(CAMERA));

	pCameraComp->m_bActive = false;
	pCameraComp->SetPossesed(false);

	pBoxColliderComp->SetDimentions(4, 4, 4);
	SetName(std::string("Boid ") += std::to_string(GetEntityID()));



	// TEST DELETE WHEN USING
	pBrainComp->SetBehaviour(WANDER);
	pBrainComp->AddBehaviour(ALIGNMENT);
	pBrainComp->AddBehaviour(SEPARATION);
	pBrainComp->AddBehaviour(COHESION);
}


/// <summary>
/// Finalizes an instance of the <see cref="Boid"/> class.
/// </summary>
Boid::~Boid()
{
}


/// <summary>
/// Updates the specified a f delta time.
/// </summary>
/// <param name="a_fDeltaTime">a f delta time.</param>
void Boid::Update(float a_fDeltaTime)
{
	PARENT::Update(a_fDeltaTime);
}

/// <summary>
/// Draws the specified a UI program identifier.
/// </summary>
/// <param name="a_uiProgramID">a UI program identifier.</param>
/// <param name="a_uiVBO">a UI vbo.</param>
/// <param name="a_uiIBO">a UI ibo.</param>
void Boid::Draw(unsigned int a_uiProgramID, unsigned int a_uiVBO, unsigned int a_uiIBO)
{
	PARENT::Draw(a_uiProgramID, a_uiVBO, a_uiIBO);
}

