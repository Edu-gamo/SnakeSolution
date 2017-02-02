#pragma once
#include "Sprite.hh"
#include <time.h>

class Food {
public:
	void SetFood(std::vector<std::pair<int, int>> availablePositions, int difficulty) {
		std::srand((Uint32)time(NULL));

		if (difficulty == 2) {
			spr.objectID = (ObjectID)(std::rand() % 2 + (int)ObjectID::FRUIT_G);
		} else {
			spr.objectID = (ObjectID)((int)ObjectID::FRUIT_G);
		}

		spr.transform.w = W.GetWidth() / 31;
		spr.transform.h = W.GetHeight() / 24;

		if (availablePositions.size() > 0) {
			int pos = std::rand() % availablePositions.size();

			spr.transform.x = availablePositions[pos].first * spr.transform.w;
			spr.transform.y = availablePositions[pos].second * spr.transform.h;
		}

		eaten = false;
	}
	void SetEaten() { eaten = true; }
	bool IsEaten() { return eaten; }
	void SetSprite(Sprite newSprite) { spr = newSprite; }
	Sprite GetSprite() { return spr; }

private:
	Sprite spr;
	bool eaten = false;
};