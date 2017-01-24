#include "Snake.h"
#include "System.hh"

void DrawParts(int x1, int y1, int x2, int y2, Direction dir);
int SwitchSprite(Direction fromDir, Direction toDir);
ObjectID TurnSprite(Direction fromDir, Direction toDir);

Snake::Snake() {

	Sprite newSpr;
	newSpr.objectID = ObjectID::SNK_HEAD_RIGHT;
	newSpr.transform.w = W.GetWidth() / 30;
	newSpr.transform.h = W.GetHeight() / 24;

	head.x = 15;
	head.y = 5;
	head.dir = Direction::RIGHT;
	newSpr.transform = Transform(head.x * newSpr.transform.w, head.y * newSpr.transform.h, newSpr.transform.w, newSpr.transform.h);
	head.spr = newSpr;

	newSpr.objectID = ObjectID::SNK_TAIL_RIGHT;
	tail.x = 5;
	tail.y = 5;
	tail.dir = Direction::RIGHT;
	newSpr.transform = Transform(tail.x * newSpr.transform.w, tail.y * newSpr.transform.h, newSpr.transform.w, newSpr.transform.h);
	tail.spr = newSpr;

}

void Snake::Move(Direction dir) {

	//Comprobar si se ha cambiado de dirección
	if (dir != head.dir) {
		//Guardamos la nueva parte deonde se ha cambiado de dirección
		SnakePart newPart = head;
		newPart.spr.objectID = TurnSprite(head.dir, dir);
		newPart.dir = dir;
		snk.insert(snk.begin(), newPart);

		head.spr.objectID = (ObjectID)((int)head.spr.objectID + SwitchSprite(head.dir, dir));
		head.dir = dir; //Cambiamos la dirección de la cabeza
	}

	//Mover la cabeza dependiendo de la dirección, y comprobar que no colisiona con los limites
	switch (head.dir) {
	case Direction::RIGHT:
		if (head.x + 1 == W.GetWidth() / head.spr.transform.w - 1) {
			dead = true;
		}
		else {
			head.x++;
		}
		break;
	case Direction::LEFT:
		if (head.x - 1 == 0) {
			dead = true;
		}
		else {
			head.x--;
		}
		break;
	case Direction::UP:
		if (head.y - 1 == 0) {
			dead = true;
		}
		else {
			head.y--;
		}
		break;
	case Direction::DOWN:
		if (head.y + 1 == W.GetHeight() / head.spr.transform.h - 1) {
			dead = true;
		}
		else {
			head.y++;
		}
		break;
	}
	head.spr.transform = Transform(head.x * head.spr.transform.w, head.y * head.spr.transform.h, head.spr.transform.w, head.spr.transform.h);

	if (!dead) {

		//Mover la cola dependiendo de la dirección
		switch (tail.dir) {
		case Direction::RIGHT:
			tail.x++;
			break;
		case Direction::LEFT:
			tail.x--;
			break;
		case Direction::UP:
			tail.y--;
			break;
		case Direction::DOWN:
			tail.y++;
			break;
		}
		tail.spr.transform = Transform(tail.x * tail.spr.transform.w, tail.y * tail.spr.transform.h, tail.spr.transform.w, tail.spr.transform.h);

		if (snk.size() > 0) {
			//Comprobar cola
			if (tail.x == snk.back().x && tail.y == snk.back().y) {
				tail.spr.objectID = (ObjectID)((int)tail.spr.objectID + SwitchSprite(tail.dir, snk.back().dir));
				tail.dir = snk.back().dir;
				snk.pop_back();
			}
		}

		//Comprobar colision con si misma en caso de no colisionar con los extremos del mapa, y haya tres o más cambios de dirección
		if (snk.size() >= 3) {
			if ((head.x >= tail.x && head.x <= snk.back().x) || (head.x <= tail.x && head.x >= snk.back().x)) {
				if ((head.y >= tail.y && head.y <= snk.back().y) || (head.y <= tail.y && head.y >= snk.back().y)) {
					dead = true;
				}
			}
			for (int i = snk.size() - 1; i >= 2 && !dead; i--) {
				if ((head.x >= snk[i].x && head.x <= snk[i - 1].x) || (head.x <= snk[i].x && head.x >= snk[i - 1].x)) {
					if ((head.y >= snk[i].y && head.y <= snk[i - 1].y) || (head.y <= snk[i].y && head.y >= snk[i - 1].y)) {
						dead = true;
					}
				}
			}
		}

	}

}

void Snake::Draw() {
	tail.spr.Draw();
	if (snk.size() > 0) {
		DrawParts(tail.x, tail.y, snk.back().x, snk.back().y, tail.dir);
		for (int i = snk.size() - 1; i > 0; i--) {
			snk[i].spr.Draw();
			DrawParts(snk[i].x, snk[i].y, snk[i - 1].x, snk[i - 1].y, snk[i].dir);
		}
		snk.front().spr.Draw();
		DrawParts(snk.front().x, snk.front().y, head.x, head.y, snk.front().dir);
	}
	else {
		DrawParts(tail.x, tail.y, head.x, head.y, tail.dir);
	}
	head.spr.Draw();
}

//Funcion para pintar las secciones entre dos puntos
void DrawParts(int x1, int y1, int x2, int y2, Direction dir) {

	Sprite newSpr;
	newSpr.transform.w = W.GetWidth() / 30;
	newSpr.transform.h = W.GetHeight() / 24;

	switch (dir) {

	case Direction::RIGHT:
		newSpr.objectID = ObjectID::SNK_BODY_HOR;
		newSpr.transform.y = y1 * newSpr.transform.h;
		for (int j = x1 + 1; j < x2; j++) {
			newSpr.transform.x = j * newSpr.transform.w;
			newSpr.Draw();
		}
		break;

	case Direction::LEFT:
		newSpr.objectID = ObjectID::SNK_BODY_HOR;
		newSpr.transform.y = y1 * newSpr.transform.h;
		for (int j = x1 - 1; j > x2; j--) {
			newSpr.transform.x = j * newSpr.transform.w;
			newSpr.Draw();
		}
		break;

	case Direction::UP:
		newSpr.objectID = ObjectID::SNK_BODY_VERT;
		newSpr.transform.x = x1 * newSpr.transform.w;
		for (int j = y1 - 1; j > y2; j--) {
			newSpr.transform.y = j * newSpr.transform.h;
			newSpr.Draw();
		}
		break;

	case Direction::DOWN:
		newSpr.objectID = ObjectID::SNK_BODY_VERT;
		newSpr.transform.x = x1 * newSpr.transform.w;
		for (int j = y1 + 1; j < y2; j++) {
			newSpr.transform.y = j * newSpr.transform.h;
			newSpr.Draw();
		}
		break;

	}

}

int SwitchSprite(Direction fromDir, Direction toDir) {
	switch (fromDir) {

	case Direction::RIGHT:
		switch (toDir) {
		case Direction::UP:
			return 1;
		case Direction::DOWN:
			return 3;
		}
		break;

	case Direction::LEFT:
		switch (toDir) {
		case Direction::UP:
			return -1;
		case Direction::DOWN:
			return 1;
		}
		break;

	case Direction::UP:
		switch (toDir) {
		case Direction::RIGHT:
			return -1;
		case Direction::LEFT:
			return 1;
		}
		break;

	case Direction::DOWN:
		switch (toDir) {
		case Direction::RIGHT:
			return -3;
		case Direction::LEFT:
			return -1;
		}
		break;
	}

	return 0;

}

ObjectID TurnSprite(Direction fromDir, Direction toDir) {
	if (fromDir != toDir) {
		switch (fromDir) {

		case Direction::RIGHT:
			switch (toDir) {
			case Direction::UP:
				return ObjectID::SNK_UP_LEFT;
			case Direction::DOWN:
				return ObjectID::SNK_DOWN_LEFT;
			}
			break;

		case Direction::LEFT:
			switch (toDir) {
			case Direction::UP:
				return ObjectID::SNK_UP_RIGHT;
			case Direction::DOWN:
				return ObjectID::SNK_DOWN_RIGHT;
			}
			break;

		case Direction::UP:
			switch (toDir) {
			case Direction::RIGHT:
				return ObjectID::SNK_DOWN_RIGHT;
			case Direction::LEFT:
				return ObjectID::SNK_DOWN_LEFT;
			}
			break;

		case Direction::DOWN:
			switch (toDir) {
			case Direction::RIGHT:
				return ObjectID::SNK_UP_RIGHT;
			case Direction::LEFT:
				return ObjectID::SNK_UP_LEFT;
			}
			break;
		}
	}
}