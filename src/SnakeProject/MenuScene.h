#pragma once
#include "Scene.hh"
#include "Button.h"
#include "System.hh"

class MenuScene : public Scene {
public:
	explicit MenuScene();
	~MenuScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;

	int GetDifficulty() { return difficulty; }

	int GoToGame() { return toPlay; }

private:
	Sprite menu_background;
	Button play, exit, easy, medium, hard, ranking;
	int difficulty = 0;
	bool toPlay;
};