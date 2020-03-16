#include "Game.h"
#include <iostream>
#include <SDL_image.h>

void Game::moveShip()
{
	ship.setPosition(mousePosition.x, 500);
}

void Game::checkBounds()
{
	// check right boundary
	if(ship.getPosition().x > 768)
	{
		
		ship.setPosition(768 - ship.getPosition().w * 0.1, ship.getPosition().y);
	}

	// check left boundary
	if (ship.getPosition().x < 0)
	{

		ship.setPosition(ship.getPosition().w * 0.1, ship.getPosition().y);
	}
	if (ship.getPosition().y > 568)
	{

		ship.setPosition(ship.getPosition().x , 568 - ship.getPosition().h * 0.1);
	}

	// check left boundary
	if (ship.getPosition().y < 0)
	{

		ship.setPosition(ship.getPosition().x , ship.getPosition().h * 0.1);
	}
}

Game::Game()
{
}

Game::Game(const char* windowName, int windowSizeX, int windowSizeY)
{
	int flags = SDL_INIT_EVERYTHING;

	if (SDL_Init(flags) == 0) // if initialized SDL correctly...
	{
		// Create the window
		pWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSizeX, windowSizeY, SDL_WINDOW_SHOWN);

		if (pWindow != nullptr)
		{
			// Create the renderer
			pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_PRESENTVSYNC);

			if (pRenderer != nullptr)
			{
				IMG_Init(IMG_INIT_PNG);
			}
		}
	}
}

Game::~Game()
{
}

void Game::run()
{
	ship = Sprite(pRenderer, "Seagull_Wizard_1.png", 32, 32);
	//ship.setPosition(384, 568);
	ship.setPosition(400, sin((float)SDL_GetTicks() / 1000.f) * 200 + 200);
	projectile = Sprite(pRenderer, "Can_1.png", 140, 140);
	projectile.setPosition(0, 0);
	background = Sprite(pRenderer, "background.png", 800, 600);
	background.setPosition(0, 0);



	isRunning = true;
	
	// set initial delta time
	deltaTime = 1.0f / targetFramerate;
	lastFrameStartTimeMs = SDL_GetTicks();

	while (isRunning)
	{
		input();
		update();
		draw();
		waitForNextFrame();
	}

	cleanup();
}

void Game::input()
{
	auto wheel = 0;
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			// when the x button is clicked on the window
			case SDL_QUIT:
				quit();
				break;
			// when the mouse is moved
			case SDL_MOUSEMOTION:
				mousePosition.x = event.motion.x;
				mousePosition.y = event.motion.y;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					// press on the esc key to quit
					case SDLK_ESCAPE:
						quit();
					break;
					case SDLK_w:
						// move up
						std::cout << "move up" << std::endl;
						ship.setPosition(ship.getPosition().x , ship.getPosition().y - 32);
						break;
					case SDLK_a:
						// move left
						std::cout << "move left" << std::endl;
						ship.setPosition(ship.getPosition().x - 32, ship.getPosition().y);
						break;
					case SDLK_s:
						// move down
						ship.setPosition(ship.getPosition().x, ship.getPosition().y + 32);
						std::cout << "move down" << std::endl;
						break;
					case SDLK_d:
						// move right
						std::cout << "move right" << std::endl;
						ship.setPosition(ship.getPosition().x + 32, ship.getPosition().y);
						break;
				}
				break;
			default:
				break;
		}
		
	}
}

void Game::update()
{
	
	checkBounds();
		if (ship.isCollidingWith(projectile))
		{
			std::cout << "collision" << std::endl;
				ship.setPosition(-100,-100);
		}

		if (gameTime > 120)
		{
			quit();
		}
	

	/*projectile.velX = sin(gameTime) * 100;
	projectile.velY = sin(gameTime) * 100;

	projectile.dst.x = projectile.dst.x + projectile.velX * deltaTime;
	projectile.dst.y = projectile.dst.y + projectile.velY * deltaTime;*/

	//ship.setPosition(400, sin((float)SDL_GetTicks() / 1000.f) * 200 + 200);
	//projectile.setSize(sin(gameTime * 100) + 100, sin(gameTime) * 100 + 100);

	// automatically quit after 30 seconds just as an example to show Qame.quit()
}	
	


void Game::draw()
{
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 255, 0);
	SDL_RenderClear(pRenderer);
	background.draw(pRenderer);
	ship.draw(pRenderer);
	projectile.draw(pRenderer);
	SDL_RenderPresent(pRenderer);
}

void Game::waitForNextFrame()
{
	Uint32 gameTimeMs = SDL_GetTicks();
	timeSinceLastFrame = gameTimeMs - lastFrameStartTimeMs;

	if (timeSinceLastFrame < frameDelayMs)
	{
		SDL_Delay(frameDelayMs - timeSinceLastFrame);
	}

	frameEndTimeMs = SDL_GetTicks();
	deltaTime = (frameEndTimeMs - lastFrameStartTimeMs)/1000.f;
	gameTime = frameEndTimeMs / 1000.f;
	lastFrameStartTimeMs = frameEndTimeMs;
	//std::cout << deltaTime << std::endl;
}

void Game::quit()
{
	isRunning = false;
}

void Game::cleanup()
{
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	std::cout << "Goodbye World" << std::endl;
}
