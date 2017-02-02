#include "RankingScene.h"
#include "System.hh"
#include "GUI.hh"

string DifficultyString(int dif);
char DetectarTeclado();

RankingScene::RankingScene(void) {
	menu_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::MENU_BG };
}

RankingScene::~RankingScene(void) {
}

void RankingScene::OnEntry(void) {

	string strDifficulty = DifficultyString(difficulty);
	ranking_desordenado = IOManager::leerRanking(strDifficulty);

	name = "";

	needName = false;
	if (ranking_desordenado.size() == 0 || ranking_desordenado.size() < 10 || score > ranking_desordenado.back().second) {
		needName = true;
	}

	saveRanking = true;

}

void RankingScene::OnExit(void) {
}

void RankingScene::Update(void) {

	if (IM.IsKeyDown<KEY_BUTTON_ENTER>() && !needName) SetState<SceneState::SLEEP>();

	if (needName) {
		char letra;
		letra = DetectarTeclado();
		if (letra != '\0' && letra != ';') {
			if (letra == '<' && name.size() > 0) { name.pop_back(); }
			else if (letra != '<' && name.size() < 15) name += letra;
		}
		if (letra == '\0' && name.size() >= 3) needName = false;
	}

	if (saveRanking && !needName) {
		saveRanking = false;
		if (ranking_desordenado.size() > 0) {
			if (score > ranking_desordenado.back().second) {
				for (auto it = ranking_desordenado.begin(); it != ranking_desordenado.end(); ++it) {
					if (score > it->second) {
						ranking_desordenado.insert(it, pair<string, int>(name, score));
						if (ranking_desordenado.size() > 10) {
							ranking_desordenado.pop_back();
						}
						break;
					}
				}
			}
			else if (ranking_desordenado.size() < 10) {
				ranking_desordenado.push_back(pair<string, int>(name, score));
			}
		}
		else ranking_desordenado.push_back(pair<string, int>(name, score));

		string strDifficulty = DifficultyString(difficulty);
		IOManager::introducirRanking(ranking_desordenado, strDifficulty);
	}

}

void RankingScene::Draw(void) {
	menu_background.Draw(); // Render background

	if (needName) {
		GUI::DrawTextBlended<FontID::ARIAL>("ENTER NAME: " + name, { W.GetWidth() / 2, W.GetHeight() / 2, 1, 1 }, { 255, 255, 255 });
	}

	if (!needName) {
		string strDifficulty = DifficultyString(difficulty);
		GUI::DrawTextBlended<FontID::ARIAL>("RANKING: " + strDifficulty, { W.GetWidth() / 2, 15, 1, 1 }, { 255, 255, 255 });

		int posY = 200;
		for (auto it = ranking_desordenado.begin(); it != ranking_desordenado.end(); ++it) {
			GUI::DrawTextBlended<FontID::ARIAL>(it->first + " ==> " + std::to_string(it->second), { W.GetWidth() / 2, posY, 1, 1 }, { 255, 255, 255 });
			posY += 50;
		}

		GUI::DrawTextBlended<FontID::ARIAL>("Press ENTER to continue...", { W.GetWidth() / 2, W.GetHeight() - 50, 1, 1 }, { 255, 255, 255 });
	}
}

string DifficultyString(int dif) {
	string strDifficulty;
	switch (dif) {
		case 0:
			strDifficulty = "EASY";
			break;
		case 1:
			strDifficulty = "MEDIUM";
			break;
		case 2:
			strDifficulty = "HARD";
			break;
	}
	return strDifficulty;
}

char DetectarTeclado() {
	if (IM.IsKeyDown<'q'>()) { return 'Q'; }
	else if (IM.IsKeyDown<'w'>()) { return 'W'; }
	else if (IM.IsKeyDown<'e'>()) { return 'E'; }
	else if (IM.IsKeyDown<'r'>()) { return 'R'; }
	else if (IM.IsKeyDown<'t'>()) { return 'T'; }
	else if (IM.IsKeyDown<'y'>()) { return 'Y'; }
	else if (IM.IsKeyDown<'u'>()) { return 'U'; }
	else if (IM.IsKeyDown<'i'>()) { return 'I'; }
	else if (IM.IsKeyDown<'o'>()) { return 'O'; }
	else if (IM.IsKeyDown<'p'>()) { return 'P'; }
	else if (IM.IsKeyDown<'a'>()) { return 'A'; }
	else if (IM.IsKeyDown<'s'>()) { return 'S'; }
	else if (IM.IsKeyDown<'d'>()) { return 'D'; }
	else if (IM.IsKeyDown<'f'>()) { return 'F'; }
	else if (IM.IsKeyDown<'g'>()) { return 'G'; }
	else if (IM.IsKeyDown<'h'>()) { return 'H'; }
	else if (IM.IsKeyDown<'j'>()) { return 'J'; }
	else if (IM.IsKeyDown<'k'>()) { return 'K'; }
	else if (IM.IsKeyDown<'l'>()) { return 'L'; }
	else if (IM.IsKeyDown<'z'>()) { return 'Z'; }
	else if (IM.IsKeyDown<'x'>()) { return 'X'; }
	else if (IM.IsKeyDown<'c'>()) { return 'C'; }
	else if (IM.IsKeyDown<'v'>()) { return 'V'; }
	else if (IM.IsKeyDown<'b'>()) { return 'B'; }
	else if (IM.IsKeyDown<'n'>()) { return 'N'; }
	else if (IM.IsKeyDown<'m'>()) { return 'M'; }
	else if (IM.IsKeyDown<KEY_BUTTON_BACKSPACE>()) { return '<'; }
	else if (IM.IsKeyDown<KEY_BUTTON_ENTER>()) { return '\0'; }
	else return ';';
}