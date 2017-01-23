#pragma once
#include "Sprite.hh"

class Button {
public:

	const int SPR_WIDTH = 300;
	const int SPR_HEIGHT = 100;

	void ChangeState(bool state) {
		active = state;
	}

	bool IsActive() {
		return active;
	}

	void SetSprite(Sprite spr) {
		buttonImg = spr;
	}

	Sprite GetSprite() {
		return buttonImg;
	}

	bool CheckPos(int cX, int cY) {
		if (cX > buttonImg.transform.x && cX < buttonImg.transform.x + buttonImg.transform.w) {
			if (cY > buttonImg.transform.y && cY < buttonImg.transform.y + buttonImg.transform.h) {
				return true;
			}
		}
		return false;
	}

private:
	Sprite buttonImg;
	bool active = false;
};