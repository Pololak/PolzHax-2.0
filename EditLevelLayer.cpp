#include "EditLevelLayer.h"
#include "LevelShare.h"
#include "state.h"
#include "nfd.h"

void EditLevelLayer::Callback::onExportLevel(CCObject*) {
	nfdchar_t* path = nullptr;
	if (NFD_SaveDialog("gmd", CCFileUtils::sharedFileUtils()->getWritablePath2().c_str(), &path) == NFD_OKAY) {
		std::ofstream file(path);
		dump_level(this->m_level, file);
		free(path);
		gd::FLAlertLayer::create(nullptr, "Success", "OK", nullptr, "The level has been saved.")->show();
	}
}

void EditLevelLayer::Callback::onResetPercentage(CCObject*) {
	this->m_level->m_normalPercentRand1 = 0;
	this->m_level->m_normalPercentRand2 = 0;
	this->m_level->m_normalPercent = 0;
	this->m_level->m_practicePercent = 0;
	this->m_level->m_isVerified = false;
}

bool __fastcall EditLevelLayer::initH(gd::EditLevelLayer* self, void*, gd::GJGameLevel* level) {
	if (!EditLevelLayer::init(self, level)) return false;

	auto director = CCDirector::sharedDirector();

	auto shareMenu = CCMenu::create();

	auto btn_spr = CCSprite::createWithSpriteFrameName("GJ_downloadBtn_001.png");
	if (!btn_spr->initWithFile("BE_Export_File.png")) {
		btn_spr->initWithSpriteFrameName("GJ_downloadBtn_001.png");
	}
	auto button = gd::CCMenuItemSpriteExtra::create(btn_spr, nullptr, self, menu_selector(EditLevelLayer::Callback::onExportLevel));
	button->setPosition({ -30, +30 });

	shareMenu->setZOrder(1);
	shareMenu->setPosition({ director->getScreenRight(), director->getScreenBottom() });
	shareMenu->addChild(button);
	self->addChild(shareMenu);

	if (setting().onDeveloperMode) {
		auto onResetPercentageSpr = CCSprite::createWithSpriteFrameName("GJ_replayBtn_001.png");
		auto onResetPercentage = gd::CCMenuItemSpriteExtra::create(onResetPercentageSpr, self, menu_selector(EditLevelLayer::Callback::onResetPercentage));
		onResetPercentageSpr->setOpacity(100);
		onResetPercentage->setPositionX(-180);
		self->m_buttonMenu->addChild(onResetPercentage);
	}

	return true;
}

void EditLevelLayer::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x56fa0), EditLevelLayer::initH, reinterpret_cast<void**>(&EditLevelLayer::init));
}