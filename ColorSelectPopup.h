#pragma once
#include "pch.h"

namespace ColorSelectPopup {
	inline bool(__thiscall* init)(gd::ColorSelectPopup*, gd::GameObject*, CCArray*, void*);
	bool __fastcall initH(gd::ColorSelectPopup*, void*, gd::GameObject*, CCArray*, void*);

	inline void(__thiscall* colorValueChanged)(gd::ColorSelectPopup*, ccColor3B);
	void __fastcall colorValueChangedH(gd::ColorSelectPopup*, void*, ccColor3B);

	inline void(__thiscall* closeColorSelect)(gd::ColorSelectPopup*, CCObject*);
	void __fastcall closeColorSelectH(gd::ColorSelectPopup*, void*, CCObject*);

	inline void(__thiscall* updateCopyColorTextInputLabel)(gd::ColorSelectPopup*);
	void __fastcall updateCopyColorTextInputLabelH(gd::ColorSelectPopup*);

	class Callback : public gd::ColorSelectPopup {
	public:
		void onDefault(CCObject*);
		void onLiveEdit(CCObject*);
	};

	void mem_init();
}

namespace SetupPulsePopup {
	inline bool(__thiscall* init)(gd::SetupPulsePopup*, gd::EffectGameObject*, CCArray*);
	bool __fastcall initH(gd::SetupPulsePopup*, void*, gd::EffectGameObject*, CCArray*);

	inline void(__thiscall* closeColorSelect)(gd::SetupPulsePopup*, CCObject*);
	void __fastcall closeColorSelectH(gd::SetupPulsePopup*, void*, CCObject*);

	inline void(__thiscall* colorValueChanged)(gd::SetupPulsePopup*);
	void __fastcall colorValueChangedH(gd::SetupPulsePopup*);

	inline void(__thiscall* updatePulseMode)(gd::SetupPulsePopup*);
	void __fastcall updatePulseModeH(gd::SetupPulsePopup*);

	void mem_init();
}