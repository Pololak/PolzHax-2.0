#pragma once
#include "pch.h"

namespace EditorPauseLayer {
	inline void(__thiscall* customSetup)(gd::EditorPauseLayer*);
	void __fastcall customSetupH(gd::EditorPauseLayer*);

	inline void(__thiscall* dtor)(gd::EditorPauseLayer*);
	void __fastcall dtorH(gd::EditorPauseLayer*);

	inline void(__thiscall* keyDown)(gd::EditorPauseLayer*, enumKeyCodes);
	void __fastcall keyDownH(gd::EditorPauseLayer*, void*, enumKeyCodes);

	inline void(__thiscall* saveLevel)(gd::EditorPauseLayer*);
	void __fastcall saveLevelH(gd::EditorPauseLayer*);

	void selectAllWithDirection(gd::EditorPauseLayer*, bool);

	class Callback : public gd::EditorPauseLayer {
	public:
		void onSaveLevel(CCObject*);
		void onPasteString(CCObject*);
		void onSelectAll(CCObject*);
		void onSelectAllLeft(CCObject*);
		void onSelectAllRight(CCObject*);
	};

	void mem_init();
}