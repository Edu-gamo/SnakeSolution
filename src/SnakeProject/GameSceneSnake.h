#pragma once
#include "Scene.hh"

#include "Sprite.hh"

class GameSceneSnake : public Scene {
public:
	explicit GameSceneSnake();
	~GameSceneSnake() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite game_background;
};