#include "EndLevelLayer.h"
#include "state.h"

void EndLevelLayer::Callback::onLastCheckpoint(CCObject* sender) {
	if (auto pl = gd::GameManager::sharedState()->getPlayLayer()) {
		reinterpret_cast<gd::EndLevelLayer*>(reinterpret_cast<CCNode*>(sender))->getParent()->getParent()->getParent()->removeFromParent();
		pl->resetLevel();
		CCEGLView::sharedOpenGLView()->showCursor(gd::GameManager::sharedState()->getGameVariable("0024"));
	}
}

void __fastcall EndLevelLayer::customSetupH(gd::EndLevelLayer* self) {
	EndLevelLayer::customSetup(self);

	auto practiceButton = gd::CCMenuItemSpriteExtra::create(
		CCSprite::createWithSpriteFrameName("GJ_practiceBtn_001.png"),
		self,
		menu_selector(EndLevelLayer::Callback::onLastCheckpoint));
	practiceButton->setPositionY(-125.f);
	
	if (setting().onLastCheckpoint && self->m_bottomMenu && gd::GameManager::sharedState()->getPlayLayer()->m_isPracticeMode) {
		if (self->m_bottomMenu->getChildrenCount() == 2) {
			static_cast<gd::CCMenuItemSpriteExtra*>(self->m_bottomMenu->getChildren()->objectAtIndex(0))->setPositionX(-100.f);
			static_cast<gd::CCMenuItemSpriteExtra*>(self->m_bottomMenu->getChildren()->objectAtIndex(1))->setPositionX(100.f);
		}
		else {
			static_cast<gd::CCMenuItemSpriteExtra*>(self->m_bottomMenu->getChildren()->objectAtIndex(0))->setPositionX(-130.f);
			static_cast<gd::CCMenuItemSpriteExtra*>(self->m_bottomMenu->getChildren()->objectAtIndex(1))->setPositionX(130.f);
			static_cast<gd::CCMenuItemSpriteExtra*>(self->m_bottomMenu->getChildren()->objectAtIndex(2))->setPositionX(-45.f);
			practiceButton->setPositionX(45.f);
		}
		self->m_bottomMenu->addChild(practiceButton);
	}
}