#pragma once
#include <unordered_map>
#include <SDL_mixer.h>
#include "Assert.hh"
#include "ID.hh"

#define MM MusicManager::Instance()

class MusicManager {
	MusicManager() {
		Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	}
	MusicManager(const MusicManager &rhs) = delete;
	MusicManager &operator=(const MusicManager &rhs) = delete;
public:
	inline static MusicManager &Instance() {
		static MusicManager music;
		return music;
	}

	~MusicManager() {
		for (auto &t : m_musicData) Mix_FreeMusic(t.second), t.second = nullptr;
		for (auto &f : m_soundsData) Mix_FreeChunk(f.second), f.second = nullptr;
		Mix_CloseAudio();
	}

	template<ObjectID objectID> void LoadMusic(std::string &&filename) {
		m_musicData.emplace(objectID, Mix_LoadMUS(RESOURCE_FILE(filename)));
	}

	template<ObjectID objectID> void LoadSound(std::string &&filename) {
		m_soundsData.emplace(objectID, Mix_LoadWAV(RESOURCE_FILE(filename)));
	}

	template<ObjectID objectID> void PlayMusic() {
		Mix_PlayMusic(m_musicData[objectID], -1);
	}

	void StopMusic() {
		Mix_HaltMusic();
	}

	template<ObjectID objectID> void PlaySound() {
		Mix_PlayChannel(-1, m_soundsData[objectID], 0);
	}

private:
	std::unordered_map<ObjectID, Mix_Music*> m_musicData;
	std::unordered_map<ObjectID, Mix_Chunk*> m_soundsData;
};