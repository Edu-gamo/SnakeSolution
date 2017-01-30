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
	int score = 0;
	int difficulty = 0;
	int contadorAlimentos = 0;
	int contadorNivel = 1;
	int limiteAlimentos;
	int alimentosASumar = 0;
	int vidas;
	bool pauseLevelUp = false;
	bool pauseDead = false;

	int maxTime;
	int actualTime;
	int time = 0;

	//Previous snake on level up
	SnakePart preHead;
	SnakePart preTail;
	std::vector<SnakePart> preSnakeParts; //Vector que almacena la posición de todos los cambios de dirección
};