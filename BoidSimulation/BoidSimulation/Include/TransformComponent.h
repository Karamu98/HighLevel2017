// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="TransformComponent.h" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef _TRANSFORM_COMPONENT_H_
#define _TRANSFORM_COMPONENT_H_



// This component is the ROOT component

//includes
#include "Component.h"
#include "glm/ext.hpp"
#include "btBulletDynamicsCommon.h"

class Entity;

/// <summary>
/// Enum MATRIX_ROW
/// </summary>
enum MATRIX_ROW
{
	/// <summary>
	/// The right vector
	/// </summary>
	RIGHT_VECTOR,
	/// <summary>
	/// Up vector
	/// </summary>
	UP_VECTOR,
	/// <summary>
	/// The forward vector
	/// </summary>
	FORWARD_VECTOR,
	/// <summary>
	/// The position vector
	/// </summary>
	POSITION_VECTOR,
};


/// <summary>
/// Class TransformComponent.
/// </summary>
/// <seealso cref="Component" />
class TransformComponent : public Component
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="TransformComponent" /> class.
	/// </summary>
	/// <param name="a_pOwner">a p owner.</param>
	TransformComponent(Entity* a_pOwner);

	/// <summary>
	/// Finalizes an instance of the <see cref="TransformComponent" /> class.
	/// </summary>
	~TransformComponent();

	/// <summary>
	/// Updates the specified a f delta time.
	/// </summary>
	/// <param name="a_fDeltaTime">a f delta time.</param>
	virtual void Update(float a_fDeltaTime) {};
	/// <summary>
	/// Draws the specified a u program identifier.
	/// </summary>
	/// <param name="a_uProgramID">a u program identifier.</param>
	/// <param name="a_uVBO">a u vbo.</param>
	/// <param name="a_uIBO">a u ibo.</param>
	virtual void Draw(unsigned int a_uProgramID, unsigned int a_uVBO, unsigned int a_uIBO) {};

	/// <summary>
	/// Called when [GUI].
	/// </summary>
	virtual void OnGUI();


	/// <summary>
	/// Gets the transform.
	/// </summary>
	/// <returns>btTransform.</returns>
	btTransform GetTransform();
	

	/// <summary>
	/// Gets the right direction.
	/// </summary>
	/// <returns>glm.vec3.</returns>
	glm::vec3 GetRightDirection();

	/// <summary>
	/// Gets up direction.
	/// </summary>
	/// <returns>glm.vec3.</returns>
	glm::vec3 GetUpDirection();

	/// <summary>
	/// Gets the facing direction.
	/// </summary>
	/// <returns>glm.vec3.</returns>
	glm::vec3 GetFacingDirection();

	/// <summary>
	/// Gets the current position.
	/// </summary>
	/// <returns>glm.vec3.</returns>
	glm::vec3 GetCurrentPosition();


	/// <summary>
	/// Sets the right direction.
	/// </summary>
	/// <param name="vRightDirection">The v right direction.</param>
	void SetRightDirection(glm::vec3 vRightDirection);

	/// <summary>
	/// Sets up direction.
	/// </summary>
	/// <param name="vUpDirection">The v up direction.</param>
	void SetUpDirection(glm::vec3 vUpDirection);

	/// <summary>
	/// Sets the facing direction.
	/// </summary>
	/// <param name="vFacingDirection">The v facing direction.</param>
	void SetFacingDirection(glm::vec3 vFacingDirection);

	/// <summary>
	/// Sets the current position.
	/// </summary>
	/// <param name="vCurrentPosition">The v current position.</param>
	void SetCurrentPosition(glm::vec3 vCurrentPosition);


	/// <summary>
	/// ps the get transform matrix.
	/// </summary>
	/// <returns>glm.mat4 *.</returns>
	glm::mat4* pGetTransformMatrix();

private:

	/// <summary>
	/// Sets the entity matrix row.
	/// </summary>
	/// <param name="eRow">The e row.</param>
	/// <param name="vVec">The v vec.</param>
	void SetEntityMatrixRow(MATRIX_ROW eRow, glm::vec3 vVec);

	/// <summary>
	/// Gets the entity matrix row.
	/// </summary>
	/// <param name="eRow">The e row.</param>
	/// <returns>glm.vec3.</returns>
	glm::vec3 GetEntityMatrixRow(MATRIX_ROW eRow);

	/// <summary>
	/// The m m4 transform matrix
	/// </summary>
	glm::mat4 m_m4TransformMatrix;
};

#endif