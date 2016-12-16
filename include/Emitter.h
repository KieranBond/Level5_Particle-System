#pragma once
#ifndef __EMITTER_H__
#define __EMITTER_H__

#include <glm/glm.hpp>
#include "Transform.h"
#include <mutex>

#define MAX_PARTICLES 65536

class Particle;
class Texture;

class Emitter
{
public:

	/*
	//
	//	Constructors
	//
	*/

	Emitter();
	Emitter(glm::vec4 a_pos, glm::vec4 a_direction);
	Emitter(glm::vec4 a_pos, glm::vec4 a_direction, float a_radius, glm::vec3 a_particleSize, float a_particleLifeSpan, float a_emitRate, float a_emitVelocity, bool a_emitting = true);
	~Emitter();

	/*
	//
	//	Other functions
	//
	*/

	void Update(const float a_fDeltaTime);
	void UpdateWithThread(const float a_fDeltaTime, int index, int indexEnd);
	void threadUpdate(const float a_fDeltaTime);
	void Draw(glm::mat4 a_camerMat);
	void DrawWithThread(glm::mat4 a_cameraMat, int index, int indexEnd);
	void threadDraw(glm::mat4 a_cameraMat);

	void EmitToggle(const bool a_emit);
	void applyTextureToAll(Texture* a_texture);

	/*
	//
	//	Get functions
	//
	*/

	float getEmitRate();
	float getEmitVelocity();
	glm::vec4 getPosition();
	void getPosition(glm::vec4& a_pos);
	glm::vec4 getDirection();
	void getDirection(glm::vec4& a_dir);
	float getRadius();
	float getGravity();
	glm::vec4 getMaxRandDirection();
	glm::vec4 getMaxRandPosition();
	float getMaxRandVelocity();

	/*
	//
	//	Particle gets.
	//
	*/

	float getParticleLifeSpan();
	Particle* getParticle(int index);
	glm::vec3 getParticleSize();
	glm::vec4 getParticleColour(int index);//Gets particle[i] current colour
	glm::vec4 getParticleStartColour();//Gets default particle start colour
	glm::vec4 getParticleStartColour(int index);//Gets particle[i] start colour
	glm::vec4 getParticleEndColour();//Gets default end colour
	glm::vec4 getParticleEndColour(int index);//Gets particle[i] end colour

	/*
	//
	//	Set functions
	//
	*/

	void setEmitRate(const float a_emitRate);
	void setEmitVelocity(const float a_emitVel);
	void setPosition(const glm::vec4 a_pos);
	void setDirection(const glm::vec4 a_dir);
	void setRadius(float a_radius);
	void setGravity(float a_gravity);
	void setMaxRandDirection(float a_randDir);
	void setMaxRandPosition(float a_randPos);
	void setMaxRandVelocity(float a_randVel);

	/*
	//
	// Particle sets
	//
	*/

	void setParticleLifeSpan(float a_time);
	void setParticleSize(glm::vec3 a_size);
	void setParticleColour(int index, glm::vec4 a_colour);//Sets particle[i] colour
	void setParticleStartColour(glm::vec4 a_colour);//sets default start colour
	void setParticleStartColour(int index, glm::vec4 a_colour);//Sets start colour for particle[i]
	void setParticleEndColour(glm::vec4 a_colour);//Sets default end colour
	void setParticleEndColour(int index, glm::vec4 a_colour);//Sets particle[i]'s end colour



	const int m_maxParticles = MAX_PARTICLES;//Change max particles if I want to change how many are done per frame.

private:

	/*
	//
	//	Private functions
	//
	*/
	static const int maxNumOfThreads = 30;//Thread max
	std::mutex updateMute;//Update threads mutex
	std::mutex drawMute;//Draw threads mutex

	void initialiseParticles();
	void nullParticles();

	//float getRand(float min, float max);//Gets a random float between min and max.
	glm::vec4 getRandomDirection();//Uses glm to return a linearRand direction
	glm::vec4 getRandomPosition();//Uses glm to return a linearRand pos
	float getRandomVelocity();
	bool flip();//Randomly returns true or false.


	//Contains info like position, direction, etc
	Transform m_transform;

	bool isEmitting = false;
	float m_emitRatePerFrame = 0;
	float m_emitCount = 0;


	Particle* m_particleArray[MAX_PARTICLES];
	int m_particleCount = 0;


	glm::vec3 m_particleSize;
	float m_particleLifeSpan;

	glm::vec4 m_maxDirectionVariance = glm::vec4(0,0,0,0);

	float m_maxSpeedVariance = 1.5f;

	glm::vec4 m_minimumPositionVariance = glm::vec4(0.f, 0.f, 0.f, 0.f);
	glm::vec4 m_maximumPositionVariance = glm::vec4(3.5f, 3.5f, 3.5f, 3.5f);

};

#endif