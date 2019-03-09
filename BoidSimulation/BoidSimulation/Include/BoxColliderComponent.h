// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="BoxColliderComponent.h" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************

#ifndef _BOX_COLLIDER_H__
#define _BOX_COLLIDER_H__

#include "Component.h"
#include <vector>
#include "btBulletDynamicsCommon.h"

class Entity;

/// <summary>
/// Class BoxColliderComponent.
/// </summary>
/// <seealso cref="Component" />
class BoxColliderComponent : public Component
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="BoxColliderComponent" /> class.
	/// </summary>
	/// <param name="pOwnerEntity">The p owner entity.</param>
	BoxColliderComponent(Entity* pOwnerEntity);

	/// <summary>
	/// Finalizes an instance of the <see cref="BoxColliderComponent" /> class.
	/// </summary>
	~BoxColliderComponent();


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
	virtual void OnGUI();


	/// <summary>
	/// Gets the dimentions.
	/// </summary>
	/// <returns>glm.vec3 *.</returns>
	glm::vec3* GetDimentions();


	/// <summary>
	/// Sets the dimentions.
	/// </summary>
	/// <param name="a_size">a size.</param>
	void SetDimentions(glm::vec3 a_size);

	/// <summary>
	/// Sets the dimentions.
	/// </summary>
	/// <param name="a_x">a x.</param>
	/// <param name="a_y">a y.</param>
	/// <param name="a_z">a z.</param>
	void SetDimentions(float a_x, float a_y, float a_z);


	/// <summary>
	/// Sets the container.
	/// </summary>
	/// <param name="a_isContainer">a is container.</param>
	void SetContainer(bool a_isContainer);


	/// <summary>
	/// ps the get box shape.
	/// </summary>
	/// <returns>btBoxShape *.</returns>
	btBoxShape* pGetBoxShape();


	/// <summary>
	/// Determines whether this instance is container.
	/// </summary>
	/// <returns>bool.</returns>
	bool IsContainer();
	


	/// <summary>
	/// The f test distance
	/// </summary>
	float fTestDistance;


private:
	
	/// <summary>
	/// The m shape
	/// </summary>
	btBoxShape * m_Shape;
	/// <summary>
	/// The m other
	/// </summary>
	BoxColliderComponent* m_other; // cache 

/// <summary>
/// The m v3 dimentions
/// </summary>
	glm::vec3 m_v3Dimentions;
	/// <summary>
	/// The b is container
	/// </summary>
	bool bIsContainer;

};


#endif