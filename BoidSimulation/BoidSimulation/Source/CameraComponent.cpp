// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="CameraComponent.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "glm/ext.hpp"
#include "Utilities.h"
#include "Entity.h"

#include "GL/glew.h"
#include "glfw3.h"
#include "glm/ext.hpp"

#include "glm/glm.hpp"
#include "imgui.h"

#include "Constants.h"



#include <iostream>



typedef Component PARENT;

/// <summary>
/// Initializes a new instance of the <see cref="CameraComponent"/> class.
/// </summary>
/// <param name="pOwnerEntity">The p owner entity.</param>
CameraComponent::CameraComponent(Entity* pOwnerEntity) : PARENT(pOwnerEntity)
, m_fFOV(120)
, m_fSpeed(150)
, m_pLocalPosition(glm::vec4(0, 0, 0, 1))
, m_bIsPossesed(false)
{
	m_eComponentType = CAMERA;
	m_bActive = false;

	if (pGetOwnerEntity() != NULL)
	{
		// create a world-space matrix for a camera

		// Get a position in front of the entity
		glm::vec3 forward = pGetOwnerEntity()->pGetRootTransformComp()->GetFacingDirection() * 1.0f;
		m_m4CameraMatrix = glm::inverse(glm::lookAt(pGetOwnerEntity()->pGetRootTransformComp()->GetCurrentPosition(), -forward, pGetOwnerEntity()->pGetRootTransformComp()->GetUpDirection()));
	}
}

/// <summary>
/// Finalizes an instance of the <see cref="CameraComponent"/> class.
/// </summary>
CameraComponent::~CameraComponent()
{
}

/// <summary>
/// Updates the specified a f delta time.
/// </summary>
/// <param name="a_fDeltaTime">a f delta time.</param>
void CameraComponent::Update(float a_fDeltaTime)
{
	if (m_bActive)
	{
		glm::mat4* rootTransform = pGetOwnerEntity()->pGetRootTransformComp()->pGetTransformMatrix();

		if (m_bIsPossesed)
		{
			Utility::freeMovement(*rootTransform, a_fDeltaTime, m_fSpeed, glm::vec3(0, 1, 0)); // Replace speed and Up with variables from attached transform comp
		}
		m_m4CameraMatrix = *rootTransform;

		m_m4CameraMatrix[3] = m_m4CameraMatrix[3] + m_pLocalPosition;

		// Create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
		m_m4ProjectionMatrix = glm::perspective(glm::pi<float>() * (m_fFOV / 360), g_uiDEFAULT_SCREENWIDTH / (float)g_uiDEFAULT_SCREENHEIGHT, 0.1f, 5000.0f);
	}
}

/// <summary>
/// Draws the specified a u program identifier.
/// </summary>
/// <param name="a_uProgramID">a u program identifier.</param>
/// <param name="a_uVBO">a u vbo.</param>
/// <param name="a_uIBO">a u ibo.</param>
void CameraComponent::Draw(unsigned int a_uProgramID, unsigned int a_uVBO, unsigned int a_uIBO)
{
	if (!m_bActive)
	{
		return;
	}

	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// get the view matrix from the world-space camera matrix
	m_m4ViewMatrix = glm::inverse(this->GetCameraMatrix());

	// bind our shader program
	glUseProgram(a_uProgramID);
	// bind our vertex array object
	glBindVertexArray(a_uVBO);

	// get our shaders uniform location for our projectionViewMatrix and then use glUniformMatrix4fv to fill it with the correct data
	unsigned int projectionViewUniform = glGetUniformLocation(a_uProgramID, "ProjectionView");
	glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(m_m4ProjectionMatrix * m_m4ViewMatrix));

	// pass our camera position to our fragment shader uniform
	unsigned int cameraPosUniform = glGetUniformLocation(a_uProgramID, "cameraPosition");
	glUniform4fv(cameraPosUniform, 1, glm::value_ptr(m_m4CameraMatrix[3]));
}

/// <summary>
/// Sets the possesed.
/// </summary>
/// <param name="a_newState">a new state.</param>
void CameraComponent::SetPossesed(bool a_newState)
{
	m_bIsPossesed = a_newState;
}

/// <summary>
/// Determines whether this instance is possessed.
/// </summary>
/// <returns>bool.</returns>
bool CameraComponent::IsPossessed()
{
	return m_bIsPossesed;
}

/// <summary>
/// Gets the camera matrix.
/// </summary>
/// <returns>glm.mat4.</returns>
glm::mat4 CameraComponent::GetCameraMatrix()
{
	return m_m4CameraMatrix;
}

/// <summary>
/// Gets the projection matrix.
/// </summary>
/// <returns>glm.mat4.</returns>
glm::mat4 CameraComponent::GetProjectionMatrix()
{
	return m_m4ProjectionMatrix;
}

/// <summary>
/// Gets the view matrix.
/// </summary>
/// <returns>glm.mat4.</returns>
glm::mat4 CameraComponent::GetViewMatrix()
{
	return m_m4ViewMatrix;
}


/// <summary>
/// ps the get fov.
/// </summary>
/// <returns>float *.</returns>
float * CameraComponent::pGetFOV()
{
	return &m_fFOV;
}

/// <summary>
/// ps the get speed.
/// </summary>
/// <returns>float *.</returns>
float * CameraComponent::pGetSpeed()
{
	return &m_fSpeed;
}

/// <summary>
/// ps the get possesed.
/// </summary>
/// <returns>bool *.</returns>
bool * CameraComponent::pGetPossesed()
{
	return &m_bIsPossesed;
}
