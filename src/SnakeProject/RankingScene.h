#pragma once
#include "Scene.hh"
#include "Button.h"

class RankingScene : public Scene {
public:
	explicit RankingScene();
	~RankingScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

	void SetScore(std::pair<int, int> n_score) { difficulty = n_score.first; score = n_score.second; }

private:
	Sprite menu_background;
	int score;
	int difficulty;
	std::vector<std::pair<std::string, int>> ranking_desordenado;
	bool needName;
	std::string name;
	bool saveRanking;
};