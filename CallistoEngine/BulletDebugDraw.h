#pragma once
//https://pybullet.org/Bullet/phpBB3/viewtopic.php?t=11517
// Helper class; draws the world as seen by Bullet.
// This is very handy to see it Bullet's world matches yours
// How to use this class :
// Declare an instance of the class :
// 
// dynamicsWorld->setDebugDrawer(&mydebugdrawer);
// Each frame, call it :
// mydebugdrawer.SetMatrices(ViewMatrix, ProjectionMatrix);
// dynamicsWorld->debugDrawWorld();

#include "Objects/ShaderObject_GL.h"
//#include " ShaderObject_GL.h"
#include <Bullet/LinearMath/btIDebugDraw.h>
#include "Game.h"

class BulletDebugDrawer_OpenGL : public btIDebugDraw
{
private:
	unsigned int VBO, VAO;
	ShaderObject_GL* mShader;

public:
	BulletDebugDrawer_OpenGL()
	{
		mShader = new ShaderObject_GL("Resources/Shaders/BulletLineShader.vert", "Resources/Shaders/BulletLineShader.frag");
	}

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	{
		glDisable(GL_DEPTH_TEST);

	//	mShader* lineShader = AssetManager::Instance().GetShader("Assets/Shaders/DebugView/BulletLineShader");

		mShader->UseProgram();
		mShader->SetMat4("view", Game::GetGame()->GetGameCamera()->GetView());
		mShader->SetMat4("proj", Game::GetGame()->GetGameCamera()->GetProjection());

		// Vertex data
		GLfloat points[12]{};

		points[0] = from.x();
		points[1] = from.y();
		points[2] = from.z();
		points[3] = color.x();
		points[4] = color.y();
		points[5] = color.z();

		points[6] = to.x();
		points[7] = to.y();
		points[8] = to.z();
		points[9] = color.x();
		points[10] = color.y();
		points[11] = color.z();

		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glBindVertexArray(0);

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);

		glEnable(GL_DEPTH_TEST);

	}
	virtual void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&) {}
	virtual void reportErrorWarning(const char*) {}
	virtual void draw3dText(const btVector3&, const char*) {}
	virtual void setDebugMode(int p)
	{
		m = p;
	}
	int getDebugMode(void) const { return 3; }
	int m;
};