// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="TransformComponent.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "TransformComponent.h"
#include "Entity.h"
#include "imgui.h"

//typedefs
typedef Component PARENT;

/// <summary>
/// Initializes a new instance of the <see cref="TransformComponent"/> class.
/// </summary>
/// <param name="pOwner">The p owner.</param>
TransformComponent::TransformComponent(Entity* pOwner) : PARENT(pOwner)
{
	m_eComponentType = TRANSFORM;

	SetCurrentPosition(glm::vec3(0, 0, 0));
	SetFacingDirection(glm::vec3(0, 0, 1));
	SetUpDirection(glm::vec3(0, 1, 0));
	SetRightDirection(glm::vec3(1, 0, 0));
}


/// <summary>
/// Finalizes an instance of the <see cref="TransformComponent"/> class.
/// </summary>
TransformComponent::~TransformComponent()
{
}


/// <summary>
/// Called when [GUI].
/// </summary>
void TransformComponent::OnGUI()
{
	// List Transfrom Component
	ImGui::TextColored(ImVec4(255, 255, 255, 1), "Transform Component");
	ImGui::Text("Name: ");
	ImGui::SameLine(50);
	ImGui::InputText("", (char*)pGetOwnerEntity()->GetName()->c_str(), 10);
	ImGui::Text("Position X: %i Y: %i Z: %i", (int)pGetOwnerEntity()->pGetRootTransformComp()->GetCurrentPosition().x, (int)pGetOwnerEntity()->pGetRootTransformComp()->GetCurrentPosition().y, (int)pGetOwnerEntity()->pGetRootTransformComp()->GetCurrentPosition().z);
	if(ImGui::Button("Reset"))
	{
		SetCurrentPosition(glm::vec3(0, 0, 0));
		SetFacingDirection(glm::vec3(0, 0, 1));
		SetUpDirection(glm::vec3(0, 1, 0));
		SetRightDirection(glm::vec3(1, 0, 0));
	}
	ImGui::NewLine();
}

/// <summary>
/// Gets the transform.
/// </summary>
/// <returns>btTransform.</returns>
btTransform TransformComponent::GetTransform()
{
	// Create a transform for the collision box
	btTransform conversionTransform;

	// Convert transform location to work with bullet physics
	conversionTransform.setOrigin(btVector3(btScalar(GetCurrentPosition().x), btScalar(GetCurrentPosition().y), btScalar(GetCurrentPosition().z)));

	// Convert stored rotation to work with bullet physics
	btMatrix3x3 conversionMatrix = btMatrix3x3
	(
		GetRightDirection().x, GetRightDirection().y, GetRightDirection().z,
		GetUpDirection().x, GetUpDirection().y, GetUpDirection().z,
		-GetRightDirection().x, -GetRightDirection().y, -GetRightDirection().z
	);

	// Apply converted rotation
	conversionTransform.setBasis(conversionMatrix);
	return conversionTransform;
}

/// <summary>
/// Gets the right direction.
/// </summary>
/// <returns>glm.vec3.</returns>
glm::vec3 TransformComponent::GetRightDirection()
{
	return GetEntityMatrixRow(RIGHT_VECTOR);
}
/// <summary>
/// Gets up direction.
/// </summary>
/// <returns>glm.vec3.</returns>
glm::vec3 TransformComponent::GetUpDirection()
{
	return GetEntityMatrixRow(UP_VECTOR);
}
/// <summary>
/// Gets the facing direction.
/// </summary>
/// <returns>glm.vec3.</returns>
glm::vec3 TransformComponent::GetFacingDirection()
{
	return GetEntityMatrixRow(FORWARD_VECTOR);
}
/// <summary>
/// Gets the current position.
/// </summary>
/// <returns>glm.vec3.</returns>
glm::vec3 TransformComponent::GetCurrentPosition()
{
	return GetEntityMatrixRow(POSITION_VECTOR);
}

/// <summary>
/// Sets the right direction.
/// </summary>
/// <param name="vRightDirection">The v right direction.</param>
void TransformComponent::SetRightDirection(glm::vec3 vRightDirection)
{
	SetEntityMatrixRow(RIGHT_VECTOR, vRightDirection);
}
/// <summary>
/// Sets up direction.
/// </summary>
/// <param name="vUpDirection">The v up direction.</param>
void TransformComponent::SetUpDirection(glm::vec3 vUpDirection)
{
	SetEntityMatrixRow(UP_VECTOR, vUpDirection); 
}
/// <summary>
/// Sets the facing direction.
/// </summary>
/// <param name="vFacingDirection">The v facing direction.</param>
void TransformComponent::SetFacingDirection(glm::vec3 vFacingDirection)
{
	SetEntityMatrixRow(FORWARD_VECTOR, vFacingDirection);
}
/// <summary>
/// Sets the current position.
/// </summary>
/// <param name="vCurrentPosition">The v current position.</param>
void TransformComponent::SetCurrentPosition(glm::vec3 vCurrentPosition)
{
	SetEntityMatrixRow(POSITION_VECTOR, vCurrentPosition);
}

/// <summary>
/// ps the get transform matrix.
/// </summary>
/// <returns>glm.mat4 *.</returns>
glm::mat4* TransformComponent::pGetTransformMatrix()
{
	return &m_m4TransformMatrix;
}

/// <summary>
/// Sets the entity matrix row.
/// </summary>
/// <param name="eRow">The e row.</param>
/// <param name="vVec">The v vec.</param>
void TransformComponent::SetEntityMatrixRow(MATRIX_ROW eRow, glm::vec3 vVec)
{
	m_m4TransformMatrix[eRow] = glm::vec4(vVec, (eRow == POSITION_VECTOR ? 1.f : 0.f));
}
/// <summary>
/// Gets the entity matrix row.
/// </summary>
/// <param name="eRow">The e row.</param>
/// <returns>glm.vec3.</returns>
glm::vec3 TransformComponent::GetEntityMatrixRow(MATRIX_ROW eRow)
{
	return m_m4TransformMatrix[eRow];
}
