#include "EditorPauseLayer.h"
#include "utils.hpp"

gd::EditorPauseLayer* m_editorPauseLayer{ nullptr };

class SaveLevelProtocol : public gd::FLAlertLayerProtocol {
protected:
	void FLAlert_Clicked(gd::FLAlertLayer* layer, bool btn2) {
		if (btn2) {
			m_editorPauseLayer->saveLevel();
		}
	}
};

SaveLevelProtocol saveLevelProtocol;

void EditorPauseLayer::Callback::onSaveLevel(CCObject*) {
	gd::FLAlertLayer::create(&saveLevelProtocol, "Save", "NO", "YES", 300.f, "<cy>Save</c> the level?")->show();
}

void EditorPauseLayer::Callback::onPasteString(CCObject*) {
	if (gd::GameManager::sharedState()->getLevelEditorLayer()) {
		auto string = clipboard::read();
		gd::GameManager::sharedState()->getLevelEditorLayer()->m_editorUI->pasteObjects(string);
		gd::GameManager::sharedState()->getLevelEditorLayer()->m_editorUI->updateButtons();
	}
}

void EditorPauseLayer::Callback::onSelectAll(CCObject*) {
	auto levelEditor = gd::GameManager::sharedState()->getLevelEditorLayer();
	auto editorUI = levelEditor->m_editorUI;

	auto objs = CCArray::create();
	for (int i = 0; i < levelEditor->m_levelSections->count(); i++)
		objs->addObjectsFromArray(reinterpret_cast<CCArray*>(levelEditor->m_levelSections->objectAtIndex(i)));

	auto objs2 = CCArray::create();
	for (int i = 0; i < objs2->count(); i++)
		if (reinterpret_cast<gd::GameObject*>(objs->objectAtIndex(i))->m_editorLayer == levelEditor->m_groupIDFilter || levelEditor->m_groupIDFilter == -1)
			objs2->addObject(objs->objectAtIndex(i));

	editorUI->selectObjects(objs2);
	editorUI->updateButtons();
	editorUI->deactivateRotationControl();
	editorUI->deactivateScaleControl();
	editorUI->updateObjectInfoLabel();
}

void __fastcall EditorPauseLayer::customSetupH(gd::EditorPauseLayer* self) {
	EditorPauseLayer::customSetup(self);
	m_editorPauseLayer = self;

	auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();

	auto mainMenu = static_cast<CCMenu*>(self->getChildren()->objectAtIndex(0));
	auto actionsMenu = static_cast<CCMenu*>(self->m_audioOnBtn->getParent());

	auto onResume = static_cast<gd::CCMenuItemSpriteExtra*>(mainMenu->getChildren()->objectAtIndex(0));
	onResume->setPositionY(84.f);
	auto onSaveAndPlay = static_cast<gd::CCMenuItemSpriteExtra*>(mainMenu->getChildren()->objectAtIndex(1));
	onSaveAndPlay->setPositionY(42.f);
	auto onSaveAndExit = static_cast<gd::CCMenuItemSpriteExtra*>(mainMenu->getChildren()->objectAtIndex(2));
	onSaveAndExit->setPositionY(0.f);
	auto onExitNoSave = static_cast<gd::CCMenuItemSpriteExtra*>(mainMenu->getChildren()->objectAtIndex(3));
	onExitNoSave->setPositionY(-84.f);

	auto onSaveSpr = gd::ButtonSprite::create("Save", 0xb4, true, "goldFont.fnt", "GJ_button_01.png", 28.f, .8f);
	auto onSave = gd::CCMenuItemSpriteExtra::create(onSaveSpr, nullptr, self, menu_selector(EditorPauseLayer::Callback::onSaveLevel));
	onSave->setPositionY(-42.f);

	mainMenu->addChild(onSave);

	auto onPasteStringSpr = gd::ButtonSprite::create("Paste\nString", 0x28, true, "bigFont.fnt", "GJ_button_04.png", 30.f, .6f);
	auto onPasteString = gd::CCMenuItemSpriteExtra::create(onPasteStringSpr, nullptr, self, menu_selector(EditorPauseLayer::Callback::onPasteString));
	onPasteString->setPosition(actionsMenu->convertToNodeSpace({ winSize.width - 45.f, winSize.height - 30.f }));

	actionsMenu->addChild(onPasteString);

	auto onSettingsSpr = CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png");
	onSettingsSpr->setScale(.65f);
	auto onSettings = gd::CCMenuItemSpriteExtra::create(onSettingsSpr, nullptr, self, menu_selector(gd::MenuLayer::onOptions));
	onSettings->setPosition(actionsMenu->convertToNodeSpace({ winSize.width - 32.f, winSize.height - 66.f }));

	actionsMenu->addChild(onSettings);
}

void __fastcall EditorPauseLayer::dtorH(gd::EditorPauseLayer* self) {
	m_editorPauseLayer = nullptr;
	EditorPauseLayer::dtor(self);
}

void __fastcall EditorPauseLayer::keyDownH(gd::EditorPauseLayer* self, void*, enumKeyCodes key) {
	if (key == KEY_Escape) reinterpret_cast<gd::EditorPauseLayer*>(reinterpret_cast<uintptr_t>(self) - 0xf4)->onResume(nullptr);
	else EditorPauseLayer::keyDown(self, key);
}

void EditorPauseLayer::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x5aa90), EditorPauseLayer::customSetupH, reinterpret_cast<void**>(&EditorPauseLayer::customSetup));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x5a5f0), EditorPauseLayer::dtorH, reinterpret_cast<void**>(&EditorPauseLayer::dtor));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x5ca20), EditorPauseLayer::keyDownH, reinterpret_cast<void**>(&EditorPauseLayer::keyDown));
}