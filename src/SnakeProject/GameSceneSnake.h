#pragma once
#include "Scene.hh"
#include "Snake.h"
#include "Food.h"

class GameSceneSnake : public Scene {
public:
	explicit GameSceneSnake();
	~GameSceneSnake() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void DrawWalls();

	void SetDifficulty(int diff) { difficulty = diff; }
	int GetDifficulty() { return difficulty; }

	std::vector<std::pair<bool, std::pair<int, int>>> ChangeObstacles(bool snakeColor);
	std::vector<std::pair<int, int>> AvailablePositions();

private:
	Sprite game_background;
	Snake m_snake;
	int frameRate = 0;
	int frameLimit = 200;
	int minLimit = 60;
	int speedIncrement = 10;
	Direction newDir;
	Food food;
	int score;
	int difficulty = 0;
};