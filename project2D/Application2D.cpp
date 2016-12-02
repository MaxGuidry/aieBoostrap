#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

Application2D::Application2D() {
}

Application2D::~Application2D() {

}

bool Application2D::startup() {

	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);

	//m_audio = new aie::Audio("./audio/powerup.wav");
	m_test = new aie::Audio("./audio/PPI.wav");
	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;
	Player1.m_isShooting = false;
	Player1.m_playerPosition = Vector2(600, 40);
	m_backgroundColor1 = -.99;
	m_backgroundColor2 = .99;
	m_lastBackgroundColor1 = -1;
	for (int i = 0; i < 20; i++)
	{
		Enemies[i]=Enemy();
		Enemies[i].m_position.x = (Enemies[i].m_height*i*1.5) + 30;
		Enemies[i].m_position.y = 600;
	}
	numberOfEnemies = 20;
	//m_test->play();
	return true;
}

void Application2D::shutdown() {

	delete m_test;
	delete m_audio;
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

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
	if (input->isKeyDown(aie::INPUT_KEY_SPACE) && Player1.m_isShooting == false)
	{
		Fire.position.x = Player1.m_playerPosition.x;
		Player1.m_isShooting = true;
		Fire.m_shootTimer = 0;
	}
	if (Player1.m_isShooting == true)
	{
		Fire.m_shootTimer += 14;
	}
	if (Fire.m_shootTimer > 620)
		Player1.m_isShooting = false;
	if (Player1.m_isShooting == true)
	{
		Enemy test[20];
		for (int i = 0; i < numberOfEnemies; i++)
		{
			if ((Enemies[i].m_position.x - Enemies[i].m_width < Fire.position.x - 5 && Enemies[i].m_position.x + Enemies[i].m_width > Fire.position.x - 5 
				|| Enemies[i].m_position.x - Enemies[i].m_width < Fire.position.x + 5 && Enemies[i].m_position.x + Enemies[i].m_width > Fire.position.x + 5)
				&&(Enemies[i].m_position.y-Enemies[i].m_height <Fire.position.y +30&&Enemies[i].m_position.y + Enemies[i].m_height >Fire.position.y-30))
			{
  				Enemies[i].m_isAlive = false;
 				Enemies =Enemies[i].deleteEnemy(Enemies,numberOfEnemies); 
				numberOfEnemies--;
				
			}
 			test[i] = Enemies[i];
		}
	}
	// example of audio
	//if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	//	m_audio->play();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	// demonstrate animation
	//m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	//m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	// demonstrate spinning sprite
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSprite(m_shipTexture, Player1.m_playerPosition.x, 50, 0, 0, 0, 1);

	// draw a thin line
	//m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	// draw a moving purple circle
	//m_2dRenderer->setRenderColour(1, 0, 1, 1);
	//m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	// draw a rotating red box
	//m_2dRenderer->setRenderColour(cos(m_timer), cos(m_timer), cos(m_timer), 1);
	//m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	// draw a slightly rotated sprite with no texture, coloured yellow
	//m_2dRenderer->setRenderColour(1, 1, 0, 1);
	//m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f, 1);

	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	//m_2dRenderer->drawText(m_font, "Press Space for sound!", 0, 720 - 64);

	if (Player1.m_isShooting == true)
	{
		m_2dRenderer->setRenderColour(1, .5, .1, 1);
		Fire.position.y = 107 + Fire.m_shootTimer;
		m_2dRenderer->drawBox(Fire.position.x, 107 + Fire.m_shootTimer, 5, 30, 0, 0);
	}

	for (int i = 0; i < 20; i++)
	{
		//if (Enemies[i].m_isAlive == true)
		//{
			m_2dRenderer->setRenderColour(0, 1, .1, 1);
			m_2dRenderer->drawBox(Enemies[i].m_position.x, 600, Enemies[i].m_height, Enemies[i].m_width, 0, 0);
		//}
	}
	if (m_backgroundColor1 > m_lastBackgroundColor1)
	{
		m_lastBackgroundColor1 = m_backgroundColor1;
		m_backgroundColor1 += .01;
		m_backgroundColor2 -= .02;
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