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
		for (int i = 0; i < numofE; i++)
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
	
	bool m_isShooting;
	float m_shootTimer;
	Vector2 position;

};
class Player
{
public:
	Vector2 m_playerPosition;
	float m_shotCooldown;
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
	aie::Texture*		m_backgroundSpace;
	aie::Texture*		m_enemyship;
	aie::Font*			m_font;
	aie::Font*			m_gameOverFont;
	aie::Audio*			m_audio;
	aie::Audio*			m_explosion;
	aie::Audio*			m_shootSound;
	float m_cameraX, m_cameraY;
	float m_timer;
	Player Player1;
	Enemy * Enemies = new Enemy[20];
	Enemy * enemyPointer;
	int numberOfEnemies;
	int numberOfBullets;
	int m_MaxBullets = 5;
	Bullet Magazine[5];
	bool m_GameOver;
	float m_backgroundColor1, m_backgroundColor2, m_lastBackgroundColor1, m_lastBackgroundColor2;

};

