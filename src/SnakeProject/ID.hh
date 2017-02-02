/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#pragma once
#include <iostream>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : int {
	//Green snake parts (0-13)
	SNK_G_BODY_HOR, SNK_G_BODY_VERT, //Body parts
	SNK_G_HEAD_RIGHT, SNK_G_HEAD_UP, SNK_G_HEAD_LEFT, SNK_G_HEAD_DOWN, //Head parts
	SNK_G_TAIL_RIGHT, SNK_G_TAIL_UP, SNK_G_TAIL_LEFT, SNK_G_TAIL_DOWN, //Tail parts
	SNK_G_UP_RIGHT, SNK_G_UP_LEFT, SNK_G_DOWN_RIGHT, SNK_G_DOWN_LEFT, //Turn parts

	//Red snake parts (14-27)
	SNK_R_BODY_HOR, SNK_R_BODY_VERT, //Body parts
	SNK_R_HEAD_RIGHT, SNK_R_HEAD_UP, SNK_R_HEAD_LEFT, SNK_R_HEAD_DOWN, //Head parts
	SNK_R_TAIL_RIGHT, SNK_R_TAIL_UP, SNK_R_TAIL_LEFT, SNK_R_TAIL_DOWN, //Tail parts
	SNK_R_UP_RIGHT, SNK_R_UP_LEFT, SNK_R_DOWN_RIGHT, SNK_R_DOWN_LEFT, //Turn parts

	/*//Blue snake parts ()
	SNK_B_BODY_HOR, SNK_B_BODY_VERT, //Body parts
	SNK_B_HEAD_RIGHT, SNK_B_HEAD_UP, SNK_B_HEAD_LEFT, SNK_B_HEAD_DOWN, //Head parts
	SNK_B_TAIL_RIGHT, SNK_B_TAIL_UP, SNK_B_TAIL_LEFT, SNK_B_TAIL_DOWN, //Tail parts
	SNK_B_UP_RIGHT, SNK_B_UP_LEFT, SNK_B_DOWN_RIGHT, SNK_B_DOWN_LEFT, //Turn parts*/

	MENU_BG, GAME_BG, //Menu Background
	PLAY_BUT, EXIT_BUT, EASY_BUT, MEDIUM_BUT, HARD_BUT, RANK_BUT, //Buttons
	WALL_G, WALL_R,
	FRUIT_G, FRUIT_R, //Food
	HEART,
	TIME_BAR1, TIME_BAR2,

	MUSIC_MENU, MUSIC_GAME, //Music
	POINTS //Sounds
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