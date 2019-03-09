// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="BoxColliderComponent.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "Gizmos.h"
#include "imgui.h"
#include "Entity.h"
#include "Game.h"

typedef Component PARENT;

/// <summary>
/// Initializes a new instance of the <see cref="BoxColliderComponent"/> class.
/// </summary>
/// <param name="pOwnerEntity">The p owner entity.</param>
BoxColliderComponent::BoxColliderComponent(Entity* pOwnerEntity) : PARENT(pOwnerEntity)
, m_v3Dimentions(5, 5, 5)
{

	m_eComponentType = BOXCOLLIDER;

	m_Shape = new btBoxShape(btVector3(btScalar(m_v3Dimentions.x), btScalar(m_v3Dimentions.y), btScalar(m_v3Dimentions.z)));
}

/// <summary>
/// Finalizes an instance of the <see cref="BoxColliderComponent"/> class.
/// </summary>
BoxColliderComponent::~BoxColliderComponent()
{
}

/// <summary>
/// Updates the specified a f delta time.
/// </summary>
/// <param name="a_fDeltaTime">a f delta time.</param>
void BoxColliderComponent::Update(float a_fDeltaTime)
{
	if (!m_bActive)
	{
		return;
	}

	m_Shape->setImplicitShapeDimensions(btVector3(btScalar(m_v3Dimentions.x), btScalar(m_v3Dimentions.y), btScalar(m_v3Dimentions.z)));

}

/// <summary>
/// Draws the specified a u program identifier.
/// </summary>
/// <param name="a_uProgramID">a u program identifier.</param>
/// <param name="a_uVBO">a u vbo.</param>
/// <param name="a_uIBO">a u ibo.</param>
void BoxColliderComponent::Draw(unsigned int a_uProgramID, unsigned int a_uVBO, unsigned int a_uIBO)
{
	PARENT::Draw(a_uProgramID, a_uVBO, a_uIBO);
	if (!m_bActive)
	{
		return;
	}
	Gizmos::addBox(pGetOwnerEntity()->pGetRootTransformComp()->GetCurrentPosition(), (glm::vec3(m_v3Dimentions.x, m_v3Dimentions.y, m_v3Dimentions.z)), false, glm::vec4(255, 255, 255, 1));
}

/// <summary>
/// Called when [GUI].
/// </summary>
void BoxColliderComponent::OnGUI()
{
	PARENT::OnGUI();
	if (!m_bActive)
	{
		return;
	}
	// List Box Component
	ImGui::TextColored(ImVec4(255, 255, 255, 1), "Dimentions:");
	ImGui::SliderFloat("Height: ", &m_v3Dimentions.y, 0, 500);
	ImGui::SliderFloat("Width: ", &m_v3Dimentions.x, 0, 500);
	ImGui::SliderFloat("Length: ", &m_v3Dimentions.z, 0, 500);
	ImGui::NewLine();
}

/// <summary>
/// Gets the dimentions.
/// </summary>
/// <returns>glm.vec3 *.</returns>
glm::vec3 * BoxColliderComponent::GetDimentions()
{
	return &m_v3Dimentions;
}

/// <summary>
/// Sets the dimentions.
/// </summary>
/// <param name="a_size">a size.</param>
void BoxColliderComponent::SetDimentions(glm::vec3 a_size)
{
	m_v3Dimentions = a_size;
}

/// <summary>
/// Sets the dimentions.
/// </summary>
/// <param name="a_x">a x.</param>
/// <param name="a_y">a y.</param>
/// <param name="a_z">a z.</param>
void BoxColliderComponent::SetDimentions(float a_x, float a_y, float a_z)
{
	m_v3Dimentions.x = a_x;
	m_v3Dimentions.y = a_y;
	m_v3Dimentions.z = a_z;
}

/// <summary>
/// Sets the container.
/// </summary>
/// <param name="a_isContainer">a is container.</param>
void BoxColliderComponent::SetContainer(bool a_isContainer)
{
	bIsContainer = a_isContainer;
}

/// <summary>
/// ps the get box shape.
/// </summary>
/// <returns>btBoxShape *.</returns>
btBoxShape * BoxColliderComponent::pGetBoxShape()
{
	return m_Shape;
}

/// <summary>
/// Determines whether this instance is container.
/// </summary>
/// <returns>bool.</returns>
bool BoxColliderComponent::IsContainer()
{
	return bIsContainer;
}

