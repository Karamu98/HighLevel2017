// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="RidgedbodyComponent.h" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef _RIDGEDBODYCOMPONENT_H__
#define _RIDGEDBODYCOMPONENT_H__

#include "Component.h"
#include "btBulletDynamicsCommon.h"

class Entity;

/// <summary>
/// Class RigidBodyComponent.
/// </summary>
/// <seealso cref="Component" />
class RigidBodyComponent : public Component
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="RigidBodyComponent"/> class.
	/// </summary>
	/// <param name="pOwnerEntity">The p owner entity.</param>
	RigidBodyComponent(Entity* pOwnerEntity);
	/// <summary>
	/// Finalizes an instance of the <see cref="RigidBodyComponent"/> class.
	/// </summary>
	~RigidBodyComponent();

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
	virtual void Draw(unsigned int a_uProgramID, unsigned int a_uVBO, unsigned int a_uIBO) {};
	/// <summary>
	/// Called when [GUI].
	/// </summary>
	virtual void OnGUI();

private:

	/// <summary>
	/// The m local inertia
	/// </summary>
	btVector3 m_localInertia;
	/// <summary>
	/// The m f mass
	/// </summary>
	btScalar m_fMass;
	/// <summary>
	/// The m rigid body
	/// </summary>
	btRigidBody* m_rigidBody;
};


#endif // !_RIDGEDBODYCOMPONENT_H__
