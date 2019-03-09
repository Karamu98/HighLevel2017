#ifndef _ENEMY_H
#define _ENEMY_H


// Includes
#include "Entity.h"
#include "MD5Model.h"

//Forward Declarations
class TransformComponent;
class ModelComponent;

class Enemy : public Entity
{
public:
	Enemy();
	Enemy(MD5Model a_m);
	~Enemy();
	//Override update function hence why its virtual - as it inherits from entity

	virtual void Update(float a_fDeltaTime);
	void Draw(unsigned int a_uiProgramID, unsigned int a_uiVBO, unsigned int a_uiIBO);

protected:
	float m_fScale;
};

#endif //_ENEMY_H