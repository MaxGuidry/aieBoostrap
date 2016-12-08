#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include<fstream>
Application2D::Application2D()
{
}

Application2D::~Application2D()
{

}

bool Application2D::startup()
{

	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	//m_audio = new aie::Audio("./audio/powerup.wav");
	m_explosion = new aie::Audio("./audio/Explosion.wav");
	m_shootSound = new aie::Audio("./audio/Laser.wav");
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;
	Player1.m_isShooting = false;
	Player1.m_killCount = 0;
	Player1.m_playerPosition = Vector2(600, 40);
	m_backgroundColor1 = -.99;
	m_backgroundColor2 = .99;
	m_lastBackgroundColor1 = -1;
	numberOfBullets = 0;
	numberOfEnemies = 20;
	Player1.m_shotCooldown = 0;
	for (int i = 0; i < numberOfEnemies; i++)
	{
		Enemies[i] = Enemy();
		Enemies[i].m_position.x = (Enemies[i].m_height*i*1.5) + 30;
		Enemies[i].m_position.y = 600;
	}
	for (int i = 0; i < m_MaxBullets; i++)
	{
		Magazine[i].position.y = Player1.m_playerPosition.y;
	}
	//m_test->play();
	return true;
}

void Application2D::shutdown()
{
	delete m_explosion;
	delete m_audio;
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime)
{

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();


	if (input->isKeyDown(aie::INPUT_KEY_RIGHT) && Player1.m_playerPosition.x < 1230)//change to variable storing window size
	{
		Player1.m_playerPosition = Player1.m_playerPosition + Vector2(7, 0);
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT) && Player1.m_playerPosition.x > 50)
	{
		Player1.m_playerPosition = Player1.m_playerPosition - Vector2(7, 0);
	}
	if (input->isKeyDown(aie::INPUT_KEY_SPACE)&&Player1.m_shotCooldown>=.2)
	{
		Magazine[numberOfBullets].position.x = Player1.m_playerPosition.x;
		Player1.m_isShooting = true;
		Magazine[numberOfBullets].m_isShooting = true;
		Magazine[numberOfBullets].m_shootTimer = 0;
		(numberOfBullets < m_MaxBullets) ? numberOfBullets++ : numberOfBullets += 0;
		if (numberOfBullets == m_MaxBullets)
		{
			numberOfBullets = 0;
		}
		Player1.m_shotCooldown = 0;
	}
	if (Player1.m_isShooting == true)
	{
		for (int i = 0; i < m_MaxBullets; i++)
		{
			Magazine[i].m_shootTimer += 16;
		}
	}
	
	for (int i = 0; i < m_MaxBullets; i++)
	{
		if (Magazine[i].m_shootTimer > 720)
		{
			Magazine[i].m_isShooting = false;
		}
	}
	
	if (Player1.m_isShooting == true)
	{
		
		for (int j = 0; j < m_MaxBullets; j++)
		{
			for (int i = 0; i < m_MaxBullets; i++)
			{
				if ((Enemies[i].m_position.x - Enemies[i].m_width < Magazine[j].position.x - 5 && Enemies[i].m_position.x + Enemies[i].m_width > Magazine[j].position.x - 5
					|| Enemies[i].m_position.x - Enemies[i].m_width < Magazine[j].position.x + 5 && Enemies[i].m_position.x + Enemies[i].m_width > Magazine[j].position.x + 5)
					&& (Enemies[i].m_position.y - Enemies[i].m_height <Magazine[j].position.y + 30 && Enemies[i].m_position.y + Enemies[i].m_height >Magazine[j].position.y - 30))
				{
					Enemies[i].m_isAlive = false;
					Enemies = Enemies[i].deleteEnemy(Enemies, numberOfEnemies);
					numberOfEnemies--;
					Player1.m_killCount++;

				}
				
			}
		}
	}
	Player1.m_shotCooldown += deltaTime;
	// example of audio
	//if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	//	m_audio->play();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw()
{

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();


	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSprite(m_shipTexture, Player1.m_playerPosition.x, 50, 0, 0, 0, 1);



	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	char KillBuffer[32];
	sprintf_s(KillBuffer, 32, "Kill Count: %i", Player1.m_killCount);
	m_2dRenderer->drawText(m_font, KillBuffer, 0, 720 - 64);
	for (int i = 0; i < m_MaxBullets; i++)
	{
		if (Player1.m_isShooting == true)
		{
			m_2dRenderer->setRenderColour(1, .5, .1, 1);
			Magazine[i].position.y = 107 + Magazine[i].m_shootTimer;
			m_2dRenderer->drawBox(Magazine[i].position.x, 107 + Magazine[i].m_shootTimer, 5, 30, 0, 0);
		}
	}

	for (int i = 0; i < numberOfEnemies; i++)
	{

		m_2dRenderer->setRenderColour(.5, .5, .3, 1);
		m_2dRenderer->drawBox(Enemies[i].m_position.x, 600, Enemies[i].m_height, Enemies[i].m_width, 0, 0);

	}
	if (m_backgroundColor1 > m_lastBackgroundColor1)
	{
		m_lastBackgroundColor1 = m_backgroundColor1;
		m_backgroundColor1 += .01;
		m_backgroundColor2 -= .01;
		this->setBackgroundColour(m_backgroundColor1, m_backgroundColor2, -m_backgroundColor1, 1);
	}
	if (m_backgroundColor1 > 1)
	{
		m_backgroundColor1 -= .02;
		m_backgroundColor2 += .02;
	}
	else if (m_backgroundColor1 < m_lastBackgroundColor1)
	{
		m_lastBackgroundColor1 = m_backgroundColor1;
		m_backgroundColor2 += .01;
		m_backgroundColor1 -= .01;

		this->setBackgroundColour(m_backgroundColor1, m_backgroundColor2, -m_backgroundColor1, 1);
	}
	if (m_backgroundColor1 < -1)
	{
		m_backgroundColor1 += .02;
		m_backgroundColor2 -= .02;
	}

	// done drawing sprites
	m_2dRenderer->end();
}