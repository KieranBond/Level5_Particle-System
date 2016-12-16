#pragma once
#ifndef __TRANSFORM_H__
#define __TRANFORM_H__

#include <glm/glm.hpp>

struct Transform
{

	/*
	//	Variables
	*/

	glm::vec4 parentPosition;//x,y,z,w
	glm::vec4 position;//x,y,z,w
	glm::vec4 direction;//x,y,z,w
	float radius = 0.f;//Modifies the direction - Makes it like a cone
	float gravity = 0.f;//Gravity factor
	glm::vec3 scale;//width, height, depth (X, Y, Z)
	glm::vec4 colour;//RGBA
	glm::vec4 startColour;//rgba
	glm::vec4 midColour;//rgba
	glm::vec4 endColour;//rgba

	float velocity;

	/*
	//	Get functions
	*/

	glm::vec4 getParentPosition()
	{
		return parentPosition;
	}

	glm::vec4 getPosition()
	{
		return position;
	}

	glm::vec4 getDirection()
	{
		return direction;
	}

	float getRadius()
	{
		return radius;
	}

	glm::vec3 getScale()
	{
		return scale;
	}

	glm::vec4 getColour()
	{
		return colour;
	}

	glm::vec4 getStartColour()
	{
		return startColour;
	}

	glm::vec4 getMidColour()
	{
		return midColour;
	}

	glm::vec4 getEndColour()
	{
		return endColour;
	}

	float getVelocity()
	{	
		return velocity;
	}

	/*
	//	Set functions
	*/

	void setParentPosition(glm::vec4 a_position)
	{
		parentPosition = a_position;
	}

	void setPosition(glm::vec4 a_position)
	{
		position = a_position;
	}

	void setDirection(glm::vec4 a_direction)
	{
		direction = a_direction;
	}

	void setRadius(float a_radius)
	{
		radius = a_radius;
	}

	void setScale(glm::vec3 a_scale)
	{
		scale = a_scale;
	}

	void setColour(glm::vec4 a_colour)
	{
		colour = a_colour;
	}

	void setStartColour(glm::vec4 a_colour)
	{
		startColour = a_colour;
	}

	void setMidColour(glm::vec4 a_colour)
	{
		midColour = a_colour;
	}

	void setEndColour(glm::vec4 a_colour)
	{
		endColour = a_colour;
	}

	void setVelocity(float a_velocity)
	{
		velocity = a_velocity;
	}
};

#endif //Transform_H
