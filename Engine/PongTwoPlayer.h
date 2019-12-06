#pragma once
#include "PongGame.h"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

class PongTwoPlayer : public PongGame 
{ 
public:
	PongTwoPlayer(Graphics& gfx, Keyboard& keyboard, StringSwitch<DataPass>& data) : PongGame(gfx, keyboard, data) {}
	int Update() override 
	{ 
		player1.Update();
		player2.Update();
		return 0;
	}

	void Draw() override 
	{ 
		player1.Draw();
		player2.Draw();
	}

private:
	class Player
	{
	public:
		Player(PongTwoPlayer& PTP, int y, int x, const char up, const char down) : PTP(PTP), y(y), x(x), up(up), down(down){}
		void Update()
		{
			if (PTP.kbd.KeyIsPressed(up))
				if (y > 0)
					y = y - 2;
			if (PTP.kbd.KeyIsPressed(down))
				if (y < Graphics::ScreenHeight - 100)
					y = y + 2;
		}
		void Draw()
		{
			PTP.gfx.DrawRectangleDim(x, y, 5, 100, Colors::White);
		}
	private:
		PongTwoPlayer& PTP;
		int y, x;
		const char up;
		const char down;
	} player1{*this, 200, 25, 'W', 'S' }, player2{ *this, 200, Graphics::ScreenWidth - 25, 'O', 'L' };

private:
	int y1 = 200;
	int y2 = 200;
};