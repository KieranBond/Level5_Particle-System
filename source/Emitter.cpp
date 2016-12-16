#include "glm\ext.hpp"
#include "Emitter.h"
#include "Particle.h"
#include "Texture.h"
#include <thread>
#include <stdlib.h>
#include <iostream>
#include "Gizmos.h"

/*						  /*
//						  //
//		CONSTRUCTORS	  //
//		& other stuff	  //
//						  //
//						  */

Emitter::Emitter()
{
	//initialiseParticles();
}

Emitter::Emitter(glm::vec4 a_pos, glm::vec4 a_direction)
{
	nullParticles();

	setPosition(a_pos);
	setDirection(glm::normalize(a_direction));

	//initialiseParticles();
}

Emitter::Emitter(glm::vec4 a_pos, glm::vec4 a_direction, float a_radius, glm::vec3 a_particleSize, float a_particleLifeSpan, float a_emitRate, float a_emitVelocity, bool a_emitting)
{
	nullParticles();

	setPosition(a_pos);
	setDirection(glm::normalize(a_direction));
	setRadius(glm::normalize(a_radius));
	m_particleSize = a_particleSize;//Need to make function
	setParticleLifeSpan(a_particleLifeSpan);
	setEmitRate(a_emitRate);
	setEmitVelocity(a_emitVelocity);
	EmitToggle(a_emitting);

	//initialiseParticles();
}

Emitter::~Emitter()
{
}

void Emitter::EmitToggle(const bool a_emit)
{
	isEmitting = a_emit;
}

void Emitter::applyTextureToAll(Texture* a_texture)
{
	if (a_texture)
	{
		for (int i = 0; i < MAX_PARTICLES; i++)
		{
			if (m_particleArray[i]) m_particleArray[i]->setTexture(a_texture);
		}
	}
}

//void Emitter::Update(float a_fDeltaTime)
//{
//
//	if (m_particleCount <= MAX_PARTICLES)//If we've not got all our particles out
//	{
//		for (int n = 0; n < MAX_PARTICLES; n++)//This is so we can find any of our null ones - Might be the last one.
//		{
//			if (!m_particleArray[n])//If it's null
//			{
//				m_particleArray[n] = new Particle(NULL, m_pos,
//					glm::normalize(getRandomDirection()), m_emitVelocity,
//					m_particleSize, glm::vec4(255, 255, 255, 255),
//					m_particleLifeSpan);//Creates a new particle.
//
//				m_particleArray[n]->setAlive(true);
//				m_particleArray[n]->UpdateAndCheckIfAlive(a_fDeltaTime);
//
//				m_particleCount++;//Add to particle count
//				//break;
//			}
//		}
//	}
//
//
//	for (int i = 0; i < MAX_PARTICLES; i++)//For each particle
//	{
//
//		if (m_particleArray[i])//If not null.
//		{
//			if (!(m_particleArray[i]->UpdateAndCheckIfAlive(a_fDeltaTime))) //If not alive, let's delete whatever was there(if anything) and set it to null.
//			{
//
//				delete m_particleArray[i];
//				m_particleArray[i] = nullptr;
//				m_particleCount--;//Remove one from particle count
//			}
//			else
//			{
//				m_particleArray[i]->setDirection(glm::normalize(getRandomDirection()));
//				
//			}
//
//		}
//	}
//
//}

void Emitter::Update(const float a_fDeltaTime)
{
	m_emitCount += a_fDeltaTime;//Add to our timer

	if (m_emitCount > m_emitRatePerFrame)//If we're not over our count
	{
		for (int n = 0; n < 256; n++)//Displaced spawning
		{
			for (int j = 0; j < MAX_PARTICLES; j++)//For every particle - this is the spawn loop
			{
				if (!(m_particleArray[j]))//If it's null
				{
					//PUMP ONE OUTTTTTTTT

					m_particleArray[j] = new Particle(NULL, getRandomPosition(), getRandomDirection(),
						getRandomVelocity(), getGravity(), getParticleSize(), getParticleStartColour(), getParticleEndColour(), getParticleLifeSpan());

					m_particleCount++;//Add to the count.

					break;
				}
			}
		}
		m_emitCount = 0;
	}


	for (int i = 0; i < MAX_PARTICLES; i++)//for every particle - This is the update loop
	{
		if (m_particleArray[i])//If not null
		{
			if (!(m_particleArray[i]->UpdateAndCheckIfAlive(a_fDeltaTime)))//Update it. If not alive though - 
			{
				delete m_particleArray[i];	 //Destroy this shit
				m_particleArray[i] = nullptr;//Destroy this shit

				m_particleCount--;//Remove one from the particle counter
			}
		}
	}
}

void Emitter::UpdateWithThread(float a_fDeltaTime, int index, int indexEnd)
{
	m_emitCount += a_fDeltaTime;//Add to our timer

	//int threadSect = (MAX_PARTICLES / maxNumOfThreads) * index;//(10k / 10) * 1,2,3

	//int threadSectEnd = threadSect*index;
	//if (threadSect == 10)//To allow us to start on first 10 of array
	//{
	//	threadSect = 0;
	//}
	updateMute.try_lock();

	if (m_emitCount > m_emitRatePerFrame)//If we're not over our count
	{
		for (int n = 0; n < 256; n++)//Displaced spawning
		{
			for (int j = index; j < indexEnd; j++)//For every particle - this is the spawn loop
			{
				if (!(m_particleArray[j]))//If it's null
				{
					//PUMP ONE OUTTTTTTTT
					m_particleArray[j] = new Particle(NULL, getRandomPosition(), getRandomDirection(),
					getRandomVelocity(), getGravity(), getParticleSize(), getParticleStartColour(), getParticleEndColour(), getParticleLifeSpan());

					m_particleCount++;//Add to the count.

					//break;
				}
				else
				{
					if (m_particleArray[j])
					{


						//reinitialise particle
						m_particleArray[j]->restartParticle(NULL, getRandomPosition(), getRandomDirection(),
							getRandomVelocity(), getGravity(), getParticleSize(), getParticleStartColour(), getParticleEndColour(), getParticleLifeSpan());

						m_particleCount++;

						break;
					}
					
				}

			}
		}
		m_emitCount = 0;
	}


	for (int i = index; i < indexEnd; i++)//for every particle - This is the update loop
	{
		if (m_particleArray[i])//If not null
		{
			if (!(m_particleArray[i]->UpdateAndCheckIfAlive(a_fDeltaTime)))//Update it. If not alive though - 
			{
				//delete m_particleArray[i];	 //Destroy this shit
				if(m_particleArray[i])
				{
					m_particleArray[i]->setAlive(false);
				m_particleArray[i] = nullptr;//Destroy this shit

				m_particleCount--;//Remove one from the particle counter
				}
			}
		}
	}

	updateMute.unlock();
}

void Emitter::threadUpdate(float a_fDeltaTime)
{
	std::thread m_threads[maxNumOfThreads];

	//Need another for loop. One to go through each thread - One to track what range of particles each thread works on


	
	int maxPerThread = MAX_PARTICLES / maxNumOfThreads;
	int beg = 0;
	int end = maxPerThread;

	for(int i = 0; i < maxNumOfThreads; i++)
	{
		m_threads[i] = std::thread(&Emitter::UpdateWithThread, this, a_fDeltaTime, beg, end);
		beg = end + 1;
		end = i*maxPerThread-1;

		bool unlocked = false;

		do
		{
			unlocked = m_threads[i].joinable();

			if (unlocked)
			{
				m_threads[i].join();
			}

		} while (unlocked = false);
	}


	for (int i = 0; i < maxNumOfThreads; i++)
	{
		if (m_threads[i].joinable())//If the thread is done.
		{
			//m_threads[i].join();//Join it back in.
			m_threads[i].~thread();
		}
	}
}

void Emitter::Draw(glm::mat4 a_cameraMat)
{
	int jankCount = 0;//Particle counter

	Particle* p;

	for (int i = 0; i < m_maxParticles; i++)//For each particle.
	{
		p = getParticle(i);//Gets Particle[index]
									  
		if (p)//if not null
		{
			if (p->getAlive()) //If alive
			{				
				jankCount++;
				Gizmos::addBillboard(glm::vec3(p->getPosition()), glm::vec3(1, 1, 1), p->getColour(), a_cameraMat);//Draws a billboard
			}
		}
	}

	std::cout << "Particles: " << jankCount << " ";
}

void Emitter::DrawWithThread(glm::mat4 a_cameraMat, int index, int indexEnd)
{
	//int jankCount = 0;//Particle counter

	Particle* p;

	drawMute.try_lock();

	for (int j = index; j < indexEnd; j++)//For every particle in this threads range - this is the draw loop
	{
		p = getParticle(j);//Gets Particle[index]

		if (p)//if not null
		{
			if (p->getAlive()) //If alive
			{
				//jankCount++;
				Gizmos::addBillboard(glm::vec3(p->getPosition()), glm::vec3(1, 1, 1), p->getColour(), a_cameraMat);//Draws a billboard
			}
		}
	}

	drawMute.unlock();

	//std::cout << "Particles: " << jankCount << " ";
}

void Emitter::threadDraw(glm::mat4 a_cameraMat)
{
	std::thread m_threads[maxNumOfThreads];


	int maxPerThread = MAX_PARTICLES / maxNumOfThreads;
	int beg = 0;
	int end = maxPerThread;

	for (int i = 0; i < maxNumOfThreads; i++)
	{
		m_threads[i] = std::thread(&Emitter::DrawWithThread, this, a_cameraMat, beg, end);
		beg = end + 1;
		end = i*maxPerThread - 1;

		bool unlocked = false;

		do
		{
			unlocked = m_threads[i].joinable();
		
			if (unlocked)
			{
				m_threads[i].join();
			}
		
		} while (unlocked = false);
	}

	for (int i = 0; i < maxNumOfThreads; i++)
	{
		//if (m_threads[i].joinable())//If the thread is done.
		//{
			//m_threads[i].join();//Join it back in.
			m_threads[i].~thread();
		//}
	}
}

/*						//
//						//
//		GET SECTION		//
//						//
//						*/

float Emitter::getEmitRate()
{
	return m_emitRatePerFrame;
}

float Emitter::getEmitVelocity()
{
	//return m_emitVelocity;
	return m_transform.velocity;
}

glm::vec4 Emitter::getPosition()
{
	//return m_pos;
	return m_transform.position;
}

void Emitter::getPosition(glm::vec4& a_pos)
{
	//a_pos = m_pos;
	a_pos = m_transform.position;
}

glm::vec4 Emitter::getDirection()
{
	//return m_emitDirection;
	return m_transform.direction;
}

void Emitter::getDirection(glm::vec4& a_dir)
{
	//a_dir = m_emitDirection;
	a_dir = m_transform.direction;
}

float Emitter::getRadius()
{
	return m_transform.radius;
}

float Emitter::getGravity()
{
	return m_transform.gravity;
}

glm::vec4 Emitter::getMaxRandDirection()
{
	return m_maxDirectionVariance;
}

glm::vec4 Emitter::getMaxRandPosition()
{
	return m_maximumPositionVariance;
}

float Emitter::getMaxRandVelocity()
{
	return m_maxSpeedVariance;
}


/*						//
//						//
// PARTICLE GET SECTION //
//						//
//						*/


float Emitter::getParticleLifeSpan()
{
	return m_particleLifeSpan;
}

Particle* Emitter::getParticle(int index)
{
	return m_particleArray[index];
}

glm::vec3 Emitter::getParticleSize()
{
	return m_particleSize;
}

glm::vec4 Emitter::getParticleColour(int index)
{
	if (m_particleArray[index])
	{
		return m_particleArray[index]->getColour();
	}
	else return glm::vec4(0, 0, 0, 0);
}

glm::vec4 Emitter::getParticleStartColour()
{
	//return m_particleStartColour;
	return m_transform.startColour;
}

glm::vec4 Emitter::getParticleStartColour(int index)
{
	if (m_particleArray[index])
	{
		return m_particleArray[index]->getStartColour();
	}
	else return glm::vec4(0, 0, 0, 0);
}

glm::vec4 Emitter::getParticleEndColour()
{
	//return m_particleEndColour;
	return m_transform.endColour;
}

glm::vec4 Emitter::getParticleEndColour(int index)
{
	if (m_particleArray[index])
	{
		return m_particleArray[index]->getEndColour();
	}
	else return glm::vec4(0, 0, 0, 0);
}

/*						//
//						//
//		SET SECTION		//
//						//
//						*/

void Emitter::setEmitRate(const float a_emitRate)
{
	m_emitRatePerFrame = a_emitRate;
}  

void Emitter::setEmitVelocity(const float a_emitVel)
{
	//m_emitVelocity = a_emitVel;
	m_transform.velocity = a_emitVel;

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (m_particleArray[i]) m_particleArray[i]->setVelocity(m_transform.velocity);
	}
}

void Emitter::setPosition(const glm::vec4 a_pos)
{
	//m_pos = a_pos;
	m_transform.position = a_pos;

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		//if (m_particleArray[i]) m_particleArray[i]->setEmitterPosition(m_pos);
		if (m_particleArray[i]) m_particleArray[i]->setEmitterPosition(m_transform.position);
	}
}

void Emitter::setDirection(const glm::vec4 a_dir)
{
	//m_emitDirection = glm::normalize(a_dir);
	m_transform.direction = glm::normalize(a_dir);

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if(m_particleArray[i]) m_particleArray[i]->setDirection(glm::normalize(getRandomDirection()));
	}
}

void Emitter::setRadius(float a_radius)
{
	m_transform.radius = a_radius;
}

void Emitter::setGravity(float a_gravity)
{
	m_transform.gravity = a_gravity;
}

void Emitter::setMaxRandDirection(float a_maxRand)
{
	m_maxDirectionVariance = m_transform.direction + a_maxRand;//Gets our direction, then adds it onto each axis'
}

void Emitter::setMaxRandPosition(float a_maxRand)
{
	m_maximumPositionVariance = m_transform.position + a_maxRand;//Makes it bigger than our position, then adds the random on all axis'
	
}

void Emitter::setMaxRandVelocity(float a_maxRand)
{
	m_maxSpeedVariance = a_maxRand;
}


/*						//
//						//
// PARTICLE SET SECTION //
//						//
//						*/


void Emitter::setParticleLifeSpan(float a_time)
{
	m_particleLifeSpan = a_time;

	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (m_particleArray[i]) m_particleArray[i]->setLifeSpan(m_particleLifeSpan);
	}
}

void Emitter::setParticleSize(glm::vec3 a_size)
{
	m_transform.scale = a_size;
	m_particleSize = a_size;
}

void Emitter::setParticleColour(int index, glm::vec4 a_colour)
{
	if (m_particleArray[index])
	{
		m_particleArray[index]->setColour(a_colour);
	}
}

void Emitter::setParticleStartColour(glm::vec4 a_colour)
{
	m_transform.startColour = a_colour;
}

void Emitter::setParticleStartColour(int index, glm::vec4 a_colour)
{
	if (m_particleArray[index])
	{
		m_particleArray[index]->setStartColour(a_colour);
	}
}

void Emitter::setParticleEndColour(glm::vec4 a_colour)
{
	m_transform.endColour = a_colour;
}

void Emitter::setParticleEndColour(int index, glm::vec4 a_colour)
{
	if (m_particleArray[index])
	{
		m_particleArray[index]->setEndColour(a_colour);
	}
}

/*						/*
//						//
//		OTHER SECTION	//
//						//
//						*/


void Emitter::initialiseParticles()
{
	for (int i = 0; i < MAX_PARTICLES; i++)
	{
		if (!(m_particleArray[i]))
		{
			m_particleArray[i] = new Particle(m_transform.position);
			m_particleArray[i]->setAlive(false);
		}
	}
}

void Emitter::nullParticles()
{
	for(int i = 0; i < MAX_PARTICLES; i++)
	{		
		m_particleArray[i] = nullptr;
	}
}

//float Emitter::getRand(float min, float max)
//{
//	srand((time(NULL)+time(NULL)+time(NULL))+time(NULL));//Random seed with time each time performed.
//
//	int tempMin = min * 1000;//Try to lose minimum data
//	int tempMax = max * 1000;//Try to lose minimum data
//	int diff = tempMax - tempMin + 1;
//
//	float r = rand() % diff + tempMin;
//
//	return r /= 100;
//}

glm::vec4 Emitter::getRandomDirection()
{
	//glm::vec4 ranDirection(glm::linearRand(m_emitDirection.x, m_maxDirectionVariance), 
	//						glm::linearRand(m_emitDirection.y, m_maxDirectionVariance), 
	//						glm::linearRand(m_emitDirection.z, m_maxDirectionVariance),
	//						glm::linearRand(m_emitDirection.w, m_maxDirectionVariance));

	float m_rad = getRadius();

	glm::vec4 ranDirection(glm::linearRand(m_transform.direction.x-m_rad, m_maxDirectionVariance.x+m_rad),//-radius, +radius
						   glm::linearRand(m_transform.direction.y-m_rad, m_maxDirectionVariance.y+m_rad),
						   glm::linearRand(m_transform.direction.z-m_rad, m_maxDirectionVariance.z+m_rad),
						   glm::linearRand(m_transform.direction.w-m_rad, m_maxDirectionVariance.w+m_rad));

	return ranDirection;	
}

glm::vec4 Emitter::getRandomPosition()
{
	//glm::vec4 ranPosition(glm::linearRand(m_pos.x, m_maximumPositionVariance),
	//					  glm::linearRand(m_pos.y, m_maximumPositionVariance),
	//					  glm::linearRand(m_pos.z, m_maximumPositionVariance),
	//					  glm::linearRand(m_pos.w, m_maximumPositionVariance));

	glm::vec4 ranPosition(glm::linearRand(m_transform.position.x, m_maximumPositionVariance.x),
						  glm::linearRand(m_transform.position.y, m_maximumPositionVariance.y),
						  glm::linearRand(m_transform.position.z, m_maximumPositionVariance.z),
						  glm::linearRand(m_transform.position.w, m_maximumPositionVariance.w));

	return ranPosition;
}

float Emitter::getRandomVelocity()
/*
	Uses glm's linearRand function to get a float between our velocity and max variance.
*/
{
	float ranVel = glm::linearRand(m_transform.velocity, m_maxSpeedVariance);

	return ranVel;
}

bool Emitter::flip()
{
	srand(time(NULL)*2);

	int r = rand() % 2;//Should return either 1 or 0.

	bool flip = false;
	if (r == 0) flip = true;

	return flip;
}