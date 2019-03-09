#include "GizmoRender.h"
#include "TransformComponent.h"
#include "Gizmos.h"
#include "Entity.h"

#include <iostream>


typedef Component PARENT;

GizmoRender::GizmoRender(Entity* pOwnerEntity) : PARENT(pOwnerEntity)
{
	m_eComponentType = GIZMORENDER;
}

GizmoRender::~GizmoRender()
{
}

void GizmoRender::Update(float a_fDeltaTime)
{

}
