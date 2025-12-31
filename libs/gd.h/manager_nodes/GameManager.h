#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <gd.h>

namespace gd {
	enum IconType {
		Cube = 0,
		Ship = 1,
		Ball = 2,
		Bird = 3,
		Dart = 4,
		Robot = 5,
		Special = 99,
	};

	class PlayLayer;
	class LevelEditorLayer;

	class GameManager : public GManager {
	public:
		int m_idk; // 0x104
		int m_idk2; // 0x108
		cocos2d::CCDictionary* m_valueKeeper; // 0x10c
		cocos2d::CCDictionary* m_customObjectDict; // 0x110
		int m_idk5; // 0x114
		int m_idk6; // 0x118
		int m_idk7; // 0x11c
		int m_idk8; // 0x120
		int m_idk9; // 0x124
		int m_idk10; // 0x128
		int m_idk11; // 0x12c
		int m_idk12; // 0x130
		int m_idk13; // 0x134
		int m_idk14; // 0x138
		int m_idk15; // 0x13c
		int m_idk16; // 0x140
		int m_idk17; // 0x144
		int m_idk18; // 0x148
		PlayLayer* m_playLayer; // 0x14c
		LevelEditorLayer* m_editorLayer; // 0x150
		void* m_levelSelectLayer; // 0x154
		MenuLayer* m_menuLayer; // 0x158
		bool m_mainMenuActive; // 0x15c
		PAD(0x3)
		void* m_premiumPopup; // 0x160
		bool m_firstSetup; // 0x164
		bool m_showedMenu; // 0x165
		PAD(0x2)
		std::string m_playerUDID; // 0x168
		std::string m_playerName; // 0x180
		int m_playerUserID; // 0x198
		bool m_playerScoreValid; // 0x19c
		PAD(0x3)
		float m_bgVolume; // 0x1a0
		float m_sfxVolume; // 0x1a4
		int m_timeOffset; // 0x1a8
		bool m_ratedGame; // 0x1ac
		bool m_clickedFacebook; // 0x1ad
		bool m_clickedTwitter; // 0x1ae
		bool m_clickedYouTube; // 0x1af
		bool m_didPauseBGMusic; // 0x1b0
		bool m_wasHigh; // 0x1b1
		bool m_editorEnabled; // 0x1b2
		PAD(0x1)
		int m_lastScene; // 0x1b4
		int m_lastScene2; // 0x1b8
		bool m_searchObjectBool; // 0x1bc
		PAD(0x3)
		int m_playerFrameRand1; // 0x1c0 // ts pmo
		int m_playerFrameRand2; // 0x1c4
		int m_playerFrame; // 0x1c8
		int m_playerShipRand1; // 0x1cc
		int m_playerShipRand2; // 0x1d0
		int m_playerShip; // 0x1d4
		int m_playerBallRand1; // 0x1d8
		int m_playerBallRand2; // 0x1dc
		int m_playerBall; // 0x1e0
		int m_playerBirdRand1; // 0x1e4
		int m_playerBirdRand2; // 0x1e8
		int m_playerBird; // 0x1ec
		int m_playerDartRand1; // 0x1f0
		int m_playerDartRand2; // 0x1f4
		int m_playerDart; // 0x1f8
		int m_playerRobotRand1; // 0x1fc
		int m_playerRobotRand2; // 0x200
		int m_playerRobot; // 0x204
		int m_playerColorRand1; // 0x208
		int m_playerColorRand2; // 0x20c
		int m_playerColor; // 0x210
		int m_playerColor2Rand1; // 0x214
		int m_playerColor2Rand2; // 0x218
		int m_playerColor2; // 0x21c
		int m_playerStreakRand1; // 0x220
		int m_playerStreakRand2; // 0x224
		int m_playerStreak; // 0x228
		bool m_playerGlow; // 0x22c
		PAD(0x3)
		IconType m_playerIconType; // 0x230
		bool m_didSetupEveryplay; // 0x234
		bool m_showSongMarkers; // 0x235
		bool m_showBPMMarkers; // 0x236
		bool m_recordGameplay; // 0x237
		bool m_showProgressBar; // 0x238
		bool m_performanceMode; // 0x239
		bool m_commentSortRecent; // 0x23a
		bool m_showedPirate; // 0x23b
		bool m_clickedGarage; // 0x23c
		bool m_clickedEditor; // 0x23d
		bool m_clickedName; // 0x23e
		bool m_clickedPractice; // 0x23f
		bool m_showedEditorGuide; // 0x240
		bool m_showedRateDiffDialog; // 0x241
		bool m_showedRateStarDialog; // 0x242
		bool m_showedLowDetailDialog; // 0x243
		GameRateDelegate* m_rateDelegate; // 0x244
		cocos2d::ccColor3B m_storedColor; // 0x248
		PAD(0x1)
		int m_lastLevelID; // 0x24c
		int m_lastCustomColorIdx; // 0x248
		int m_lastGroupID; // 0x24c
		int m_loadedBGIdx; // 0x250
		int m_loadedGIdx; // 0x254
		int m_loadedFontIdx; // 0x258
		int m_totalAttempts; // 0x25c
		int m_bootups; // 0x260
		bool m_hasRatedGame; // 0x264
		bool m_didPlayGame; // 0x265
		bool m_isResetting; // 0x266
		bool m_showingPromo; // 0x267
		bool m_testSmoothFix; // 0x268
		bool m_hasRatingPower; // 0x269
		bool m_fetchNewLevelsQueued; // 0x26a
		PAD(0x1)
		PAD(0x8)
		int m_resolution; // 0x274
		cocos2d::TextureQuality m_quality; // 0x278

	public:
		static GameManager* sharedState() {
			return reinterpret_cast<GameManager* (__stdcall*)()>(
				base + 0x9ac40
				)();
		}
		void reloadAll(bool bSwitch, bool bFullscreen, bool bReloadedInSession) {
			return reinterpret_cast<void(__thiscall*)(GameManager*, bool, bool, bool)>(
				base + 0xa2f70
				)(this, bSwitch, bFullscreen, bReloadedInSession);
		}
		bool getGameVariable(const char* key) {
			return reinterpret_cast<bool(__thiscall*)(GameManager*, const char*)>(
				base + 0x9f520
				)(this, key);
		}
		void setGameVariable(const char* key, bool value) {
			return reinterpret_cast<void(__thiscall*)(GameManager*, const char*, bool)>(
				base + 0x9f340
				)(this, key, value);
		}
		int getIntGameVariable(const char* key) {
			return reinterpret_cast<int(__thiscall*)(GameManager*, const char*)>(
				base + 0x9f860
				)(this, key);
		}
		void setIntGameVariable(const char* key, int value) {
			reinterpret_cast<void(__thiscall*)(GameManager*, const char*, int)>(base + 0x9f780)(this, key, value);
		}
		static void toggleGameVariable(const char* key) {
			reinterpret_cast<void(__stdcall*)(const char*)>(base + 0x9f680)(key);
		}
		bool getUGV(const char* key) {
			return reinterpret_cast<bool(__thiscall*)(GameManager*, const char*)>(
				base + 0xCA0D0
				)(this, key);
		}
		void fadeInMusic(const char* filename) {
			return reinterpret_cast<void(__thiscall*)(GameManager*, const char*)>(
				base + 0xC4BD0
				)(this, filename);
		}
		PlayLayer* getPlayLayer() {
			return from<PlayLayer*>(this, 0x14c);
		}
		LevelEditorLayer* getLevelEditorLayer() {
			return from<LevelEditorLayer*>(this, 0x150);
		}
		bool getProgressBar() {
			return from<bool>(this, 0x238);
		}
		cocos2d::ccColor3B colorForIdx(int colorID) {
			cocos2d::ccColor3B out;
			reinterpret_cast<cocos2d::ccColor3B* (__thiscall*)(GameManager*, cocos2d::ccColor3B*, int)>(base + 0x9e9f0)(this, &out, colorID);
			return out;
		}
	};
}

#endif