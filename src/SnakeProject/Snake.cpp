#include "Snake.h"
#include "System.hh"

Snake::Snake() {

	Sprite newSpr;
	newSpr.objectID = ObjectID::SNK_G_HEAD_RIGHT;
	newSpr.transform.w = W.GetWidth() / 31;
	newSpr.transform.h = W.GetHeight() / 24;

	head.x = 3;
	head.y = 2;
	head.dir = Direction::RIGHT;
	newSpr.transform = Transform(head.x * newSpr.transform.w, head.y * newSpr.transform.h, newSpr.transform.w, newSpr.transform.h);
	head.spr = newSpr;

	newSpr.objectID = ObjectID::SNK_G_TAIL_RIGHT;
	tail.x = 2;
	tail.y = 2;
	tail.dir = Direction::RIGHT;
	newSpr.transform = Transform(tail.x * newSpr.transform.w, tail.y * newSpr.transform.h, newSpr.transform.w, newSpr.transform.h);
	tail.spr = newSpr;

}

//Controla el movimiento de la serpiente incluidas las colisiones
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
	if (ObstaclesCollision()) {
		dead = true;
	}
	else {
		switch (head.dir) {
		case Direction::RIGHT: head.x++;
			break;
		case Direction::LEFT: head.x--;
			break;
		case Direction::UP: head.y--;
			break;
		case Direction::DOWN: head.y++;
			break;
		}
	}
	head.spr.transform = Transform(head.x * head.spr.transform.w, head.y * head.spr.transform.h, head.spr.transform.w, head.spr.transform.h);

	if (!dead) {

		if (!growing) {//Si la serpiente ha comido la cola no se mueve
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
		}
		else {
			growing = false;
			CheckSnake();
		}

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

//Pinta toda la serpiente
void Snake::Draw() {
	tail.spr.objectID = ChangeSkin(skinGreen, tail.spr.objectID);
	tail.spr.Draw();
	if (snk.size() > 0) {
		DrawParts(tail.x, tail.y, snk.back().x, snk.back().y, tail.dir);
		for (int i = snk.size() - 1; i > 0; i--) {
			snk[i].spr.objectID = ChangeSkin(skinGreen, snk[i].spr.objectID);
			snk[i].spr.Draw();
			DrawParts(snk[i].x, snk[i].y, snk[i - 1].x, snk[i - 1].y, snk[i].dir);
		}
		snk.front().spr.objectID = ChangeSkin(skinGreen, snk.front().spr.objectID);
		snk.front().spr.Draw();
		DrawParts(snk.front().x, snk.front().y, head.x, head.y, snk.front().dir);
	}
	else {
		DrawParts(tail.x, tail.y, head.x, head.y, tail.dir);
	}
	head.spr.objectID = ChangeSkin(skinGreen, head.spr.objectID);
	head.spr.Draw();
}

//Funcion para pintar las secciones de la serpiente entre dos puntos de cambio
void Snake::DrawParts(int x1, int y1, int x2, int y2, Direction dir) {

	Sprite newSpr;
	newSpr.transform.w = W.GetWidth() / 31;
	newSpr.transform.h = W.GetHeight() / 24;

	switch (dir) {

	case Direction::RIGHT:
		if (skinGreen) { newSpr.objectID = ObjectID::SNK_G_BODY_HOR; }
		else { newSpr.objectID = ObjectID::SNK_R_BODY_HOR; }
		newSpr.transform.y = y1 * newSpr.transform.h;
		for (int j = x1 + 1; j < x2; j++) {
			newSpr.transform.x = j * newSpr.transform.w;
			newSpr.Draw();
		}
		break;

	case Direction::LEFT:
		if (skinGreen) { newSpr.objectID = ObjectID::SNK_G_BODY_HOR; }
		else { newSpr.objectID = ObjectID::SNK_R_BODY_HOR; }
		newSpr.transform.y = y1 * newSpr.transform.h;
		for (int j = x1 - 1; j > x2; j--) {
			newSpr.transform.x = j * newSpr.transform.w;
			newSpr.Draw();
		}
		break;

	case Direction::UP:
		if (skinGreen) { newSpr.objectID = ObjectID::SNK_G_BODY_VERT; }
		else { newSpr.objectID = ObjectID::SNK_R_BODY_VERT; }
		newSpr.transform.x = x1 * newSpr.transform.w;
		for (int j = y1 - 1; j > y2; j--) {
			newSpr.transform.y = j * newSpr.transform.h;
			newSpr.Draw();
		}
		break;

	case Direction::DOWN:
		if (skinGreen) { newSpr.objectID = ObjectID::SNK_G_BODY_VERT; }
		else { newSpr.objectID = ObjectID::SNK_R_BODY_VERT; }
		newSpr.transform.x = x1 * newSpr.transform.w;
		for (int j = y1 + 1; j < y2; j++) {
			newSpr.transform.y = j * newSpr.transform.h;
			newSpr.Draw();
		}
		break;

	}

}

//Cambia un sprite dependendo de la dirección
int Snake::SwitchSprite(Direction fromDir, Direction toDir) {
	switch (fromDir) {

	case Direction::RIGHT:
		switch (toDir) {
		case Direction::UP:
			return 1;
		case Direction::DOWN:
			return 3;
		case Direction::LEFT:
			return 2;
		}
		break;

	case Direction::LEFT:
		switch (toDir) {
		case Direction::UP:
			return -1;
		case Direction::DOWN:
			return 1;
		case Direction::RIGHT:
			return -2;
		}
		break;

	case Direction::UP:
		switch (toDir) {
		case Direction::RIGHT:
			return -1;
		case Direction::LEFT:
			return 1;
		case Direction::DOWN:
			return 2;
		}
		break;

	case Direction::DOWN:
		switch (toDir) {
		case Direction::RIGHT:
			return -3;
		case Direction::LEFT:
			return -1;
		case Direction::UP:
			return -2;
		}
		break;
	}

	return 0;

}

//Comprueba que sprite de giro se debe pintar
ObjectID Snake::TurnSprite(Direction fromDir, Direction toDir) {
	if (fromDir != toDir) {
		switch (fromDir) {

		case Direction::RIGHT:
			switch (toDir) {
			case Direction::UP:
				return ObjectID::SNK_G_UP_LEFT;
			case Direction::DOWN:
				return ObjectID::SNK_G_DOWN_LEFT;
			}
			break;

		case Direction::LEFT:
			switch (toDir) {
			case Direction::UP:
				return ObjectID::SNK_G_UP_RIGHT;
			case Direction::DOWN:
				return ObjectID::SNK_G_DOWN_RIGHT;
			}
			break;

		case Direction::UP:
			switch (toDir) {
			case Direction::RIGHT:
				return ObjectID::SNK_G_DOWN_RIGHT;
			case Direction::LEFT:
				return ObjectID::SNK_G_DOWN_LEFT;
			}
			break;

		case Direction::DOWN:
			switch (toDir) {
			case Direction::RIGHT:
				return ObjectID::SNK_G_UP_RIGHT;
			case Direction::LEFT:
				return ObjectID::SNK_G_UP_LEFT;
			}
			break;
		}
	}
}

ObjectID Snake::ChangeSkin(bool skin, ObjectID actualSkin) {
	if (skin && (int)actualSkin > 13) { return (ObjectID)((int)actualSkin - 14); }
	else if (!skin && (int)actualSkin < 14) { return (ObjectID)((int)actualSkin + 14); }
	return actualSkin;
}

//Comprueba si la cabeza de la serpiente colisiona con los obstaculos o con los limites
bool Snake::ObstaclesCollision() {

	switch (head.dir) {

	case Direction::RIGHT:
		if (obstacles.size() > 0) {
			for (int i = 0; i < obstacles.size(); i++) {
				if (obstacles[i].first) {
					if (head.x + 1 == obstacles[i].second.first && head.y == obstacles[i].second.second) { return true; }
				}
			}
		}
		if (head.x + 1 == W.GetWidth() / head.spr.transform.w - 1) { return true; }
		else return false;
		break;

	case Direction::LEFT:
		if (obstacles.size() > 0) {
			for (int i = 0; i < obstacles.size(); i++) {
				if (obstacles[i].first) {
					if (head.x - 1 == obstacles[i].second.first && head.y == obstacles[i].second.second) { return true; }
				}
			}
		}
		if (head.x - 1 == 0) { return true; }
		else return false;
		break;

	case Direction::UP:
		if (obstacles.size() > 0) {
			for (int i = 0; i < obstacles.size(); i++) {
				if (obstacles[i].first) {
					if (head.x == obstacles[i].second.first && head.y - 1 == obstacles[i].second.second) { return true; }
				}
			}
		}
		if (head.y - 1 == 0) { return true; }
		else return false;
		break;

	case Direction::DOWN:
		if (obstacles.size() > 0) {
			for (int i = 0; i < obstacles.size(); i++) {
				if (obstacles[i].first) {
					if (head.x == obstacles[i].second.first && head.y + 1 == obstacles[i].second.second) { return true; }
				}
			}
		}
		if (head.y + 1 == W.GetHeight() / head.spr.transform.h - 1) { return true; }
		else return false;
		break;

	}

}

//Comprueba que la serpiente no este traspasando ningun obstaculo despues de cambiar los obstaculos activos
void Snake::CheckSnake() {
	bool collide = false;
	if (obstacles.size() > 0) {

		do {
			collide = false;

			if (snk.size() > 0) {

				for (int i = 0; i < obstacles.size(); i++) {

					if (obstacles[i].first) {

						if ((obstacles[i].second.first <= head.x && obstacles[i].second.first >= snk.front().x) || (obstacles[i].second.first >= head.x && obstacles[i].second.first <= snk.front().x)) {
							if ((obstacles[i].second.second <= head.y && obstacles[i].second.second >= snk.front().y) || (obstacles[i].second.second >= head.y && obstacles[i].second.second <= snk.front().y)) {
								tail.x = obstacles[i].second.first;
								tail.y = obstacles[i].second.second;
								tail.spr.objectID = (ObjectID)((int)tail.spr.objectID + SwitchSprite(tail.dir, head.dir));
								tail.dir = head.dir;
								collide = true;
								snk.clear();
								break;
							}
						}

						if (!collide) {

							for (int j = 0; j < snk.size() - 1; j++) {
								if ((obstacles[i].second.first <= snk[j].x && obstacles[i].second.first >= snk[j + 1].x) || (obstacles[i].second.first >= snk[j].x + 1 && obstacles[i].second.first <= snk[j + 1].x)) {
									if ((obstacles[i].second.second <= snk[j].y - 1 && obstacles[i].second.second >= snk[j + 1].y) || (obstacles[i].second.second >= snk[j].y + 1 && obstacles[i].second.second <= snk[j + 1].y)) {
										tail.x = obstacles[i].second.first;
										tail.y = obstacles[i].second.second;
										tail.spr.objectID = (ObjectID)((int)tail.spr.objectID + SwitchSprite(tail.dir, snk[j + 1].dir));
										tail.dir = snk[j + 1].dir;
										collide = true;
										for (int k = snk.size() - 1; k > j; k--) {
											snk.pop_back();
										}
									}
								}
							}

							if (!collide) {
								if ((obstacles[i].second.first <= tail.x && obstacles[i].second.first >= snk.back().x) || (obstacles[i].second.first >= tail.x && obstacles[i].second.first <= snk.back().x)) {
									if ((obstacles[i].second.second <= tail.y && obstacles[i].second.second >= snk.back().y) || (obstacles[i].second.second >= tail.y && obstacles[i].second.second <= snk.back().y)) {
										tail.x = obstacles[i].second.first;
										tail.y = obstacles[i].second.second;
										if (obstacles[i].second.first == tail.x && obstacles[i].second.second == tail.y) { collide = false; }
										else { collide = true; }
									}
								}
							}

						}

					}

				}

			}
			else {

				for (int i = 0; i < obstacles.size(); i++) {
					if (obstacles[i].first) {
						if ((obstacles[i].second.first <= head.x && obstacles[i].second.first >= tail.x) || (obstacles[i].second.first >= head.x && obstacles[i].second.first <= tail.x)) {
							if ((obstacles[i].second.second <= head.y && obstacles[i].second.second >= tail.y) || (obstacles[i].second.second >= head.y && obstacles[i].second.second <= tail.y)) {
								tail.x = obstacles[i].second.first;
								tail.y = obstacles[i].second.second;
								if (obstacles[i].second.first == tail.x && obstacles[i].second.second == tail.y) { collide = false; }
								else { collide = true; }
							}
						}
					}
				}

			}

		} while (collide);

	}
}