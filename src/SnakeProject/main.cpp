/******************************************************************
* Copyright (C) 2016 Jordi Serrano Berbel <jsberbel95@gmail.com> *
* This can not be copied, modified and/or distributed without    *
* express permission of the copyright owner.                     *
******************************************************************/

#include "GameEngine.hh"

// Game constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

int main(int argc, char* args[]) {
	//IOManager::introducirRanking("Carlos", 9999);
	/*vector<pair<string, int>> ranking = IOManager::leerRanking();

	for (auto it = ranking.begin(); it != ranking.end(); ++it) {
		auto v_temp = *it;
		std::cout << v_temp.first << ' ' << v_temp.second << endl;
	}/¡*/

	GameEngine::Run<SCREEN_WIDTH, SCREEN_HEIGHT>("Snake");
	return 0;
}