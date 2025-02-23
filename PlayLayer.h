#pragma once
#include "pch.h"

namespace PlayLayer {
	inline bool(__thiscall* init)(gd::PlayLayer*, gd::GJGameLevel*);
	bool __fastcall initH(gd::PlayLayer*, void*, gd::GJGameLevel*);

	inline void(__thiscall* update)(gd::PlayLayer*, float);
	void __fastcall updateH(gd::PlayLayer*, void*, float);

	inline void(__thiscall* destroyPlayer)(gd::PlayLayer*, gd::PlayerObject*);
	void __fastcall destroyPlayerH(gd::PlayLayer*, void*, gd::PlayerObject*);

	inline void(__thiscall* resetLevel)(gd::PlayLayer*);
	void __fastcall resetLevelH(gd::PlayLayer*);

	inline void(__thiscall* togglePracticeMode)(gd::PlayLayer*, bool);
	void __fastcall togglePracticeModeH(gd::PlayLayer*, void*, bool);

	inline void(__thiscall* createCheckpoint)(gd::PlayLayer*);
	void __fastcall createCheckpointH(gd::PlayLayer*);

	inline void(__thiscall* removeLastCheckpoint)(gd::PlayLayer*);
	void __fastcall removeLastCheckpointH(gd::PlayLayer*);

	inline void(__thiscall* onQuit)(gd::PlayLayer*);
	void __fastcall onQuitH(gd::PlayLayer*);

	inline void(__thiscall* levelComplete)(gd::PlayLayer*);
	void __fastcall levelCompleteH(gd::PlayLayer*);

	inline void(__thiscall* addObject)(gd::PlayLayer*, gd::GameObject*);
	void __fastcall addObjectH(gd::PlayLayer*, void*, gd::GameObject*);

	inline void(__thiscall* lightningFlash)(gd::PlayLayer*, CCPoint, ccColor3B);
	void __fastcall lightningFlashH(gd::PlayLayer*, void*, CCPoint, ccColor3B);

	void onPrevStartPos();
	void onNextStartPos();

	void mem_init();
}