// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="ModelComponent.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "ModelComponent.h"

//Includes
#include "MD5Model.h"
#include <GL/glew.h>
#include <glm/ext.hpp>
#include "Game.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "imgui.h"

#include <iostream>


//typedefs
typedef Component PARENT;

//Constants
/// <summary>
/// The f anim playback rate
/// </summary>
static const float fANIM_PLAYBACK_RATE = 2.0f;

/// <summary>
/// Initializes a new instance of the <see cref="ModelComponent"/> class.
/// </summary>
/// <param name="a_pOwnerEntity">a p owner entity.</param>
ModelComponent::ModelComponent(Entity* a_pOwnerEntity) : PARENT(a_pOwnerEntity), m_fAnimTime(0.0f)
{
	m_eComponentType = MODEL;
	m_szCurrentAnimation = "";
}


/// <summary>
/// Finalizes an instance of the <see cref="ModelComponent"/> class.
/// </summary>
ModelComponent::~ModelComponent()
{
}

/// <summary>
/// Updates the specified a f delta time.
/// </summary>
/// <param name="a_fDeltaTime">a f delta time.</param>
void ModelComponent::Update(float a_fDeltaTime)
{
	if (!m_bActive)
	{
		return;
	}

	if (m_szCurrentAnimation != "")
	{
		//Apply delta time
		m_fAnimTime += a_fDeltaTime * fANIM_PLAYBACK_RATE;

		//Evaluate current animation
		m_xModel.evaluateAnimation(m_szCurrentAnimation, m_fAnimTime, true);

		//Update the model bones
		m_xModel.UpdateBones();
	}
}

/// <summary>
/// Draws the specified a u program identifier.
/// </summary>
/// <param name="a_uProgramID">a u program identifier.</param>
/// <param name="a_uVBO">a u vbo.</param>
/// <param name="a_uIBO">a u ibo.</param>
void ModelComponent::Draw(unsigned int a_uProgramID, unsigned int a_uVBO, unsigned int a_uIBO)
{
	if (!m_bActive)
	{
		return;
	}
	//Bind the array of bones
	MD5Skeleton* skeleton = m_xModel.m_skeleton;
	int iBoneLocation = glGetUniformLocation(a_uProgramID, "Bones");
	glUniformMatrix4fv(iBoneLocation, skeleton->m_jointCount, GL_FALSE, (float*)skeleton->m_bones);

	TransformComponent* pTransformComp = pGetOwnerEntity()->pGetRootTransformComp();

	const glm::mat4& m4EntityMatrix = *pTransformComp->pGetTransformMatrix();

	//Draw each mesh in the MD5 Model
	for (unsigned int i = 0; i < m_xModel.getMeshCount(); ++i)
	{
		//get current mesh
		MD5Mesh* pMesh = m_xModel.m_meshes[i];

		unsigned int uiModelUniform = glGetUniformLocation(a_uProgramID, "Model");
		glUniformMatrix4fv(uiModelUniform, 1, false, glm::value_ptr(m4EntityMatrix));

		//Bind the texture to one of the ative texture
		//if the shader supports multiple textures, it would bind each texture to a new active texture id
		//bind the texturelocation variable from the shaders and set its value to 0 as the active texture is 0
		unsigned int uiTexUniformID = glGetUniformLocation(a_uProgramID, "DiffuseTexture");
		glUniform1i(uiTexUniformID, 0);

		//set our ative texture and bind the loaded texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, pMesh->m_material.textureIDs[MD5Material::DiffuseTexture]);

		uiTexUniformID = glGetUniformLocation(a_uProgramID, "NormalMap");
		glUniform1i(uiTexUniformID, 1);
		//set our active texture, and bind our loaded texture
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, pMesh->m_material.textureIDs[MD5Material::NormalTexture]);

		uiTexUniformID = glGetUniformLocation(a_uProgramID, "SpecularMap");
		glUniform1i(uiTexUniformID, 2);

		//set our active texture, and bind our loaded texture
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, pMesh->m_material.textureIDs[MD5Material::SpecularTexture]);

		uiTexUniformID = glGetUniformLocation(a_uProgramID, "DisplacementMap");
		glUniform1i(uiTexUniformID, 3);
		//set our active texture, and bind our loaded texture
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, pMesh->m_material.textureIDs[MD5Material::DisplacementTexture]);

		// Send the vertex data to the VBO
		glBindBuffer(GL_ARRAY_BUFFER, a_uVBO);
		glBufferData(GL_ARRAY_BUFFER, pMesh->m_vertices.size() * sizeof(MD5Vertex), pMesh->m_vertices.data(), GL_STATIC_DRAW);

		// send the index data to the IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, a_uIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, pMesh->m_indices.size() * sizeof(unsigned int), pMesh->m_indices.data(), GL_STATIC_DRAW);

		glDrawElements(GL_TRIANGLES, pMesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}
}

/// <summary>
/// Called when [GUI].
/// </summary>
void ModelComponent::OnGUI()
{
	PARENT::OnGUI();
	if (!m_bActive)
	{
		return;
	}
	ImGui::Text("Loaded model: %s", m_xModel.GetModelPath());
	ImGui::NewLine();
}

/// <summary>
/// Sets the model.
/// </summary>
/// <param name="a_MD5Model">a m d5 model.</param>
void ModelComponent::SetModel(MD5Model* a_MD5Model)
{
	m_xModel = *a_MD5Model;
}

/// <summary>
/// Sets the current anim.
/// </summary>
/// <param name="a_szCurrentAnim">a sz current anim.</param>
void ModelComponent::SetCurrentAnim(const char* a_szCurrentAnim)
{
	 m_szCurrentAnimation = a_szCurrentAnim; 
}

/// <summary>
/// Gets the current anim.
/// </summary>
/// <returns>const char *.</returns>
const char* ModelComponent::GetCurrentAnim()
{
	return m_szCurrentAnimation;
}

/// <summary>
/// Gets the model.
/// </summary>
/// <returns>const MD5Model *.</returns>
const MD5Model* ModelComponent::GetModel()
{
	return &m_xModel;
}