// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Player.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Player.h"
#include "Utilities.h"
#include "TransformComponent.h"
#include "CameraComponent.h"

#include "imgui.h"

typedef Entity PARENT;


/// <summary>
/// Initializes a new instance of the <see cref="Player"/> class.
/// </summary>
Player::Player() : m_fScale(0.1f)
{
	//Add new components to the component list
	AddComponent(new CameraComponent(this));

	pCameraComp = (CameraComponent*)(this->FindComponentOfType(CAMERA));

	pCameraComp->SetPossesed(true);
	pCameraComp->m_bActive = true;

	SetName(std::string("Player ") += std::to_string(GetEntityID()));
}

/// <summary>
/// Finalizes an instance of the <see cref="Player"/> class.
/// </summary>
Player::~Player()
{
}


/// <summary>
/// Updates the specified a f delta time.
/// </summary>
/// <param name="a_fDeltaTime">a f delta time.</param>
void Player::Update(float a_fDeltaTime)
{
	PARENT::Update(a_fDeltaTime);
}

/// <summary>
/// Draws the specified a UI program identifier.
/// </summary>
/// <param name="a_uiProgramID">a UI program identifier.</param>
/// <param name="a_uiVBO">a UI vbo.</param>
/// <param name="a_uiIBO">a UI ibo.</param>
void Player::Draw(unsigned int a_uiProgramID, unsigned int a_uiVBO, unsigned int a_uiIBO)
{
	PARENT::Draw(a_uiProgramID, a_uiVBO, a_uiIBO);
}

