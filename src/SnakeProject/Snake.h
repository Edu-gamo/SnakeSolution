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
	void Move(Direction dir); //Mueve la serpiente en una direcci�n comprobando las colisiones col los limites y con ella misma
	bool IsDead() { return dead; }
	void Draw();
	SnakePart GetHead() { return head; }

private:
	SnakePart head;
	SnakePart tail;
	std::vector<SnakePart> snk; //Vector que almacena la posici�n de todos los cambios de direcci�n
	bool dead = false;
};