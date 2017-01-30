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

	void SetScore(int n_score) { score = n_score; }

private:
	Sprite menu_background;
	int score;
	std::vector<std::pair<std::string, int>> ranking_desordenado;
};