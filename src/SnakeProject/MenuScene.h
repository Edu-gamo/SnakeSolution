#pragma once
#include "Scene.hh"
#include "Button.h"

class MenuScene : public Scene {
public:
	explicit MenuScene();
	~MenuScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite menu_background;
	Button play, exit, easy, medium, hard;
};