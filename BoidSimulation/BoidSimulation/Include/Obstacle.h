#ifndef _OBSTACLE_H__
#define _OBSTACLE_H__

// Includes
#include "Entity.h"

// Forward Declarations

class Obstacle : public Entity
{
public:
	Obstacle();
	~Obstacle();
	//Override update function hence why its virtual - as it inherits from entity

	virtual void Update(float a_fDeltaTime);
	void Draw(unsigned int a_uiProgramID, unsigned int a_uiVBO, unsigned int a_uiIBO);

protected:
	float m_fScale;

private:


};


#endif