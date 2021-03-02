#include "../Usefull/javid's GameEngine/olcPixelGameEngine.h"

enum direction
{
	stop, up, right, left, down
};

struct Food
{
	olc::vi2d position;
	bool isExist = false;
};

struct Block
{
	olc::vi2d current;
	olc::vi2d previous;
	Block(const olc::vf2d& position) : current(position) {};
};

class Game : public olc::PixelGameEngine
{
public:
	Game();
	void Input();
	void Draw();
	void Logic();
	void Restart();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsed) override;	
private:
	bool isGameOver;
	direction dir;
	std::vector<Block> m_snake;
	Food m_food;
};