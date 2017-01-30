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

	void SetScore(int scor) { score = scor; }

private:
	Sprite menu_background;
	int score;
	
};