#pragma once
#include "VecMatrix.h"
#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"

class Player;
class Enemy;
class Bullet;

class Bullet
{
public:

	bool m_isShooting;
	float m_shootTimer;
	Vector2 position;

};
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
	Bullet shot;
	Vector2 m_position;
	float m_height = 40, m_width = 20;
	bool m_isAlive;
};


class Player
{
public:
	void UpdateAcceleration(Vector2 Force)
	{
		m_acceleration = Force;
	}
	void UpdateVelocity(Vector2 acceleration)
	{

		m_velocity = m_velocity + (acceleration);
		if (m_velocity.Magnitude() > m_maxVelocity)
		{
			m_velocity = m_velocity.Normalize();
			m_velocity = m_velocity*m_maxVelocity;
		}


	}
	void UpdatePosition(Vector2 velocity)
	{
		m_playerPosition = m_playerPosition + velocity;
	}
	float UpdateRotation(Vector2 acceleration)
	{
		return atan(acceleration.y / acceleration.x);
	}

	Vector2 m_playerPosition;
	Vector2 m_velocity;
	Vector2 m_acceleration;
	float m_maxVelocity;
	float m_shotCooldown;
	bool m_isShooting;
	int m_killCount;
};
class boid
{

public:
	Vector2 randomForce;
	boid() {};
	boid(Vector2 position, Vector2 velocity) :m_position(position), m_velocity(velocity) 
	{
		
		randomForce = Vector2(0, 0);
		m_forceapplied = Vector2(0, 0); 
	};
	
	Vector2 getPosition()
	{
		return m_position;
	}
	void moveBoids(boid b[],float deltaTime)
	{
		for (int i = 0; i < 20; i++)
		{
			rule1(b,b[i]);
			rule2(b, b[i],deltaTime);
			rule3(b, b[i],deltaTime);
		}
		updateVelocity(deltaTime);
		updatePosition(deltaTime);
		m_forceapplied = Vector2(0, 0);
	}
	bool operator !=(boid b)
	{
		if (m_position == b.m_position&&m_velocity == b.m_velocity&&m_forceapplied == m_forceapplied)
			return false;
		return true;
	}
	void addForce(Vector2 force)
	{
		m_forceapplied = m_forceapplied + force*50;
	}
private:
	void rule1(boid b[], boid current)
	{
		Vector2 COM = Vector2(0, 0);
		for (int i = 0; i < 20; i++)
		{
			if (b[i] != current)
			{
				COM = COM + b[i].m_position;
			}
		}
		COM = COM *(1.0f / 19.0f);
		m_position = m_position + ((COM - current.m_position)*(1.0f / 100.0f));
	}
	void rule2(boid b[], boid current,float deltaTime)
	{
		Vector2 c = Vector2(0,0);
		for (int i = 0; i < 20; i++)
		{
			if (b[i] != current)
			{
				if ((b[i].m_position - current.m_position).Magnitude() < 100)
				{
					addForce((b[i].m_position - current.m_position)*deltaTime*12.0f);
					
					
				}
			}
		}

	}
	void rule3(boid b[], boid current,float deltaTime)
	{
		Vector2 AV = Vector2(0, 0);
		for (int i = 0; i < 20; i++)
		{
			if (b[i] != current)
			{
				AV = AV + b[i].m_velocity;
			}
		}
		AV = AV*(1.0f / 19.0f)*(1.0f / 20.0f);
		addForce(AV*deltaTime);
	}
	void updateVelocity(float deltaTime)
	{
		
		m_velocity = m_velocity + (m_forceapplied*deltaTime);
		if (m_velocity.Magnitude() >= m_maxVelo)
		{
			m_velocity = m_velocity.Normalize();
			m_velocity = m_velocity*m_maxVelo;
		}
	}
	void updatePosition(float deltaTime)
	{
		m_position = m_position + (m_velocity*deltaTime);
	}
	Vector2 m_position;
	Vector2 m_velocity;
	Vector2 m_forceapplied;
	float m_maxVelo = 300;
	

};

class Application2D : public aie::Application
{
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();
	/*collisionCheck(Player1.m_isShooting, m_MaxBullets, numberOfEnemies, Enemies, Magazine, Player1.m_killCount, m_explosion)
	bool collisionCheck(bool &PlayerIsShooting, int &MaxBullets, int &numberOfEnemies, Enemy Enemies[], Bullet Magazine[], int &killCount, aie::Audio * Explosion)
	{
		if (PlayerIsShooting == true)
		{

			for (int j = 0; j < MaxBullets; j++)
			{
				for (int i = 0; i < numberOfEnemies; i++)
				{
					if ((Enemies[i].m_position.x - Enemies[i].m_width < Magazine[j].position.x - 5 && Enemies[i].m_position.x + Enemies[i].m_width > Magazine[j].position.x - 5
						|| Enemies[i].m_position.x - Enemies[i].m_width < Magazine[j].position.x + 5 && Enemies[i].m_position.x + Enemies[i].m_width > Magazine[j].position.x + 5)
						&& (Enemies[i].m_position.y - Enemies[i].m_height <Magazine[j].position.y + 30 && Enemies[i].m_position.y + Enemies[i].m_height >Magazine[j].position.y - 30))
					{
						Enemies[i].m_isAlive = false;
						Enemies = Enemies[0].deleteEnemy(Enemies, numberOfEnemies);
						numberOfEnemies--;
						killCount++;
						Explosion->stop();
						Explosion->play();
						return true;
					}

				}
			}
		}
		return false;
	}*/


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
	aie::Audio*			m_gameMusic;
	aie::Audio*			m_deathMusic;
	aie::Audio*			m_winMusic;
	std::fstream*		m_file;
	float m_cameraX, m_cameraY;
	float m_timer;
	Player Player1;
	Enemy * Enemies = new Enemy[21];
	Enemy * enemyPointer;
	int numberOfEnemies;
	int numberOfBullets;
	int m_MaxBullets = 5;
	Bullet Magazine[5];
	bool m_GameOver;
	bool m_lose;
	int m_GameTimer;
	float test;
	boid boids[20];
	bool gameStarted;
	float m_backgroundColor1, m_backgroundColor2, m_lastBackgroundColor1, m_lastBackgroundColor2;

};

