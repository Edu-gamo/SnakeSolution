#include "GameSceneSnake.h"
#include "System.hh"

GameSceneSnake::GameSceneSnake(void) {
	game_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

GameSceneSnake::~GameSceneSnake(void) {
}

void GameSceneSnake::OnEntry(void) {
}

void GameSceneSnake::OnExit(void) {
}

void GameSceneSnake::Update(void) {

	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) SetState<SceneState::SLEEP>();

}

void GameSceneSnake::Draw(void) {
	game_background.Draw(); // Render background
}