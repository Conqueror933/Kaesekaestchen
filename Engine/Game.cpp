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
	gfx(wnd)
{
}

Game::~Game()
{
	if (curInterface != nullptr)
	{
		delete curInterface;
		curInterface = nullptr;
	}
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
	switch (gamestate)
	{
	case GsMenu:
		if (prevgamestate != GsMenu)
			if (curInterface != nullptr)
			{
				delete curInterface;
				curInterface = new Menu(gfx); 
			}
			else
				curInterface = new Menu(gfx);
		//<code>
		gamestate = static_cast<Menu*>(curInterface)->Update(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), wnd.mouse.LeftIsPressed());
		//</code>
		prevgamestate = GsMenu;
		break;
	case GstwoPlayer:
		if (prevgamestate != GstwoPlayer)
			if (curInterface != nullptr)
			{
				delete curInterface;
				curInterface = new Board(gfx, 5, 30);
			}
			else
				curInterface = new Board(gfx, 5, 30);
		//<code>
		if (!static_cast<Board*>(curInterface)->Update(wnd.mouse.GetPosX(), wnd.mouse.GetPosY(), wnd.mouse.LeftIsPressed()))
			gamestate = GsMenu; //GsVictory;
		//</code>
		prevgamestate = GstwoPlayer;
		break;
	case GsAILevel1:
		if (prevgamestate != GsAILevel1)
			if (curInterface != nullptr)
			{
				delete curInterface;
				//curInterface = new SMTH;
			}
			else
				//curInterface = new SMTH;
		//<code>

		//</code>
		prevgamestate = GsAILevel1;
		break;
	case GsAILevel2:
		if (prevgamestate != GsAILevel2)
			if (curInterface != nullptr)
			{
				delete curInterface;
				//curInterface = new SMTH;
			}
			else
				//curInterface = new SMTH;
		//<code>

		//</code>
		prevgamestate = GsAILevel2;
		break;
	case GsAILevel3:
		if (prevgamestate != GsAILevel3)
			if (curInterface != nullptr)
			{
				delete curInterface;
				//curInterface = new SMTH;
			}
			else
				//curInterface = new SMTH;
		//<code>

		//</code>
		prevgamestate = GsAILevel3;
		break;
	case GsOptionen:
		if (prevgamestate != GsOptionen)
			if (curInterface != nullptr)
			{
				delete curInterface;
				//curInterface = new SMTH;
			}
			else
				//curInterface = new SMTH;
		//<code>

		//</code>
		prevgamestate = GsOptionen;
		break;
	default:
		gamestate = GsError;
	}
}

void Game::ComposeFrame()
{
	switch (prevgamestate)
	{
	case GsMenu:
		static_cast<Menu*>(curInterface)->Draw();
		break;
	case GstwoPlayer:
		static_cast<Board*>(curInterface)->Draw();
		break;
	case GsAILevel1:
		break;
	case GsAILevel2:
		break;
	case GsAILevel3:
		break;
	case GsOptionen:
		break;
	default:
		throw std::exception("Bad Gamestate.");
	}
}
