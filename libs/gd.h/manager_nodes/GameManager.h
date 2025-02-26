#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <gd.h>

namespace gd {

	class PlayLayer;

	class GameManager : public GManager {
	protected:
		bool m_bSwitchModes;
		bool m_bToFullscreen;
		bool m_bReloading;
		bool m_bUnknown;
		PAD(4);
		cocos2d::CCDictionary* m_pValueKeeper;
		cocos2d::CCDictionary* m_pUnlockValueKeeper;
		cocos2d::CCDictionary* m_pCustomObjectDict;
		PAD(4);
		double m_dUnknown;
		PAD(16);
		double m_dUnknown2;
		PAD(8);
		bool m_bLoaded; //?
		std::string m_sUnknown;
		PlayLayer* m_pPlayLayer;
		PAD(24);
		std::string m_sPlayerUDID;
		std::string m_sPlayerName;
		bool m_bCommentsEnabled;
		int m_nPlayerUserIDRand1;
		int m_nPlayerUserIDRand2;
		int m_nPlayerUserID;
		float m_fBackgroundMusicVolume;
		float m_fEffectsVolume;
		int m_nTimeOffset;
		PAD(28);
		int m_nPlayerFrameRand1;
		int m_nPlayerFrameRand2;
		int m_nPlayerFrame;
		int m_nPlayerShipRand1;
		int m_nPlayerShipRand2;
		int m_nPlayerShip;
		int m_nPlayerBallRand1;
		int m_nPlayerBallRand2;
		int m_nPlayerBall;
		int m_nPlayerBirdRand1;
		int m_nPlayerBirdRand2;
		int m_nPlayerBird;
		int m_nPlayerDartRand1;
		int m_nPlayerDartRand2;
		int m_nPlayerDart;
		int m_nPlayerRobotRand1;
		int m_nPlayerRobotRand2;
		int m_nPlayerRobot;
		int m_nPlayerSpiderRand1;
		int m_nPlayerSpiderRand2;
		int m_nPlayerSpider;
		int m_nPlayerColorRand1;
		int m_nPlayerColorRand2;
		int m_nPlayerColor;
		int m_nPlayerColor2Rand1;
		int m_nPlayerColor2Rand2;
		int m_nPlayerColor2;
		int m_nPlayerStreakRand1;
		int m_nPlayerStreakRand2;
		int m_nPlayerStreak;
		int m_nPlayerDeathEffectRand1;
		int m_nPlayerDeathEffectRand2;
		int m_nPlayerDeathEffect;
		PAD(8);
		int m_nSecretNumberRand1; //? may be named differently
		int m_nSecretNumberRand2;
		bool m_bPlayerGlow;
		int m_nPlayerIconType;
		bool m_bUnknown2;
		bool m_bShowSongMarkers;
		bool m_bShowBPMMarkers;
		bool m_bRecordGameplay;
		bool m_bShowProgressBar;
		bool m_bPerformanceMode;
		bool m_bClickedGarage;
		bool m_bClickedEditor;
		bool m_bClickedName;
		bool m_bClickedPractice;
		bool m_bShowedEditorGuide;
		bool m_bShowedRateDiffDialog;
		bool m_bShowedRateStarDialog;
		bool m_bShowedLowDetailDialog;
		PAD(48);
		int m_nBootups;
		bool m_bHasRatedGame;
		PAD(3);
		bool m_bGameCenterEnabled;
		bool m_bSmoothFix;
		PAD(16);
		int m_nResolution;
		cocos2d::TextureQuality m_eQuality; //more after that i havent re'd

	public:
		static GameManager* sharedState() {
			return reinterpret_cast<GameManager* (__stdcall*)()>(
				base + 0x9ac40
				)();
		}
		void reloadAll(bool bSwitch, bool bFullscreen, bool bReloadedInSession) {
			return reinterpret_cast<void(__thiscall*)(GameManager*, bool, bool, bool)>(
				base + 0xCE950
				)(this, bSwitch, bFullscreen, bReloadedInSession);
		}
		void setQuality(cocos2d::TextureQuality quality) {
			m_eQuality = quality;
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
	};
}

#endif