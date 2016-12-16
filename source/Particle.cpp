#include "Particle.h"
#include "Texture.h"
#include "glm\ext.hpp"

/*						  /*
//						  //
//		CONSTRUCTORS	  //
//		& other stuff	  //
//						  //
//						  */

Particle::Particle()
{

}

Particle::~Particle()
{

}

Particle::Particle(Texture* a_texture)
{
	m_texture = a_texture;
}

Particle::Particle(glm::vec4 a_pos)
{
	m_transform.parentPosition = a_pos;
	m_transform.position = a_pos;
}

Particle::Particle(Particle& a_particle)
{
	*this = a_particle;
}

//Main constructor without gravity.
Particle::Particle(Texture* a_texture, glm::vec4 a_emitterPos, glm::vec4 a_direction, 
				   float a_velocity, glm::vec3 a_size, glm::vec4 a_startColour, glm::vec4 a_endColour, float a_lifeSpan)
{
	m_texture = a_texture;
	m_lifetimeInSeconds = a_lifeSpan;

	//Set all the transforms
	m_transform.position = a_emitterPos;
	m_transform.parentPosition = a_emitterPos;
	m_transform.direction = a_direction;
	m_transform.velocity = a_velocity;
	m_transform.gravity = 0;//Set this just incase.
	m_transform.scale = a_size;
	m_transform.colour = a_startColour;
	m_transform.startColour = a_startColour;
	m_transform.endColour = a_endColour;
}

//Main constructor with gravity.
Particle::Particle(Texture* a_texture, glm::vec4 a_emitterPos, glm::vec4 a_direction,
	float a_velocity, float a_gravity, glm::vec3 a_size, glm::vec4 a_startColour, glm::vec4 a_endColour, float a_lifeSpan)
{
	m_texture = a_texture;
	m_lifetimeInSeconds = a_lifeSpan;

	//Set all the transforms
	m_transform.position = a_emitterPos;
	m_transform.parentPosition = a_emitterPos;
	m_transform.direction = a_direction;
	m_transform.velocity = a_velocity;
	m_transform.gravity = -a_gravity;//Flip it for the calc later.
	m_transform.scale = a_size;
	m_transform.colour = a_startColour;
	m_transform.startColour = a_startColour;
	m_transform.endColour = a_endColour;
}


//void Particle::Update(const float a_fDeltaTime)
//{
//	m_currentLifeTime++;
//
//	if (m_currentLifeTime < m_lifetimeInSeconds)
//	{
//		isAlive = true;
//		
//
//		m_pos += (glm::normalize(m_direction) * m_velocity) * a_fDeltaTime;
//
//	}
//	else
//	{
//		isAlive = false;
//	}
//}

bool Particle::UpdateAndCheckIfAlive(const float a_fDeltaTime)
{
	if (this)
	{
		if (m_currentLifeTime == 0 && isAlive)
		{
			//Sets it up ready to go on its journey
			m_transform.position = m_transform.parentPosition;
		}

		m_currentLifeTime++;

		if (m_currentLifeTime < m_lifetimeInSeconds)
		{
			m_transform.direction += glm::vec4(0.f, getGravity(), 0.f, 0.f);//Adds gravity effect

			m_transform.position += (glm::normalize(getDirection()) * m_transform.velocity) * a_fDeltaTime;

			m_transform.colour = glm::mix(m_transform.startColour, m_transform.endColour, m_currentLifeTime / m_lifetimeInSeconds);
			isAlive = true;
			return true;
		}
		else
		{
			isAlive = false;
			return false;
		}
	}
	return false;
}

void Particle::addToCurrentLifeTime(float a_fTime)
{
	m_currentLifeTime += a_fTime;
}

void Particle::restartParticle(Texture* a_texture, glm::vec4 a_emitterPos, glm::vec4 a_direction, float a_velocity, float a_gravity, glm::vec3 a_size, glm::vec4 a_startColour, glm::vec4 a_endColour, float a_lifeSpan)
{
	if (this)
	{
		setTexture(a_texture);
		setEmitterPosition(a_emitterPos);
		setDirection(a_direction);
		setVelocity(a_velocity);
		setGravity(a_gravity);
		setSize(a_size);
		setStartColour(a_startColour);
		setEndColour(a_endColour);
		setLifeSpan(a_lifeSpan);

		isAlive = true;
	}
}

//void Particle::reIntialise(Texture* a_texture, glm::vec4 a_emitterPos, glm::vec4 a_direction, float a_velocity, float a_gravity, glm::vec3 a_size, glm::vec4 a_startColour, glm::vec4 a_endColour, float a_lifeSpan)
//{
//	setTexture(a_texture);
//
//}


/*						/*
//						//
//		SET SECTION		//
//						//
//						*/

void Particle::setTexture(Texture* a_texture)
{
	m_texture = a_texture;
}

void Particle::setEmitterPosition(glm::vec4 a_pos)
{
	//m_emitterPos = a_pos;
	m_transform.parentPosition = a_pos;
}

void Particle::setPosition(glm::vec4 a_pos)
{
	//m_pos = a_pos;
	m_transform.position = a_pos;
}

void Particle::setDirection(glm::vec4 a_direction)
{
	//m_direction = a_direction;
	m_transform.direction = a_direction;
}

void Particle::setVelocity(float a_velocity)
{
	//m_velocity = a_velocity;
	m_transform.velocity = a_velocity;
}

void Particle::setGravity(float a_gravity)
{
	m_transform.gravity = -a_gravity;
}

void Particle::setSize(glm::vec3 a_size)
{
	//m_size = a_size;
	m_transform.scale = a_size;
}

void Particle::setColour(glm::vec4 a_colour)
{
	//m_colour = a_colour;
	m_transform.colour = a_colour;
}

void Particle::setStartColour(glm::vec4 a_colour)
{
	m_transform.startColour = a_colour;
}

void Particle::setEndColour(glm::vec4 a_colour)
{
	m_transform.endColour = a_colour;
}

void Particle::setAlpha(float a_alpha)
{
	//m_colour.a = a_alpha;
	m_transform.colour.a = a_alpha;
}

void Particle::setLifeSpan(float a_lifeSpan)
{
	m_lifetimeInSeconds = a_lifeSpan;
}

void Particle::setAlive(bool a_live)
{
	isAlive = a_live;
}

/*						/*
//						//
//		GET SECTION		//
//						//
//						*/


void Particle::getTexture(Texture& a_texture)
{
	a_texture = *m_texture;
}

void Particle::getEmitterPosition(glm::vec4& a_pos)
{
	//a_pos = m_emitterPos;
	a_pos = m_transform.parentPosition;
}

void Particle::getPosition(glm::vec4& a_pos)
{
	//a_pos = m_pos;
	a_pos = m_transform.position;
}

glm::vec4 Particle::getPosition()
{
	//return m_pos;
	return m_transform.position;
}

void Particle::getDirection(glm::vec4& a_direction)
{
	//a_direction = m_direction;
	a_direction =  m_transform.direction;
}

glm::vec4 Particle::getDirection()
{
	return m_transform.direction;
}

void Particle::getVelocity(float& a_velocity)
{
	//a_velocity = m_velocity;
	a_velocity = m_transform.velocity;
}

float Particle::getVelocity()
{
	//return m_velocity;
	return m_transform.velocity;
}

float Particle::getGravity()
{
	return m_transform.gravity;
}

void Particle::getSize(glm::vec3& a_size)
{
	//a_size = m_size;
	a_size = m_transform.scale;
}

glm::vec4 Particle::getColour()
{
	return m_transform.colour;
}

void Particle::getColour(glm::vec4& a_colour)
{
	//a_colour = m_colour;
	a_colour = m_transform.colour;
}

glm::vec4 Particle::getStartColour()
{
	return m_transform.startColour;
}

glm::vec4 Particle::getEndColour()
{
	return m_transform.endColour;
}

void Particle::getLifeSpan(float& a_lifeSpan)
{
	a_lifeSpan = m_lifetimeInSeconds;
}

float Particle::getLifeSpan()
{
	return m_lifetimeInSeconds;
}

float Particle::getCurrentLifeTime()
{
	return m_currentLifeTime;
}

bool Particle::getAlive()
{
	return isAlive;
}