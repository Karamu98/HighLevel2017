// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="BrainComponent.h" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef _BRAIN_COMPONENT_H__
#define _BRAIN_COMPONENT_H__

//includes
#include "glm/glm.hpp"
#include "Component.h"

/// <summary>
/// Enum BEHAVIOUR_TYPE
/// </summary>
enum BEHAVIOUR_TYPE
{
	/// <summary>
	/// The seek
	/// </summary>
	SEEK, // 1 (No bitshift)
/// <summary>
/// The wander
/// </summary>
WANDER, // 2 (Bitshift 1)
/// <summary>
/// The flee
/// </summary>
FLEE, // 4 (Bitshift 2)
/// <summary>
/// The evade
/// </summary>
EVADE, // 8 (Bitshift 3)
/// <summary>
/// The pursue
/// </summary>
PURSUE, // 16 (Bitshift 4)
/// <summary>
/// The separation
/// </summary>
SEPARATION, // 32 (Bitshift 5)
/// <summary>
/// The alignment
/// </summary>
ALIGNMENT, // 64 (Bitshift 6)
/// <summary>
/// The cohesion
/// </summary>
COHESION, // 128 (Bitshift 7)
/// <summary>
/// The none
/// </summary>
NONE
};

class Entity;

/// <summary>
/// Class BrainComponent.
/// </summary>
/// <seealso cref="Component" />
class BrainComponent : public Component
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="BrainComponent"/> class.
	/// </summary>
	/// <param name="pOwnerEntity">The p owner entity.</param>
	BrainComponent(Entity* pOwnerEntity);
	/// <summary>
	/// Finalizes an instance of the <see cref="BrainComponent"/> class.
	/// </summary>
	~BrainComponent();

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

	/// <summary>
	/// Gets the speed.
	/// </summary>
	/// <returns>float.</returns>
	float GetSpeed();
	/// <summary>
	/// Sets the speed.
	/// </summary>
	/// <param name="a_newSpeed">a new speed.</param>
	void SetSpeed(float a_newSpeed);

	/// <summary>
	/// Gets the current velocity.
	/// </summary>
	/// <returns>glm.vec3.</returns>
	glm::vec3 GetCurrentVelocity();

	/// <summary>
	/// Sets the behaviour.
	/// </summary>
	/// <param name="a_type">a type.</param>
	void SetBehaviour(BEHAVIOUR_TYPE a_type);
	/// <summary>
	/// Adds the behaviour.
	/// </summary>
	/// <param name="a_typeToAdd">a type to add.</param>
	void AddBehaviour(BEHAVIOUR_TYPE a_typeToAdd);
	/// <summary>
	/// Removes the behaviour.
	/// </summary>
	/// <param name="a_typeToRemove">a type to remove.</param>
	void RemoveBehaviour(BEHAVIOUR_TYPE a_typeToRemove);
	/// <summary>
	/// Clears the behaviours.
	/// </summary>
	void ClearBehaviours();

	// Universal Functions
/// <summary>
/// Toggles the behaviour.
/// </summary>
/// <param name="a_behaviourToToggle">a behaviour to toggle.</param>
	void ToggleBehaviour(BEHAVIOUR_TYPE a_behaviourToToggle);

	// Seek Functions
/// <summary>
/// Sets the seek target.
/// </summary>
/// <param name="a_entity">a entity.</param>
	void SetSeekTarget(Entity* a_entity);
	/// <summary>
	/// Sets the seek target.
	/// </summary>
	/// <param name="a_newTarget">a new target.</param>
	void SetSeekTarget(glm::vec3 a_newTarget);

	// Wander Functions
/// <summary>
/// Sets the wander radius.
/// </summary>
/// <param name="a_newRadius">a new radius.</param>
	void SetWanderRadius(float a_newRadius);
	/// <summary>
	/// Sets the wander jitter.
	/// </summary>
	/// <param name="a_newJitter">a new jitter.</param>
	void SetWanderJitter(float a_newJitter);
	/// <summary>
	/// Sets the wander multiplier.
	/// </summary>
	/// <param name="a_newCircleDistance">a new circle distance.</param>
	void SetWanderMultiplier(float a_newCircleDistance);

	// Flee Functions
/// <summary>
/// Sets the flee target.
/// </summary>
/// <param name="a_entity">a entity.</param>
	void SetFleeTarget(Entity* a_entity);

	// Evade Functions
/// <summary>
/// Sets the evade target.
/// </summary>
/// <param name="a_entity">a entity.</param>
	void SetEvadeTarget(Entity* a_entity);

	// Pursue Functions
/// <summary>
/// Sets the pursue target.
/// </summary>
/// <param name="a_entity">a entity.</param>
	void SetPursueTarget(Entity* a_entity);

	// Separation Functions
/// <summary>
/// Sets the separation radius.
/// </summary>
/// <param name="a_newRadius">a new radius.</param>
	void SetSeparationRadius(float a_newRadius);

	// Alignment Functions
/// <summary>
/// Sets the alignment radius.
/// </summary>
/// <param name="a_newRadius">a new radius.</param>
	void SetAlignmentRadius(float a_newRadius);

	// Cohesion Functions
/// <summary>
/// Sets the cohesion radius.
/// </summary>
/// <param name="a_newRadius">a new radius.</param>
	void SetCohesionRadius(float a_newRadius);


private:

	// Basic 
/// <summary>
/// Calculates the seek force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <returns>glm.vec3.</returns>
	glm::vec3 CalculateSeekForce(glm::vec3 a_v3CurrentPos);
	/// <summary>
	/// Calculates the seek force.
	/// </summary>
	/// <param name="a_v3CurrentPos">a v3 current position.</param>
	/// <param name="a_v3Target">a v3 target.</param>
	/// <returns>glm.vec3.</returns>
	glm::vec3 CalculateSeekForce(glm::vec3 a_v3CurrentPos, glm::vec3 a_v3Target);
	/// <summary>
	/// Calculates the wander force.
	/// </summary>
	/// <param name="a_v3CurrentPos">a v3 current position.</param>
	/// <param name="a_v3CurrentForward">a v3 current forward.</param>
	/// <returns>glm.vec3.</returns>
	glm::vec3 CalculateWanderForce(glm::vec3 a_v3CurrentPos, glm::vec3 a_v3CurrentForward);
	/// <summary>
	/// Calculates the flee force.
	/// </summary>
	/// <param name="a_v3CurrentPos">a v3 current position.</param>
	/// <returns>glm.vec3.</returns>
	glm::vec3 CalculateFleeForce(glm::vec3 a_v3CurrentPos);
	/// <summary>
	/// Calculates the flee force.
	/// </summary>
	/// <param name="a_v3CurrentPos">a v3 current position.</param>
	/// <param name="a_v3Target">a v3 target.</param>
	/// <returns>glm.vec3.</returns>
	glm::vec3 CalculateFleeForce(glm::vec3 a_v3CurrentPos, glm::vec3 a_v3Target);

	// Intermediate
/// <summary>
/// Calculates the evade force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <param name="a_v3CurrentForward">a v3 current forward.</param>
/// <returns>glm.vec3.</returns>
	glm::vec3 CalculateEvadeForce(glm::vec3 a_v3CurrentPos, glm::vec3 a_v3CurrentForward);
	/// <summary>
	/// Calculates the pursue force.
	/// </summary>
	/// <param name="a_v3CurrentPos">a v3 current position.</param>
	/// <param name="a_v3CurrentForward">a v3 current forward.</param>
	/// <returns>glm.vec3.</returns>
	glm::vec3 CalculatePursueForce(glm::vec3 a_v3CurrentPos, glm::vec3 a_v3CurrentForward);

	// Flocking
/// <summary>
/// Calculates the separation force.
/// </summary>
/// <param name="a_v3CurrentPos">a v3 current position.</param>
/// <returns>glm.vec3.</returns>
	glm::vec3 CalculateSeparationForce(glm::vec3 a_v3CurrentPos);
	/// <summary>
	/// Calculates the separation force.
	/// </summary>
	/// <param name="a_v3CurrentPos">a v3 current position.</param>
	/// <param name="a_v3TargetPos">a v3 target position.</param>
	/// <returns>glm.vec3.</returns>
	glm::vec3 CalculateSeparationForce(glm::vec3 a_v3CurrentPos, glm::vec3 a_v3TargetPos);
	/// <summary>
	/// Calculates the alignment force.
	/// </summary>
	/// <param name="a_v3CurrentPos">a v3 current position.</param>
	/// <returns>glm.vec3.</returns>
	glm::vec3 CalculateAlignmentForce(glm::vec3 a_v3CurrentPos);
	/// <summary>
	/// Calculates the cohesion force.
	/// </summary>
	/// <param name="a_v3CurrentPos">a v3 current position.</param>
	/// <returns>glm.vec3.</returns>
	glm::vec3 CalculateCohesionForce(glm::vec3 a_v3CurrentPos);



	/// <summary>
	/// The m f speed
	/// </summary>
	float m_fSpeed;
	/// <summary>
	/// The m v3 current velocity
	/// </summary>
	glm::vec3 m_v3CurrentVelocity;

	// Seek Variables
/// <summary>
/// The m f seek weight
/// </summary>
	float m_fSeekWeight;
	/// <summary>
	/// The m v3 seek target
	/// </summary>
	glm::vec3 m_v3SeekTarget;

	// Wander Variables
/// <summary>
/// The m f wander weight
/// </summary>
	float m_fWanderWeight; // How much this behaviour effects the final position of the agent
/// <summary>
/// The m f wander radius
/// </summary>
	float m_fWanderRadius; // The radius of the wander circle
/// <summary>
/// The m f wander jitter
/// </summary>
	float m_fWanderJitter; // Controls the jitter of the agent
/// <summary>
/// The m f wander circle multiplier
/// </summary>
	float m_fWanderCircleMultiplier; // How far "in front" the circle is

	// Flee Variables
/// <summary>
/// The m f flee weight
/// </summary>
	float m_fFleeWeight;
	/// <summary>
	/// The m v3 flee target
	/// </summary>
	glm::vec3 m_v3FleeTarget;

	// Evade Variables
/// <summary>
/// The m f evade weight
/// </summary>
	float m_fEvadeWeight;
	/// <summary>
	/// The m f evade multiplier
	/// </summary>
	float m_fEvadeMultiplier;
	/// <summary>
	/// The m evade target
	/// </summary>
	Entity* m_EvadeTarget;

	// Pursue Variables
/// <summary>
/// The m f pursue weight
/// </summary>
	float m_fPursueWeight;
	/// <summary>
	/// The m f pursue multiplier
	/// </summary>
	float m_fPursueMultiplier;
	/// <summary>
	/// The m pursue target
	/// </summary>
	Entity* m_PursueTarget;

	// Separation Variables
/// <summary>
/// The m f separation weight
/// </summary>
	float m_fSeparationWeight;
	/// <summary>
	/// The m f separation radius
	/// </summary>
	float m_fSeparationRadius;

	// Alignment Variables
/// <summary>
/// The m f alignment weight
/// </summary>
	float m_fAlignmentWeight;
	/// <summary>
	/// The m f alignment radius
	/// </summary>
	float m_fAlignmentRadius;
	/// <summary>
	/// The m i alignment neighbour count
	/// </summary>
	int m_iAlignmentNeighbourCount;

	// Cohesion Variables
/// <summary>
/// The m f cohesion weight
/// </summary>
	float m_fCohesionWeight;
	/// <summary>
	/// The m f cohesion radius
	/// </summary>
	float m_fCohesionRadius;
	/// <summary>
	/// The m i cohesion neighbour count
	/// </summary>
	int m_iCohesionNeighbourCount;
	
	/// <summary>
	/// The m UI is behaviour
	/// </summary>
	uint8_t m_uiIsBehaviour; // Using a 8 bit integer to store boolean values (Because I think this is fun!) booleans are found in same order as BEHAVIOUR_TYPE excluding NONE


	// Debug
/// <summary>
/// The m b debug logging
/// </summary>
	bool m_bDebugLogging = false;
	/// <summary>
	/// The m b debug gizmos
	/// </summary>
	bool m_bDebugGizmos = true;
};

#endif