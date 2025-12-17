#include "LevelSettingsLayer.hpp"

bool __fastcall LevelSettingsLayer::initH(gd::LevelSettingsLayer* self, void*, gd::LevelSettingsObject* settingsObject) {
	bool res = LevelSettingsLayer::init(self, settingsObject);

	auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();

	//auto flipGravityLabel = CCLabelBMFont::create("Start Flipped", "goldFont.fnt");
	//flipGravityLabel->setScale(0.5f);
	//flipGravityLabel->setAnchorPoint({ 0.f, 0.5f });
	//flipGravityLabel->setPosition({ (winSize.width / 2.f) - 120.f, (winSize.height / 2.f) - 135.f });
	//self->m_pLayer->addChild(flipGravityLabel);

	//auto toggleOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
	//auto toggleOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

	//auto flipGravityToggler = gd::CCMenuItemToggler::create(toggleOff, toggleOn, self, menu_selector(gd::LevelSettingsLayer::onGravityFlipped));
	//flipGravityToggler->toggle(self->m_settingsObject->m_isFlipped);
	//flipGravityToggler->setScale(0.7f);
	//flipGravityToggler->setPosition(self->m_pButtonMenu->convertToNodeSpace({ (winSize.width / 2.f) - 135.f, (winSize.height / 2.f) - 135.f }));
	//self->m_pButtonMenu->addChild(flipGravityToggler);

	return res;
}

void LevelSettingsLayer::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x102270), LevelSettingsLayer::initH, reinterpret_cast<void**>(&LevelSettingsLayer::init));
}