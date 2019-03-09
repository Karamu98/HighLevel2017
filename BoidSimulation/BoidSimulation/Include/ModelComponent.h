// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="ModelComponent.h" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef _MODEL_COMPONENT_H_
#define _MODEL_COMPONENT_H_

//Includes
#include "Component.h"
#include "MD5Model.h"
#include <vector>

/// <summary>
/// Class ModelComponent.
/// </summary>
/// <seealso cref="Component" />
class ModelComponent : public Component
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="ModelComponent"/> class.
	/// </summary>
	/// <param name="pOwnerEntity">The p owner entity.</param>
	ModelComponent(Entity* pOwnerEntity);
	/// <summary>
	/// Finalizes an instance of the <see cref="ModelComponent"/> class.
	/// </summary>
	~ModelComponent();

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
	virtual void Draw(unsigned int a_uProgramID, unsigned int a_uVBO, unsigned int a_uIBO);
	/// <summary>
	/// Called when [GUI].
	/// </summary>
	virtual void OnGUI();

	/// <summary>
	/// Sets the model.
	/// </summary>
	/// <param name="a_MD5Model">a m d5 model.</param>
	void SetModel(MD5Model* a_MD5Model);
	/// <summary>
	/// Sets the current anim.
	/// </summary>
	/// <param name="a_szCurrentAnim">a sz current anim.</param>
	void SetCurrentAnim(const char* a_szCurrentAnim);

	/// <summary>
	/// Gets the model.
	/// </summary>
	/// <returns>const MD5Model *.</returns>
	const MD5Model* GetModel();
	/// <summary>
	/// Gets the current anim.
	/// </summary>
	/// <returns>const char *.</returns>
	const char* GetCurrentAnim();

private: 
	/// <summary>
	/// The m x model
	/// </summary>
	MD5Model m_xModel;
	/// <summary>
	/// The m sz current animation
	/// </summary>
	const char* m_szCurrentAnimation;
	/// <summary>
	/// The m f anim time
	/// </summary>
	float m_fAnimTime;
};


#endif // !_MODEL_COMPONENT_H_




