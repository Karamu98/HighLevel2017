// ***********************************************************************
// Assembly         : 
// Author           : s1608758
// Created          : 05-22-2018
//
// Last Modified By : s1608758
// Last Modified On : 05-22-2018
// ***********************************************************************
// <copyright file="Entity.cpp" company="University of Gloucestershire">
//     Copyright (c) University of Gloucestershire. All rights reserved.
// </copyright>
// <summary></summary>
// ***********************************************************************
#include "Entity.h"
#include "TransformComponent.h"
#include "imgui.h"

#include "Component.h"
#include <iostream>

unsigned int Entity::s_uiEntityIDCount = 0;
/// <summary>
/// The s UI entity identifier count
/// </summary>
std::map<const unsigned int, Entity*> Entity::s_xEntityMap;

typedef std::pair<const unsigned int, Entity*> EntityPair;

/// <summary>
/// Initializes a new instance of the <see cref="Entity"/> class.
/// </summary>
Entity::Entity()
{
	//Increment entity ID
	m_uiEntityID = s_uiEntityIDCount++;

	//Add entity to list
	s_xEntityMap.insert(EntityPair(m_uiEntityID, this));

	SetName(std::string("Default ") += std::to_string(GetEntityID()));

	AddComponent(new TransformComponent(this));

	m_rootTransformComponent = static_cast<TransformComponent*>(FindComponentOfType(TRANSFORM));
}

/// <summary>
/// Initializes a new instance of the <see cref="Entity"/> class.
/// </summary>
/// <param name="a_original">a original.</param>
Entity::Entity(Entity * a_original)
{
	//Increment entity ID
	m_uiEntityID = s_uiEntityIDCount++;

	//Add entity to list
	s_xEntityMap.insert(EntityPair(m_uiEntityID, this));

	SetName(std::string(a_original->GetName()->c_str()) += std::to_string(GetEntityID()));

	DuplicateComponents(a_original);
	AddComponent(new TransformComponent(this)); // Temp while duplicate is broken

	m_rootTransformComponent = static_cast<TransformComponent*>(FindComponentOfType(TRANSFORM));

}


/// <summary>
/// Finalizes an instance of the <see cref="Entity"/> class.
/// </summary>
Entity::~Entity()
{
}

/// <summary>
/// Updates the specified a f delta time.
/// </summary>
/// <param name="a_fDeltaTime">a f delta time.</param>
void Entity::Update(float a_fDeltaTime)
{
	std::vector<Component*>::iterator xIter;
	for(xIter = m_apComponentList.begin(); xIter < m_apComponentList.end(); ++xIter)
	{
		Component* pComponent = *xIter;
		if (pComponent)
		{
			pComponent->Update(a_fDeltaTime);
		}
	}
}

/// <summary>
/// Draws the specified a UI program identifier.
/// </summary>
/// <param name="a_uiProgramID">a UI program identifier.</param>
/// <param name="a_uiVBO">a UI vbo.</param>
/// <param name="a_uiIBO">a UI ibo.</param>
void Entity::Draw(unsigned int a_uiProgramID, unsigned int a_uiVBO, unsigned int a_uiIBO)
{
	std::vector<Component*>::iterator xIter;
	for (xIter = m_apComponentList.begin(); xIter < m_apComponentList.end(); ++xIter)
	{
		Component* pComponent = *xIter;
		if (pComponent)
		{
			pComponent->Draw(a_uiProgramID, a_uiVBO, a_uiIBO);
		}
	}
}

/// <summary>
/// Called when [GUI].
/// </summary>
void Entity::OnGUI()
{
	std::vector<Component*>::iterator xIter;
	for (xIter = m_apComponentList.begin(); xIter < m_apComponentList.end(); ++xIter)
	{
		Component* pComponent = *xIter;
		if (pComponent)
		{
			pComponent->OnGUI();
		}
	}

}

/// <summary>
/// Adds the component.
/// </summary>
/// <param name="a_pComponent">a p component.</param>
void Entity::AddComponent(Component * a_pComponent)
{
	m_apComponentList.push_back(a_pComponent);
}

/// <summary>
/// Duplicates the components.
/// </summary>
/// <param name="a_original">a original.</param>
void Entity::DuplicateComponents(Entity* a_original)
{
	/*std::vector<Component*>::iterator xIter;
	for (xIter = a_original->GetComponentList()->begin(); xIter < a_original->GetComponentList()->end(); ++xIter)
	{
		Component* pOriginalComp = *xIter;
		Component* newComp = new Component(this);

		*newComp = *pOriginalComp;

		AddComponent(newComp);
	}*/
}

/// <summary>
/// Finds the type of the component of.
/// </summary>
/// <param name="eComponentType">Type of the e component.</param>
/// <returns>Component *.</returns>
Component* Entity::FindComponentOfType(COMPONENT_TYPE eComponentType)
{
	std::vector<Component*>::iterator xIter;
	for (xIter = m_apComponentList.begin(); xIter < m_apComponentList.end(); ++xIter)
	{
		Component* pComponent = *xIter;
		if (pComponent && pComponent->GetComponentType() == eComponentType)
		{
			return pComponent;
		}
	}
	return nullptr;
}

/// <summary>
/// Gets the component list.
/// </summary>
/// <returns>std.vector&lt;Component*&gt;*.</returns>
std::vector<Component*>* Entity::GetComponentList()
{
	return &m_apComponentList;
}

/// <summary>
/// ps the get root transform comp.
/// </summary>
/// <returns>TransformComponent *.</returns>
TransformComponent * Entity::pGetRootTransformComp()
{
	return m_rootTransformComponent;
}

/// <summary>
/// Gets the name.
/// </summary>
/// <returns>std.string *.</returns>
std::string* Entity::GetName()
{
	return &ssName;
}

/// <summary>
/// Sets the name.
/// </summary>
/// <param name="a_newName">a new name.</param>
void Entity::SetName(std::string a_newName)
{
	ssName = a_newName;
}

/// <summary>
/// Gets the entity map.
/// </summary>
/// <returns>std.map&lt;const unsigned int,Entity*&gt;.</returns>
std::map<const unsigned int, Entity*> Entity::GetEntityMap()
{
	return s_xEntityMap;
}
