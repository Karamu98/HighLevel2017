// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Component.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Component.h"
#include "MD5Model.h"
#include <GL/glew.h>
#include <glm/ext.hpp>
#include "Game.h"
#include "Entity.h"
#include "imgui.h"



/// <summary>
/// Initializes a new instance of the <see cref="Component"/> class.
/// </summary>
/// <param name="a_pOwnerEntity">a p owner entity.</param>
Component::Component(Entity * a_pOwnerEntity)
	: m_pOwnerEntity(a_pOwnerEntity),
	m_bActive(true)
{

}

/// <summary>
/// Finalizes an instance of the <see cref="Component"/> class.
/// </summary>
Component::~Component()
{
}

/// <summary>
/// Draws the specified a u program identifier.
/// </summary>
/// <param name="a_uProgramID">a u program identifier.</param>
/// <param name="a_uVBO">a u vbo.</param>
/// <param name="a_uIBO">a u ibo.</param>
void Component::Draw(unsigned int a_uProgramID, unsigned int a_uVBO, unsigned int a_uIBO)
{
}

/// <summary>
/// Updates the specified a f delta time.
/// </summary>
/// <param name="a_fDeltaTime">a f delta time.</param>
void Component::Update(float a_fDeltaTime)
{
}

/// <summary>
/// Called when [GUI].
/// </summary>
void Component::OnGUI()
{
	switch (m_eComponentType)
	{
	case MODEL:
	{
		ImGui::TextColored(ImVec4(255, 255, 255, 1), "Model Component");
		break;
	}
	case BRAIN:
	{
		ImGui::TextColored(ImVec4(255, 255, 255, 1), "Brain Component");
		break;
	}
	case BOXCOLLIDER:
	{
		ImGui::TextColored(ImVec4(255, 255, 255, 1), "Box Collider Component");
		break;
	}
	default:
		break;
	}

	ImGui::PushID(m_eComponentType);
	if (!m_bActive)
	{
		if (ImGui::Button("Activate"))
		{
			m_bActive = true;
		}
	}
	else
	{
		if (ImGui::Button("Deactivate"))
		{
			m_bActive = false;
		}
	}
	ImGui::PopID();
	ImGui::NewLine();

}

/// <summary>
/// Gets the type of the component.
/// </summary>
/// <returns>COMPONENT_TYPE.</returns>
COMPONENT_TYPE Component::GetComponentType()
{
	return m_eComponentType;

}
/// <summary>
/// ps the get owner entity.
/// </summary>
/// <returns>Entity *.</returns>
Entity* Component::pGetOwnerEntity()
{
	return m_pOwnerEntity;
}


