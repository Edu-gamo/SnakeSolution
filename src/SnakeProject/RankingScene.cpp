#include "RankingScene.h"
#include "System.hh"
#include "GUI.hh"
//#include "IOManager.hh"

using namespace std;

//vector<pair<string, int>> ranking_desordenado = IOManager::leerRanking();

RankingScene::RankingScene(void) {
	menu_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::MENU_BG };
}

RankingScene::~RankingScene(void) {
}

void RankingScene::OnEntry(void) {

}

void RankingScene::OnExit(void) {
}

void RankingScene::Update(void) {
	/*for (auto it = ranking_desordenado.begin(); it != ranking_desordenado.end(); ++it) {
		auto v_temp = *it;
		std::cout << v_temp.second << " " << score << endl;
	}*/
}

void RankingScene::Draw(void) {
	menu_background.Draw(); // Render background
	GUI::DrawTextBlended<FontID::ARIAL>("RANKING", { W.GetWidth() / 2, 15, 1, 1 }, { 255, 255, 255 });
}
