// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="RidgedbodyComponent.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "BoxColliderComponent.h"
#include "..\Include\RidgedbodyComponent.h"
#include "btBulletDynamicsCommon.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "imgui.h"
#include "Game.h"

typedef Component PARENT;

/// <summary>
/// Initializes a new instance of the <see cref="RigidBodyComponent"/> class.
/// </summary>
/// <param name="pOwnerEntity">The p owner entity.</param>
RigidBodyComponent::RigidBodyComponent(Entity * pOwnerEntity) : PARENT(pOwnerEntity)
, m_fMass(10)
{
	m_eComponentType = RIDGEDBODY;


	btBoxShape* shape = ((BoxColliderComponent*)(pGetOwnerEntity()->FindComponentOfType(BOXCOLLIDER)))->pGetBoxShape();

	if (shape != nullptr)
	{
		btTransform transform = pOwnerEntity->pGetRootTransformComp()->GetTransform();
		btDefaultMotionState* bodyMotion = new btDefaultMotionState(transform.getIdentity());

		btRigidBody::btRigidBodyConstructionInfo bodyCI(m_fMass, bodyMotion, shape, m_localInertia);
		m_rigidBody = new btRigidBody(bodyCI);

		Game::pGetGame()->GetDynamicsWorld()->addRigidBody(m_rigidBody);
	}
}

/// <summary>
/// Finalizes an instance of the <see cref="RigidBodyComponent"/> class.
/// </summary>
RigidBodyComponent::~RigidBodyComponent()
{
}

/// <summary>
/// Updates the specified a f delta time.
/// </summary>
/// <param name="a_fDeltaTime">a f delta time.</param>
void RigidBodyComponent::Update(float a_fDeltaTime)
{
	PARENT::Update(a_fDeltaTime);
	pGetOwnerEntity()->pGetRootTransformComp()->SetCurrentPosition(glm::vec3(m_rigidBody->getWorldTransform().getOrigin().getX(), m_rigidBody->getWorldTransform().getOrigin().getY(), m_rigidBody->getWorldTransform().getOrigin().getZ()));

	m_rigidBody->setMassProps(m_fMass, btVector3(0, 0, 0));


}

/// <summary>
/// Called when [GUI].
/// </summary>
void RigidBodyComponent::OnGUI()
{
	PARENT::OnGUI();
	ImGui::InputFloat("Mass: ", &m_fMass);
	ImGui::NewLine();
}
