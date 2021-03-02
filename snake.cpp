#define OLC_PGE_APPLICATION
#include "../Usefull/javid's GameEngine/olcPixelGameEngine.h"

struct block
{
	olc::vi2d current;
	olc::vi2d previous;
	block(int x, int y) : current(olc::vi2d(x, y)) {};
};

struct food
{
	olc::vi2d pos;
	bool isEat = false;;
};

enum direction
{
	up,down,right,left
};

class Game : public olc::PixelGameEngine
{
public:
	Game();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsed) override;
	void move(const direction& dir);
	void Input();
	void food_gen();
	void display();

private:
	std::vector<block> snake;
	food m_food;
	bool isGameOver;
	direction dir;
};

Game::Game()
{
	sAppName = "====# Snake #====";
}

void Game::move(const direction& dir)
{
	snake[0].previous = snake[0].current;
	switch (dir)
	{
	case direction::up:   snake[0].current.y--;
		break;
	case direction::down: snake[0].current.y++;
		break;
	case direction::left: snake[0].current.x--;
		break;
	case direction::right:snake[0].current.x++;
		break;
	}
	snake[snake.size() - 1].current = snake[0].previous;
}

void Game::food_gen()
{
gen:
	m_food.pos.x = rand() % ScreenWidth();
	m_food.pos.y = rand() % ScreenHeight();

	for (const block& part : snake)
		if (part.current == m_food.pos)
			goto gen;
	m_food.isEat = false;
}

void Game::display()
{
	DrawRect(0, 0, GetPixelSize().x, GetPixelSize().y, olc::BLACK);
	for (const block& part : snake) DrawRect(part.current, olc::vi2d(GetPixelSize()), olc::WHITE);
}

void Game::Input()
{
	if(GetKey(olc::Key::LEFT).bPressed)
		dir = direction::left;

	if (GetKey(olc::Key::UP).bPressed)
		dir = direction::up;
	
	if (GetKey(olc::Key::DOWN).bPressed)
		dir = direction::down;

	if (GetKey(olc::Key::RIGHT).bPressed)
		dir = direction::right;
}

bool Game::OnUserCreate()
{
	srand(time(NULL));
	snake.emplace_back(block(0, 0));
	isGameOver = false;
	
	return true;
}

bool Game::OnUserUpdate(float fElapsed)
{
	if (m_food.isEat) food_gen;

	return true;
}



int main()
{
	
}