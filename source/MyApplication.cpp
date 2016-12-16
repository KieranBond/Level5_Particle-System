#include "MyApplication.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include <iostream>

#include "TextureManager.h"
#include "Particle.h"
#include "Emitter.h"

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

MyApplication::MyApplication()
{

}

MyApplication::~MyApplication()
{

}

bool MyApplication::onCreate(int a_argc, char* a_argv[])
{
	// initialise the Gizmos helper class
	Gizmos::create();

	emitterOne = new Emitter(glm::vec4(10,0,0,0), glm::vec4(1.2, 1.2, 1.2, 0));//x, y, z, w
	emitterOne->setRadius(0.f);//Bigger = more cone. Goes in every direction
	emitterOne->setEmitRate(0.2f);//Smaller - More spawn more frequently
	emitterOne->setEmitVelocity(30.f);//How fast this rocket goes
	emitterOne->setGravity(0.2f);//Small is big
	emitterOne->setParticleLifeSpan(200.f);//The bigger the longer
	emitterOne->setMaxRandDirection(30.f);//Adds this onto direction
	emitterOne->setMaxRandPosition(3.f);//How far in any direction particles spawn from emitter pos
	emitterOne->setMaxRandVelocity(5.f);//How much velocity can vary from set velocity.
	emitterOne->setParticleStartColour(glm::vec4(0.3f, 0.1f, 0.f, 0.3f));//Red.
	//0.f, 0.f, 0.f, 0.3f//Black colour
	emitterOne->setParticleEndColour(glm::vec4(0.08f, 0.08f, 0.08f, 0.f));//Dark grey. 0 alpha to make it fade
	emitterOne->EmitToggle(true);

	/*
	//emitterTwo = new Emitter(glm::vec4(10, 0, 0, 0), glm::vec4(1.2, 1.2, 1.2, 0));//x, y, z, w
	//emitterTwo->setEmitRate(0.2f);//Smaller - More spawn more frequently
	//emitterTwo->setEmitVelocity(10);
	//emitterTwo->setParticleLifeSpan(400);
	//emitterTwo->setMaxRandDirection(0.2f);
	//emitterTwo->setMaxRandPosition(1.f);
	//emitterTwo->setMaxRandVelocity(5.f);
	//emitterTwo->setParticleStartColour(glm::vec4(0.3f, 0.1f, 0.f, 0.3f));//Red/Amber.
	//emitterTwo->setParticleEndColour(glm::vec4(0.08f, 0.08f, 0.08f, 0.f));//Dark grey. 0 alpha to make it fade
	//emitterTwo->EmitToggle(true);
	*/

	//Initialise our Texture Manager class
	//TextureManager* texManager = TextureManager::CreateInstance();
	//unsigned int texID = texManager->LoadTexture("./images/bae.jpg");
	//unsigned int texID2 = texManager->LoadTexture("./images/bae.jpg");
	//unsigned int texID3 = texManager->LoadTexture("./images/bae.jpg");
	//
	//texManager->ReleaseTexture(texID2);
	//texManager->ReleaseTexture(texID3);
	//texManager->ReleaseTexture(texID);

	// create a world-space matrix for a camera
	m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
	
	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	return true;
}

void MyApplication::onUpdate(float a_deltaTime)
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform(glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	Gizmos::addCylinderFilled(glm::vec3(0.f, 2.f, 0.f), 2.f, 4, 20, glm::vec4(0.4f, 0.2f, 0.6f, 1.f));

	// add a 20x20 grid on the XZ-plane
	for ( int i = 0 ; i < 21 ; ++i )
	{
		Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
		
		Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
						 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	}


	emitterOne->threadUpdate(a_deltaTime);
	//emitterOne->Update(a_deltaTime);//Update all particles - Use this if you want to disable multi-threading.

	Particle* p;

	//emitterOne->threadDraw(m_cameraMatrix);//This draws with threads - Doesn't seem to make it better though.
	emitterOne->Draw(m_cameraMatrix);//Just draws normally. Through the emitter.

	//Particle* p2;

	//int jankCount = 0;
	//
	//for (int i = 0; i < emitterOne->m_maxParticles; i++)//For each particle.
	//{
	//	//emitterOne->Update(a_deltaTime);
	//
	//	p = emitterOne->getParticle(i);//Gets Particle[index]
	//	//p2 = emitterTwo->getParticle(i);
	//
	//	if (p)//if not null
	//	{
	//		if (p->getAlive()) //If alive
	//		{
	//			jankCount++;
	//			Gizmos::addBillboard(glm::vec3(p->getPosition()), glm::vec3(1, 1, 1), p->getColour(), m_cameraMatrix);//Draws a billboard
	//		}
	//
	//		//if (p2)//if not null
	//		//{
	//		//	if (p2->getAlive()) //If alive
	//		//	{
	//		//		//p2Alive = true;
	//		//		Gizmos::addBillboard(glm::vec3(p2->getPosition()), glm::vec3(1, 1, 1), p2->getColour(), m_cameraMatrix);
	//		//	}
	//		//}
	//	}
	//}

	//std::cout << "FPS: " << 1 / a_deltaTime << "   " << "Particles: " << jankCount << std::endl;
	std::cout << " FPS: " << 1 / a_deltaTime << std::endl;

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void MyApplication::onDraw()
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(viewMatrix, m_projectionMatrix);
}

void MyApplication::onDestroy()
{
	// clean up anything we created
	TextureManager::DestroyInstance();

	delete emitterOne;
	emitterOne = nullptr;

	Gizmos::destroy();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	MyApplication* app = new MyApplication();
	
	if (app->create("Test Project",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}