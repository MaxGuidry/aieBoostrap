#pragma once
#include "VecMatrix.h"
#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"

class Player;
class Enemy;
class Bullet;

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
		Enemy tester[20];
		int counter = 0;
		for (int i = 0; i < numofE;i++)
		{
		
			if (enemies[i].m_isAlive == true)
			{
				Enemies[counter] = enemies[i];
				tester[counter] = enemies[i];
				counter++;
			}
		}
		
		
		delete enemies;
		return Enemies;
	}
	Vector2 m_position;
	float m_height = 40, m_width = 20;
	bool m_isAlive;
};

class Bullet
{
public:
	void DrawBullet(aie::Renderer2D *&m_2dRenderer,Player Player1)
	{
		if (Player1.m_isShooting == true)
		{
			m_2dRenderer->setRenderColour(1, .5, .1, 1);
			this->position.y = 107 + this->m_shootTimer;
			m_2dRenderer->drawBox(this->position.x, 107 + this->m_shootTimer, 5, 30, 0, 0);
		}
	}
	bool m_isShooting;
	float m_shootTimer;
	Vector2 position;

};
class Player
{
public:
	Vector2 m_playerPosition;
	bool m_isShooting;
	int m_killCount;
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

