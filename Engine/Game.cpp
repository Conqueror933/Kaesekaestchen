/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Game.cpp																			  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "Board.h"
#include <assert.h>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	menu(gfx)
{
	players.emplace_back(Player{ 1, Colors::Blue });
	players.emplace_back(Player{ 2, Colors::Red });
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (gamestate == GstwoPlayer)
	{
		if (!brd.GameEnded())
		{
			GameRunning();
		}
		else
		{
			if (players[0].GetCounter() > players[1].GetCounter())
			{
				//players[0] wins
				gfx.DrawRectangle(0, 0, 700, 500, players[0].GetColor());
			}
			else if (players[0].GetCounter() < players[1].GetCounter())
			{
				// players[1] wins
				gfx.DrawRectangle(0, 0, 700, 500, players[1].GetColor());
			}
			else
			{
				//Unentschieden || smth went very wrong
				gfx.DrawRectangle(0, 0, 700, 500, Colors::Green);
			}
		}
	}
	else if(gamestate == GsMenu)
	{
		gamestate = menu.Update(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), wnd.mouse.LeftIsPressed());
	}
	
}

void Game::ComposeFrame()
{
	if (gamestate == GstwoPlayer)
		brd.Draw();
	else
		menu.Draw();
}

void Game::GameRunning()
{
	while (!wnd.mouse.IsEmpty())
	{
		const auto e = wnd.mouse.Read();
		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			int x = wnd.mouse.GetPosX();
			int y = wnd.mouse.GetPosY();


			int old = brd.Cellsfilled();
			if (timmyturner % 2 == 0)
			{
				timmyturner += brd.Update(x, y, players[0]);	//successful click == +1 == next player		//confirmed
			}												//if click missed == +0 == same player		//confirmed
			else if (timmyturner % 2 == 1)
			{
				timmyturner += brd.Update(x, y, players[1]);
			}
			else
			{
				//smth went wrong
				gfx.DrawRectangle(0, 0, 700, 500, Colors::Cyan);
			}
			//filled out a cell, so you can go again
			if (old + 1 <= brd.Cellsfilled())					//has filled cell == -1 == same player
				timmyturner--;								//if click missed == didnt fill cell == false == -0
		}
	}
}
