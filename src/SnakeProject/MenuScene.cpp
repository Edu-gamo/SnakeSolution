#include "MenuScene.h"
#include "System.hh"

MenuScene::MenuScene(void) {
	menu_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::MENU_BG };

	Sprite spr;
	spr.objectID = ObjectID::PLAY_BUT;
	spr.transform = Transform(W.GetWidth() / 2 - (play.SPR_WIDTH / 2), W.GetHeight() / 2 - 125, play.SPR_WIDTH, play.SPR_HEIGHT);
	play.SetSprite(spr);

	spr.objectID = ObjectID::EXIT_BUT;
	spr.transform = Transform(W.GetWidth() / 2 - (exit.SPR_WIDTH / 2), W.GetHeight() / 2 + 25, exit.SPR_WIDTH, exit.SPR_HEIGHT);
	exit.SetSprite(spr);

	spr.objectID = ObjectID::EASY_BUT;
	spr.transform = Transform(W.GetWidth() / 2 - (easy.SPR_WIDTH / 2), W.GetHeight() / 2 - 150, easy.SPR_WIDTH, easy.SPR_HEIGHT);
	easy.SetSprite(spr);

	spr.objectID = ObjectID::MEDIUM_BUT;
	spr.transform = Transform(W.GetWidth() / 2 - (medium.SPR_WIDTH / 2), W.GetHeight() / 2 + 0, medium.SPR_WIDTH, medium.SPR_HEIGHT);
	medium.SetSprite(spr);

	spr.objectID = ObjectID::HARD_BUT;
	spr.transform = Transform(W.GetWidth() / 2 - (hard.SPR_WIDTH / 2), W.GetHeight() / 2 + 150, hard.SPR_WIDTH, hard.SPR_HEIGHT);
	hard.SetSprite(spr);
}

MenuScene::~MenuScene(void) {
}

void MenuScene::OnEntry(void) {
	play.ChangeState(true);
	exit.ChangeState(true);

	easy.ChangeState(false);
	medium.ChangeState(false);
	hard.ChangeState(false);
}

void MenuScene::OnExit(void) {
}

void MenuScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		mouseCoords = IM.GetMouseCoords();

		//Comprobar si se ha pulsado alguno de los botones de dificultad
		if (easy.IsActive() && easy.CheckPos(mouseCoords.x, mouseCoords.y)) { difficulty = 0; SetState<SceneState::SLEEP>(); }
		else if (medium.IsActive() && medium.CheckPos(mouseCoords.x, mouseCoords.y)) { difficulty = 1; SetState<SceneState::SLEEP>(); }
		else if (hard.IsActive() && hard.CheckPos(mouseCoords.x, mouseCoords.y)) { difficulty = 2; SetState<SceneState::SLEEP>(); }

		//Comprobar si se ha pulsado el boton de jugar
		if (play.IsActive() && play.CheckPos(mouseCoords.x, mouseCoords.y)) {

			play.ChangeState(false);
			exit.ChangeState(false);

			easy.ChangeState(true);
			medium.ChangeState(true);
			hard.ChangeState(true);

		}

		//Comprobar si se ha pulsado el boton de salir
		if (exit.IsActive() && exit.CheckPos(mouseCoords.x, mouseCoords.y)) SetState<SceneState::EXIT>();
	}

	//Comprobar si se ha pulsado la tecla Escape
	if (IM.IsKeyDown<KEY_BUTTON_ESCAPE>()) {

		if (!exit.IsActive()) {

			play.ChangeState(true);
			exit.ChangeState(true);

			easy.ChangeState(false);
			medium.ChangeState(false);
			hard.ChangeState(false);

		}
		else SetState<SceneState::EXIT>();

	}

}

void MenuScene::Draw(void) {
	menu_background.Draw(); // Render background
	if (play.IsActive()) play.GetSprite().Draw();
	if (exit.IsActive()) exit.GetSprite().Draw();
	if (easy.IsActive()) easy.GetSprite().Draw();
	if (medium.IsActive()) medium.GetSprite().Draw();
	if (hard.IsActive()) hard.GetSprite().Draw();
	/*GUI::DrawTextShaded<FontID::FACTORY>("ENTI CRUSH", { W.GetWidth() >> 1,
	int(W.GetHeight()*.1f), 1, 1 }, { 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
	GUI::DrawTextBlended<FontID::CANDY>("Score: " + std::to_string(m_score),
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 }, { 115, 0, 180 }); // Render score that will be different when updated*/
}