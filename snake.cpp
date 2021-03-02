#include "snake.h"

Game::Game()
{
	sAppName = "=====# SNAKE #=====";
}

void Game::Input()
{
	if (GetKey(olc::Key::W).bPressed)
		if(dir != direction::down) 
			dir = direction::up;

	if (GetKey(olc::Key::S).bPressed)
		if (dir != direction::up)
			dir = direction::down;

	if (GetKey(olc::Key::A).bPressed)
		if (dir != direction::right)
			dir = direction::left;

	if (GetKey(olc::Key::D).bPressed)
		if (dir != direction::left)
			dir = direction::right;

	if (GetKey(olc::Key::R).bPressed)
		Restart();

	if (GetKey(olc::Key::ESCAPE).bPressed)
		exit(0);
}

void Game::Draw()
{
	std::string head = std::to_string(m_snake[0].current.x) + " : " + std::to_string(m_snake[0].current.y);
	std::string food = std::to_string(m_food.position.x) + " : " + std::to_string(m_food.position.y);

	FillRect(0, 0, ScreenWidth(), ScreenHeight(), olc::BLACK);
	for (const Block& part : m_snake)
		FillRect(part.current, GetPixelSize(), olc::GREEN);
	FillRect(m_food.position, GetPixelSize(), olc::RED);
	DrawString(0, 0, std::to_string(ScreenWidth()));
	DrawString(0, ScreenHeight() - 10, head);
	DrawString(ScreenWidth() - food.size() - 50, ScreenHeight() - 10, food);
}

void Game::Logic()
{
	if(!m_food.isExist) // Generation of food
	{
	gen:
		m_food.position.x = rand() % ScreenWidth();
		m_food.position.y = rand() % ScreenHeight();

		if (m_food.position.x % GetPixelSize().x != 0 || m_food.position.y % GetPixelSize().y != 0)
			goto gen;

		for (const Block& part : m_snake)
			if (part.current == m_food.position)
				goto gen;

		m_food.isExist = true;
	}

	// Snake movement

	m_snake[0].previous = m_snake[0].current;
		
	switch (dir)
	{
	case stop: ;
		break;
	case up:    m_snake[0].current.y--;
		break;
	case right: m_snake[0].current.x++;
		break;
	case left:  m_snake[0].current.x--;
		break;
	case down:  m_snake[0].current.y++;
		break;
	
	}

	for (int i = 1; i < m_snake.size(); i++)
	{
		m_snake[i].previous = m_snake[i].current;
		m_snake[i].current = m_snake[i - 1].previous;
	}

	//Collision detection

	if (m_snake[0].current.x > ScreenWidth())
		m_snake[0].current.x %= ScreenWidth();

	if (m_snake[0].current.x < 0)
		m_snake[0].current.x += ScreenWidth();

	if (m_snake[0].current.y > ScreenHeight())
		m_snake[0].current.y %= ScreenHeight();

	if (m_snake[0].current.y < 0)
		m_snake[0].current.y += ScreenHeight();

	for (int i = 1; i < m_snake.size(); i++)
		if (m_snake[0].current == m_snake[1].current)
			isGameOver = true;

	if((m_snake[0].current.x >= m_food.position.x && m_snake[0].current.x <= m_food.position.x + GetPixelSize().x) && 
		(m_snake[0].current.y >= m_food.position.y && m_snake[0].current.y <= m_food.position.y + GetPixelSize().y))
	{
		m_food.isExist = false;
		m_snake.emplace_back(m_snake[0].previous);
	}
}

void Game::Restart()
{
	dir = direction::stop;
	m_snake.clear();
	m_snake.emplace_back(Block(olc::vi2d(0, 0)));
	m_food.isExist = false;
	isGameOver = false;
}

bool Game::OnUserCreate()
{
	dir = direction::stop;
	m_snake.emplace_back(Block(olc::vi2d(0, 0)));
	m_food.isExist = false;
	isGameOver = false;
	return true;
}

bool Game::OnUserUpdate(float fElapsed)
{
	if (!isGameOver)
	{
		Input();
		Logic();
		Draw();
	}
	else DrawString(ScreenWidth() / 2, ScreenHeight() / 2, "GAME OVER", olc::RED);
	return true;
}
