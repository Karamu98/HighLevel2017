// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Container.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Container.h"
#include "TransformComponent.h"

#include "BoxColliderComponent.h"
#include "Gizmos.h"
#include "imgui.h"

typedef Entity PARENT;

/// <summary>
/// Initializes a new instance of the <see cref="Container"/> class.
/// </summary>
Container::Container() : m_fScale(0.1f)
{
	AddComponent(new BoxColliderComponent(this));

	pBoxColComp = (BoxColliderComponent*)(this->FindComponentOfType(BOXCOLLIDER));
	SetName(std::string("Container ") += std::to_string(GetEntityID()));
}

/// <summary>
/// Initializes a new instance of the <see cref="Container"/> class.
/// </summary>
/// <param name="a_dimentions">a dimentions.</param>
Container::Container(glm::vec3 a_dimentions) : m_fScale(0.1f)
{
	AddComponent(new BoxColliderComponent(this));

	pBoxColComp = (BoxColliderComponent*)(this->FindComponentOfType(BOXCOLLIDER));

	pBoxColComp->SetDimentions(a_dimentions);
	pBoxColComp->SetContainer(true);
	SetName("Container" + GetEntityID());
}

/// <summary>
/// Finalizes an instance of the <see cref="Container"/> class.
/// </summary>
Container::~Container()
{
}

/// <summary>
/// Updates the specified a f delta time.
/// </summary>
/// <param name="a_fDeltaTime">a f delta time.</param>
void Container::Update(float a_fDeltaTime)
{
	PARENT::Update(a_fDeltaTime);
}

/// <summary>
/// Draws the specified a UI program identifier.
/// </summary>
/// <param name="a_uiProgramID">a UI program identifier.</param>
/// <param name="a_uiVBO">a UI vbo.</param>
/// <param name="a_uiIBO">a UI ibo.</param>
void Container::Draw(unsigned int a_uiProgramID, unsigned int a_uiVBO, unsigned int a_uiIBO)
{
	PARENT::Draw(a_uiProgramID, a_uiVBO, a_uiIBO);
}
