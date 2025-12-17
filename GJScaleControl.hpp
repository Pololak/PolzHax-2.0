#pragma once
#include "pch.h"

namespace GJScaleControl {
	inline bool(__thiscall* init)(gd::GJScaleControl*);
	bool __fastcall initH(gd::GJScaleControl*, void*);

	void mem_init();
}