#pragma once
#include "TwoPlayer.h"
#include "AI.h"
#include "Mouse.h"
#include "Interface.h"

class Kaesekaestchen : public Interface
{
private:
	enum Kaesekaestchenmode
	{
		running,
		Player1Victory,
		Player2Victory,
		Undecided
	};
public:
	Kaesekaestchen(Graphics& gfx, Mouse& mouse, void* data, int flag);
	~Kaesekaestchen();
	int Update();
	void Draw();

private:
	Graphics& gfx;
	Mouse& mouse;
	Board* brd;
	Kaesekaestchenmode kkm;
};
