#ifndef _COLLISION_COMPONENT_H__
#define _COLLISION_COMPONENT_H__

//includes
#include "glm/glm.hpp"
#include "Component.h"
#include <vector>

typedef enum COLLISION_BOUND_TYPE
{
	CUBE,
	RECTANGLE,
	SPHERE,
	CONVEXMESH,
	NONE
};


class Entity;

class CollisionComponent : Component
{
public:
	CollisionComponent(Entity* pOwnerEntity);
	~CollisionComponent();

	bool IsOverlapping(Entity* a_entity1);
	COLLISION_BOUND_TYPE GetCollisionType();
	void* GetData();
	void SetCollider(COLLISION_BOUND_TYPE a_colType, void* a_data);

	bool AABB();

private:
	COLLISION_BOUND_TYPE m_CollisionType;
	void* m_voCollisionData;
	std::vector<Entity*> m_vCollisionList;

	// Debug
	bool m_bDebug = false;
	bool m_bGizmos = false;


};

#endif


