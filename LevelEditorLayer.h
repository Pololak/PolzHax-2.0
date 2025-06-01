#pragma once
#include "pch.h"

namespace LevelEditorLayer {
	inline bool(__thiscall* init)(gd::LevelEditorLayer*, gd::GJGameLevel*);
	bool __fastcall initH(gd::LevelEditorLayer*, void*, gd::GJGameLevel*);

	inline void(__thiscall* updateVisibility)(gd::LevelEditorLayer*, float);
	void __fastcall updateVisibilityH(gd::LevelEditorLayer*, void*, float);

	inline void(__thiscall* update)(gd::LevelEditorLayer*, float);
	void __fastcall updateH(gd::LevelEditorLayer*, void*, float);

	inline void(__thiscall* onPlaytest)(gd::LevelEditorLayer*);
	void __fastcall onPlaytestH(gd::LevelEditorLayer*);

	inline void(__thiscall* onResumePlaytest)(gd::LevelEditorLayer*);
	void __fastcall onResumePlaytestH(gd::LevelEditorLayer*);

	inline void(__thiscall* onPausePlaytest)(gd::LevelEditorLayer*);
	void __fastcall onPausePlaytestH(gd::LevelEditorLayer*);

	inline void(__thiscall* onStopPlaytest)(gd::LevelEditorLayer*);
	void __fastcall onStopPlaytestH(gd::LevelEditorLayer*);

	inline void(__thiscall* addSpecial)(gd::LevelEditorLayer*, gd::GameObject*);
	void __fastcall addSpecialH(gd::LevelEditorLayer*, void*, gd::GameObject*);

	inline void(__thiscall* removeObject)(gd::LevelEditorLayer*, gd::GameObject*, bool);
	void __fastcall removeObjectH(gd::LevelEditorLayer*, void*, gd::GameObject*, bool);
	
	void mem_init();
}

namespace DrawGridLayer {
	inline void(__thiscall* draw)(gd::DrawGridLayer*);
	void __fastcall drawH(gd::DrawGridLayer*);
}