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
		R.LoadTexture<ObjectID::BG_00>("gfx/bg.jpg");

		R.LoadTexture<ObjectID::MENU_BG>("gfx/BACKGROUND1.jpg");
		R.LoadTexture<ObjectID::PLAY_BUT>("gfx/BOTONPLAY1.jpg");
		R.LoadTexture<ObjectID::EXIT_BUT>("gfx/BOTONEXIT1.jpg");
		R.LoadTexture<ObjectID::EASY_BUT>("gfx/BOTONEASY1.jpg");
		R.LoadTexture<ObjectID::MEDIUM_BUT>("gfx/BOTONMEDIUM1.jpg");
		R.LoadTexture<ObjectID::HARD_BUT>("gfx/BOTONHARD1.jpg");

		R.LoadTexture<ObjectID::FRUIT>("gfx/fruit.png");

		R.LoadTexture<ObjectID::SNK_BODY_HOR>("gfx/snake-B-HOR.png");
		R.LoadTexture<ObjectID::SNK_BODY_VERT>("gfx/snake-B-VERT.png");

		R.LoadTexture<ObjectID::SNK_HEAD_RIGHT>("gfx/snake-H-RIGHT.png");
		R.LoadTexture<ObjectID::SNK_HEAD_UP>("gfx/snake-H-UP.png");
		R.LoadTexture<ObjectID::SNK_HEAD_LEFT>("gfx/snake-H-LEFT.png");
		R.LoadTexture<ObjectID::SNK_HEAD_DOWN>("gfx/snake-H-DOWN.png");

		R.LoadTexture<ObjectID::SNK_TAIL_RIGHT>("gfx/snake-T-RIGHT.png");
		R.LoadTexture<ObjectID::SNK_TAIL_UP>("gfx/snake-T-UP.png");
		R.LoadTexture<ObjectID::SNK_TAIL_LEFT>("gfx/snake-T-LEFT.png");
		R.LoadTexture<ObjectID::SNK_TAIL_DOWN>("gfx/snake-T-DOWN.png");

		R.LoadTexture<ObjectID::SNK_UP_RIGHT>("gfx/snake-UpRight.png");
		R.LoadTexture<ObjectID::SNK_UP_LEFT>("gfx/snake-UpLeft.png");
		R.LoadTexture<ObjectID::SNK_DOWN_RIGHT>("gfx/snake-DownRight.png");
		R.LoadTexture<ObjectID::SNK_DOWN_LEFT>("gfx/snake-DownLeft.png");

	}
	//! Adds the game scenes into the Scene Manager and decides which is the first screen
	void AddScenes(void) {
		SM.AddScene<MenuScene>();
		SM.AddScene<GameSceneSnake>();
		SM.SetCurScene<MenuScene>();
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
			case SceneState::SLEEP:		if (m_curScene == SM.GetScene<MenuScene>()) { SM.SetCurScene<GameSceneSnake>(); }
										else { SM.SetCurScene<MenuScene>(); } m_curScene = SM.GetCurScene(); break;
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