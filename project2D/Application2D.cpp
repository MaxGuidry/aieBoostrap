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
	srand(time(NULL));
	m_2dRenderer = new aie::Renderer2D();
	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");
	m_backgroundSpace = new aie::Texture("./textures/space.png");
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_gameOverFont = new aie::Font("./font/consolas.ttf", 230);
	m_enemyship = new aie::Texture("./textures/spaceship.png");
	m_explosion = new aie::Audio("./audio/Explosion.wav");
	m_shootSound = new aie::Audio("./audio/Laser.wav");
	m_gameMusic = new aie::Audio("./audio/BackgroundSpace.wav");
	m_deathMusic = new aie::Audio("./audio/DeathMusic.wav");
	m_winMusic = new aie::Audio("./audio/WinMusic.wav");
	m_winMusic->setGain(1.9);
	m_deathMusic->setGain(1.5);
	m_explosion->setGain(.5);
	m_shootSound->setGain(.1);
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;
	Player1.m_isShooting = false;
	Player1.m_killCount = 0;
	Player1.m_playerPosition = Vector2(1280 / 2, m_shipTexture->getHeight() / 2);
	Player1.m_velocity = Vector2(0, 0);
	m_backgroundColor1 = -.99;
	m_backgroundColor2 = .99;
	m_lastBackgroundColor1 = -1;
	numberOfBullets = 0;
	numberOfEnemies = 21;
	Player1.m_shotCooldown = 0;
	Enemies = new Enemy[numberOfEnemies];
	for (int i = 0; i < numberOfEnemies; i++)
	{
		Enemies[i] = Enemy();
		Enemies[i].m_position.x = (Enemies[i].m_height*i*1.5) + 30;
		Enemies[i].m_position.y = 600;
		Enemies[i].shot.position = Vector2(Enemies[i].m_position.x, Enemies[i].m_position.y);
		Enemies[i].shot.m_isShooting = false;
		Enemies[i].shot.m_shootTimer = 0;
		Enemies[i].m_isAlive = true;
	}
	for (int i = 0; i < m_MaxBullets; i++)
	{
		Magazine[i].m_isShooting = false;
		Magazine[i].position.x = Player1.m_playerPosition.x;
		Magazine[i].position.y = Player1.m_playerPosition.y;
		Magazine[i].m_shootTimer = 0;
	}
	m_GameOver = false;
	m_lose = false;
	gameStarted = false;
	m_file = new std::fstream("test.txt", std::ios_base::app);
	
	test = 0;
	return true;
}

void Application2D::shutdown()
{
	delete m_winMusic;
	delete m_deathMusic;
	delete m_gameMusic;
	delete m_explosion;
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
	delete m_backgroundSpace;
	delete m_enemyship;
	delete m_gameOverFont;
	delete m_shootSound;
	delete Enemies;

}

void Application2D::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	m_timer += deltaTime;
	
	if (gameStarted == false)
	{
		
		if (input->wasMouseButtonPressed(INPUT_MOUSE)&&input->getMouseX() < 760 && input->getMouseX() > 530 && input->getMouseY() > 650 && input->getMouseY() < 720)
		{
			gameStarted = true;
			m_GameTimer = 12;
		}

		if (input->wasMouseButtonPressed(INPUT_MOUSE)&& input->getMouseX() < 730 && input->getMouseX() > 570 && input->getMouseY() > 110 && input->getMouseY() < 180)
		{
			gameStarted = true;
			m_GameTimer = 15;
		}
		if (input->wasMouseButtonPressed(INPUT_MOUSE)&&input->getMouseX() < 750 && input->getMouseX() > 530 && input->getMouseY() > 310 && input->getMouseY() < 380)
		{
			gameStarted = true;
			m_GameTimer = 20;
		}
		if (input->wasMouseButtonPressed(INPUT_MOUSE)&&input->getMouseX() < 730 && input->getMouseX() > 570 && input->getMouseY() > 510 && input->getMouseY() < 580)
		{
			gameStarted = true;
			m_GameTimer = 25;
		}
	}
	else {
		if (m_GameOver == false)
		{
			m_gameMusic->play();
			m_gameMusic->setLooping(true);
			test += deltaTime;
			// input example
			if (test >= 1)
			{
				test = 0;
				m_GameTimer--;
			}
			if (m_GameTimer == 0)
			{
				m_GameOver = true;
				m_lose = true;
			}

			for (int i = 0; i < m_MaxBullets; i++)
			{
				if (Magazine[i].m_isShooting == false)
				{
					Magazine[i].position.x = Player1.m_playerPosition.x;
				}
			}
			if (input->isKeyDown(aie::INPUT_KEY_RIGHT) && Player1.m_playerPosition.x < 1230)//change to variable storing window size
			{
				Player1.m_playerPosition = Player1.m_playerPosition + Vector2(7, 0);
			}
			if (input->isKeyDown(aie::INPUT_KEY_LEFT) && Player1.m_playerPosition.x > 50)
			{
				Player1.m_playerPosition = Player1.m_playerPosition - Vector2(7, 0);
			}
			if (input->isKeyDown(aie::INPUT_KEY_SPACE) && Player1.m_shotCooldown >= .26)
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
				m_shootSound->stop();
				m_shootSound->play();
			}
			if (Player1.m_isShooting == true)
			{
				for (int i = 0; i < m_MaxBullets; i++)
				{
					if (Magazine[i].m_isShooting == true)
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
					Magazine[j].position.y = 107 + Magazine[j].m_shootTimer;

					for (int i = 0; i < numberOfEnemies; i++)
					{
						if ((Enemies[i].m_position.x - Enemies[i].m_width < Magazine[j].position.x - 5 && Enemies[i].m_position.x + Enemies[i].m_width > Magazine[j].position.x - 5
							|| Enemies[i].m_position.x - Enemies[i].m_width < Magazine[j].position.x + 5 && Enemies[i].m_position.x + Enemies[i].m_width > Magazine[j].position.x + 5)
							&& (Enemies[i].m_position.y - Enemies[i].m_height <Magazine[j].position.y + 30 && Enemies[i].m_position.y + Enemies[i].m_height >Magazine[j].position.y - 30))
						{
							Enemies[i].m_isAlive = false;
							Enemies = Enemies[0].deleteEnemy(Enemies, numberOfEnemies);
							numberOfEnemies--;
							Player1.m_killCount++;
							m_explosion->stop();
							m_explosion->play();
						}
					}
				}
			}
			for (int i = 0; i < numberOfEnemies; i++)
			{

				if (Enemies[i].shot.position.y - 15 < Player1.m_playerPosition.y + m_shipTexture->getHeight() / 2 && Enemies[i].shot.position.x > Player1.m_playerPosition.x - m_shipTexture->getWidth() / 2 && Enemies[i].shot.position.x < Player1.m_playerPosition.x + m_shipTexture->getWidth() / 2)
				{
					m_GameOver = true;
					m_lose = true;
					m_deathMusic->play();
				}
			}
			Player1.m_shotCooldown += deltaTime;
			if (Player1.m_killCount == 21)
			{
				m_GameOver = true;
				m_winMusic->play();
			}

		}
		else
		{
			m_gameMusic->stop();
		}
		if (input->isKeyDown(aie::INPUT_KEY_R) && m_GameOver == true)
		{
			m_winMusic->stop();
			m_deathMusic->stop();
			shutdown();
			startup();
		}
		m_file->open("test.txt", std::ios_base::out);
		if (m_file->is_open())
		{
			*m_file << "Player position x: " << Player1.m_playerPosition.x << std::endl;
			*m_file << "Player position y: " << Player1.m_playerPosition.y << std::endl;
			m_file->close();
		}

		for (int i = 0; i < numberOfEnemies; i++)
		{
			int random = rand() % 95;
			if (random == 2 && Enemies[i].shot.m_isShooting == false)
			{
				Enemies[i].shot.m_isShooting = true;
			}
			if (Enemies[i].shot.position.y < 0)
			{
				Enemies[i].shot.m_isShooting = false;
				Enemies[i].shot.m_shootTimer = 0;
				Enemies[i].shot.position.y = Enemies[i].m_position.y;
			}
			if (Enemies[i].shot.m_isShooting == true)
			{
				Enemies[i].shot.position.y -= 10;
				//Enemies[i].shot.m_shootTimer -= 8;
			}
		}

		//Vector2 mousePosition = Vector2(input->getMouseX(), input->getMouseY());
		//Vector2 directionOfMovement = (mousePosition - Player1.m_playerPosition);
		//float DistanceFromMouse = directionOfMovement.Magnitude();
		////Vector2 directionOfMovement = Vector2(1280 / 2, 720 / 2) - Player1.m_playerPosition;
		//directionOfMovement.Normalize();

		//Player1.UpdateVelocity(directionOfMovement*deltaTime);
		//
		//if (DistanceFromMouse <= 100.0f)
		//{

		//	Player1.UpdateVelocity(directionOfMovement*DistanceFromMouse*-.5* deltaTime);
		//}
		//Player1.UpdatePosition(Player1.m_velocity *deltaTime);
		// exit the application
	}
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
	if (gameStarted == false)
	{
		char impossible[15];
		sprintf_s(impossible, 15, "Impossible");
		m_2dRenderer->drawText(m_font, impossible, 575, 670);
		char easy[10];
		sprintf_s(easy, 10, "Easy");
		m_2dRenderer->drawText(m_font, easy, 600, 550);
		char medium[10];
		sprintf_s(medium, 10, "Medium");
		m_2dRenderer->drawText(m_font, medium, 590, 350);
		char hard[10];
		sprintf_s(hard, 10, "Hard");
		m_2dRenderer->drawText(m_font, hard, 600, 150);
	}
	else {

		if (m_GameOver == false)
		{
			for (int i = 0; i < numberOfEnemies; i++)
			{
				m_2dRenderer->drawSprite(m_enemyship, Enemies[i].m_position.x, 600, Enemies[i].m_height + 10, Enemies[i].m_width + 20, 0, 0);

			}
			// demonstrate spinning sprite
			m_2dRenderer->setUVRect(0, 0, 1, 1);
			m_2dRenderer->drawSprite(m_shipTexture, Player1.m_playerPosition.x, Player1.m_playerPosition.y, 0, 0, 0, 1);
			m_2dRenderer->drawLine(
				Player1.m_playerPosition.x, Player1.m_playerPosition.y,
				Player1.m_playerPosition.x + Player1.m_velocity.x,
				Player1.m_playerPosition.y + Player1.m_velocity.y,
				1);
			m_2dRenderer->drawSprite(m_backgroundSpace, 620, 720 / 2, 1320, 720, 0, 1);
			// output some text, uses the last used colour
			char fps[32];
			sprintf_s(fps, 32, "FPS: %i", getFPS());
			m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
			char KillBuffer[32];
			sprintf_s(KillBuffer, 32, "Kill Count: %i", Player1.m_killCount);
			m_2dRenderer->drawText(m_font, KillBuffer, 0, 720 - 64);
			for (int i = 0; i < m_MaxBullets; i++)
			{

				if (Magazine[i].m_isShooting == true)
				{
					m_2dRenderer->setRenderColour(0, 1, 0, 1);
					m_2dRenderer->drawBox(Magazine[i].position.x, 91 + Magazine[i].m_shootTimer, 5, 30, 0, 0);
				}
			}
			for (int i = 0; i < numberOfEnemies; i++)
			{

				if (Enemies[i].shot.m_isShooting == true)
				{
					m_2dRenderer->setRenderColour(1, 0, 0, 1);
					m_2dRenderer->drawBox(Enemies[i].m_position.x, Enemies[i].shot.position.y, 5, 30, 0, 0);
				}
			}
			m_2dRenderer->setRenderColour(1, 1, 1, 1);
			char timer[15];
			sprintf_s(timer, 15, "Time Left: %i", m_GameTimer);
			m_2dRenderer->drawText(m_font, timer, 1280 / 2 - 180, 680);

		}
		else
		{

			this->setBackgroundColour(0, 0, 0, 1);
			char GameOver[32];
			sprintf_s(GameOver, 32, "Game Over!");
			m_2dRenderer->drawText(m_gameOverFont, GameOver, 30, 500, 1);
			char restart[40];
			sprintf_s(restart, 40, "Press \"r\" to restart.");
			m_2dRenderer->drawText(m_font, restart, 1240 / 2 - 120, 40, 1);
			if (m_lose == true)
			{
				char lost[20];
				sprintf_s(lost, 20, "You Lost");
				m_2dRenderer->drawText(m_gameOverFont, lost, 100, 200, 1);
			}
			else
			{
				char won[20];
				sprintf_s(won, 20, "You Won");
				m_2dRenderer->drawText(m_gameOverFont, won, 160, 200, 1);
			}
		}
	}
	// done drawing sprites
	m_2dRenderer->end();
}