// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Component.h" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "MD5Model.h"

class Entity;

/// <summary>
/// Enum COMPONENT_TYPE
/// </summary>
enum COMPONENT_TYPE
{
	/// <summary>
	/// The transform
	/// </summary>
	TRANSFORM,
	/// <summary>
	/// The model
	/// </summary>
	MODEL,
	/// <summary>
	/// The brain
	/// </summary>
	BRAIN,
	/// <summary>
	/// The camera
	/// </summary>
	CAMERA,
	/// <summary>
	/// The boxcollider
	/// </summary>
	BOXCOLLIDER,
	/// <summary>
	/// The ridgedbody
	/// </summary>
	RIDGEDBODY
};

/// <summary>
/// Class Component.
/// </summary>
class Component
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="Component"/> class.
	/// </summary>
	/// <param name="a_pOwnerEntity">a p owner entity.</param>
	Component(Entity* a_pOwnerEntity);
	/// <summary>
	/// Finalizes an instance of the <see cref="Component"/> class.
	/// </summary>
	~Component();
	/// <summary>
	/// Draws the specified a u program identifier.
	/// </summary>
	/// <param name="a_uProgramID">a u program identifier.</param>
	/// <param name="a_uVBO">a u vbo.</param>
	/// <param name="a_uIBO">a u ibo.</param>
	virtual void Draw(unsigned int a_uProgramID, unsigned int a_uVBO, unsigned int a_uIBO);
	/// <summary>
	/// Updates the specified a f delta time.
	/// </summary>
	/// <param name="a_fDeltaTime">a f delta time.</param>
	virtual void Update(float a_fDeltaTime);
	/// <summary>
	/// Called when [GUI].
	/// </summary>
	virtual void OnGUI();

	/// <summary>
	/// Gets the type of the component.
	/// </summary>
	/// <returns>COMPONENT_TYPE.</returns>
	COMPONENT_TYPE GetComponentType();
	/// <summary>
	/// ps the get owner entity.
	/// </summary>
	/// <returns>Entity *.</returns>
	Entity* pGetOwnerEntity();


	/// <summary>
	/// The m e component type
	/// </summary>
	COMPONENT_TYPE m_eComponentType;

	/// <summary>
	/// The m b active
	/// </summary>
	bool m_bActive;

private:
	/// <summary>
	/// The m p owner entity
	/// </summary>
	Entity* m_pOwnerEntity;

};
#endif