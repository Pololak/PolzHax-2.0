#pragma once
#include "pch.h"

namespace SetGroupIDLayer {
	inline bool(__thiscall* init)(gd::SetGroupIDLayer*, gd::GameObject*, CCArray*);
	bool __fastcall initH(gd::SetGroupIDLayer*, void*, gd::GameObject*, CCArray*);

	inline void(__thiscall* textChanged)(gd::SetGroupIDLayer*, gd::CCTextInputNode*);
	void __fastcall textChangedH(gd::SetGroupIDLayer*, void*, gd::CCTextInputNode*);

	inline void(__thiscall* onEditorLayer)(gd::SetGroupIDLayer*, CCObject*);
	void __fastcall onEditorLayerH(gd::SetGroupIDLayer*, void*, CCObject*);

	inline void(__thiscall* onEditorLayer2)(gd::SetGroupIDLayer*, CCObject*);
	void __fastcall onEditorLayer2H(gd::SetGroupIDLayer*, void*, CCObject*);

	inline void(__thiscall* onZOrder)(gd::SetGroupIDLayer*, CCObject*);
	void __fastcall onZOrderH(gd::SetGroupIDLayer*, void*, CCObject*);

	void mem_init();
}