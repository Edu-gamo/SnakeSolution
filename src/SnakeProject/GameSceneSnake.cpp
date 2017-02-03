#include "GameSceneSnake.h"
#include "System.hh"
#include "GUI.hh"

GameSceneSnake::GameSceneSnake(void) {
	game_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::GAME_BG };
}

GameSceneSnake::~GameSceneSnake(void) {
}

void GameSceneSnake::OnEntry(void) {
	MM.PlayMusic<ObjectID::MUSIC_GAME>();
	m_snake = Snake();
	newDir = m_snake.GetHead().dir;
	frameLimit = 200;
	score = 0;
	contadorNivel = 1;
	contadorAlimentos = 0;
	saveScore = 0;
	std::vector<std::pair<bool, std::pair<int, int>>> newObstacles;

	if (difficulty == 0) {
			alimentosASumar = IOManager::consultarXML("easy", "aditionalfood");
			limiteAlimentos = IOManager::consultarXML("easy", "startingFood");
			vidas = IOManager::consultarXML("easy", "lives");
			frameLimit -= IOManager::consultarXML("easy", "startingSpeed");
			maxTime = IOManager::consultarXML("easy", "time");
			actualTime = maxTime;
	} else if (difficulty == 1) {
		alimentosASumar = IOManager::consultarXML("medium", "aditionalfood");
		limiteAlimentos = IOManager::consultarXML("medium", "startingFood");
		vidas = IOManager::consultarXML("medium", "lives");
		frameLimit -= IOManager::consultarXML("medium", "startingSpeed");
		maxTime = IOManager::consultarXML("medium", "time");
		actualTime = maxTime;
		for (int i = 4; i < (W.GetHeight() / m_snake.GetHead().spr.transform.h) - 5; i++) {
			std::pair<int, int> pos;
			pos.second = i;

			pos.first = 7;
			newObstacles.push_back(std::pair<bool, std::pair<int, int>>(true, pos));

			pos.first = (W.GetWidth() / m_snake.GetHead().spr.transform.w) - 8;
			newObstacles.push_back(std::pair<bool, std::pair<int, int>>(true, pos));
		}
	} else {
		alimentosASumar = IOManager::consultarXML("hard", "aditionalfood");
		limiteAlimentos = IOManager::consultarXML("hard", "startingFood");
		vidas = IOManager::consultarXML("hard", "lives");
		frameLimit -= IOManager::consultarXML("hard", "startingSpeed");
		maxTime = IOManager::consultarXML("hard", "time");
		actualTime = maxTime;

		for (int i = 4; i < (W.GetHeight() / m_snake.GetHead().spr.transform.h) - 5; i++) {
			std::pair<int, int> pos;
			pos.second = i;

			pos.first = 7;
			newObstacles.push_back(std::pair<bool, std::pair<int, int>>(true, pos));

			pos.first = (W.GetWidth() / m_snake.GetHead().spr.transform.w) - 8;
			newObstacles.push_back(std::pair<bool, std::pair<int, int>>(true, pos));
		}
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
	food.SetFood(AvailablePositions(), difficulty);

	//Initial snake
	preHead = m_snake.GetHead();
	preTail = m_snake.GetTail();
	preSnakeParts = m_snake.GetSnakeParts();
}

void GameSceneSnake::OnExit(void) {
	MM.StopMusic();
}

void GameSceneSnake::Update(void) {

	if (IM.IsKeyDown<KEY_BUTTON_ENTER>() && pauseDead) pauseDead = false;

	if (IM.IsKeyDown<KEY_BUTTON_ENTER>() && m_snake.IsDead() && vidas == 0) {
		SetState<SceneState::SLEEP>();
	}

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
		MM.PlaySound<ObjectID::POINTS>();
		food.SetEaten();
		m_snake.SnakeGrow();
		score += (contadorAlimentos+1) * 100;
		if (frameLimit > minLimit && score % 2 == 0) {
			if (frameLimit - speedIncrement <= minLimit) { frameLimit = minLimit; }
			else frameLimit -= speedIncrement;
		}
		if (difficulty == 2) {
			if (food.GetSprite().objectID == ObjectID::FRUIT_G) {
				m_snake.SetSkinGreen(true);
				m_snake.SetObstacles(ChangeObstacles(true));
			}
			else {
				m_snake.SetSkinGreen(false);
				m_snake.SetObstacles(ChangeObstacles(false));
			}
		}
	}
	if (food.IsEaten()) {
		food.SetFood(AvailablePositions(), difficulty);
		contadorAlimentos++;
	}
	if (contadorAlimentos < limiteAlimentos) {
		if (frameRate > frameLimit) {
			if (m_snake.IsDead() && vidas > 0) {
				vidas--;
				m_snake.SetDead(false);
				m_snake.SetHead(preHead);
				m_snake.SetTail(preTail);
				m_snake.SetSnakeParts(preSnakeParts);
				score = saveScore;
				newDir = preHead.dir;
				contadorAlimentos = 0;
				pauseDead = true;

				//Reset speed
				frameLimit = 200;
				if (difficulty == 0) {
					frameLimit -= IOManager::consultarXML("easy", "startingSpeed");
				}
				else if (difficulty == 1) {
					frameLimit -= IOManager::consultarXML("medium", "startingSpeed");
				}
				else {
					frameLimit -= IOManager::consultarXML("hard", "startingSpeed");
				}

			}
			if (!m_snake.IsDead() && !pauseDead) {
				m_snake.Move(newDir);
			}
			frameRate = 0;
		}
		else {
			frameRate += (int)TM.GetDeltaTime();
		}

	}
	else {
		pauseLevelUp = true;
		if (IM.IsKeyDown<KEY_BUTTON_ENTER>()) {
			pauseLevelUp = false;
			contadorNivel++;
			contadorAlimentos = 0;
			limiteAlimentos += alimentosASumar * contadorNivel;

			//Reset speed
			frameLimit = 200;
			if (difficulty == 0) {
				frameLimit -= IOManager::consultarXML("easy", "startingSpeed");
			}
			else if (difficulty == 1) {
				frameLimit -= IOManager::consultarXML("medium", "startingSpeed");
			}
			else {
				frameLimit -= IOManager::consultarXML("hard", "startingSpeed");
			}

			//Save snake
			preHead = m_snake.GetHead();
			preTail = m_snake.GetTail();
			preSnakeParts = m_snake.GetSnakeParts();
			saveScore = score;
		}
	}

	if (!m_snake.IsDead() && !pauseDead && !pauseLevelUp) {
		if (time > 1000) {
			actualTime -= 1;
			time = 0;
		}
		time += TM.GetDeltaTime();
	} else {
		actualTime = maxTime;
	}
	if (actualTime == 0) m_snake.SetDead(true);

	if(m_snake.IsDead() && vidas > 0) MM.PlaySound<ObjectID::DEATH>();
	if(m_snake.IsDead() && vidas == 0) MM.PlaySound<ObjectID::GAME_OVER>();

}

void GameSceneSnake::Draw(void) {
	game_background.Draw(); // Render background
	DrawWalls();
	m_snake.Draw();
	food.GetSprite().Draw();

	//Pintar GUI
	GUI::DrawTextBlended<FontID::ARIAL>("Nivel: " + std::to_string(contadorNivel),  { W.GetWidth() / 3, 15, 1, 1 },{ 0, 0, 0 });
	GUI::DrawTextBlended<FontID::ARIAL>("Score: " + std::to_string(score), { W.GetWidth() / 2, 15, 1, 1 }, { 0, 0, 0 });
	GUI::DrawTextBlended<FontID::ARIAL>("Vida: ", { W.GetWidth() / 9, 15, 1, 1 }, { 0, 0, 0 });
	for (int i = 0; i < vidas; i++) {
		Sprite newSpr;
		newSpr.objectID = ObjectID::HEART;
		newSpr.transform.w = W.GetWidth() / 31;
		newSpr.transform.h = W.GetHeight() / 24;
		newSpr.transform.y = 0;
		newSpr.transform.x = (W.GetWidth() / 7) + i * newSpr.transform.w;
		newSpr.Draw();
	}

	if (actualTime > 0) {
		Sprite newSpr;
		newSpr.objectID = ObjectID::TIME_BAR2;
		newSpr.transform.h = W.GetHeight() / 24;
		newSpr.transform.y = 0;
		newSpr.transform.x = W.GetWidth() - 150;
		newSpr.transform.w = 100;
		newSpr.Draw();
		newSpr.objectID = ObjectID::TIME_BAR1;
		newSpr.transform.w = 100 * ((float)actualTime / (float)maxTime);
		newSpr.Draw();
	}

	if (pauseLevelUp) {
		GUI::DrawTextBlended<FontID::ARIAL>("LEVEL: " + std::to_string(contadorNivel) + " COMPLETE", { W.GetWidth() / 2, (W.GetHeight() / 2) - 15, 1, 1 }, { 0, 0, 0 });
		GUI::DrawTextBlended<FontID::ARIAL>("Press ENTER to continue...", { W.GetWidth() / 2, W.GetHeight() - 50, 1, 1 }, { 0, 0, 0 });
	}

	if (pauseDead) {
		GUI::DrawTextBlended<FontID::ARIAL>("LIVES LEFT " + std::to_string(vidas), { W.GetWidth() / 2, (W.GetHeight() / 2) - 15, 1, 1 }, { 0, 0, 0 });
		GUI::DrawTextBlended<FontID::ARIAL>("Press ENTER to continue...", { W.GetWidth() / 2, W.GetHeight() - 50, 1, 1 }, { 0, 0, 0 });
	}

	if (m_snake.IsDead() && vidas == 0) {
		GUI::DrawTextBlended<FontID::ARIAL>("GAME OVER", { W.GetWidth() / 2, (W.GetHeight() / 2) - 15, 1, 1 }, { 0, 0, 0 });
		GUI::DrawTextBlended<FontID::ARIAL>("Press ENTER to continue...", { W.GetWidth() / 2, W.GetHeight() - 50, 1, 1 }, { 0, 0, 0 });
	}

}

void GameSceneSnake::DrawWalls() {
	Sprite newSpr;
	if (m_snake.IsGreen()) { newSpr.objectID = ObjectID::WALL_G; }
	else { newSpr.objectID = ObjectID::WALL_R; }
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
			if (difficulty < 2 || i < obs.size() / 2) { newSpr.objectID = ObjectID::WALL_G; }
			else { newSpr.objectID = ObjectID::WALL_R; }
			newSpr.transform.x = obs[i].second.first * newSpr.transform.w;
			newSpr.transform.y = obs[i].second.second * newSpr.transform.h;
			newSpr.Draw();
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
					if (obs[k].second.first == i && obs[k].second.second == j) {
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