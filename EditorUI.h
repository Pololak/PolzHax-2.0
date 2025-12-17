#pragma once
#include "pch.h"

namespace EditorUI {
	inline bool(__thiscall* init)(gd::EditorUI*, gd::LevelEditorLayer*);
	bool __fastcall initH(gd::EditorUI*, void*, gd::LevelEditorLayer*);

	inline void(__thiscall* createMoveMenu)(gd::EditorUI*);
	void __fastcall createMoveMenuH(gd::EditorUI*);

	inline CCPoint*(__thiscall* moveForCommand)(gd::EditorUI*, CCPoint*, gd::EditCommand);
	CCPoint* __fastcall moveForCommandH(gd::EditorUI* self, void* edx, CCPoint* pos, gd::EditCommand com);

	inline void(__thiscall* transformObject)(gd::EditorUI*, gd::GameObject*, gd::EditCommand, bool);
	void __fastcall transformObjectH(gd::EditorUI* self, void* edx, gd::GameObject* obj, gd::EditCommand com, bool idk);

	inline void(__thiscall* onCopy)(gd::EditorUI*, CCObject*);
	void __fastcall onCopyH(gd::EditorUI*, void*, CCObject*);

	inline void(__thiscall* dtor)(gd::EditorUI*);
	void __fastcall dtorH(gd::EditorUI*);

	inline void(__thiscall* keyDown)(gd::EditorUI*, enumKeyCodes);
	void __fastcall keyDownH(gd::EditorUI*, void*, enumKeyCodes);

	inline void(__thiscall* keyUp)(gd::EditorUI*, enumKeyCodes);
	void __fastcall keyUpH(gd::EditorUI*, void*, enumKeyCodes);

	inline void(__thiscall* scrollWheel)(gd::EditorUI*, float, float);
	void __fastcall scrollWheelH(gd::EditorUI*, void*, float, float);

	inline void(__thiscall* moveObject)(gd::EditorUI*, gd::GameObject*, CCPoint);
	void __fastcall moveObjectH(gd::EditorUI*, void*, gd::GameObject*, CCPoint);

	inline void(__thiscall* blocksArray)();
	void __fastcall blocksArrayH();

	inline void(__thiscall* selectObject)(gd::EditorUI*, gd::GameObject*);
	void __fastcall selectObjectH(gd::EditorUI*, void*, gd::GameObject*);

	inline void(__thiscall* updateObjectInfoLabel)(gd::EditorUI*);
	void __fastcall updateObjectInfoLabelH(gd::EditorUI*);

	inline void(__thiscall* onGroupUp)(gd::EditorUI*, CCObject*);
	void __fastcall onGroupUpH(gd::EditorUI*, void*, CCObject*);

	inline void(__thiscall* onGroupDown)(gd::EditorUI*, CCObject*);
	void __fastcall onGroupDownH(gd::EditorUI*, void*, CCObject*);

	inline void(__thiscall* selectObjects)(gd::EditorUI*, CCArray*);
	void __fastcall selectObjectsH(gd::EditorUI*, void*, CCArray*);

	inline void(__thiscall* transformObjectCall)(gd::EditorUI*, gd::EditCommand);
	void __fastcall transformObjectCallH(gd::EditorUI*, void*, gd::EditCommand);

	inline void(__thiscall* moveObjectCall)(gd::EditorUI*, gd::EditCommand);
	void __fastcall moveObjectCallH(gd::EditorUI*, void*, gd::EditCommand);

	inline bool(__thiscall* ccTouchBegan)(gd::EditorUI*, CCTouch*, CCEvent*);
	bool __fastcall ccTouchBeganH(gd::EditorUI*, void*, CCTouch*, CCEvent*);

	inline void(__thiscall* ccTouchEnded)(gd::EditorUI*, CCTouch*, CCEvent*);
	void __fastcall ccTouchEndedH(gd::EditorUI*, void*, CCTouch*, CCEvent*);

	inline void(__thiscall* onPlaytest)(gd::EditorUI*, CCObject*);
	void __fastcall onPlaytestH(gd::EditorUI*, void*, CCObject*);

	inline void(__thiscall* toggleSpecialEditButtons)(gd::EditorUI*);
	void __fastcall toggleSpecialEditButtonsH(gd::EditorUI*);

	inline void(__thiscall* angleChanged)(gd::EditorUI*, float);
	void __fastcall angleChangedH(gd::EditorUI*, void*, float);

	inline void(__thiscall* onPaste)(gd::EditorUI*, CCObject*);
	void __fastcall onPasteH(gd::EditorUI*, void*, CCObject*);

	inline void(__thiscall* onDuplicate)(gd::EditorUI*, CCObject*);
	void __fastcall onDuplicateH(gd::EditorUI*, void*, CCObject*);

	inline void(__thiscall* onCreateObject)(gd::EditorUI*, int);
	void __fastcall onCreateObjectH(gd::EditorUI*, void*, int);

	inline CCArray* (__thiscall* pasteObjects)(gd::EditorUI*, std::string);
	CCArray* __fastcall pasteObjectsH(gd::EditorUI*, void*, std::string);

	inline void(__thiscall* updateButtons)(gd::EditorUI*);
	void __fastcall updateButtonsH(gd::EditorUI*);

	inline void(__thiscall* scaleObjects)(gd::EditorUI*, CCArray*, CCPoint);
	void __fastcall scaleObjectsH(gd::EditorUI*, void*, CCArray*, CCPoint);

	inline void(__thiscall* onStopPlaytest)(gd::EditorUI*, CCObject*);
	void __fastcall onStopPlaytestH(gd::EditorUI*, void*, CCObject*);

	void updateObjectHitbox(gd::EditorUI*);

	class Callback : public gd::EditorUI {
	public:
		void onCustomMoveObject(CCObject*);
		void onCustomTransformObject(CCObject*);
		void onCircleTool(CCObject*);

		void onNextFreeEditorLayer(CCObject*);
		void onAllEditorLayer(CCObject*);
	};

	void mem_init();
}

namespace EditButtonBar {
	inline bool(__thiscall* init)(gd::EditButtonBar*, CCArray*, int, bool, int, int, CCPoint);
	bool __fastcall initH(gd::EditButtonBar*, void*, CCArray*, int, bool, int, int, CCPoint);

	void mem_init();
}

namespace GJScaleControl {
	inline void(__thiscall* ccTouchMoved)(gd::GJScaleControl*, CCTouch*, CCEvent*);
	void __fastcall ccTouchMovedH(gd::GJScaleControl*, void*, CCTouch*, CCEvent*);
}

namespace GJRotationControl {
	inline void(__thiscall* ccTouchMoved)(gd::GJRotationControl*, CCTouch*, CCEvent*);
	void __fastcall ccTouchMovedH(gd::GJRotationControl*, void*, CCTouch*, CCEvent*);
}