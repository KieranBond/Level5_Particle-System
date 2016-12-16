#ifndef __EMITTER_H__
#define __EMITTER_H__

#include "Particle.h"

class Emitter
	/*
	*
	*	This Class is designed to hold an array of Particles. It'll update all of its particles when updated.
	*	
	*	It'll act as a base position for the particles to spawn at and have a velocity for them.
	*
	*/
{
public:

	Emitter();//Default constructor
	~Emitter();//Destructor

	Emitter(int a_numberOfParticles);
	Emitter(int a_numberOfParticles, glm::vec4 a_position);
	Emitter(int a_numberOfParticles, glm::vec4 a_position, glm::vec4 a_rotation);

	void Update(float a_fDeltaTime);

	////					\\\\
	//	---	Get Methods ---   \\
	////					\\\\
	
	glm::vec4 getPosition() { return mPos_; };
	glm::vec4 getRotation() { return mRot_; };
	float	  getSpeed() { return mSpeed_; };
	bool	  getEmitting() { return mEmitting_; };

	////					\\\\
	//	---	Set Methods ---   \\
	////					\\\\

	void setPosition(glm::vec4 a_position) { mPos_ = a_position; };
	void setRotation(glm::vec4 a_rotation) { mRot_ = a_rotation; };
	void setSpeed(float a_speed) { mSpeed_ = a_speed; };
	void setEmitting(bool a_emit) { mEmitting_ = a_emit; };

private:

	Particle* mParticles_;

	void initParticles(int a_numberOfParticles);//Method to initialise Particles.

	glm::vec4 mPos_;
	glm::vec4 mRot_;

	float mSpeed_;
	bool  mEmitting_;
};
#endif // !__EMITTER_H__