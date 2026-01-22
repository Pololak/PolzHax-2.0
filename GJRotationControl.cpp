#include "GJRotationControl.hpp"

bool __fastcall GJRotationControl::initH(gd::GJRotationControl* self) {
	if (!GJRotationControl::init(self)) return false;

	auto angleLabel = CCLabelBMFont::create("", "bigFont.fnt");
	angleLabel->setScale(.65f);
	angleLabel->setPositionY(40.f);
	self->addChild(angleLabel, 0, 23);

	return true;
}

void __fastcall GJRotationControl::ccTouchMovedH(gd::GJRotationControl* _self, void*, CCTouch* touch, CCEvent* event) {
	GJRotationControl::ccTouchMoved(_self, touch, event);

	gd::GameManager::sharedState()->getLevelEditorLayer()->m_editorUI->updateObjectInfoLabel();

	gd::GJRotationControl* self = reinterpret_cast<gd::GJRotationControl*>(reinterpret_cast<uintptr_t>(_self) - 0xe8);
	auto angleLabel = static_cast<CCLabelBMFont*>(self->getChildByTag(23));
	if (angleLabel) {
		angleLabel->setString(CCString::createWithFormat("%.0f", self->m_currentRotation)->getCString());
	}
}

void GJRotationControl::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x73d10), GJRotationControl::initH, reinterpret_cast<void**>(&GJRotationControl::init));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x740e0), GJRotationControl::ccTouchMovedH, reinterpret_cast<void**>(&GJRotationControl::ccTouchMoved));
}