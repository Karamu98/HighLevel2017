#include "CollisionComponent.h"
#include "Constants.h"
#include "Entity.h"

#include "Gizmos.h"
#include <iostream>


typedef Component PARENT;

CollisionComponent::CollisionComponent(Entity* pOwnerEntity) : PARENT(pOwnerEntity)
, m_CollisionType(NONE)
{
}

CollisionComponent::~CollisionComponent()
{
}

bool CollisionComponent::IsOverlapping(Entity * a_entity1)
{
	CollisionComponent* targetCol = static_cast<CollisionComponent*>(a_entity1->FindComponentOfType(COLLISION));

	switch (m_CollisionType)
	{
		case CUBE:
		{
			// Cube col test (aabb)
			float* LocalSize = static_cast<float*>(m_voCollisionData);

			switch (targetCol->GetCollisionType())
			{
				case CUBE:
				{
					float* TargetSize = static_cast<float*>(targetCol->GetData());

					AABB()
				}
			default:
				break;
			}
		}
		case RECTANGLE:
		{
			// Rectangle col test (aabb)
		}
		case SPHERE:
		{
			// Sphere col test (distance)
		}
		case CONVEXMESH:
		{
			// SAT (May not be included)
		}
		case NONE:
		{
			if (m_bDebug)
			{
				std::cout << m_pOwnerEntity << " has no collider but has component!" << std::endl;
				return false;
			}
		}
		default:
		{
			if (m_bDebug)
			{
				std::cout << m_pOwnerEntity << " has an unrecognised collision type!" << std::endl;
				return false;
			}
		}

	}
}

void * CollisionComponent::GetData()
{
	return m_voCollisionData;
}

void CollisionComponent::SetCollider(COLLISION_BOUND_TYPE a_colType, void * a_data)
{
	m_CollisionType = a_colType;
	m_voCollisionData = a_data;
}
