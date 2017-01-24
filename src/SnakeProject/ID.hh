/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include <iostream>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : int {
	CANDY_BLUE, CANDY_GREEN, CANDY_YELLOW, CANDY_RED, CANDY_PURPLE, CANDY_ORANGE, CANDY_MAX, CANDY_EMPTY, // Candies IDs
	CELL_EMPTY, // Cell IDs
	BG_00,  // Background IDs
	MENU_BG, //Menu Background
	PLAY_BUT, EXIT_BUT, EASY_BUT, MEDIUM_BUT, HARD_BUT, //Buttons
	FRUIT, //Food
	SNK_BODY_HOR, SNK_BODY_VERT, //Body parts
	SNK_HEAD_RIGHT, SNK_HEAD_UP, SNK_HEAD_LEFT, SNK_HEAD_DOWN, //Head parts
	SNK_TAIL_RIGHT, SNK_TAIL_UP, SNK_TAIL_LEFT, SNK_TAIL_DOWN, //Tail parts
	SNK_UP_RIGHT, SNK_UP_LEFT, SNK_DOWN_RIGHT, SNK_DOWN_LEFT //Turn parts
};
inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator>>(std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };

// Enum ID used to store each true type font for text rendering
enum class FontID : int {
	ARIAL,
	CANDY,
	FACTORY,
	MAX
};