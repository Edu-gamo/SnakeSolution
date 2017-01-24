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
	void Draw();
	SnakePart GetHead() { return head; }

private:
	SnakePart head;
	SnakePart tail;
	std::vector<SnakePart> snk; //Vector que almacena la posición de todos los cambios de dirección
	bool dead = false;
};