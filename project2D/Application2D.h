#pragma once
#include "VecMatrix.h"
#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"

class Enemy
{
public:
	Enemy()
	{
		m_isAlive = true;
	}
	Enemy * deleteEnemy(Enemy enemies[], int numofE)
	{
		int size = 0;
		for (int i = 0; i < numofE; i++)
		{
			if (enemies[i].m_isAlive == true)
				size++;
		}

		Enemy *Enemies = new Enemy[size];
		for (int i = 0; i < size;)
		{
			if (enemies[i].m_isAlive == true)
			{
				Enemies[i] = enemies[i];
				i++;
			}
		}
		Enemy tester[20];
		for (int i = 0; i < 20; i++)
		{
			if (enemies[i].m_isAlive == true)
				tester[i] = enemies[i];
		}
		delete enemies;
		return Enemies;
	}
	Vector2 m_position;
	float m_height = 50, m_width = 35;
	bool m_isAlive;
};
class Bullet
{
public:
	float m_shootTimer;
	Vector2 position;

};
class Player
{
public:
	Vector2 m_playerPosition;
	bool m_isShooting;
};

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Texture*		m_texture;
	aie::Texture*		m_shipTexture;
	aie::Font*			m_font;
	aie::Audio*			m_audio;
	aie::Audio*			m_test;
	float m_cameraX, m_cameraY;
	float m_timer;
	Player Player1;
	Bullet Fire;
	Enemy * Enemies = new Enemy[20];
	Enemy * enemyPointer;
	int numberOfEnemies;
	float m_backgroundColor1, m_backgroundColor2, m_lastBackgroundColor1, m_lastBackgroundColor2;

};

