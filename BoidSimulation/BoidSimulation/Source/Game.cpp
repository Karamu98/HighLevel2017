// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Game.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Game.h"

// Core includes
#include <iostream>
#include <time.h>

// Framework includes
#include "Gizmos.h"
#include "Utilities.h"
#include "GL/glew.h"
#include "glfw3.h"
#include "glm/ext.hpp"

// Project includes
#include "Boid.h"
#include "Player.h"
#include "Container.h"
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "RidgedBodyComponent.h"
#include "BrainComponent.h"
#include "CameraComponent.h"
#include "BoxColliderComponent.h"
#include "Component.h"
#include "Entity.h"
#include "../imgui/include/imgui.h"

#include <vector>


/// <summary>
/// Prevents a default instance of the <see cref="Game"/> class from being created.
/// </summary>
Game::Game()
{
}


/// <summary>
/// Finalizes an instance of the <see cref="Game"/> class.
/// </summary>
Game::~Game()
{
}

/// <summary>
/// ps the get game.
/// </summary>
/// <returns>Game *.</returns>
Game * Game::pGetGame()
{
	if (m_instance == nullptr)
	{
		m_instance = new Game();
	}
	return m_instance;
}

/// <summary>
/// Gets the dynamics world.
/// </summary>
/// <returns>btDynamicsWorld *&.</returns>
btDynamicsWorld*& Game::GetDynamicsWorld()
{
	return m_dynamicWorld;
}

/// <summary>
/// Initializes the open gl.
/// </summary>
void Game::InitOpenGL()
{
	// Load the shaders for this program
	m_vertexShader = Utility::loadShader("../resources/shaders/vertex.glsl", GL_VERTEX_SHADER);
	m_fragmentShader = Utility::loadShader("../resources/shaders/fragment.glsl", GL_FRAGMENT_SHADER);

	// Define the input and output varialbes in the shaders
	// Note: these names are taken from the glsl files -- added in inputs for UV coordinates
	const char* szInputs[] = { "Position", "Normal", "Tangent", "Indices", "Weights","Tex1" };
	const char* szOutputs[] = { "FragColor" };

	// bind the shaders to create our shader program
	m_programID = Utility::createProgram(
		m_vertexShader,
		0,
		0,
		0,
		m_fragmentShader,
		6, szInputs, 1, szOutputs);

	// Generate our OpenGL Vertex and Index Buffers for rendering our FBX Model Data
	// OPENGL: generate the VBO, IBO and VAO
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
	glGenVertexArrays(1, &m_vao);

	// OPENGL: Bind  VAO, and then bind the VBO and IBO to the VAO
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	// There is no need to populate the vbo & ibo buffers with any data at this stage
	// this can be done when rendering each mesh component of the FBX model

	// enable the attribute locations that will be used on our shaders
	glEnableVertexAttribArray(0); //Pos
	glEnableVertexAttribArray(1); //Norm
	glEnableVertexAttribArray(2); //tangent
	glEnableVertexAttribArray(3); //Indices
	glEnableVertexAttribArray(4); //Weights
	glEnableVertexAttribArray(5); //Tex1

								  // tell our shaders where the information within our buffers lie
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(MD5Vertex), ((char *)0) + MD5Vertex::PositionOffset);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(MD5Vertex), ((char *)0) + MD5Vertex::NormalOffset);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(MD5Vertex), ((char *)0) + MD5Vertex::TangentOffset);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(MD5Vertex), ((char *)0) + MD5Vertex::IndicesOffset);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_TRUE, sizeof(MD5Vertex), ((char *)0) + MD5Vertex::WeightsOffset);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_TRUE, sizeof(MD5Vertex), ((char *)0) + MD5Vertex::TexCoord1Offset);

	// finally, where done describing our mesh to the shader
	// we can describe the next mesh
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f, 0.25f, 0.25f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

/// <summary>
/// Ons the create.
/// </summary>
/// <returns>bool.</returns>
bool Game::onCreate()
{
	m_collisionConfig = new btDefaultCollisionConfiguration();
	m_collisionDispatcher = new btCollisionDispatcher(m_collisionConfig);
	m_overlappingPairCache = new btDbvtBroadphase();
	m_collisionSolver = new btSequentialImpulseConstraintSolver;

	m_dynamicWorld = new btDiscreteDynamicsWorld(m_collisionDispatcher, m_overlappingPairCache, m_collisionSolver, m_collisionConfig);
	if (m_dynamicWorld)
	{
		m_dynamicWorld->setGravity(btVector3(0, -100, 0));
	}

	FMOD::System_Create(&m_pFMODSystem);

	m_pFMODSystem->init(32, FMOD_INIT_NORMAL, nullptr);

	m_pFMODSystem->createSound("../resources/audio/ambiance.mp3", FMOD_DEFAULT, 0, &m_pAmbiance);

	m_pAmbiance->setMode(FMOD_LOOP_NORMAL);


	m_pFMODSystem->playSound(m_pAmbiance, 0, false, &m_pChannel1);

	// Initialise the Gizmos helper class
	Gizmos::create();

	// Load scene
	LoadModels();
	CreateBounds(glm::vec3(200, 200, 200));
	CreatePlayer();
	CreateEnemies();

	// Set the position of the light
	m_lightPos = glm::vec4(0.f, 50.f, 0.f, 1.f);

	// Initialise OpenGL
	InitOpenGL();


	
	// Create Floor Collider
	btTransform tTransform;
	tTransform.setIdentity();
	tTransform.setOrigin(btVector3(0, -100, 0));

	btCollisionShape* groundShape = new btBoxShape(btVector3(250, 1, 250));

	btDefaultMotionState* groundMotionState = new btDefaultMotionState(tTransform);
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	m_dynamicWorld->addRigidBody(groundRigidBody);

	
	

	return true;
}

/// <summary>
/// Updates the specified a delta time.
/// </summary>
/// <param name="a_deltaTime">a delta time.</param>

/// <summary>
/// Updates the specified a delta time.
/// </summary>
/// <param name="a_deltaTime">a delta time.</param>
void Game::Update(float a_deltaTime)
{
	m_dynamicWorld->stepSimulation(a_deltaTime);

#pragma region ImGui
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Create", "Ctrl+N"))
		{
			Entity* newEntity = new Entity();
			m_axEntityArray.push_back(newEntity);
			m_selectedEntity = newEntity;
		}

		if (ImGui::MenuItem("Duplicate", "Ctrl+D"))
		{
			Entity* newEntity = new Entity(m_selectedEntity);
			m_axEntityArray.push_back(newEntity);
			m_selectedEntity = newEntity;

			m_selectedEntity->pGetRootTransformComp()->SetCurrentPosition(glm::vec3(0, 0, 0));
			m_selectedEntity->pGetRootTransformComp()->SetFacingDirection(glm::vec3(0, 0, 1));
			m_selectedEntity->pGetRootTransformComp()->SetUpDirection(glm::vec3(0, 1, 0));
			m_selectedEntity->pGetRootTransformComp()->SetRightDirection(glm::vec3(1, 0, 0));
		}

		if (ImGui::MenuItem("Delete"))
		{
			ptrdiff_t old = std::find(m_axEntityArray.begin(), m_axEntityArray.end(), m_selectedEntity) - m_axEntityArray.begin();

			m_axEntityArray.erase(m_axEntityArray.begin() + old);
			m_selectedEntity = m_axEntityArray.at(0);
		
		}


		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("Add Component", "Ctrl+C"))
		{
			bComponentTool = true;
			bComponentAdd = true;
		}
		if (ImGui::MenuItem("Delete Component"))
		{
			bComponentTool = true;
			bComponentAdd = false;
		}

		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
	if (bComponentTool)
	{
		ImGui::Begin("Select Component", NULL, ImGuiWindowFlags_NoCollapse);
		ImGui::BeginChild("Scrolling");
		if (bComponentAdd)
		{
			for (int i = 0; i < 6; i++)
			{
				switch (i)
				{
				case MODEL:
				{
					if (ImGui::Button("Model Component"))
					{
						ModelComponent* newComp = new ModelComponent(m_selectedEntity);
						newComp->SetModel(xImpModel);
						newComp->SetCurrentAnim("idle1");
						m_selectedEntity->AddComponent(newComp);
						bComponentTool = false;
					}
					break;
				}
				case BRAIN:
				{
					if (ImGui::Button("Brain Component"))
					{
						BrainComponent* newComp = new BrainComponent(m_selectedEntity);
						newComp->SetBehaviour(WANDER);
						newComp->AddBehaviour(ALIGNMENT);
						newComp->AddBehaviour(SEPARATION);
						newComp->AddBehaviour(COHESION);
						m_selectedEntity->AddComponent(newComp);
						bComponentTool = false;
					}
					break;
				}
				case CAMERA:
				{
					if (ImGui::Button("Camera Component"))
					{
						m_selectedEntity->AddComponent(new CameraComponent(m_selectedEntity));
						bComponentTool = false;
					}
					break;
				}
				case BOXCOLLIDER:
				{
					if (ImGui::Button("Box Collider"))
					{
						m_selectedEntity->AddComponent(new BoxColliderComponent(m_selectedEntity));
						bComponentTool = false;
					}
					break;
				}
				case RIDGEDBODY:
				{
					if (ImGui::Button("RidgedBody"))
					{
						m_selectedEntity->AddComponent(new RigidBodyComponent(m_selectedEntity));
						bComponentTool = false;
					}
				}
				default:
					break;
				}
			}

			ImGui::NewLine();
			if (ImGui::Button("Cancel"))
			{
				bComponentTool = false;
			}
		}
		else
		{
			std::vector<Component*>::iterator xIter = m_selectedEntity->GetComponentList()->begin();
			std::vector<Component*>::iterator end = m_selectedEntity->GetComponentList()->end();

			for (xIter; xIter != end && bComponentTool; xIter++)
			{
				Component* comp = *xIter;

				if (!comp)
				{
					return;
				}


				ImGui::PushID(xIter - m_selectedEntity->GetComponentList()->begin());
				switch (comp->GetComponentType())
				{
				case MODEL:
				{
					if (ImGui::Button("Model Component"))
					{
						ptrdiff_t old = std::find(m_selectedEntity->GetComponentList()->begin(), m_selectedEntity->GetComponentList()->end(), comp) - m_selectedEntity->GetComponentList()->begin();

						m_selectedEntity->GetComponentList()->erase(m_selectedEntity->GetComponentList()->begin() + old);
						bComponentTool = false;
					}
					break;
				}
				case BRAIN:
				{
					if (ImGui::Button("Brain Component"))
					{
						ptrdiff_t old = std::find(m_selectedEntity->GetComponentList()->begin(), m_selectedEntity->GetComponentList()->end(), comp) - m_selectedEntity->GetComponentList()->begin();

						m_selectedEntity->GetComponentList()->erase(m_selectedEntity->GetComponentList()->begin() + old);
						bComponentTool = false;
					}
					break;
				}
				case CAMERA:
				{
					if (ImGui::Button("Camera"))
					{
						ptrdiff_t old = std::find(m_selectedEntity->GetComponentList()->begin(), m_selectedEntity->GetComponentList()->end(), comp) - m_selectedEntity->GetComponentList()->begin();

						m_selectedEntity->GetComponentList()->erase(m_selectedEntity->GetComponentList()->begin() + old);
						bComponentTool = false;
					}
					break;
				}
				case BOXCOLLIDER:
				{
					if (ImGui::Button("Box Collider"))
					{
						ptrdiff_t old = std::find(m_selectedEntity->GetComponentList()->begin(), m_selectedEntity->GetComponentList()->end(), comp) - m_selectedEntity->GetComponentList()->begin();

						m_selectedEntity->GetComponentList()->erase(m_selectedEntity->GetComponentList()->begin() + old);
						bComponentTool = false;
					}
					break;
				}
				case RIDGEDBODY:
				{
					if (ImGui::Button("Ridgedbody"))
					{
						ptrdiff_t old = std::find(m_selectedEntity->GetComponentList()->begin(), m_selectedEntity->GetComponentList()->end(), comp) - m_selectedEntity->GetComponentList()->begin();

						m_selectedEntity->GetComponentList()->erase(m_selectedEntity->GetComponentList()->begin() + old);
						bComponentTool = false;
					}
					break;
				}
				default:
				{
					break;
				}
				}
				ImGui::PopID();
				if (!bComponentTool)
				{
					break;
				}
			}			

			ImGui::NewLine();
			if (ImGui::Button("Cancel"))
			{
				bComponentTool = false;
			}
		}

		ImGui::EndChild();
		ImGui::End();
	}



	// Fix for some weird NaN issues in the model matrix we've been seeing
	if (a_deltaTime <= 0.f) return;

	ImGui::Begin("Camera", NULL, ImGuiWindowFlags_NoCollapse);

	TransformComponent* pSelectedEntityTransform = m_selectedEntity->pGetRootTransformComp();

	// Loop through other components
	if (m_selectedCamera != nullptr)
	{
		ImGui::TextColored(ImVec4(40, 0, 170, 1), "Camera:");
		ImGui::SliderFloat("FOV", m_selectedCamera->pGetFOV(), 60, 140);
		ImGui::SliderFloat("Camera Speed", m_selectedCamera->pGetSpeed(), 1, 200);

		CameraComponent* testCam = static_cast<CameraComponent*>(m_selectedEntity->FindComponentOfType(CAMERA));

		if (testCam != NULL)
		{
			if (m_selectedCamera != testCam)
			{
				if (ImGui::Button("Switch Camera"))
				{
					m_selectedCamera->m_bActive = false;
					m_selectedCamera->SetPossesed(false);
					m_selectedCamera = static_cast<CameraComponent*>(m_selectedEntity->FindComponentOfType(CAMERA));
					m_selectedCamera->m_bActive = true;
					
				}
			}
		}

		if (*m_selectedCamera->pGetPossesed())
		{
			if (ImGui::Button("Unpossess"))
			{
				m_selectedCamera->SetPossesed(false);
			}
		}
		else
		{
			if (ImGui::Button("Possess"))
			{
				m_selectedCamera->SetPossesed(true);
			}
		}

		ImGui::NewLine();
	}
	ImGui::End();

	ImGui::Begin("World Outliner", NULL, ImGuiWindowFlags_NoCollapse);

	ImGui::TextColored(ImVec4(0, 170, 0, 1), "Entity List:");
	ImGui::BeginChild("Scrolling");

	if (m_axEntityArray.capacity() > 0)
	{
		std::string id = "";
		for (int i = 0; i < m_axEntityArray.size(); i++)
		{
			id = *m_axEntityArray.at(i)->GetName();

			ImGui::Text("%s", id.c_str());
			ImGui::SameLine(ImGui::GetWindowWidth() - 80);

			ImGui::PushID(i);
			if (ImGui::Button("Select"))
			{
				m_selectedEntity = m_axEntityArray.at(i);
			}
			ImGui::PopID();
		}
		ImGui::EndChild();

		ImGui::End();
	}

	ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoCollapse);
	ImGui::TextColored(ImVec4(170, 0, 0, 1), "Selected Entity:");

	m_selectedEntity->OnGUI();

	ImGui::End();

#pragma endregion


#pragma region Player_Updating

	m_player->Update(a_deltaTime);

#pragma endregion

#pragma region Gizmos
	// clear all gizmos from last frame
	Gizmos::clear();

	// add an identity matrix gizmo
	Gizmos::addTransform(glm::mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));

	// Create the world floor
	Gizmos::addBox(glm::vec3(0.f, -100.f, 0.f), glm::vec3(500.f, 1, 500.f), true, glm::vec4(255.0f, 255.0f, 255.f, 0.5f));

	// Create box to represent the light
	Gizmos::addBox(m_lightPos, glm::vec3(0.2f, 0.2f, 0.2f), true, glm::vec4(1.0f, 0.85f, 0.05f, 1.f));

#pragma endregion

#pragma region Entity_Updating
	// Update all our entities
	std::vector< Entity* >::iterator xIter;
	for (xIter = m_axEntityArray.begin(); xIter < m_axEntityArray.end(); ++xIter)
	{
		Entity* pCurrentEntity = *xIter;
		if (pCurrentEntity)
		{
			pCurrentEntity->Update(a_deltaTime);
		}
	}
#pragma endregion

	// quit our application when escape is pressed
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

/// <summary>
/// Draws this instance.
/// </summary>
void Game::Draw()
{
	Entity* currentEntity;

	currentEntity = m_selectedEntity;

	// Test selected entity first
	if (m_selectedCamera != nullptr) // If the selected entity has a camera
	{
		// Draw the screen with this camera
		m_selectedCamera->Draw(m_programID, m_vbo, m_ibo);

		// Pass the directional light direction to our fragment shader
		glm::vec4 lightDir = -m_lightPos;
		lightDir.w = 0.f;
		lightDir = glm::normalize(lightDir);
		unsigned int lightDirUniform = glGetUniformLocation(m_programID, "lightDirection");
		glUniform4fv(lightDirUniform, 1, glm::value_ptr(lightDir));


		// Draw all our enemies models
		std::vector< Entity* >::iterator xIter;
		for (xIter = m_axEntityArray.begin(); xIter < m_axEntityArray.end(); ++xIter)
		{
			Entity* pCurrentEntity = *xIter;
			if (pCurrentEntity)
			{
				pCurrentEntity->Draw(m_programID, m_vbo, m_ibo);
			}
		}

		glBindVertexArray(0);
		glUseProgram(0);

		// Draw the gizmos from this frame

		if (bUseGizmos)
		{
			Gizmos::draw(m_selectedCamera->GetViewMatrix(), m_selectedCamera->GetProjectionMatrix());
		}

		// Early Out
		return;
	}


	// Loop though all entities looking for a camera component
	for (int i = 0; i < m_axEntityArray.size(); i++)
	{
		// Assign camera and entity to current iter
		currentEntity = m_axEntityArray.at(i);

		// If this entity has a camera
		if (m_selectedCamera != nullptr)
		{
			// Draw the screen with this camera
			m_selectedCamera->Draw(m_programID, m_vbo, m_ibo);

			// Pass the directional light direction to our fragment shader
			glm::vec4 lightDir = -m_lightPos;
			lightDir.w = 0.f;
			lightDir = glm::normalize(lightDir);
			unsigned int lightDirUniform = glGetUniformLocation(m_programID, "lightDirection");
			glUniform4fv(lightDirUniform, 1, glm::value_ptr(lightDir));


			// Draw all our entities
			std::vector< Entity* >::iterator xIter;
			for (xIter = m_axEntityArray.begin(); xIter < m_axEntityArray.end(); ++xIter)
			{
				Entity* pCurrentEntity = *xIter;
				if (pCurrentEntity)
				{
					pCurrentEntity->Draw(m_programID, m_vbo, m_ibo);
				}
			}

			glBindVertexArray(0);
			glUseProgram(0);

			// Draw the gizmos from this frame

			if (bUseGizmos)
			{
				Gizmos::draw(m_selectedCamera->GetViewMatrix(), m_selectedCamera->GetProjectionMatrix());
			}

			// Early Out
			return;
		}
	}
	
	std::cout << "No Camera's in scene.";
}

/// <summary>
/// Destroys this instance.
/// </summary>
void Game::Destroy()
{
	Gizmos::destroy();

#pragma region Bullet_Physics_CleanUp
	for (int i = 0; i < m_dynamicWorld->getNumCollisionObjects(); i++)
	{
		btCollisionObject* obj = m_dynamicWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);

		m_dynamicWorld->removeCollisionObject(obj);
		if (body && body->getMotionState())
		{
			delete body;
		}
	}

	delete m_dynamicWorld;
	delete m_collisionSolver;
	delete m_overlappingPairCache;
	delete m_collisionDispatcher;
	delete m_collisionConfig;
#pragma endregion 
}

/// <summary>
/// Loads the models.
/// </summary>
void Game::LoadModels()
{
	// Load Imp
	xImpModel = new MD5Model();
	const unsigned int g_uNumOfImpAnims = 2;
	const char* aImpAnims[g_uNumOfImpAnims] =
	{
		"../resources/Animations/imp/idle1.md5anim",
		"../resources/Animations/imp/walk1.md5anim",
	};

	xImpModel->Load("../resources/Models/imp.md5mesh", 0.1f); // Load the mesh
	xImpModel->LoadAnims(g_uNumOfImpAnims, aImpAnims); // Load the anims

	// Load Pinky
	xPinkyModel = new MD5Model();
	const unsigned int g_uNumOfPinkyAnims = 2;
	const char* aPinkyAnims[g_uNumOfPinkyAnims] =
	{
		"../resources/Animations/pinky/idle1.md5anim",
		"../resources/Animations/pinky/run.md5anim",
	};

	// Load pinky
	xPinkyModel->Load("../resources/Models/pinky.md5mesh", 0.1f);
	xPinkyModel->LoadAnims(g_uNumOfPinkyAnims, aPinkyAnims);
}

/// <summary>
/// Creates the enemies.
/// </summary>
void Game::CreateEnemies()
{
	MD5Model xDuplicateImp = *xImpModel;

	// Seed the random
	srand(time(nullptr));

	// Create all our enemies
	for (int i = 0; i < iMAX_NUM_OF_ENEMIES; ++i)
	{
		// Create a new Enemy
		Boid* pNewBoid;

		int iRandModel = rand() % 2;

		if (iRandModel == 0)
		{
			pNewBoid = new Boid(xImpModel);
		}
		else
		{
			pNewBoid = new Boid(xPinkyModel);
		}

		// Random start position
		float x = rand() % 101 + (-50);
		float y = rand() % 51 + 1;
		float z = rand() % 101 + (-50);
	
		TransformComponent* pTransformComp = pNewBoid->pGetRootTransformComp();
		pTransformComp->SetCurrentPosition(glm::vec3(x, y, z));

		// Random facing direction
		glm::vec3 v3Forward(glm::vec3(x, 0.f, z));

		// Normalise
		v3Forward = glm::normalize(v3Forward);

		glm::vec3 v3Up = pTransformComp->GetUpDirection();

		v3Up = v3Up - (v3Forward * glm::dot(v3Forward, v3Up));
		v3Up = glm::normalize(v3Up);
		glm::vec3 v3Right = glm::normalize(glm::cross(v3Up, v3Forward));
		// Calculate our Up using Gramschmidt


		// Set the matrix
		pTransformComp->SetUpDirection(v3Up);
		pTransformComp->SetRightDirection(v3Right);
		pTransformComp->SetFacingDirection(v3Forward);

		// Add to our enemy array
		m_axEntityArray.push_back(pNewBoid);
	}	
}

/// <summary>
/// Creates the player.
/// </summary>
void Game::CreatePlayer()
{
	m_player = new Player();

	m_axEntityArray.push_back(m_player);

	m_selectedEntity = m_player;
	m_selectedCamera = static_cast<CameraComponent*>(m_player->FindComponentOfType(CAMERA));
}

/// <summary>
/// Creates the bounds.
/// </summary>
/// <param name="a_size">a size.</param>
void Game::CreateBounds(glm::vec3 a_size)
{
	Container* bounds = new Container(a_size);

	m_axEntityArray.push_back(bounds);
}
