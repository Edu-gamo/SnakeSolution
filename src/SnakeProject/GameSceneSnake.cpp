#include "GameSceneSnake.h"
#include "System.hh"

GameSceneSnake::GameSceneSnake(void) {
	game_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::GAME_BG };
}

GameSceneSnake::~GameSceneSnake(void) {
}

void GameSceneSnake::OnEntry(void) {
	m_snake = Snake();
	newDir = m_snake.GetHead().dir;
	score = 0;
	frameLimit = 200;
	std::vector<std::pair<bool, std::pair<int, int>>> newObstacles;
	if (difficulty > 0) {
		for (int i = 4; i < (W.GetHeight() / m_snake.GetHead().spr.transform.h) - 5; i++) {
			std::pair<int, int> pos;
			pos.second = i;

			pos.first = 7;
			newObstacles.push_back(std::pair<bool, std::pair<int, int>>(true, pos));

			pos.first = (W.GetWidth() / m_snake.GetHead().spr.transform.w) - 8;
			newObstacles.push_back(std::pair<bool, std::pair<int, int>>(true, pos));
		}
	}
	if (difficulty == 2) {
		for (int i = 8; i < (W.GetWidth() / m_snake.GetHead().spr.transform.w) - 8; i++) {
			std::pair<int, int> pos;
			pos.first = i;

			pos.second = 4;
			newObstacles.push_back(std::pair<bool, std::pair<int, int>>(false, pos));

			pos.second = (W.GetHeight() / m_snake.GetHead().spr.transform.h) - 6;
			newObstacles.push_back(std::pair<bool, std::pair<int, int>>(false, pos));

		}
	}
	m_snake.SetObstacles(newObstacles);
	food.SetFood(AvailablePositions());
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

	if (m_snake.GetHead().spr.transform.x == food.GetSprite().transform.x && m_snake.GetHead().spr.transform.y == food.GetSprite().transform.y) {
		food.SetEaten();
		m_snake.SnakeGrow();
		score++;
		if (frameLimit > minLimit && score % 2 == 0) {
			if (frameLimit - speedIncrement <= minLimit) { frameLimit = minLimit; }
			else frameLimit -= speedIncrement;
		}
		if (food.GetSprite().objectID == ObjectID::FRUIT_G) {
			m_snake.SetSkinGreen(true);
			if (difficulty == 2) m_snake.SetObstacles(ChangeObstacles(true));
		}
		else {
			m_snake.SetSkinGreen(false);
			if (difficulty == 2) m_snake.SetObstacles(ChangeObstacles(false));
		}
	}
	if (food.IsEaten()) food.SetFood(AvailablePositions());

	if (frameRate > frameLimit) {
		if (!m_snake.IsDead()) {
			m_snake.Move(newDir);
		}
		frameRate = 0;
	}
	else {
		frameRate += (int)TM.GetDeltaTime();
	}

}

void GameSceneSnake::Draw(void) {
	game_background.Draw(); // Render background
	DrawWalls();
	m_snake.Draw();
	food.GetSprite().Draw();
}

void GameSceneSnake::DrawWalls() {
	Sprite newSpr;
	/*if (m_snake.IsGreen()) { newSpr.objectID = ObjectID::WALL_G; }
	else { newSpr.objectID = ObjectID::WALL_B; }*/
	newSpr.objectID = ObjectID::WALL_G;
	newSpr.transform.w = W.GetWidth() / 31;
	newSpr.transform.h = W.GetHeight() / 24;

	//Pinta los limites Horizontales
	for (int i = 0; i < W.GetWidth() / newSpr.transform.w; i++) {
		newSpr.transform.x = i * newSpr.transform.w;

		newSpr.transform.y = 0;
		newSpr.Draw();

		newSpr.transform.y = W.GetHeight() - newSpr.transform.h;
		newSpr.Draw();

	}

	//Pinta los limites Verticales
	for (int i = 1; i < W.GetHeight() / newSpr.transform.h; i++) {
		newSpr.transform.y = i * newSpr.transform.h;

		newSpr.transform.x = 0;
		newSpr.Draw();

		newSpr.transform.x = W.GetWidth() - newSpr.transform.w;
		newSpr.Draw();

	}

	//Pinta los obstaculos
	std::vector<std::pair<bool, std::pair<int, int>>> obs = m_snake.GetObstacles();
	if (obs.size() > 0) {
		for (int i = 0; i < obs.size(); i++) {
			if (obs[i].first) { newSpr.objectID = ObjectID::WALL_G; }
			else { newSpr.objectID = ObjectID::WALL_B; }
			//if (obs[i].first) {
			newSpr.transform.x = obs[i].second.first * newSpr.transform.w;
			newSpr.transform.y = obs[i].second.second * newSpr.transform.h;
			newSpr.Draw();
			//}
		}
	}

}

std::vector<std::pair<bool, std::pair<int, int>>> GameSceneSnake::ChangeObstacles(bool snakeColor) {
	std::vector<std::pair<bool, std::pair<int, int>>> obs = m_snake.GetObstacles();
	if (obs.size() > 0) {
		if (obs[0].first != snakeColor) {
			for (int i = 0; i < obs.size(); i++) {
				obs[i].first = !obs[i].first;
			}
		}
	}
	return obs;
}

std::vector<std::pair<int, int>> GameSceneSnake::AvailablePositions() {
	std::vector<std::pair<int, int>> positions;

	for (int i = 1; i < (W.GetWidth() / m_snake.GetHead().spr.transform.w) - 1; i++) {
		for (int j = 1; j < (W.GetHeight() / m_snake.GetHead().spr.transform.h) - 1; j++) {

			bool empty = true;

			//Comprobar que la posicion no coincide con los obstaculos
			std::vector<std::pair<bool, std::pair<int, int>>> obs = m_snake.GetObstacles();
			if (obs.size() > 0) {
				for (int k = 0; k < obs.size(); k++) {
					if (/*obs[i].first &&*/ (obs[k].second.first == i && obs[k].second.second == j)) {
						empty = false;
					}
				}
			}

			if (empty) {
				//Comprobar que la posicion no coincide con la serpiente
				std::vector<SnakePart> snkParts = m_snake.GetSnakeParts();
				if (snkParts.size() > 0) {
					//Comprobar partes de la serpiente
					if ((i <= snkParts.back().x && i >= m_snake.GetTail().x) || (i >= snkParts.back().x && i <= m_snake.GetTail().x)) {
						if ((j <= snkParts.back().y && j >= m_snake.GetTail().y) || (j >= snkParts.back().y && j <= m_snake.GetTail().y)) {
							empty = false;
						}
					}
					for (int k = snkParts.size() - 1; k > 0; k--) {
						if ((i <= snkParts[k].x && i >= snkParts[k - 1].x) || (i >= snkParts[k].x && i <= snkParts[k - 1].x)) {
							if ((j <= snkParts[k].y && j >= snkParts[k - 1].y) || (j >= snkParts[k].y && j <= snkParts[k - 1].y)) {
								empty = false;
							}
						}
					}
					if ((i <= m_snake.GetHead().x && i >= snkParts.front().x) || (i >= m_snake.GetHead().x && i <= snkParts.front().x)) {
						if ((j <= m_snake.GetHead().y && j >= snkParts.front().y) || (j >= m_snake.GetHead().y && j <= snkParts.front().y)) {
							empty = false;
						}
					}
				}
				else {
					if ((i <= m_snake.GetHead().x && i >= m_snake.GetTail().x) || (i >= m_snake.GetHead().x && i <= m_snake.GetTail().x)) {
						if ((j <= m_snake.GetHead().y && j >= m_snake.GetTail().y) || (j >= m_snake.GetHead().y && j <= m_snake.GetTail().y)) {
							empty = false;
						}
					}
				}
			}

			if (empty)positions.push_back(std::pair<int, int>(i, j));

		}
	}

	return positions;
}