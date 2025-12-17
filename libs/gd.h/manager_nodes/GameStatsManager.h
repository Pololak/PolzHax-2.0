#ifndef __GAMESTATSMANAGER_H__
#define __GAMESTATSMANAGER_H__

#include <gd.h>

namespace gd {
	class GManager;
	class GJGameLevel;

	class GameStatsManager : public GManager {
	public:
		int m_idk;
		int m_idk2;
		int m_idk3;
		int m_idk4;

		static GameStatsManager* sharedState() {
			return reinterpret_cast<GameStatsManager * (__stdcall*)()>(
				base + 0xb8cd0
				)();
		}

		int getStat(const char* idx) {
			return reinterpret_cast<int(__thiscall*)(GameStatsManager*, const char*)>(base + 0xb8ef0)(this, idx);
		}

		void setStat(const char* idx, int amt) {
			reinterpret_cast<void(__thiscall*)(GameStatsManager*, const char*, int)>(base + 0xb8fb0)(this, idx, amt);
		}

		bool hasCompletedLevel(GJGameLevel* gameLevel) {
			return reinterpret_cast<bool(__thiscall*)(GameStatsManager*, GJGameLevel*)>(base + 0xbaa80)(this, gameLevel);
		}
	};
}

#endif // !__GAMESTATSMANAGER_H__
