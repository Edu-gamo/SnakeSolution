#pragma once
#include "Sprite.hh"
#include <vector>

enum class Direction : int {
	RIGHT, UP, LEFT, DOWN
};

struct SnakePart {

	int x;
	int y;
	Direction dir;
	Sprite spr;

};

class Snake {
public:
	Snake();
	void Move(Direction dir); //Mueve la serpiente en una dirección comprobando las colisiones col los limites y con ella misma
	bool IsDead() { return dead; }
	void SetDead(bool n_dead) { dead = n_dead; }
	void Draw();

	SnakePart GetHead() { return head; }
	SnakePart GetTail() { return tail; }
	std::vector<SnakePart> GetSnakeParts() { return snk; }

	void SetHead(SnakePart newHead) { head = newHead; }
	void SetTail(SnakePart newTail) { tail = newTail; }
	void SetSnakeParts(std::vector<SnakePart> newSnakeParts) { snk = newSnakeParts; }

	void DrawParts(int x1, int y1, int x2, int y2, Direction dir);
	int SwitchSprite(Direction fromDir, Direction toDir);
	ObjectID TurnSprite(Direction fromDir, Direction toDir);
	ObjectID ChangeSkin(bool skin, ObjectID actualSkin);

	void SetSkinGreen(bool skin) { skinGreen = skin; }
	bool IsGreen() { return skinGreen; }

	void SnakeGrow() { growing = true; }

	bool ObstaclesCollision();

	void SetObstacles(std::vector<std::pair<bool, std::pair<int, int>>> obs) { obstacles = obs; }
	std::vector<std::pair<bool, std::pair<int, int>>> GetObstacles() { return obstacles; }

	void CheckSnake();

private:
	SnakePart head;
	SnakePart tail;
	std::vector<SnakePart> snk; //Vector que almacena la posición de todos los cambios de dirección
	bool dead = false;
	bool skinGreen = true;
	bool growing = false;
	std::vector<std::pair<bool, std::pair<int, int>>> obstacles;
};