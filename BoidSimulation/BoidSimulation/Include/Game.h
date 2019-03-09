// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Game.h" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef _GAME_H
#define _GAME_H

// Includes
#include "Application.h"
#include "glm/glm.hpp"
#include "MD5Model.h"
#include "btBulletDynamicsCommon.h"
#include <vector>
#include <fmod.hpp>

// Forward Declarations
class Boid;
class Entity;
class Container;
class Player;
class CameraComponent;

// Constants
/// <summary>
/// The i maximum number of enemies
/// </summary>
const int iMAX_NUM_OF_ENEMIES = 15;

/// <summary>
/// Class Game.
/// </summary>
/// <seealso cref="Application" />
class Game : public Application
{
	static Game* m_instance;


public: 


	/// <summary>
	/// Finalizes an instance of the <see cref="Game" /> class.
	/// </summary>
	~Game();


	/// <summary>
	/// ps the get game.
	/// </summary>
	/// <returns>Game *.</returns>
	static Game* pGetGame();


	/// <summary>
	/// Gets the dynamics world.
	/// </summary>
	/// <returns>btDynamicsWorld *&.</returns>
	btDynamicsWorld*& GetDynamicsWorld();

protected:

	/// <summary>
	/// Ons the create.
	/// </summary>
	/// <returns>bool.</returns>
	virtual bool onCreate();
	/// <summary>
	/// Updates the specified a delta time.
	/// </summary>
	/// <param name="a_deltaTime">a delta time.</param>
	virtual void Update(float a_deltaTime);
/// <summary>
/// Draws this instance.
/// </summary>
	virtual void Draw();

	/// <summary>
	/// Destroys this instance.
	/// </summary>
	virtual void Destroy();

private:

	/// <summary>
	/// Prevents a default instance of the <see cref="Game" /> class from being created.
	/// </summary>
	Game();

	/// <summary>
	/// Loads the models.
	/// </summary>
	void LoadModels();

	/// <summary>
	/// Creates the enemies.
	/// </summary>
	void CreateEnemies();

	/// <summary>
	/// Creates the player.
	/// </summary>
	void CreatePlayer();

	/// <summary>
	/// Creates the bounds.
	/// </summary>
	/// <param name="a_size">a size.</param>
	void CreateBounds(glm::vec3 a_size);


	/// <summary>
	/// Initializes the open gl.
	/// </summary>
	void InitOpenGL();

	/// <summary>
	/// The m program identifier
	/// </summary>
	unsigned int m_programID;
	/// <summary>
	/// The m vertex shader
	/// </summary>
	unsigned int m_vertexShader;
	/// <summary>
	/// The m fragment shader
	/// </summary>
	unsigned int m_fragmentShader;

	/// <summary>
	/// The m vao
	/// </summary>
	unsigned int m_vao;
	/// <summary>
	/// The m vbo
	/// </summary>
	unsigned int m_vbo;
	/// <summary>
	/// The m ibo
	/// </summary>
	unsigned int m_ibo;


	/// <summary>
	/// The m ax entity array
	/// </summary>
	std::vector<Entity*> m_axEntityArray;

	/// <summary>
	/// The m selected entity
	/// </summary>
	Entity* m_selectedEntity;
	/// <summary>
	/// The m selected camera
	/// </summary>
	CameraComponent* m_selectedCamera;


	// Bullet Physics
/// <summary>
/// The m collision configuration
/// </summary>
	btDefaultCollisionConfiguration* m_collisionConfig;
	/// <summary>
	/// The m collision dispatcher
	/// </summary>
	btCollisionDispatcher* m_collisionDispatcher;
	/// <summary>
	/// The m overlapping pair cache
	/// </summary>
	btBroadphaseInterface* m_overlappingPairCache;
	/// <summary>
	/// The m collision solver
	/// </summary>
	btSequentialImpulseConstraintSolver* m_collisionSolver;
	/// <summary>
	/// The m dynamic world
	/// </summary>
	btDynamicsWorld* m_dynamicWorld;


	// FMOD
/// <summary>
/// The m p fmod system
/// </summary>
	FMOD::System* m_pFMODSystem;
	/// <summary>
	/// The m p channel1
	/// </summary>
	FMOD::Channel* m_pChannel1;

	/// <summary>
	/// The m p ambiance
	/// </summary>
	FMOD::Sound*  m_pAmbiance;


	/// <summary>
	/// The m player
	/// </summary>
	Player* m_player;

	/// <summary>
	/// The m light position
	/// </summary>
	glm::vec4 m_lightPos;


	/// <summary>
	/// The b component tool
	/// </summary>
	bool bComponentTool = false;
	/// <summary>
	/// The b component add
	/// </summary>
	bool bComponentAdd = false;

	/// <summary>
	/// The x pinky model
	/// </summary>
	MD5Model* xPinkyModel;
	/// <summary>
	/// The x imp model
	/// </summary>
	MD5Model* xImpModel;



	/// <summary>
	/// The b use gizmos
	/// </summary>
	bool bUseGizmos = true;
};

#endif //_GAME_H