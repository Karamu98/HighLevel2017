// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="BrainComponent.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "BrainComponent.h"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "BoxColliderComponent.h"
#include "Constants.h"
#include "Gizmos.h"
#include "Entity.h"
#include "imgui.h"

#include <iostream>
//typedefs

typedef Component PARENT;


/// <summary>
/// Initializes a new instance of the <see cref="BrainComponent"/> class.
/// </summary>
/// <param name="pOwnerEntity">The p owner entity.</param>
BrainComponent::BrainComponent(Entity* pOwnerEntity) : PARENT(pOwnerEntity)
, m_v3CurrentVelocity(0.0f, 0.0f, 0.0f)
, m_uiIsBehaviour(0) // All bits off (All behaviours false)
, m_fSpeed(20)

// Seek Defaults
, m_fSeekWeight(1) // Needs to be set according to amount of active behaviors
, m_v3SeekTarget(0, 0, 0)

// Wander Defaults
, m_fWanderWeight(1) // Needs to be set according to amount of active behaviors
, m_fWanderRadius(0.3)
, m_fWanderJitter(0.01)
, m_fWanderCircleMultiplier(10)

// Flee Defaults
, m_fFleeWeight(1) // Needs to be set according to amount of active behaviors
, m_v3FleeTarget(0, 0, 0)

// Evade Defaults
, m_fEvadeWeight(1)
, m_fEvadeMultiplier(3)

// Pursue Defaults
, m_fPursueWeight(1)
, m_fPursueMultiplier(3)

// Separation Defaults
, m_fSeparationWeight(1)
, m_fSeparationRadius(20)

// Alignment Defaults
, m_fAlignmentWeight(1)
, m_fAlignmentRadius(35)
, m_iAlignmentNeighbourCount(0)

// Cohesion Defaults
, m_fCohesionWeight(0.5)
, m_fCohesionRadius(30)
, m_iCohesionNeighbourCount(0)

{
	m_eComponentType = BRAIN;
}

/// <summary>
/// Finalizes an instance of the <see cref="BrainComponent"/> class.
/// </summary>
BrainComponent::~BrainComponent()
{

}

/// <summary>
/// Updates the specified a f delta time.
/// </summary>
/// <param name="a_fDeltaTime">a f delta time.</param>
void BrainComponent::Update(float a_fDeltaTime)
{
	if (!m_bActive)
	{
		return;
	}

#pragma region Component_Validation
	Entity* pEntity = pGetOwnerEntity();
	if (!pEntity)
	{
		return; // Early Out
	}

	TransformComponent* pTransformComp = pGetOwnerEntity()->pGetRootTransformComp();
	if (!pTransformComp)
	{
		std::cout << "Early out" << std::endl;
		return; // Early Out
	}

	bool bCanAnimate = false; // Debug disabled
	ModelComponent* pModelComp = static_cast<ModelComponent*>(pEntity->FindComponentOfType(MODEL));
	if (!pModelComp)
	{
		bCanAnimate = false;
	}

	if (m_fSpeed == 0.0f)
	{
		return;
	}

#pragma endregion

	// Expose the variables to IMGUI

	// Pre Calculations
	glm::vec3 v3Forward = pTransformComp->GetFacingDirection(); // Cache the agent forward
	glm::vec3 v3CurrentPos = pTransformComp->GetCurrentPosition(); // Cache the agent Position

	glm::vec3 v3TotalForce = { 0, 0, 0 }; // This accumulate the force that will be applied to the agent after calculations

	// Test and Calculate 
	if (m_uiIsBehaviour != 0) // If at least one behaviour is active
	{

		// Test to animate (Need to make this more abstract in form)
		if (pModelComp->GetCurrentAnim() != "walk1" && bCanAnimate)
		{
			pModelComp->SetCurrentAnim("walk1");
		}


#pragma region Behaviour_Calculation

		// Create the testing mask
		uint8_t mask = 1 << (int)SEEK; 

		if (m_uiIsBehaviour != 0)
		{
			// SEEK
			if ((mask & m_uiIsBehaviour) > 0)
			{
				if (m_fSeekWeight != 0.0f)
				{
					v3TotalForce += CalculateSeekForce(v3CurrentPos) * m_fSeekWeight;

				}
			}
			mask = 1 << (int)WANDER;

			// WANDER
			if ((mask & m_uiIsBehaviour) > 0)
			{
				if (m_fWanderWeight != 0.0f)
				{
					v3TotalForce += CalculateWanderForce(v3CurrentPos, v3Forward) * m_fWanderWeight;
				}
			}

			mask = 1 << (int)FLEE;

			// FLEE
			if ((mask & m_uiIsBehaviour) > 0)
			{
				if (m_fFleeWeight != 0.0f)
				{
					v3TotalForce += CalculateFleeForce(v3CurrentPos) * m_fFleeWeight;
				}
			}

			mask = 1 << (int)EVADE;

			// EVADE
			if ((mask & m_uiIsBehaviour) > 0)
			{
				if (m_fEvadeWeight != 0.0f)
				{
					v3TotalForce += CalculateEvadeForce(v3CurrentPos, v3Forward) * m_fEvadeWeight;
				}
			}

			mask = 1 << (int)PURSUE;

			// PURSUE
			if ((mask & m_uiIsBehaviour) > 0)
			{
				if (m_fPursueWeight != 0.0f)
				{
					v3TotalForce += CalculatePursueForce(v3CurrentPos, v3Forward) * m_fPursueWeight;
				}
			}

			mask = 1 << (int)SEPARATION;

			// SEPARATION
			if ((mask & m_uiIsBehaviour) > 0)
			{
				if (m_fSeparationWeight != 0.0f)
				{
					v3TotalForce += CalculateSeparationForce(v3CurrentPos) * m_fSeparationWeight;
				}
			}

			mask = 1 << (int)ALIGNMENT;

			// ALIGNMENT
			if ((mask & m_uiIsBehaviour) > 0)
			{
				if (m_fAlignmentWeight != 0.0f)
				{
					v3TotalForce += CalculateAlignmentForce(v3CurrentPos) * m_fAlignmentWeight;
				}
			}

			mask = 1 << (int)COHESION;

			// COHESION
			if ((mask & m_uiIsBehaviour) > 0)
			{
				if (m_fCohesionWeight != 0.0f)
				{
					v3TotalForce += CalculateCohesionForce(v3CurrentPos) * m_fCohesionWeight;
				}
			}
		}
		

#pragma endregion

		//v3TotalForce = glm::normalize(v3TotalForce);

		// Apply final force to velocity
		m_v3CurrentVelocity += v3TotalForce;

		// Move agent with their velocity
		v3CurrentPos += m_v3CurrentVelocity * a_fDeltaTime;

		// Normlise and set our forward
		v3Forward = glm::normalize(m_v3CurrentVelocity);
		glm::vec3 v3Up = pTransformComp->GetUpDirection();

		v3Up = v3Up - (v3Forward * glm::dot(v3Forward, v3Up));
		v3Up = glm::normalize(v3Up);
		glm::vec3 v3Right = glm::normalize(glm::cross(v3Up, v3Forward));
		// Calculate our Up using Gramschmidt


		// Set the matrix
		pTransformComp->SetUpDirection(v3Up);
		pTransformComp->SetRightDirection(v3Right);
		pTransformComp->SetFacingDirection(v3Forward);
		pTransformComp->SetCurrentPosition(v3CurrentPos);

		v3TotalForce = glm::vec3();
	}
}

/// <summary>
/// Called when [GUI].
/// </summary>
void BrainComponent::OnGUI()
{
	PARENT::OnGUI();
	if (!m_bActive)
	{
		return;
	}
	// List Brain Component
	ImGui::TextColored(ImVec4(255, 255, 255, 1), "Defaults:");
	ImGui::SliderFloat("Speed: ", &m_fSpeed, 0, 200);
	ImGui::NewLine();
	if (ImGui::Button("Toggle Seek"))
	{
		ToggleBehaviour(SEEK);
	}
	if (ImGui::Button("Toggle Wander"))
	{
		ToggleBehaviour(WANDER);
	}
	if (ImGui::Button("Toggle Flee"))
	{
		ToggleBehaviour(FLEE);
	}
	if (ImGui::Button("Toggle Evade"))
	{
		ToggleBehaviour(EVADE);
	}
	if (ImGui::Button("Toggle Pursue"))
	{
		ToggleBehaviour(PURSUE);
	}
	if (ImGui::Button("Toggle Separation"))
	{
		ToggleBehaviour(SEPARATION);
	}
	if (ImGui::Button("Toggle Alignment"))
	{
		ToggleBehaviour(ALIGNMENT);
	}
	if (ImGui::Button("Toggle Cohesion"))
	{
		ToggleBehaviour(COHESION);
	}
	ImGui::NewLine();
	ImGui::PushID(pGetOwnerEntity()->GetEntityID() + "Seek");
	ImGui::TextColored(ImVec4(255, 255, 255, 1), "Seek:");
	ImGui::SliderFloat("Weight: ", &m_fSeekWeight, 0, 1);
	// Set target
	ImGui::PopID();
	ImGui::NewLine();

	ImGui::PushID(pGetOwnerEntity()->GetEntityID() + "Wander");
	ImGui::TextColored(ImVec4(255, 255, 255, 1), "Wander:");
	ImGui::SliderFloat("Weight: ", &m_fWanderWeight, 0, 1);
	ImGui::SliderFloat("Radius: ", &m_fWanderRadius, 0, 200);
	ImGui::SliderFloat("Jitter: ", &m_fWanderJitter, 0, 200);
	ImGui::SliderFloat("Sphere Distance: ", &m_fWanderCircleMultiplier, 0, 200);
	ImGui::PopID();
	ImGui::NewLine();

	ImGui::PushID(pGetOwnerEntity()->GetEntityID() + "Flee");
	ImGui::TextColored(ImVec4(255, 255, 255, 1), "Flee:");
	ImGui::SliderFloat("Weight: ", &m_fFleeWeight, 0, 1);
	// Set target
	ImGui::PopID();
	ImGui::NewLine();

	ImGui::PushID(pGetOwnerEntity()->GetEntityID() + "Evade");
	ImGui::TextColored(ImVec4(255, 255, 255, 1), "Evade:");
	ImGui::SliderFloat("Weight: ", &m_fEvadeWeight, 0, 1);
	ImGui::SliderFloat("Multiplier: ", &m_fEvadeMultiplier, 0, 200);
	// Set target
	ImGui::PopID();
	ImGui::NewLine();

	ImGui::PushID(pGetOwnerEntity()->GetEntityID() + "Pursue");
	ImGui::TextColored(ImVec4(255, 255, 255, 1), "Pursue:");
	ImGui::SliderFloat("Weight: ", &m_fPursueWeight, 0, 1);
	ImGui::SliderFloat("Multiplier: ", &m_fPursueMultiplier, 0, 200);
	// Set target
	ImGui::PopID();
	ImGui::NewLine();

	ImGui::PushID(pGetOwnerEntity()->GetEntityID() + "Separation");
	ImGui::TextColored(ImVec4(255, 255, 255, 1), "Separation:");
	ImGui::SliderFloat("Weight: ", &m_fSeparationWeight, 0, 1);
	ImGui::SliderFloat("Radius: ", &m_fSeparationRadius, 0, 200);
	ImGui::PopID();
	ImGui::NewLine();

	ImGui::PushID(pGetOwnerEntity()->GetEntityID() + "Alignment");
	ImGui::TextColored(ImVec4(255, 255, 255, 1), "Alignment:");
	ImGui::SliderFloat("Weight: ", &m_fAlignmentWeight, 0, 1);
	ImGui::SliderFloat("Radius: ", &m_fAlignmentRadius, 0, 200);
	ImGui::PopID();
	ImGui::NewLine();

	ImGui::PushID(pGetOwnerEntity()->GetEntityID() + "Cohesion");
	ImGui::TextColored(ImVec4(255, 255, 255, 1), "Cohesion:");
	ImGui::SliderFloat("Weight: ", &m_fCohesionWeight, 0, 1);
	ImGui::SliderFloat("Radius: ", &m_fCohesionRadius, 0, 200);
	ImGui::PopID();
	ImGui::NewLine();


}

/// <summary>
/// Gets the speed.
/// </summary>
/// <returns>float.</returns>
float BrainComponent::GetSpeed()
{
	return m_fSpeed;
}

/// <summary>
/// Sets the speed.
/// </summary>
/// <param name="a_newSpeed">a new speed.</param>
void BrainComponent::SetSpeed(float a_newSpeed)
{
	m_fSpeed = a_newSpeed;
}

/// <summary>
/// Gets the current velocity.
/// </summary>
/// <returns>glm.vec3.</returns>
glm::vec3 BrainComponent::GetCurrentVelocity()
{
	return m_v3CurrentVelocity;
}

/// <summary>
/// Sets the behaviour.
/// </summary>
/// <param name="a_type">a type.</param>
void BrainComponent::SetBehaviour(BEHAVIOUR_TYPE a_type)
{
	m_uiIsBehaviour = 1 << (int)a_type;
}

/// <summary>
/// Adds the behaviour.
/// </summary>
/// <param name="a_typeToAdd">a type to add.</param>
void BrainComponent::AddBehaviour(BEHAVIOUR_TYPE a_typeToAdd)
{
	uint8_t mask = 1 << (int)a_typeToAdd;

	m_uiIsBehaviour = m_uiIsBehaviour | mask;
}

/// <summary>
/// Removes the behaviour.
/// </summary>
/// <param name="a_typeToRemove">a type to remove.</param>
void BrainComponent::RemoveBehaviour(BEHAVIOUR_TYPE a_typeToRemove)
{
	uint8_t  mask = 1 << a_typeToRemove; // Make a mask based on bitValue

	m_uiIsBehaviour = m_uiIsBehaviour & (~mask); // Apply to u8 value
}

/// <summary>
/// Clears the behaviours.
/// </summary>
void BrainComponent::ClearBehaviours()
{
	m_uiIsBehaviour = 0;
}

/// <summary>
/// Toggles the behaviour.
/// </summary>
/// <param name="a_behaviourToToggle">a behaviour to toggle.</param>
void BrainComponent::ToggleBehaviour(BEHAVIOUR_TYPE a_behaviourToToggle)
{
	uint8_t mask = (1 << (int)a_behaviourToToggle); // 00000010

	m_uiIsBehaviour = m_uiIsBehaviour & (~mask); // Toggles bits defined by mask
}

/// <summary>
/// Sets the seek target.
/// </summary>
/// <param name="a_entity">a entity.</param>
void BrainComponent::SetSeekTarget(Entity* a_entity)
{
	TransformComponent* pTargetTransformComp = a_entity->pGetRootTransformComp();

	if (!pTargetTransformComp)
	{
		// Target has no transform component!
		std::cout << "No transform comp!" << std::endl; 
		return;
	}

	m_v3SeekTarget = pTargetTransformComp->GetCurrentPosition();
}

/// <summary>
/// Sets the seek target.
/// </summary>
/// <param name="a_newTarget">a new target.</param>
void BrainComponent::SetSeekTarget(glm::vec3 a_newTarget)
{
	m_v3SeekTarget = a_newTarget;
}

/// <summary>
/// Sets the wander radius.
/// </summary>
/// <param name="a_newRadius">a new radius.</param>
void BrainComponent::SetWanderRadius(float a_newRadius)
{
	m_fWanderRadius = a_newRadius;
}

/// <summary>
/// Sets the wander jitter.
/// </summary>
/// <param name="a_newJitter">a new jitter.</param>
void BrainComponent::SetWanderJitter(float a_newJitter)
{
	m_fWanderJitter = a_newJitter;
}

/// <summary>
/// Sets the wander multiplier.
/// </summary>
/// <param name="a_newCircleDistance">a new circle distance.</param>
void BrainComponent::SetWanderMultiplier(float a_newCircleDistance)
{
	m_fWanderCircleMultiplier = a_newCircleDistance;
}

/// <summary>
/// Sets the flee target.
/// </summary>
/// <param name="a_entity">a entity.</param>
void BrainComponent::SetFleeTarget(Entity * a_entity)
{
}

/// <summary>
/// Sets the evade target.
/// </summary>
/// <param name="a_entity">a entity.</param>
void BrainComponent::SetEvadeTarget(Entity* a_entity)
{
	m_EvadeTarget = a_entity;
}

/// <summary>
/// Sets the pursue target.
/// </summary>
/// <param name="a_entity">a entity.</param>
void BrainComponent::SetPursueTarget(Entity * a_entity)
{
	m_PursueTarget = a_entity;
}

/// <summary>
/// Sets the separation radius.
/// </summary>
/// <param name="a_newRadius">a new radius.</param>
void BrainComponent::SetSeparationRadius(float a_newRadius)
{
	m_fSeparationRadius = a_newRadius;
}

/// <summary>
/// Sets the alignment radius.
/// </summary>
/// <param name="a_newRadius">a new radius.</param>
void BrainComponent::SetAlignmentRadius(float a_newRadius)
{
	m_fAlignmentRadius = a_newRadius;
}

/// <summary>
/// Sets the cohesion radius.
/// </summary>
/// <param name="a_newRadius">a new radius.</param>
void BrainComponent::SetCohesionRadius(float a_newRadius)
{
	m_fCohesionRadius = a_newRadius;
}

/// <summary>
/// Calculates the seek force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <returns>glm.vec3.</returns>
glm::vec3 BrainComponent::CalculateSeekForce(glm::vec3 a_v3CurrentPos)
{
	glm::vec3 v3TargetDir = glm::normalize(m_v3SeekTarget - a_v3CurrentPos); // (Target - current).normalized = direction
	glm::vec3 v3Velocity = v3TargetDir * m_fSpeed; // Create a velocity with direction and speed
	glm::vec3 v3Force = v3Velocity - m_v3CurrentVelocity; // Apply a change (Don't snap to this new velocity)

	if (m_bDebugLogging)
	{
		std::cout << "Entity: " << this->pGetOwnerEntity()->GetEntityID() << " is Seeking location x:" << m_v3SeekTarget.x << " y:" << m_v3SeekTarget.y << " z:" << m_v3SeekTarget.z << std::endl;
	}

	if (m_bDebugGizmos)
	{
		Gizmos::addCircle(m_v3SeekTarget, 2.0f, 16.0f, false, glm::vec4(0.f, 0.8f, 0.3f, 1.f));
		Gizmos::addLine(a_v3CurrentPos, m_v3SeekTarget, glm::vec4(0.0f, 0.8f, 0.3f, 1.0f));
	}

	return v3Force;
}

/// <summary>
/// Calculates the seek force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <param name="a_v3Target">a v3 target.</param>
/// <returns>glm.vec3.</returns>
glm::vec3 BrainComponent::CalculateSeekForce(glm::vec3 a_v3CurrentPos, glm::vec3 a_v3Target)
{
	glm::vec3 v3TargetDir = glm::normalize(a_v3Target - a_v3CurrentPos); // (Target - current).normalized = direction
	glm::vec3 v3Velocity = v3TargetDir * m_fSpeed; // Create a velocity with direction and speed
	glm::vec3 v3Force = v3Velocity - m_v3CurrentVelocity; // Apply a change (Don't snap to this new velocity)


	if (m_bDebugLogging)
	{
		std::cout << "Entity: " << this->pGetOwnerEntity()->GetEntityID() << " is Seeking location x:" << a_v3Target.x << " y:" << a_v3Target.y << " z:" << a_v3Target.z << std::endl;

	}

	if (m_bDebugGizmos)
	{
		Gizmos::addCircle(a_v3Target, 2.0f, 16.0f, false, glm::vec4(0.f, 0.8f, 0.3f, 1.f));
		Gizmos::addLine(a_v3CurrentPos, a_v3Target, glm::vec4(0.0f, 0.8f, 0.3f, 1.0f));
	}

	return v3Force;
}

/// <summary>
/// Calculates the wander force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <param name="a_v3CurrentForward">a v3 current forward.</param>
/// <returns>glm.vec3.</returns>
glm::vec3 BrainComponent::CalculateWanderForce(glm::vec3 a_v3CurrentPos, glm::vec3 a_v3CurrentForward)
{
	glm::vec3 v3WanderSphereOrigin = a_v3CurrentPos + (a_v3CurrentForward * m_fWanderCircleMultiplier); // Locate the origin of the sphere in front of the agent
	glm::vec3 v3RandPoint = glm::sphericalRand(m_fWanderRadius); // Get a random point in a sphere from origin of defined size
	glm::vec3 v3RandPointInSphere = v3WanderSphereOrigin + glm::vec3(v3RandPoint.x, v3RandPoint.y, v3RandPoint.z); // Transulate the RandomSphere point to a world position local to the agent

	// Get a new random position in sphere with the jitter mod
	v3RandPoint = glm::sphericalRand(m_fWanderJitter); 

	// Apply the jitter to the random point in local sphere
	glm::vec3 v3RandTarget = v3RandPointInSphere + glm::vec3(v3RandPoint.x, v3RandPoint.y, v3RandPoint.z); 

	// Set new target (Don't understand this math)
	glm::vec3 v3Target = v3WanderSphereOrigin + (glm::normalize(v3RandTarget - v3WanderSphereOrigin) * m_fWanderRadius); 


	glm::vec3 v3TargetDir = glm::normalize(v3Target - a_v3CurrentPos);
	glm::vec3 v3Velocity = v3TargetDir * m_fSpeed;
	glm::vec3 v3Force = v3Velocity - m_v3CurrentVelocity;


	if (m_bDebugLogging)
	{
		std::cout << "Entity: " << this->pGetOwnerEntity()->GetEntityID() << " is Wandering to location x:" << v3Target.x << " y:" << v3Target.y << " z:" << v3Target.z << std::endl;

	}

	if (m_bDebugGizmos)
	{
		Gizmos::addCircle(v3WanderSphereOrigin, 2, 16, false, glm::vec4(0.0f, 0.8f, 0.3f, 1.0f));
		Gizmos::addLine(a_v3CurrentPos, v3Target, glm::vec4(0.0f, 0.8f, 0.3f, 1.0f));
	}

	return v3Force;
}

/// <summary>
/// Calculates the flee force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <returns>glm.vec3.</returns>
glm::vec3 BrainComponent::CalculateFleeForce(glm::vec3 a_v3CurrentPos)
{
	glm::vec3 v3TargetDir = glm::normalize(m_v3FleeTarget - a_v3CurrentPos); // (Target - current).normalized = direction
	glm::vec3 v3Velocity = v3TargetDir * m_fSpeed; // Create a velocity with direction and speed
	glm::vec3 v3Force = -(v3Velocity - m_v3CurrentVelocity); // Apply a change (Don't snap to this new velocity)


	if (m_bDebugLogging)
	{
		std::cout << "Entity: " << this->pGetOwnerEntity()->GetEntityID() << " is Fleeing from location x:" << m_v3FleeTarget.x << " y:" << m_v3FleeTarget.y << " z:" << m_v3FleeTarget.z << std::endl;

	}

	if (m_bDebugGizmos)
	{
		Gizmos::addCircle(m_v3FleeTarget, 2.0f, 16.0f, false, glm::vec4(0.f, 0.8f, 0.3f, 1.f));
		Gizmos::addLine(a_v3CurrentPos, m_v3FleeTarget, glm::vec4(0.0f, 0.8f, 0.3f, 1.0f));
	}

	return v3Force;
}

/// <summary>
/// Calculates the flee force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <param name="a_v3Target">a v3 target.</param>
/// <returns>glm.vec3.</returns>
glm::vec3 BrainComponent::CalculateFleeForce(glm::vec3 a_v3CurrentPos, glm::vec3 a_v3Target)
{
	glm::vec3 v3TargetDir = glm::normalize(a_v3Target - a_v3CurrentPos); // (Target - current).normalized = direction
	glm::vec3 v3Velocity = v3TargetDir * m_fSpeed; // Create a velocity with direction and speed
	glm::vec3 v3Force = -(v3Velocity - m_v3CurrentVelocity); // Apply a change (Don't snap to this new velocity)


	if (m_bDebugLogging)
	{
		std::cout << "Entity: " << this->pGetOwnerEntity()->GetEntityID() << " is Fleeing from location x:" << a_v3Target.x << " y:" << a_v3Target.y << " z:" << a_v3Target.z << std::endl;
	}

	if (m_bDebugGizmos)
	{
		Gizmos::addCircle(a_v3Target, 2.0f, 16.0f, false, glm::vec4(0.f, 0.8f, 0.3f, 1.f));
		Gizmos::addLine(a_v3CurrentPos, a_v3Target, glm::vec4(0.0f, 0.8f, 0.3f, 1.0f));
	}

	return v3Force;
}

/// <summary>
/// Calculates the evade force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <param name="a_v3CurrentForward">a v3 current forward.</param>
/// <returns>glm.vec3.</returns>
glm::vec3 BrainComponent::CalculateEvadeForce(glm::vec3 a_v3CurrentPos, glm::vec3 a_v3CurrentForward)
{
	glm::vec3 v3EvadeTarget;

	TransformComponent* pTargetTransfomComp = m_EvadeTarget->pGetRootTransformComp(); // Get the targets transform component
	BrainComponent* pTargetBrainComp = static_cast<BrainComponent*>(m_EvadeTarget->FindComponentOfType(BRAIN)); // Get the targets brain component

	// Test validity
	if (!pTargetTransfomComp)
	{
		// Target has no transform comp!
		if (m_bDebugLogging)
		{
			std::cout << "Entity: " << m_EvadeTarget->GetEntityID() << " has no Transform Component!" << std::endl;
		}
		return glm::vec3(); 
	}
	if (!pTargetBrainComp)
	{
		// No speed found
		if (m_bDebugLogging)
		{
			std::cout << "Entity: " << m_EvadeTarget->GetEntityID() << " has no Brain Component!" << std::endl;

		}
		return glm::vec3();
	}

	// Calculate where the target is going to be
	v3EvadeTarget = pTargetTransfomComp->GetCurrentPosition() + ((pTargetTransfomComp->GetFacingDirection() * pTargetBrainComp->m_fSpeed) * m_fEvadeMultiplier);


	glm::vec3 v3TargetDir = glm::normalize(v3EvadeTarget - a_v3CurrentPos); // (Target - current).normalized = direction
	glm::vec3 v3Velocity = v3TargetDir * m_fSpeed; // Create a velocity with direction and speed
	glm::vec3 v3Force = -(v3Velocity - m_v3CurrentVelocity); // Apply a change (Don't snap to this new velocity)

	if (m_bDebugLogging)
	{
		std::cout << "Entity: " << this->pGetOwnerEntity()->GetEntityID() << " is Evading Entity: " << m_EvadeTarget->GetEntityID() << std::endl;

	}

	if (m_bDebugGizmos)
	{
		Gizmos::addCircle(v3EvadeTarget, 2.0f, 16.0f, false, glm::vec4(0.f, 0.8f, 0.3f, 1.f));
		Gizmos::addLine(a_v3CurrentPos, v3EvadeTarget, glm::vec4(0.0f, 0.8f, 0.3f, 1.0f));
	}

	return v3Force;
}

/// <summary>
/// Calculates the pursue force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <param name="a_v3CurrentForward">a v3 current forward.</param>
/// <returns>glm.vec3.</returns>
glm::vec3 BrainComponent::CalculatePursueForce(glm::vec3 a_v3CurrentPos, glm::vec3 a_v3CurrentForward)
{
	glm::vec3 v3PursueTarget;

	TransformComponent* pTargetTransfomComp = m_PursueTarget->pGetRootTransformComp(); // Get the targets transform component
	BrainComponent* pTargetBrainComp = static_cast<BrainComponent*>(m_PursueTarget->FindComponentOfType(BRAIN)); // Get the targets brain component

	// Test validity
	if (!pTargetTransfomComp)
	{
		// Target has no transform comp!
		if (m_bDebugLogging)
		{
			std::cout << "Entity: " << m_EvadeTarget->GetEntityID() << " has no Transform Component!" << std::endl;
		}
		return glm::vec3();
	}
	if (!pTargetBrainComp)
	{
		// No speed found
		if (m_bDebugLogging)
		{
			std::cout << "Entity: " << m_EvadeTarget->GetEntityID() << " has no Brain Component!" << std::endl;
		}
		return glm::vec3();
	}

	// Calculate where the target is going to be
	v3PursueTarget = pTargetTransfomComp->GetCurrentPosition() + ((pTargetTransfomComp->GetFacingDirection() * pTargetBrainComp->m_fSpeed) * m_fPursueMultiplier);


	glm::vec3 v3TargetDir = glm::normalize(v3PursueTarget - a_v3CurrentPos); // (Target - current).normalized = direction
	glm::vec3 v3Velocity = (v3TargetDir * m_fSpeed) * m_fSeekWeight; // Create a velocity with direction and speed and modify its "intensity" with it's weight
	glm::vec3 v3Force = v3Velocity - m_v3CurrentVelocity; // Apply a change (Don't snap to this new velocity)


	if (m_bDebugLogging)
	{
		std::cout << "Entity: " << this->pGetOwnerEntity()->GetEntityID() << " is Pursuing Entity: " << m_PursueTarget->GetEntityID() << std::endl;
	}

	if (m_bDebugGizmos)
	{
		Gizmos::addCircle(v3PursueTarget, 2.0f, 16.0f, false, glm::vec4(0.8f, 0.4f, 0.3f, 1.f));
		Gizmos::addLine(a_v3CurrentPos, v3PursueTarget, glm::vec4(0.8f, 0.4f, 0.3f, 1.0f));
	}

	return v3Force;
}

/// <summary>
/// Calculates the separation force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <returns>glm.vec3.</returns>
glm::vec3 BrainComponent::CalculateSeparationForce(glm::vec3 a_v3CurrentPos)
{
	glm::vec3 v3Force;

	const std::map<const unsigned int, Entity*>&xEntityMap = Entity::GetEntityMap();
	std::map<const unsigned int, Entity*>::const_iterator xIter;

	for (xIter = xEntityMap.begin(); xIter != xEntityMap.end(); ++xIter)
	{
		Entity* pTarget = xIter->second;

		if (pTarget && pTarget->GetEntityID() != pGetOwnerEntity()->GetEntityID())
		{
			TransformComponent* pTargetTransfrom = pTarget->pGetRootTransformComp();
			BoxColliderComponent* pTargetBox = (BoxColliderComponent*)pTarget->FindComponentOfType(BOXCOLLIDER);


			if (pTargetBox != nullptr)
			{
				if (pTargetBox->IsContainer())
				{
					float fDistanceBetween = glm::length(a_v3CurrentPos - glm::vec3(pTargetTransfrom->GetCurrentPosition().x + (pTargetBox->GetDimentions()->x * 0.5), a_v3CurrentPos.y, a_v3CurrentPos.z));

					if (fDistanceBetween < m_fSeparationRadius)
					{
						v3Force += CalculateFleeForce(a_v3CurrentPos, glm::vec3((pTargetTransfrom->GetCurrentPosition().x + (pTargetBox->GetDimentions()->x * 0.5)), a_v3CurrentPos.y, a_v3CurrentPos.z));
					}

					fDistanceBetween = glm::length(a_v3CurrentPos - glm::vec3(pTargetTransfrom->GetCurrentPosition().x - (pTargetBox->GetDimentions()->x * 0.5), a_v3CurrentPos.y, a_v3CurrentPos.z));

					if (fDistanceBetween < (m_fSeparationRadius))
					{
						v3Force += CalculateFleeForce(a_v3CurrentPos, glm::vec3((pTargetTransfrom->GetCurrentPosition().x - (pTargetBox->GetDimentions()->x * 0.5)), a_v3CurrentPos.y, a_v3CurrentPos.z));
					}

					fDistanceBetween = glm::length(a_v3CurrentPos - glm::vec3(a_v3CurrentPos.x, pTargetTransfrom->GetCurrentPosition().y + (pTargetBox->GetDimentions()->y * 0.5), a_v3CurrentPos.z));

					if (fDistanceBetween < (m_fSeparationRadius))
					{
						v3Force += CalculateFleeForce(a_v3CurrentPos, glm::vec3(a_v3CurrentPos.x, (pTargetTransfrom->GetCurrentPosition().y + (pTargetBox->GetDimentions()->y * 0.5)), a_v3CurrentPos.z));
					}

					fDistanceBetween = glm::length(a_v3CurrentPos - glm::vec3(a_v3CurrentPos.x, pTargetTransfrom->GetCurrentPosition().y - (pTargetBox->GetDimentions()->y * 0.5), a_v3CurrentPos.z));

					if (fDistanceBetween < (m_fSeparationRadius))
					{
						v3Force += CalculateFleeForce(a_v3CurrentPos, glm::vec3(a_v3CurrentPos.x, (pTargetTransfrom->GetCurrentPosition().y - (pTargetBox->GetDimentions()->y * 0.5)), a_v3CurrentPos.z));
					}

					fDistanceBetween = glm::length(a_v3CurrentPos - glm::vec3(a_v3CurrentPos.x, a_v3CurrentPos.y, pTargetTransfrom->GetCurrentPosition().z + (pTargetBox->GetDimentions()->z * 0.5)));

					if (fDistanceBetween < (m_fSeparationRadius))
					{
						v3Force += CalculateFleeForce(a_v3CurrentPos, glm::vec3(a_v3CurrentPos.x, a_v3CurrentPos.y, (pTargetTransfrom->GetCurrentPosition().z + (pTargetBox->GetDimentions()->z * 0.5))));
					}

					fDistanceBetween = glm::length(a_v3CurrentPos - glm::vec3(a_v3CurrentPos.x, a_v3CurrentPos.y, pTargetTransfrom->GetCurrentPosition().z - (pTargetBox->GetDimentions()->z * 0.5)));

					if (fDistanceBetween < (m_fSeparationRadius))
					{
						v3Force += CalculateFleeForce(a_v3CurrentPos, glm::vec3(a_v3CurrentPos.x, a_v3CurrentPos.y, (pTargetTransfrom->GetCurrentPosition().z - (pTargetBox->GetDimentions()->z * 0.5))));
					}

					if (glm::length(v3Force) > 0)
					{
						v3Force = glm::normalize(v3Force);
					}
					
					
				}
			}
			else
			{

				glm::vec3 v3TargetPos = pTargetTransfrom->GetCurrentPosition();
				float fDistanceBetween = glm::length(a_v3CurrentPos - v3TargetPos);

				if (fDistanceBetween < m_fSeparationRadius)
				{
					v3Force += CalculateFleeForce(a_v3CurrentPos, v3TargetPos);

				}
			}
		}
	}

	if (m_bDebugGizmos)
	{
		Gizmos::addCircle(a_v3CurrentPos, m_fSeparationRadius, 16.0f, false, glm::vec4(0.8f, 0.f, 0.3f, 1.f));

	}


	return v3Force;
}

/// <summary>
/// Calculates the alignment force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <returns>glm.vec3.</returns>
glm::vec3 BrainComponent::CalculateAlignmentForce(glm::vec3 a_v3CurrentPos)
{
	glm::vec3 v3AverageVelocity;
	glm::vec3 v3Force = glm::vec3();

	const std::map<const unsigned int, Entity*>&xEntityMap = Entity::GetEntityMap();
	std::map<const unsigned int, Entity*>::const_iterator xIter;

	m_iAlignmentNeighbourCount = 0;
	for (xIter = xEntityMap.begin(); xIter != xEntityMap.end(); ++xIter)
	{
		Entity* pTarget = xIter->second;

		if (pTarget && pTarget->GetEntityID() != pGetOwnerEntity()->GetEntityID()) // If valid and not equal to self
		{
			TransformComponent* pTargetTransfrom = pTarget->pGetRootTransformComp();
			BrainComponent* pTargetBrain = static_cast<BrainComponent*>(pTarget->FindComponentOfType(BRAIN));

			// Test validity
			if (!pTargetTransfrom)
			{
				// Target has no transform comp!
				if (m_bDebugLogging)
				{
					std::cout << "Entity: " << pTarget->GetEntityID() << " has no Transform Component!" << std::endl;
				}
				return glm::vec3();
			}
			if (!pTargetBrain)
			{
				// Target has no brain comp!
				if (m_bDebugLogging)
				{
					std::cout << "Entity: " << pTarget->GetEntityID() << " has no Brain Component!" << std::endl;

				}
				return glm::vec3();
			}

			glm::vec3 v3TargetPos = pTargetTransfrom->GetCurrentPosition();
			float fDistanceBetween = glm::length(a_v3CurrentPos - v3TargetPos);

			if (fDistanceBetween < m_fAlignmentRadius)
			{
				v3AverageVelocity += pTargetBrain->GetCurrentVelocity();
				m_iAlignmentNeighbourCount++;
			}
		}
	}

	if (glm::length(v3AverageVelocity) > 0)
	{
		v3AverageVelocity /= m_iAlignmentNeighbourCount;
		v3Force = glm::normalize(v3AverageVelocity - m_v3CurrentVelocity);
	}


	if (m_bDebugGizmos)
	{
		Gizmos::addCircle(a_v3CurrentPos, m_fAlignmentRadius, 16.0f, false, glm::vec4(0.f, 0.2f, 0.8f, 1.f));

	}

	if (m_bDebugLogging)
	{
		std::cout << "Force: x:" << v3Force.x << " y: " << v3Force.y << " z: " << v3Force.z << std::endl;
	}
	return v3Force;
}

/// <summary>
/// Calculates the cohesion force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <returns>glm.vec3.</returns>
glm::vec3 BrainComponent::CalculateCohesionForce(glm::vec3 a_v3CurrentPos)
{
	glm::vec3 v3AveragePosition;
	glm::vec3 v3Force = glm::vec3();

	const std::map<const unsigned int, Entity*>&xEntityMap = Entity::GetEntityMap();
	std::map<const unsigned int, Entity*>::const_iterator xIter;

	m_iCohesionNeighbourCount = 0;
	for (xIter = xEntityMap.begin(); xIter != xEntityMap.end(); ++xIter)
	{
		Entity* pTarget = xIter->second;

		if (pTarget && pTarget->GetEntityID() != pGetOwnerEntity()->GetEntityID())
		{
			TransformComponent* pTargetTransfrom = pTarget->pGetRootTransformComp();

			// Test validity
			if (!pTargetTransfrom)
			{
				// Target has no transform comp!
				if (m_bDebugLogging)
				{
					std::cout << "Entity: " << pTarget->GetEntityID() << " has no Transform Component!" << std::endl;
				}
				return glm::vec3();
			}

			glm::vec3 v3TargetPos = pTargetTransfrom->GetCurrentPosition();
			float fDistanceBetween = glm::length(a_v3CurrentPos - v3TargetPos);

			if (fDistanceBetween < m_fCohesionRadius)
			{
				v3AveragePosition += pTargetTransfrom->GetCurrentPosition();
				m_iCohesionNeighbourCount++;
			}
		}
	}

	if (glm::length(v3AveragePosition) > 0)
	{
		v3AveragePosition /= m_iCohesionNeighbourCount;
		v3Force = glm::normalize(v3AveragePosition - a_v3CurrentPos);
	}


	if (m_bDebugGizmos)
	{
		Gizmos::addCircle(a_v3CurrentPos, m_fCohesionRadius, 16.0f, false, glm::vec4(0.f, 0.8f, 0.3f, 1.f));
	}

	if (m_bDebugLogging)
	{
		std::cout << "Force: x:" << v3Force.x << " y: " << v3Force.y << " z: " << v3Force.z << std::endl;
	}
	return v3Force;
}







