#pragma once
#include "pch.h"

namespace LevelInfoLayer {
	inline bool(__thiscall* init)(gd::LevelInfoLayer*, gd::GJGameLevel*);
	bool __fastcall initH(gd::LevelInfoLayer*, void*, gd::GJGameLevel*);

	inline void(__thiscall* levelDownloadFinished)(gd::LevelInfoLayer*, gd::GJGameLevel*);
	void __fastcall levelDownloadFinishedH(gd::LevelInfoLayer*, void*, gd::GJGameLevel*);

	void showInfoLabel(gd::LevelInfoLayer*, gd::GJGameLevel*);

	class Callback : public gd::LevelInfoLayer {
	public:
		void onMoveToTop(CCObject*);
		void onExportLevel(CCObject*);
	};

	void mem_init();
}