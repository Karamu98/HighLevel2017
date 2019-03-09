// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Constants.h" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

//Screen
/// <summary>
/// The g UI default screenwidth
/// </summary>
static const unsigned int g_uiDEFAULT_SCREENWIDTH = 1280;
/// <summary>
/// The g UI default screenheight
/// </summary>
static const unsigned int g_uiDEFAULT_SCREENHEIGHT = 720;

//Arena
/// <summary>
/// The g f arena size
/// </summary>
static const float g_fARENA_SIZE = 100.0f;
/// <summary>
/// The g f half arena size
/// </summary>
static const float g_fHALF_ARENA_SIZE = g_fARENA_SIZE * 0.5f; //Multiplication is faster that division


#endif // !_CONSTANTS_H_
