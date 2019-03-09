// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="main.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Constants.h"

#include "Game.h"

/// <summary>
/// The m instance{CC2D43FA-BBC4-448A-9D0B-7B57ADF2655C}
/// </summary>
Game* Game::m_instance = 0;

// main that controls the creation/destruction of an application
/// <summary>
/// Mains this instance.
/// </summary>
/// <returns>int.</returns>
int main()
{
	// explicitly control the creation of our application
	Game* game = Game::pGetGame();
	game->run("Game", g_uiDEFAULT_SCREENWIDTH, g_uiDEFAULT_SCREENHEIGHT, false);

	// explicitly control the destruction of our application
	delete game;

	return 0;
}