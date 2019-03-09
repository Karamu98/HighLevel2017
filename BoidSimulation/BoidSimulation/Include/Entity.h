// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Entity.h" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#ifndef _ENTITY_H
#define _ENTITY_H

// Includes
#include <map>
#include <vector>

class Component;
class TransformComponent;
enum COMPONENT_TYPE;

/// <summary>
/// Class Entity.
/// </summary>
class Entity
{
public:
	/// <summary>
	/// Initializes a new instance of the <see cref="Entity"/> class.
	/// </summary>
	Entity();
	/// <summary>
	/// Initializes a new instance of the <see cref="Entity"/> class.
	/// </summary>
	/// <param name="a_original">a original.</param>
	Entity(Entity* a_original);
	/// <summary>
	/// Finalizes an instance of the <see cref="Entity"/> class.
	/// </summary>
	~Entity();

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
	virtual void Draw(unsigned int a_uiProgramID, unsigned int a_uiVBO, unsigned int a_uiIBO);
	/// <summary>
	/// Called when [GUI].
	/// </summary>
	virtual void OnGUI();

	/// <summary>
	/// Adds the component.
	/// </summary>
	/// <param name="a_pComponent">a p component.</param>
	void AddComponent(Component* a_pComponent);
	/// <summary>
	/// Duplicates the components.
	/// </summary>
	/// <param name="a_original">a original.</param>
	void DuplicateComponents(Entity* a_original);

	/// <summary>
	/// Finds the type of the component of.
	/// </summary>
	/// <param name="eComponentType">Type of the e component.</param>
	/// <returns>Component *.</returns>
	Component* FindComponentOfType(COMPONENT_TYPE eComponentType);
	/// <summary>
	/// Gets the component list.
	/// </summary>
	/// <returns>std.vector&lt;Component*&gt;*.</returns>
	std::vector<Component*>* GetComponentList();

	/// <summary>
	/// ps the get root transform comp.
	/// </summary>
	/// <returns>TransformComponent *.</returns>
	TransformComponent* pGetRootTransformComp();

	/// <summary>
	/// Gets the name.
	/// </summary>
	/// <returns>std.string *.</returns>
	std::string* GetName();
	/// <summary>
	/// Sets the name.
	/// </summary>
	/// <param name="a_newName">a new name.</param>
	void SetName(std::string a_newName);

	/// <summary>
	/// Gets the entity identifier.
	/// </summary>
	/// <returns>unsigned int.</returns>
	inline unsigned int GetEntityID() { return m_uiEntityID; }

	/// <summary>
	/// Gets the entity map.
	/// </summary>
	/// <returns>std.map&lt;const unsigned int,Entity*&gt;.</returns>
	static std::map<const unsigned int, Entity*> GetEntityMap();

private:
	/// <summary>
	/// The m UI entity identifier
	/// </summary>
	unsigned int m_uiEntityID;

	/// <summary>
	/// The ss name
	/// </summary>
	std::string ssName;
	/// <summary>
	/// The m root transform component
	/// </summary>
	TransformComponent* m_rootTransformComponent;
	
	/// <summary>
	/// The m ap component list
	/// </summary>
	std::vector<Component*>m_apComponentList;

	static unsigned int s_uiEntityIDCount;
	static std::map<const unsigned int, Entity*>s_xEntityMap;
};

#endif // _ENTITY_H