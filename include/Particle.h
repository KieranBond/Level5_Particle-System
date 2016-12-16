#pragma once
#ifndef __PARTICLE_H__
#define __PARTICLE_H__


#include <glm/glm.hpp>
#include "Transform.h"

class Texture;

class Particle
{
public:

	/*						//
	//						//
	//	   Constructors		//
	//						//
	//						*/

	Particle();//Default constructor
	~Particle();//Destructor

	Particle(Texture* a_texture);
	Particle(glm::vec4 a_pos);
	Particle(Particle& a_particle);//Copy constructor

	//Main constructor without gravity.
	Particle(Texture* a_texture, glm::vec4 a_emitterPos, glm::vec4 a_direction, 
		float a_velocity, glm::vec3 a_size, glm::vec4 a_startColour, glm::vec4 a_endColour, float a_lifeSpan);
	
	//Main constructor with gravity.
	Particle(Texture* a_texture, glm::vec4 a_emitterPos, glm::vec4 a_direction,
		float a_velocity, float a_gravity, glm::vec3 a_size, glm::vec4 a_startColour,
		glm::vec4 a_endColour, float a_lifeSpan);

	/*						//
	//						//
	//		OTHER STUFF		//
	//						//
	//						*/

	bool UpdateAndCheckIfAlive(const float a_fDeltaTime);
	void addToCurrentLifeTime(float a_fTime);

	void restartParticle(Texture* a_texture, glm::vec4 a_emitterPos, glm::vec4 a_direction, float a_velocity, float a_gravity, glm::vec3 a_size, glm::vec4 a_startColour, glm::vec4 a_endColour, float a_lifeSpan);

	//void reInitialise(Texture* a_texture, glm::vec4 a_emitterPos, glm::vec4 a_direction, float a_velocity, glm::vec3 a_size, glm::vec4 a_startColour, glm::vec4 a_endColour, float a_lifeSpan);

	/*						//
	//						//
	//		SET SECTION		//
	//						//
	//						*/

	void setTexture(Texture* a_texture);
	void setEmitterPosition(glm::vec4 a_pos);
	void setPosition(glm::vec4 a_pos);
	void setDirection(glm::vec4 a_direction);
	void setVelocity(float a_velocity);
	void setGravity(float a_gravity);
	void setSize(glm::vec3 a_size);
	void setColour(glm::vec4 a_colour);
	void setStartColour(glm::vec4 a_colour);
	void setEndColour(glm::vec4 a_colour);
	void setAlpha(float a_alpha);
	void setLifeSpan(float a_lifeSpan);
	void setAlive(bool a_live);


	/*						//
	//						//
	//		GET SECTION		//
	//						//
	//						*/

	void getTexture(Texture& a_texture);
	void getEmitterPosition(glm::vec4& a_pos);
	void getPosition(glm::vec4& a_pos);
	glm::vec4 getPosition();
	void getDirection(glm::vec4& a_direction);
	glm::vec4 getDirection();
	void getVelocity(float& a_velocity);
	float getVelocity();
	float getGravity();
	void getSize(glm::vec3& a_size);
	glm::vec4 getColour();
	void getColour(glm::vec4& a_colour);
	glm::vec4 getStartColour();
	glm::vec4 getEndColour();
	void getLifeSpan(float& a_lifespan);
	float getLifeSpan();//Returns lifeTimeInSeconds
	float getCurrentLifeTime();
	bool  getAlive();

private:

	Transform m_transform;//Contains multiple variables like position etc.

	Texture* m_texture;
	bool hasTexture = false;

	float m_lifetimeInSeconds;
	float m_currentLifeTime = 0;
	bool isAlive = false;

};

#endif
