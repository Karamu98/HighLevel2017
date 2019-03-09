// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="CameraComponent.h" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef _CAMERA_H__
#define _CAMERA_H__

#include "Component.h"

class Entity;

/// <summary>
/// Class CameraComponent.
/// </summary>
/// <seealso cref="Component" />
class CameraComponent : public Component
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="CameraComponent"/> class.
	/// </summary>
	/// <param name="pOwnerEntity">The p owner entity.</param>
	CameraComponent(Entity* pOwnerEntity);
	/// <summary>
	/// Finalizes an instance of the <see cref="CameraComponent"/> class.
	/// </summary>
	~CameraComponent();

	/// <summary>
	/// Updates the specified a f delta time.
	/// </summary>
	/// <param name="a_fDeltaTime">a f delta time.</param>
	virtual void Update(float a_fDeltaTime);
	/// <summary>
	/// Draws the specified a u program identifier.
	/// </summary>
	/// <param name="a_uProgramID">a u program identifier.</param>
	/// <param name="a_uVBO">a u vbo.</param>
	/// <param name="a_uIBO">a u ibo.</param>
	virtual void Draw(unsigned int a_uProgramID, unsigned int a_uVBO, unsigned int a_uIBO);
	/// <summary>
	/// Called when [GUI].
	/// </summary>
	virtual void OnGUI() {};

	/// <summary>
	/// Sets the possesed.
	/// </summary>
	/// <param name="a_newState">a new state.</param>
	void SetPossesed(bool a_newState);
	/// <summary>
	/// Determines whether this instance is possessed.
	/// </summary>
	/// <returns>bool.</returns>
	bool IsPossessed();

	/// <summary>
	/// Gets the camera matrix.
	/// </summary>
	/// <returns>glm.mat4.</returns>
	glm::mat4 GetCameraMatrix();
	/// <summary>
	/// Gets the projection matrix.
	/// </summary>
	/// <returns>glm.mat4.</returns>
	glm::mat4 GetProjectionMatrix();
	/// <summary>
	/// Gets the view matrix.
	/// </summary>
	/// <returns>glm.mat4.</returns>
	glm::mat4 GetViewMatrix();


	/// <summary>
	/// ps the get fov.
	/// </summary>
	/// <returns>float *.</returns>
	float* pGetFOV();
	/// <summary>
	/// ps the get speed.
	/// </summary>
	/// <returns>float *.</returns>
	float* pGetSpeed();
	/// <summary>
	/// ps the get possesed.
	/// </summary>
	/// <returns>bool *.</returns>
	bool* pGetPossesed();

private:

	/// <summary>
	/// The m b is possesed
	/// </summary>
	bool m_bIsPossesed;

	/// <summary>
	/// The m f fov
	/// </summary>
	float m_fFOV;
	/// <summary>
	/// The m f speed
	/// </summary>
	float m_fSpeed;

	/// <summary>
	/// The m p local position
	/// </summary>
	glm::vec4 m_pLocalPosition;

	/// <summary>
	/// The m m4 camera matrix
	/// </summary>
	glm::mat4 m_m4CameraMatrix; // The result of Root + offset
/// <summary>
/// The m m4 projection matrix
/// </summary>
	glm::mat4 m_m4ProjectionMatrix;
	/// <summary>
	/// The m m4 view matrix
	/// </summary>
	glm::mat4 m_m4ViewMatrix;

};

#endif // !_CAMERA_H__
