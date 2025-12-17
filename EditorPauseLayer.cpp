#include "EditorPauseLayer.h"
#include "utils.hpp"
#include "RotateSaws.h"
#include "state.h"
#include "patching.h"

void EditorPauseLayer::Callback::onSaveLevel(CCObject*) {
	auto alert = gd::FLAlertLayer::create(this, "Save", "NO", "YES", 300.f, "<cy>Save</c> the level?");
	alert->setTag(3);
	alert->show();
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
	for (auto section : CCArrayExt<CCArray*>(levelEditor->m_levelSections)) {
		if (section) {
			for (auto obj : CCArrayExt<gd::GameObject*>(section)) {
				if (obj && obj->m_editorLayer == levelEditor->m_groupIDFilter || (obj->m_editorLayer2 == levelEditor->m_groupIDFilter && obj->m_editorLayer2 != 0) || levelEditor->m_groupIDFilter == -1)
					objs->addObject(obj);
			}
		}
	}

	editorUI->selectObjects(objs);
	editorUI->updateButtons();
	editorUI->deactivateRotationControl();
	editorUI->deactivateScaleControl();
	editorUI->updateObjectInfoLabel();
}

void EditorPauseLayer::selectAllWithDirection(gd::EditorPauseLayer* self, bool rightDir) {
	auto editorUI = self->m_editorLayer->m_editorUI;
	if (editorUI) {
		auto cameraPos = self->m_editorLayer->m_objectLayer->getPosition();
		auto cameraScale = self->m_editorLayer->m_objectLayer->getScale();
		int centerX = -(cameraPos.x) / cameraScale + CCDirector::sharedDirector()->getWinSize().width / 2;

		CCArray* arr = CCArray::create();
		for (auto section : CCArrayExt<CCArray*>(self->m_editorLayer->m_levelSections)) {
			if (section) {
				for (auto obj : CCArrayExt<gd::GameObject*>(section))
					if (obj && obj->m_editorLayer == self->m_editorLayer->m_groupIDFilter || (obj->m_editorLayer2 == self->m_editorLayer->m_groupIDFilter && obj->m_editorLayer2 != 0) || self->m_editorLayer->m_groupIDFilter == -1) {
						if ((rightDir && obj->getPositionX() >= centerX) || (!rightDir && obj->getPositionX() <= centerX)) {
							arr->addObject(obj);
							self->m_editorLayer->m_editorUI->selectObjects(arr);
						}
					}
			}
		}

		editorUI->updateButtons();
		editorUI->deactivateRotationControl();
		editorUI->deactivateScaleControl();
		editorUI->updateObjectInfoLabel();
	}
}

void EditorPauseLayer::Callback::onSelectAllLeft(CCObject*) {
	selectAllWithDirection(this, false);
}

void EditorPauseLayer::Callback::onSelectAllRight(CCObject*) {
	selectAllWithDirection(this, true);
}

void __fastcall EditorPauseLayer::customSetupH(gd::EditorPauseLayer* self) {
	EditorPauseLayer::customSetup(self);

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

	auto selectAllRightSpr = gd::ButtonSprite::create("Select\nAll Right", 0x1e, true, "bigFont.fnt", "GJ_button_04.png", 30.f, 1.f);
	auto selectAllRight = gd::CCMenuItemSpriteExtra::create(selectAllRightSpr, self, menu_selector(EditorPauseLayer::Callback::onSelectAllRight));
	selectAllRight->setPosition(actionsMenu->convertToNodeSpace({ winSize.width - 115.f, director->getScreenBottom() + 30.f }));
	actionsMenu->addChild(selectAllRight);

	auto selectAllLeftSpr = gd::ButtonSprite::create("Select\nAll Left", 0x1e, true, "bigFont.fnt", "GJ_button_04.png", 30.f, 1.f);
	auto selectAllLeft = gd::CCMenuItemSpriteExtra::create(selectAllLeftSpr, self, menu_selector(EditorPauseLayer::Callback::onSelectAllLeft));
	selectAllLeft->setPosition(actionsMenu->convertToNodeSpace({ winSize.width - 115.f, director->getScreenBottom() + 65.f }));
	actionsMenu->addChild(selectAllLeft);

	auto onSelectAllSpr = gd::ButtonSprite::create("Select\nAll", 0x1e, true, "bigFont.fnt", "GJ_button_04.png", 30.f, 1.f);
	auto onSelectAll = gd::CCMenuItemSpriteExtra::create(onSelectAllSpr, self, menu_selector(EditorPauseLayer::Callback::onSelectAll));
	onSelectAll->setPosition(actionsMenu->convertToNodeSpace({ winSize.width - 115.f, director->getScreenBottom() + 100.f }));
	actionsMenu->addChild(onSelectAll);

	auto btn = static_cast<gd::CCMenuItemSpriteExtra*>(static_cast<CCMenu*>(gd::GameManager::sharedState()->getLevelEditorLayer()->m_editorUI->m_copyBtn->getParent())->getChildByTag(45001));
	if (btn) {
		if (gd::GameManager::sharedState()->getLevelEditorLayer()->m_editorUI->m_editorLayer->m_groupIDFilter == -1) {
			btn->setVisible(false);
			btn->setEnabled(false);
		}
	}

	gd::GameManager::sharedState()->m_editorLayer->m_editorUI->m_currentGroupLabel->setVisible(false);
}

void __fastcall EditorPauseLayer::keyDownH(gd::EditorPauseLayer* self, void*, enumKeyCodes key) {
	if (key == KEY_Escape) reinterpret_cast<gd::EditorPauseLayer*>(reinterpret_cast<uintptr_t>(self) - 0xf4)->onResume(nullptr);
	else EditorPauseLayer::keyDown(self, key);
}

void __fastcall EditorPauseLayer::saveLevelH(gd::EditorPauseLayer* self) {
	if (setting().onRotateSaws) RotateSaws::stopRotations(self->m_editorLayer);
	if (self->m_editorLayer->m_playerState != 0)
		self->m_editorLayer->m_editorUI->onStopPlaytest(nullptr);

	EditorPauseLayer::saveLevel(self);

	if (setting().onRotateSaws) RotateSaws::beginRotations(self->m_editorLayer);
}

void EditorPauseLayer::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x5aa90), EditorPauseLayer::customSetupH, reinterpret_cast<void**>(&EditorPauseLayer::customSetup));
	//MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x5a5f0), EditorPauseLayer::dtorH, reinterpret_cast<void**>(&EditorPauseLayer::dtor));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x5ca20), EditorPauseLayer::keyDownH, reinterpret_cast<void**>(&EditorPauseLayer::keyDown));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x5c290), EditorPauseLayer::saveLevelH, reinterpret_cast<void**>(&EditorPauseLayer::saveLevel));
}