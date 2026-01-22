#pragma once
#include "pch.h"

namespace GJRotationControl {
	inline bool(__thiscall* init)(gd::GJRotationControl*);
	bool __fastcall initH(gd::GJRotationControl*);

	inline void(__thiscall* ccTouchMoved)(gd::GJRotationControl*, CCTouch*, CCEvent*);
	void __fastcall ccTouchMovedH(gd::GJRotationControl*, void*, CCTouch*, CCEvent*);

	void mem_init();
}