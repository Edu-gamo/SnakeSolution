#include "GameSceneSnake.h"
#include "System.hh"

void DrawWalls();

GameSceneSnake::GameSceneSnake(void) {
	game_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

GameSceneSnake::~GameSceneSnake(void) {
}

void GameSceneSnake::OnEntry(void) {
	m_snake = Snake();
	newDir = m_snake.GetHead().dir;
}

void GameSceneSnake::OnExit(void) {
}

void GameSceneSnake::Update(void) {

	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) SetState<SceneState::SLEEP>();

	//Comprobar teclas de dirección dependiendo de la dirección actual
	if (m_snake.GetHead().dir == Direction::RIGHT || m_snake.GetHead().dir == Direction::LEFT) {
		if (IM.IsKeyDown<KEY_BUTTON_UP>()) {
			newDir = Direction::UP;
		}
		else if (IM.IsKeyDown<KEY_BUTTON_DOWN>()) {
			newDir = Direction::DOWN;
		}
	}
	else {
		if (IM.IsKeyDown<KEY_BUTTON_RIGHT>()) {
			newDir = Direction::RIGHT;
		}
		else if (IM.IsKeyDown<KEY_BUTTON_LEFT>()) {
			newDir = Direction::LEFT;
		}
	}

	if (frameRate > 100) {
		if (!m_snake.IsDead()) {
			m_snake.Move(newDir);
		}
		frameRate = 0;
	}
	else {
		frameRate += TM.GetDeltaTime();
	}

}

void GameSceneSnake::Draw(void) {
	game_background.Draw(); // Render background
	m_snake.Draw();
	DrawWalls();
}

void DrawWalls() {
	Sprite newSpr;
	newSpr.objectID = ObjectID::FRUIT;
	newSpr.transform.w = W.GetWidth() / 30;
	newSpr.transform.h = W.GetHeight() / 24;

	for (int i = 0; i < W.GetWidth() / newSpr.transform.w; i++) {
		newSpr.transform.x = i * newSpr.transform.w;

		newSpr.transform.y = 0;
		newSpr.Draw();

		newSpr.transform.y = W.GetHeight() - newSpr.transform.h;
		newSpr.Draw();
	}

	for (int i = 1; i < (W.GetHeight() - 1) / newSpr.transform.h; i++) {
		newSpr.transform.y = i * newSpr.transform.h;

		newSpr.transform.x = 0;
		newSpr.Draw();

		newSpr.transform.x = W.GetWidth() - newSpr.transform.w;
		newSpr.Draw();
	}
}