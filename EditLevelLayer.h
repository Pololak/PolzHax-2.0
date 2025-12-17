#include "pch.h"

namespace EditLevelLayer {
	inline bool(__thiscall* init)(gd::EditLevelLayer*, gd::GJGameLevel*);
	bool __fastcall initH(gd::EditLevelLayer*, void*, gd::GJGameLevel*);

	class Callback : public gd::EditLevelLayer {
	public:
		void onExportLevel(CCObject*);
		void onResetPercentage(CCObject*);
	};

	void mem_init();
}