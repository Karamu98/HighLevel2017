// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Player.h" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef _PLAYER_H__
#define _PLAYER_H__



// Includes
#include "Entity.h"

// Forward Declarations
class CameraComponent;

/// <summary>
/// Class Player.
/// </summary>
/// <seealso cref="Entity" />
class Player : public Entity
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Player"/> class.
	/// </summary>
	Player();
	/// <summary>
	/// Finalizes an instance of the <see cref="Player"/> class.
	/// </summary>
	~Player();
	//Override update function hence why its virtual - as it inherits from entity

/// <summary>
/// Updates the specified a f delta time.
/// </summary>
/// <param name="a_fDeltaTime">a f delta time.</param>
	virtual void Update(float a_fDeltaTime);
	/// <summary>
	/// Draws the specified a UI program identifier.
	/// </summary>
	/// <param name="a_uiProgramID">a UI program identifier.</param>
	/// <param name="a_uiVBO">a UI vbo.</param>
	/// <param name="a_uiIBO">a UI ibo.</param>
	void Draw(unsigned int a_uiProgramID, unsigned int a_uiVBO, unsigned int a_uiIBO);


protected:
	/// <summary>
	/// The m f scale
	/// </summary>
	float m_fScale;

private:

	/// <summary>
	/// The p camera comp
	/// </summary>
	CameraComponent* pCameraComp;

};
#endif // !_Player_H__