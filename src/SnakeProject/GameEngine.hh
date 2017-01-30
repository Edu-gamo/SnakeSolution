/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include "System.hh"

#pragma region GAME_SCENES
#include "MenuScene.h"
#include "GameSceneSnake.h"
#pragma endregion TODO

//! Initializes game needs and controls the game loop
namespace GameEngine {
	//! Loads main resources such as game images and fonts
	void LoadMedia(void) {
		R.LoadFont<FontID::ARIAL>("fnt/arial.ttf", 30);

		R.LoadTexture<ObjectID::TIME_BAR1>("gfx/timeBar.png");
		R.LoadTexture<ObjectID::TIME_BAR2>("gfx/timeBar2.png");

		R.LoadTexture<ObjectID::MENU_BG>("gfx/BACKGROUND1.jpg");
		R.LoadTexture<ObjectID::GAME_BG>("gfx/GAME_BACKGROUND.jpg");

		R.LoadTexture<ObjectID::PLAY_BUT>("gfx/BOTONPLAY1.jpg");
		R.LoadTexture<ObjectID::EXIT_BUT>("gfx/BOTONEXIT1.jpg");
		R.LoadTexture<ObjectID::EASY_BUT>("gfx/BOTONEASY1.jpg");
		R.LoadTexture<ObjectID::MEDIUM_BUT>("gfx/BOTONMEDIUM1.jpg");
		R.LoadTexture<ObjectID::HARD_BUT>("gfx/BOTONHARD1.jpg");

		R.LoadTexture<ObjectID::WALL_G>("gfx/wallG.png");
		R.LoadTexture<ObjectID::WALL_R>("gfx/wallR.png");

		R.LoadTexture<ObjectID::FRUIT_G>("gfx/snakeG/fruitG.png");
		R.LoadTexture<ObjectID::FRUIT_R>("gfx/snakeR/fruitR.png");

		R.LoadTexture<ObjectID::HEART>("gfx/heart.png");

		//Green snake
		R.LoadTexture<ObjectID::SNK_G_BODY_HOR>("gfx/snakeG/snakeG-B-HOR.png");
		R.LoadTexture<ObjectID::SNK_G_BODY_VERT>("gfx/snakeG/snakeG-B-VERT.png");

		R.LoadTexture<ObjectID::SNK_G_HEAD_RIGHT>("gfx/snakeG/snakeG-H-RIGHT.png");
		R.LoadTexture<ObjectID::SNK_G_HEAD_UP>("gfx/snakeG/snakeG-H-UP.png");
		R.LoadTexture<ObjectID::SNK_G_HEAD_LEFT>("gfx/snakeG/snakeG-H-LEFT.png");
		R.LoadTexture<ObjectID::SNK_G_HEAD_DOWN>("gfx/snakeG/snakeG-H-DOWN.png");

		R.LoadTexture<ObjectID::SNK_G_TAIL_RIGHT>("gfx/snakeG/snakeG-T-RIGHT.png");
		R.LoadTexture<ObjectID::SNK_G_TAIL_UP>("gfx/snakeG/snakeG-T-UP.png");
		R.LoadTexture<ObjectID::SNK_G_TAIL_LEFT>("gfx/snakeG/snakeG-T-LEFT.png");
		R.LoadTexture<ObjectID::SNK_G_TAIL_DOWN>("gfx/snakeG/snakeG-T-DOWN.png");

		R.LoadTexture<ObjectID::SNK_G_UP_RIGHT>("gfx/snakeG/snakeG-UpRight.png");
		R.LoadTexture<ObjectID::SNK_G_UP_LEFT>("gfx/snakeG/snakeG-UpLeft.png");
		R.LoadTexture<ObjectID::SNK_G_DOWN_RIGHT>("gfx/snakeG/snakeG-DownRight.png");
		R.LoadTexture<ObjectID::SNK_G_DOWN_LEFT>("gfx/snakeG/snakeG-DownLeft.png");

		//Red snake
		R.LoadTexture<ObjectID::SNK_R_BODY_HOR>("gfx/snakeR/snakeR-B-HOR.png");
		R.LoadTexture<ObjectID::SNK_R_BODY_VERT>("gfx/snakeR/snakeR-B-VERT.png");

		R.LoadTexture<ObjectID::SNK_R_HEAD_RIGHT>("gfx/snakeR/snakeR-H-RIGHT.png");
		R.LoadTexture<ObjectID::SNK_R_HEAD_UP>("gfx/snakeR/snakeR-H-UP.png");
		R.LoadTexture<ObjectID::SNK_R_HEAD_LEFT>("gfx/snakeR/snakeR-H-LEFT.png");
		R.LoadTexture<ObjectID::SNK_R_HEAD_DOWN>("gfx/snakeR/snakeR-H-DOWN.png");

		R.LoadTexture<ObjectID::SNK_R_TAIL_RIGHT>("gfx/snakeR/snakeR-T-RIGHT.png");
		R.LoadTexture<ObjectID::SNK_R_TAIL_UP>("gfx/snakeR/snakeR-T-UP.png");
		R.LoadTexture<ObjectID::SNK_R_TAIL_LEFT>("gfx/snakeR/snakeR-T-LEFT.png");
		R.LoadTexture<ObjectID::SNK_R_TAIL_DOWN>("gfx/snakeR/snakeR-T-DOWN.png");

		R.LoadTexture<ObjectID::SNK_R_UP_RIGHT>("gfx/snakeR/snakeR-UpRight.png");
		R.LoadTexture<ObjectID::SNK_R_UP_LEFT>("gfx/snakeR/snakeR-UpLeft.png");
		R.LoadTexture<ObjectID::SNK_R_DOWN_RIGHT>("gfx/snakeR/snakeR-DownRight.png");
		R.LoadTexture<ObjectID::SNK_R_DOWN_LEFT>("gfx/snakeR/snakeR-DownLeft.png");

		/*//Blue snake
		R.LoadTexture<ObjectID::SNK_B_BODY_HOR>("gfx/snakeB/snakeB-B-HOR.png");
		R.LoadTexture<ObjectID::SNK_B_BODY_VERT>("gfx/snakeB/snakeB-B-VERT.png");

		R.LoadTexture<ObjectID::SNK_B_HEAD_RIGHT>("gfx/snakeB/snakeB-H-RIGHT.png");
		R.LoadTexture<ObjectID::SNK_B_HEAD_UP>("gfx/snakeB/snakeB-H-UP.png");
		R.LoadTexture<ObjectID::SNK_B_HEAD_LEFT>("gfx/snakeB/snakeB-H-LEFT.png");
		R.LoadTexture<ObjectID::SNK_B_HEAD_DOWN>("gfx/snakeB/snakeB-H-DOWN.png");

		R.LoadTexture<ObjectID::SNK_B_TAIL_RIGHT>("gfx/snakeB/snakeB-T-RIGHT.png");
		R.LoadTexture<ObjectID::SNK_B_TAIL_UP>("gfx/snakeB/snakeB-T-UP.png");
		R.LoadTexture<ObjectID::SNK_B_TAIL_LEFT>("gfx/snakeB/snakeB-T-LEFT.png");
		R.LoadTexture<ObjectID::SNK_B_TAIL_DOWN>("gfx/snakeB/snakeB-T-DOWN.png");

		R.LoadTexture<ObjectID::SNK_B_UP_RIGHT>("gfx/snakeB/snakeB-UpRight.png");
		R.LoadTexture<ObjectID::SNK_B_UP_LEFT>("gfx/snakeB/snakeB-UpLeft.png");
		R.LoadTexture<ObjectID::SNK_B_DOWN_RIGHT>("gfx/snakeB/snakeB-DownRight.png");
		R.LoadTexture<ObjectID::SNK_B_DOWN_LEFT>("gfx/snakeB/snakeB-DownLeft.png");*/

	}
	//! Adds the game scenes into the Scene Manager and decides which is the first screen
	void AddScenes(void) {
		SM.AddScene<MenuScene>();
		SM.AddScene<GameSceneSnake>();
		SM.SetCurScene<MenuScene>();
		//SM.AddScene<GameScene>();
		//SM.SetCurScene<GameScene>();
	}
	/**
	* Runs the game specifying the window's name and dimensions
	* @tparam screenWidth Determines the window's width
	* @tparam screenHeight Determines the window's height
	* @param name Determines the window's title
	*/
	template<int screenWidth, int screenHeight>
	void Run(std::string &&name) {
		Window::Instance(std::move(name), screenWidth, screenHeight); // Initialize window Singleton instance for the first time
		LoadMedia(); // Loads the resource assets
		AddScenes(); // Loads the scenes
		bool m_isRunning{ true }; // Decides if the game loop is running
		Scene *&m_curScene(SM.GetCurScene()); // Defines a reference to a pointer that points to the current scene pointer (mindblown)
		while (!IM.HasQuit() && m_isRunning) { // Checks while game's still playable
			TM.FPSBegin(); // Calculates the time difference for deltaTime and FPS limiting purposes
#pragma region GAME_UPDATE
			switch (m_curScene->GetState()) { // Check for the state of the screen
			case SceneState::RUNNING:	IM.Update(); m_curScene->Update(); break; // Updates the InputManager and the current scene
			case SceneState::EXIT:		m_isRunning = false; break; // Triggers an end of the game looping
			case SceneState::SLEEP:		if (m_curScene == SM.GetScene<MenuScene>()) {
				SM.GetScene<GameSceneSnake>()->SetDifficulty(SM.GetScene<MenuScene>()->GetDifficulty());
				SM.SetCurScene<GameSceneSnake>();
			}
										else { SM.SetCurScene<MenuScene>(); }
										m_curScene = SM.GetCurScene(); break;
			default:;
			}
#pragma endregion
#pragma region GAME_DRAW
			TM.FPSEnd([&]() { // Limits the FPS rendering with a lambda function as the parameter that draws the whole game
				if (m_curScene->CheckState<SceneState::RUNNING>()) { // If screen object exists and its state is running
					R.Clear();			// Clear the screen buffer
					m_curScene->Draw(); // Call the draw method of the scene
					R.Render();			// Update the screen buffer with all sprites that were pushed
				}});
#pragma endregion
		}
	}
}