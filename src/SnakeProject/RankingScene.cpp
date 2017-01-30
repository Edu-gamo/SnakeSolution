#include "RankingScene.h"
#include "System.hh"
#include "GUI.hh"
//#include "IOManager.hh"

RankingScene::RankingScene(void) {
	menu_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::MENU_BG };
}

RankingScene::~RankingScene(void) {
}

void RankingScene::OnEntry(void) {
	//ranking_desordenado = IOManager::leerRanking();
}

void RankingScene::OnExit(void) {
}

void RankingScene::Update(void) {
	if (IM.IsKeyDown<KEY_BUTTON_ENTER>()) SetState<SceneState::SLEEP>();
	/*for (auto it = ranking_desordenado.begin(); it != ranking_desordenado.end(); ++it) {
		auto v_temp = *it;
		std::cout << v_temp.second << " " << score << endl;
	}*/
}

void RankingScene::Draw(void) {
	menu_background.Draw(); // Render background
	GUI::DrawTextBlended<FontID::ARIAL>("RANKING", { W.GetWidth() / 2, 15, 1, 1 }, { 255, 255, 255 });
	GUI::DrawTextBlended<FontID::ARIAL>("Press ENTER to continue...", { W.GetWidth() / 2, W.GetHeight() - 50, 1, 1 }, { 255, 255, 255 });
}
