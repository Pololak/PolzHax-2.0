#pragma once
#include "pch.h"

namespace PauseLayer {
	inline void(__thiscall* customSetup)(gd::PauseLayer*);
	void __fastcall customSetupH(gd::PauseLayer* self);

	inline void(__thiscall* togglerMenu)();
	void __fastcall togglerMenuH();

	inline void(__thiscall* onRestart)(CCObject*);
	void __fastcall onRestartH(CCObject*);

	inline void(__thiscall* onQuit)(gd::PauseLayer*, CCObject*);
	void __fastcall onQuitH(gd::PauseLayer*, void*, CCObject*);

	inline void(__thiscall* onProgressBar)(gd::PauseLayer*, CCObject*);
	void __fastcall onProgressBarH(gd::PauseLayer*, void*, CCObject*);

	class Callback {
	public:
		void onShowPercentage(CCObject*);
	};

	void mem_init();
}