﻿#include "pch.h"

#include <DbgHelp.h>
#pragma comment(lib, "dbghelp.lib")
#include "CrashLogger.h"
#include "menu.h"
#include "state.h"
#include "utils.hpp"
#include "patching.h"
#include "imgui-hook.hpp"

#include "PlayLayer.h"
#include "PauseLayer.h"
#include "EditorUI.h"
#include "ColorSelectPopup.h"

#include "LevelShare.h"
#include "nfd.h"

void(__thiscall* fpMainLoop)(cocos2d::CCDirector* self);

void __fastcall hkMainLoop(cocos2d::CCDirector* self)
{
	ImGuiHook::poll(self->getOpenGLView());
	fpMainLoop(self);
}

bool(__thiscall* GameManager_isIconUnlocked)(gd::GameManager*, int, int);
bool __fastcall GameManager_isIconUnlockedH(gd::GameManager* self, void*, int id, int type) {
	if (setting().onIcons) return true;
	else return GameManager_isIconUnlocked(self, id, type);
}

bool(__thiscall* GameManager_isColorUnlocked)(gd::GameManager*, int, int);
bool __fastcall GameManager_isColorUnlockedH(gd::GameManager* self, void*, int id, unsigned int type) {
	if (setting().onIcons) return true;
	else return GameManager_isColorUnlocked(self, id, type);
}

void(__thiscall* CCParticleSystemQuad_draw)(CCParticleSystemQuad*);
void __fastcall CCParticleSystemQuad_drawH(CCParticleSystemQuad* self) {
	if (!setting().onNoParticles) return CCParticleSystemQuad_draw(self);
}

void(__thiscall* PlayerObject_updatePlayerFrame)(gd::PlayerObject*, int);
void __fastcall PlayerObject_updatePlayerFrameH(gd::PlayerObject* self, void* edx, int frameID) {
	if (setting().onNoMiniIcon) {
		return PlayerObject_updatePlayerFrame(self, from<int>(gd::GameManager::sharedState(), 0x1c8));
	}
	PlayerObject_updatePlayerFrame(self, frameID);
}

void(__thiscall* PlayerObject_updatePlayerRollFrame)(gd::PlayerObject*, int);
void __fastcall PlayerObject_updatePlayerRollFrameH(gd::PlayerObject* self, void* edx, int frameID) {
	if (setting().onNoMiniIcon) {
		return PlayerObject_updatePlayerRollFrame(self, from<int>(gd::GameManager::sharedState(), 0x1e0));
	}
	PlayerObject_updatePlayerRollFrame(self, frameID);
}

void(__thiscall* PlayerObject_runBallRotation2)(gd::PlayerObject*);
void __fastcall PlayerObject_runBallRotation2H(gd::PlayerObject* self) {
	if (setting().onBallRotatingBugFix) {
		self->stopActionByTag(1);
	}
	PlayerObject_runBallRotation2(self);
}

bool(__thiscall* CCKeyboardDispatcher_dispatchKeyboardMSG)(cocos2d::CCKeyboardDispatcher* self, int key, bool down);
void __fastcall CCKeyboardDispatcher_dispatchKeyboardMSGH(CCKeyboardDispatcher* self, void* edx, int key, bool down) {
	auto pl = gd::GameManager::sharedState()->getPlayLayer();
	if (down) {
		if ((key == 'R') && setting().onRetryKeybind) {
			if (pl) {
				if (!pl->m_hasCompletedLevel) {
					pl->resetLevel();
					if (layers().PauseLayerObject)
					{
						layers().PauseLayerObject->removeMeAndCleanup();
						layers().PauseLayerObject = nullptr;
					}
					pl->resume();
					return;
				}
			}
		}
		//if (pl) {
		//	if (setting().onStartPosSwitcher) {
		//		switch (key)
		//		{
		//		case KEY_Q:
		//		case KEY_Left:
		//			PlayLayer::onPrevStartPos();
		//			break;
		//		case KEY_E:
		//		case KEY_Right:
		//			PlayLayer::onNextStartPos();
		//			break;
		//		}
		//	}
		//}
	}
	CCKeyboardDispatcher_dispatchKeyboardMSG(self, key, down);
}

void(__thiscall* CCTransitionScene_initWithDuration)(CCTransitionScene*, float, CCScene*);
void __fastcall CCTransitionScene_initWithDurationH(CCTransitionScene* self, void* edx, float duration, CCScene* scene) {
	if (setting().onNoTransition) return CCTransitionScene_initWithDuration(self, 0.f, scene);
	else CCTransitionScene_initWithDuration(self, duration, scene);
}

void(__thiscall* RingObject_spawnCircle)(gd::GameObject*);
void __fastcall RingObject_spawnCircleH(gd::GameObject* self) {
	if (!setting().onNoOrbRing) return RingObject_spawnCircle(self);
}

namespace gd {
	enum class SearchType {
		Search = 0,
		Downloaded = 1,
		MostLiked = 2,
		Trending = 3,
		Recent = 4,
		UsersLevels = 5,
		Featured = 6,
		Magic = 7,
		Sends = 8,
		MapPack = 9,
		MapPackOnClick = 10,
		Awarded = 11,
		Followed = 12,
		Friends = 13,
		Users = 14,
		LikedGDW = 15,
		HallOfFame = 16,
		FeaturedGDW = 17,
		Similar = 18,
		MyLevels = 98,
		SavedLevels = 99,
		FavouriteLevels = 100
	};

	class EditLevelLayer : public CCLayer {
	public:
		GJGameLevel* level() {
			return from<GJGameLevel*>(this, 0x12c);
		}
		static auto scene(GJGameLevel* level) {
			return reinterpret_cast<cocos2d::CCScene * (__fastcall*)(GJGameLevel*)>(base + 0x56f00)(level);
		}
	};

	class LevelBrowserLayer : public CCLayer {
	public:

	};

	class GJSearchObject : public CCNode {
	public:
		SearchType m_type;
	};
}

class ImportExportCB {
public:
	void onExportLevelELL(CCObject* obj) {
		auto* const level = reinterpret_cast<gd::EditLevelLayer*>(reinterpret_cast<CCNode*>(obj)->getParent()->getParent())->level();
		nfdchar_t* path = nullptr;
		if (NFD_SaveDialog("gmd", nullptr, &path) == NFD_OKAY) {
			std::ofstream file(path);
			dump_level(level, file);
			free(path);
			gd::FLAlertLayer::create(nullptr, "Success", "OK", nullptr, "The level has been saved.")->show();
		}
	}
	void onImportLevelLBL(CCObject* obj) {
		nfdchar_t* path = nullptr;
		if (NFD_OpenDialog("gmd", nullptr, &path) == NFD_OKAY) {
			std::ifstream file(path);
			auto* const level = import_level(file);
			free(path);
			if (!level) {
				gd::FLAlertLayer::create(nullptr, "Error", "OK", nullptr, "Failed to import.")->show();
				return;
			}
			auto scene = gd::EditLevelLayer::scene(level);
			CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(.5f, scene));
		}
	}
};

bool(__thiscall* EditLevelLayer_init)(gd::EditLevelLayer*, gd::GJGameLevel*);
bool __fastcall EditLevelLayer_initH(gd::EditLevelLayer* self, void*, gd::GJGameLevel* level) {
	if (!EditLevelLayer_init(self, level)) return false;

	auto director = CCDirector::sharedDirector();

	auto shareMenu = CCMenu::create();

	auto btn_spr = CCSprite::createWithSpriteFrameName("GJ_downloadBtn_001.png");
	if (!btn_spr->initWithFile("BE_Export_File.png")) {
		btn_spr->initWithSpriteFrameName("GJ_downloadBtn_001.png");
	}
	auto button = gd::CCMenuItemSpriteExtra::create(btn_spr, nullptr, self, menu_selector(ImportExportCB::onExportLevelELL));
	button->setPosition({ -30, +30 });

	shareMenu->setZOrder(1);
	shareMenu->setPosition({ director->getScreenRight(), director->getScreenBottom() });
	shareMenu->addChild(button);
	self->addChild(shareMenu);

	return true;
}

bool(__thiscall* LevelBrowserLayer_init)(gd::LevelBrowserLayer*, gd::GJSearchObject*);
bool __fastcall LevelBrowserLayer_initH(gd::LevelBrowserLayer* self, void*, gd::GJSearchObject* obj) {
	if (!LevelBrowserLayer_init(self, obj)) return false;

	if (obj->m_type == gd::SearchType::MyLevels) {
		auto menu = CCMenu::create();
		menu->setPosition(CCDirector::sharedDirector()->getWinSize().width - 30.f, 90);
		self->addChild(menu);

		auto btn_spr = CCSprite::createWithSpriteFrameName("GJ_downloadBtn_001.png");
		if (!btn_spr->initWithFile("BE_Import_File.png")) {
			btn_spr->initWithSpriteFrameName("GJ_downloadBtn_001.png");
		}

		auto button = gd::CCMenuItemSpriteExtra::create(btn_spr, nullptr, self, menu_selector(ImportExportCB::onImportLevelLBL));

		menu->setZOrder(1);
		menu->addChild(button);
	}

	return true;
}

void(__thiscall* CCTextInputNode_updateLabel)(gd::CCTextInputNode*, std::string);
void __fastcall CCTextInputNode_updateLabelH(gd::CCTextInputNode* self, void*, std::string string) {
	if (setting().onTextLength)
		self->m_maxLabelLength = 99999;

	CCTextInputNode_updateLabel(self, string);

	if (setting().onCharFilter) {
		self->m_filter = "abcdefghijklmnopqrstuvwxyz"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"0123456789!@#$%^&*()-=_+"
			"`~[]{}/?.>,<\\|;:'\""
			" ";
		CCTextInputNode_updateLabel(self, std::move(string));
	}
}

void(__thiscall* AppDelegate_trySaveGame)(gd::AppDelegate*);
void __fastcall AppDelegate_trySaveGameH(gd::AppDelegate* self) {
	if (setting().onAutoSave)
	{
		setting().saveState();
	}
	AppDelegate_trySaveGame(self);
	std::cout << "Saved..." << std::endl;
}

DWORD WINAPI my_thread(void* hModule) {
	sequence_patch((uint32_t)gd::base + 0x558db, { 0xb8, 0x01, 0x00, 0x00, 0x00, 0x90, 0x90 });
	sequence_patch((uint32_t)gd::base + 0x38a85, { 0x6a, 0x00 });

	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

	if (MH_Initialize() != MH_OK) {
		FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
	}

	auto cocos = GetModuleHandleA("libcocos2d.dll");
	auto cocos_ext = GetModuleHandleA("libExtensions.dll");

	PlayLayer::mem_init();
	PauseLayer::mem_init();
	EditorPauseLayer::mem_init();
	EditorUI::mem_init();
	ColorSelectPopup::mem_init();
	SetupPulsePopup::mem_init();

	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x9afc0), GameManager_isIconUnlockedH, reinterpret_cast<void**>(&GameManager_isIconUnlocked));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x9b2a0), GameManager_isColorUnlockedH, reinterpret_cast<void**>(&GameManager_isColorUnlocked));

	MH_CreateHook(reinterpret_cast<void*>(GetProcAddress(cocos, "?draw@CCParticleSystemQuad@cocos2d@@UAEXXZ")), CCParticleSystemQuad_drawH, reinterpret_cast<void**>(&CCParticleSystemQuad_draw));

	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x167400), PlayerObject_updatePlayerFrameH, reinterpret_cast<void**>(&PlayerObject_updatePlayerFrame));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x167840), PlayerObject_updatePlayerRollFrameH, reinterpret_cast<void**>(&PlayerObject_updatePlayerRollFrame));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x160b20), PlayerObject_runBallRotation2H, reinterpret_cast<void**>(&PlayerObject_runBallRotation2));

	MH_CreateHook(
		reinterpret_cast<void*>(GetProcAddress(cocos, "?dispatchKeyboardMSG@CCKeyboardDispatcher@cocos2d@@QAE_NW4enumKeyCodes@2@_N@Z")),
		reinterpret_cast<void**>(&CCKeyboardDispatcher_dispatchKeyboardMSGH),
		reinterpret_cast<void**>(&CCKeyboardDispatcher_dispatchKeyboardMSG));

	MH_CreateHook(reinterpret_cast<void*>(GetProcAddress(cocos, "?initWithDuration@CCTransitionScene@cocos2d@@UAE_NMPAVCCScene@2@@Z")), CCTransitionScene_initWithDurationH, reinterpret_cast<void**>(&CCTransitionScene_initWithDuration));
	//MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x156760), OptionsLayer_onSecretVaultH, reinterpret_cast<void**>(&OptionsLayer_onSecretVault));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x19d270), RingObject_spawnCircleH, reinterpret_cast<void**>(&RingObject_spawnCircle));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x56fa0), EditLevelLayer_initH, reinterpret_cast<void**>(&EditLevelLayer_init));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0xea4c0), LevelBrowserLayer_initH, reinterpret_cast<void**>(&LevelBrowserLayer_init));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x1dac0), CCTextInputNode_updateLabelH, reinterpret_cast<void**>(&CCTextInputNode_updateLabel));

	MH_CreateHook(
		reinterpret_cast<void*>(gd::base + 0x392a0),
		reinterpret_cast<void**>(&AppDelegate_trySaveGameH),
		reinterpret_cast<void**>(&AppDelegate_trySaveGame));

	setup_imgui_menu();

	MH_EnableHook(MH_ALL_HOOKS);

	MH_CreateHook(reinterpret_cast<LPVOID>(reinterpret_cast<uintptr_t>(cocos) + 0xfde30), hkMainLoop, reinterpret_cast<LPVOID*>(&fpMainLoop));

	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0x1000, my_thread, hModule, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	setupExceptionHandler();
	return TRUE;
}

