#include "UILayer.hpp"
#include "state.h"

void __fastcall UILayer::keyDownH(gd::UILayer* self, void*, enumKeyCodes key) {
	auto playLayer = gd::GameManager::sharedState()->m_playLayer;

	if (key == setting().g_p1Click) {
		if (playLayer) playLayer->pushButton(1, false);
	}
	else if (key == setting().g_p2Click) {
		if (playLayer) playLayer->pushButton(1, true);
	}
	else {
		return UILayer::keyDown(self, key);
	}
}

void __fastcall UILayer::keyUpH(gd::UILayer* self, void*, enumKeyCodes key) {
	auto playLayer = gd::GameManager::sharedState()->m_playLayer;

	if (key == setting().g_p1Click) {
		if (playLayer) playLayer->releaseButton(1, false);
	}
	else if (key == setting().g_p2Click) {
		if (playLayer) playLayer->releaseButton(1, true);
	}
	else {
		return UILayer::keyUp(self, key);
	}
}

void UILayer::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x1a5340), UILayer::keyDownH, reinterpret_cast<void**>(&UILayer::keyDown));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x1a54d0), UILayer::keyUpH, reinterpret_cast<void**>(&UILayer::keyUp));
}