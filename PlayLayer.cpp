#include "PlayLayer.h"

#include "state.h"
#include "Checkpoint.h"
#include <vector>
#include "utils.hpp"

#include "Hitboxes.h"

#include "imgui.h"

std::vector<CheckPoint> checkpoints;

std::vector<gd::StartPosObject*> m_startPositions;
std::vector<gd::GameObject*> m_dualPortals, m_gamemodePortals, m_miniPortals, m_speedChanges, m_mirrorPortals;

int currentStartPos = 0;
std::vector<gd::StartPosObject*> startPosObjects;

bool inPractice;
bool inTestmode;
int smoothOut;

bool m_deafenPressed = false;
int m_startPercent = 0;

std::vector<gd::EffectGameObject*> m_coinsToPickup;

static gd::GameObject* getClosestObject(std::vector<gd::GameObject*>& vec, gd::StartPosObject* startPos) {
	gd::GameObject* closest = nullptr;

	std::ranges::sort(vec, [](gd::GameObject* a, gd::GameObject* b) {
		return a->getPositionX() < b->getPositionX();
		});

	for (auto obj : vec) {
		if (obj->getPositionX() - 10 > startPos->getPositionX())
			break;
		if (obj->getPositionX() - 10 < startPos->getPositionX())
			closest = obj;
	}

	return closest;
}

void setupStartPos(gd::StartPosObject* startPos) { // Eclipse Menu
	gd::LevelSettingsObject* startPosSettings = startPos->m_levelSettings;
	gd::LevelSettingsObject* levelSettings = gd::GameManager::sharedState()->getPlayLayer()->m_levelSettings;

	startPosSettings->m_startDual = levelSettings->m_startDual;
	startPosSettings->m_startMode = levelSettings->m_startMode;
	startPosSettings->m_startMini = levelSettings->m_startMini;
	startPosSettings->m_startSpeed = levelSettings->m_startSpeed;

	gd::GameObject* obj = getClosestObject(m_dualPortals, startPos);
	if (obj)
		startPosSettings->m_startDual = obj->m_objectID == 286;

	obj = getClosestObject(m_gamemodePortals, startPos);

	if (obj) {
		switch (obj->m_objectID) {
		case 12: startPosSettings->m_startMode = 0;
			break;
		case 13: startPosSettings->m_startMode = 1;
			break;
		case 47: startPosSettings->m_startMode = 2;
			break;
		case 111: startPosSettings->m_startMode = 3;
			break;
		case 660: startPosSettings->m_startMode = 4;
			break;
		case 745: startPosSettings->m_startMode = 5;
			break;
		default: break;
		}
	}

	obj = getClosestObject(m_miniPortals, startPos);

	if (obj)
		startPosSettings->m_startMini = obj->m_objectID == 101;

	obj = getClosestObject(m_speedChanges, startPos);
	if (obj) {
		switch (obj->m_objectID) {
		case 200: startPosSettings->m_startSpeed = 1;
			break;
		case 201: startPosSettings->m_startSpeed = 0;
			break;
		case 202: startPosSettings->m_startSpeed = 2;
			break;
		case 203: startPosSettings->m_startSpeed = 3;
			break;
		default: break;
		}
	}
}

void pickStartPos(gd::PlayLayer* playLayer, int32_t index) { // Eclipse Menu
	if (startPosObjects.empty()) return;

	auto count = static_cast<int32_t>(startPosObjects.size());
	if (index >= count) index = -1;
	else if (index < -1) index = count - 1;

	currentStartPos = index;
	
	auto* startPos = index >= 0 ? startPosObjects[index] : nullptr;
	if (startPos != playLayer->m_startPosObject) {
		if (startPos) {
			startPos->retain();
		}
		if (playLayer->m_startPosObject) {
			playLayer->m_startPosObject->release();
		}
		playLayer->m_startPosObject = startPos;
	}
	if (currentStartPos >= 0) { // Taswert's thing
		playLayer->m_playerStartPosition = playLayer->m_startPosObject->getOrientedBox()->m_center;
	}
	else {
		playLayer->m_playerStartPosition = ccp(0, 105);
	}
	playLayer->m_isTestMode = index >= 0;

	playLayer->resetLevel();
	playLayer->startMusic();

	auto spSwitcherLabel = static_cast<CCLabelBMFont*>(static_cast<CCMenu*>(playLayer->m_uiLayer->getChildByTag(177))->getChildByTag(178));
	if (spSwitcherLabel) {
		//gd::StartPosObject* prevSP = nullptr;
		//gd::StartPosObject* nextSP = nullptr;

		//if (currentStartPos == -1) {
		//	prevSP = startPosObjects.back();
		//}
		//else if (currentStartPos + 1 == startPosObjects.size()) {
		//	nextSP = startPosObjects.front();
		//}
		//else {
		//	prevSP = index >= 0 ? startPosObjects[currentStartPos - 1] : nullptr;
		//	nextSP = index >= 0 ? startPosObjects[currentStartPos + 1] : nullptr;
		//}
		//if (nextSP && prevSP) {
		//	std::cout << "Previous StartPosObject: " << prevSP << std::endl;
		//	std::cout << prevSP->getPositionX() / playLayer->m_levelLength * 100.f << "%" << std::endl;
		//	std::cout << "Next StartPosObject: " << nextSP << std::endl;
		//	std::cout << nextSP->getPositionX() / playLayer->m_levelLength * 100.f << "%" << std::endl;
		//}

		spSwitcherLabel->setString(CCString::createWithFormat("%d/%d", currentStartPos + 1, startPosObjects.size())->getCString());
		spSwitcherLabel->setOpacity(255);
		spSwitcherLabel->stopAllActions();
		spSwitcherLabel->runAction(CCSequence::create(CCDelayTime::create(1.f), CCFadeOut::create(0.5f), nullptr));
	}
}

void PlayLayer::onNextStartPos() {
	pickStartPos(gd::GameManager::sharedState()->getPlayLayer(), currentStartPos + 1);
}

void PlayLayer::onPrevStartPos() {
	pickStartPos(gd::GameManager::sharedState()->getPlayLayer(), currentStartPos - 1);
}

void PlayLayer::updatePlayerColors(gd::PlayLayer* self) {
	auto gm = gd::GameManager::sharedState();

	if (!self->m_player2) return;

	self->m_player2->setColor(setting().onSameDualColor ? gm->colorForIdx(gm->m_playerColor) : gm->colorForIdx(gm->m_playerColor2));
	self->m_player2->setSecondColor(setting().onSameDualColor ? gm->colorForIdx(gm->m_playerColor2) : gm->colorForIdx(gm->m_playerColor));

	self->m_player2->updateGlowColor();
}

void PlayLayer::updateCheatIndicator(gd::PlayLayer* self) {
	auto cheatIndicator = static_cast<CCLabelBMFont*>(self->m_uiLayer->getChildByTag(4900));
	if (cheatIndicator) {
		auto fontSprite = reinterpret_cast<CCSprite*>(cheatIndicator->getChildByTag(0));
		if (fontSprite) {
			if ((setting().cheatsCount != 0) && !setting().isSafeMode) fontSprite->setColor({ 255, 0, 0 });
			else if ((setting().cheatsCount != 0) && setting().isSafeMode) fontSprite->setColor({ 255, 127, 0 });
			else if ((setting().cheatsCount == 0) && (setting().isSafeMode || setting().onSafeMode)) fontSprite->setColor({ 255, 255, 0 });
			else fontSprite->setColor({ 0, 255, 0 });
		}
	}
}

void PlayLayer::updateShowHitboxes(gd::PlayLayer* self) {
	auto playerDrawNode = static_cast<CCDrawNode*>(self->m_objectLayer->getChildByTag(124));
	playerDrawNode->clear();
	auto objectDrawNode = static_cast<CCDrawNode*>(self->m_objectLayer->getChildByTag(125));
	objectDrawNode->clear();

	if ((self->m_player->m_isDead && setting().onHitboxesOnDeath) || setting().onHitboxes) {
		if (setting().onEnablePlayerHitboxes) {
			if (self->m_player) Hitboxes::drawPlayerHitbox(self->m_player, playerDrawNode);
			if (self->m_player2) Hitboxes::drawPlayerHitbox(self->m_player2, playerDrawNode);
		}

		for (int i = self->m_firstVisibleSection + 1; i <= self->m_lastVisibleSection - 1; i++) {
			if (i < 0) continue;
			if (i >= self->m_levelSections->count()) break;

			auto objectAtIndex = self->m_levelSections->objectAtIndex(i);
			auto objArr = reinterpret_cast<CCArray*>(objectAtIndex);

			for (int j = 0; j < objArr->count(); j++) {
				auto obj = reinterpret_cast<gd::GameObject*>(objArr->objectAtIndex(j));
				if (setting().onEnableSolidHitboxes)
					Hitboxes::drawSolidsObjectHitbox(obj, objectDrawNode);
				if (setting().onEnableHazardHitboxes)
					Hitboxes::drawHazardsObjectHitbox(obj, objectDrawNode);
				if (setting().onEnableSpecialHitboxes)
					Hitboxes::drawSpecialsObjectHitbox(obj, objectDrawNode);
			}
		}
	}
}

bool __fastcall PlayLayer::initH(gd::PlayLayer* self, void*, gd::GJGameLevel* level) {
	startPosObjects.clear();
	inPractice = false;
	inTestmode = self->m_isTestMode;
	smoothOut = 0;
	checkpoints.clear();
	m_dualPortals.clear();
	m_gamemodePortals.clear();
	m_miniPortals.clear();
	m_miniPortals.clear();
	m_speedChanges.clear();
	m_mirrorPortals.clear();
	m_startPositions.clear();
	m_coinsToPickup.clear();

	if (!PlayLayer::init(self, level)) return false;

	auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();
	
	std::cout << "GameManager: " << gd::GameManager::sharedState() << std::endl;
	std::cout << "FMODAudioEngine: " << gd::FMODAudioEngine::sharedEngine() << std::endl;

	// Hide Attempts
	self->m_attemptLabel->setVisible(!setting().onHideAttempts);

	// Hide Pause Button
	if (gd::GameManager::sharedState()->getGameVariable("0024")) {
		from<gd::CCMenuItemSpriteExtra*>(self->m_uiLayer, 0x1a0)->setVisible(!setting().onHidePauseButton);
	}

	// Hide Player
	self->m_player->setVisible(!setting().onHidePlayer);
	self->m_player2->setVisible(!setting().onHidePlayer);

	// No Wave Trail
	self->m_player->m_hardStreak->setVisible(!setting().onNoWaveTrail);
	self->m_player2->m_hardStreak->setVisible(!setting().onNoWaveTrail);

	if (setting().onAutoSafeMode && setting().cheatsCount > 0) safeModeON(), setting().isSafeMode = true;
	else if (!setting().onSafeMode) safeModeOFF(), setting().isSafeMode = false;

	const auto bar = gd::GameManager::sharedState()->getProgressBar();
	auto size = CCDirector::sharedDirector()->getWinSize();
	auto percentLabel = self->m_percentLabel;
	if (percentLabel) {
		if (bar) {
			percentLabel->setPosition({ size.width / 2.f + 110.2f, size.height - 8.f });
			percentLabel->setAnchorPoint({ 0.f, 0.5f });
		}
		else {
			percentLabel->setPosition({ size.width / 2.f, size.height - 8.f });
			percentLabel->setAnchorPoint({ 0.5f, 0.5f });
		}
		percentLabel->setVisible(gd::GameManager::sharedState()->getGameVariable("0040"));
	}

	auto spSwitcherMenu = CCMenu::create();
	self->m_uiLayer->addChild(spSwitcherMenu, 16, 177);
	auto spSwitcherLabel = CCLabelBMFont::create("", "bigFont.fnt");
	spSwitcherMenu->addChild(spSwitcherLabel, 0, 178);
	spSwitcherLabel->setPositionY(-145.f);
	spSwitcherLabel->setScale(.5f);
	if (!startPosObjects.empty()) spSwitcherLabel->setString(CCString::createWithFormat("%d/%d", currentStartPos + 1, startPosObjects.size())->getCString());
	spSwitcherLabel->setOpacity(255);
	spSwitcherLabel->stopAllActions();
	spSwitcherLabel->runAction(CCSequence::create(CCDelayTime::create(1.f), CCFadeOut::create(0.5f), nullptr));

	auto playerDrawNode = CCDrawNode::create();
	self->m_objectLayer->addChild(playerDrawNode, 1000, 124);
	auto objectDrawNode = CCDrawNode::create();
	self->m_objectLayer->addChild(objectDrawNode, 1000, 125);

	if (setting().onHitboxes) {
		if (setting().onEnablePlayerHitboxes) {
			if (self->m_player) Hitboxes::drawPlayerHitbox(self->m_player, playerDrawNode);
			if (self->m_player2) Hitboxes::drawPlayerHitbox(self->m_player2, playerDrawNode);
		}

		for (int i = self->m_firstVisibleSection + 1; i <= self->m_lastVisibleSection - 1; i++) {
			if (i < 0) continue;
			if (i >= self->m_levelSections->count()) break;

			auto objectAtIndex = self->m_levelSections->objectAtIndex(i);
			auto objArr = reinterpret_cast<CCArray*>(objectAtIndex);

			for (int j = 0; j < objArr->count(); j++) {
				auto obj = reinterpret_cast<gd::GameObject*>(objArr->objectAtIndex(j));
				if (setting().onEnableSolidHitboxes)
					Hitboxes::drawSolidsObjectHitbox(obj, objectDrawNode);
				if (setting().onEnableHazardHitboxes)
					Hitboxes::drawHazardsObjectHitbox(obj, objectDrawNode);
				if (setting().onEnableSpecialHitboxes)
					Hitboxes::drawSpecialsObjectHitbox(obj, objectDrawNode);
			}
		}
	}

	if (setting().onDeveloperMode) {
		auto cheatIndicator = CCLabelBMFont::create(".", "bigFont.fnt");
		cheatIndicator->setAnchorPoint({ 0.f, 1.f });
		cheatIndicator->setScale(.35f);
		cheatIndicator->getChildByTag(0)->setScale(2.5f);
		cheatIndicator->getChildByTag(0)->setAnchorPoint({ 0.f, .25f });
		cheatIndicator->setPosition(director->getScreenLeft(), director->getScreenTop());
		self->m_uiLayer->addChild(cheatIndicator, 99, 4900);

		updateCheatIndicator(self);

		auto playerInfo = CCLabelBMFont::create("FPS: X: Y: yVel: xVel: SlopeVel: Speed: ", "chatFont.fnt");
		playerInfo->setAnchorPoint({ 0.f, 0.f });
		playerInfo->setScale(.5f);
		playerInfo->setOpacity(100);
		self->m_uiLayer->addChild(playerInfo, 99, 4901);
	}

	updatePlayerColors(self);

	return true;
}

void __fastcall PlayLayer::updateH(gd::PlayLayer* self, void*, float dt) {
	layers().PauseLayerObject = nullptr;

	if (0 < smoothOut) {
		smoothOut--;
		dt = 0.01666667;
	}

	PlayLayer::update(self, dt);

	auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();

	self->m_attemptLabel->setVisible(!setting().onHideAttempts);

	if (gd::GameManager::sharedState()->getGameVariable("0024")) {
		from<gd::CCMenuItemSpriteExtra*>(self->m_uiLayer, 0x1a0)->setVisible(!setting().onHidePauseButton);
	}

	self->m_player->setVisible(!setting().onHidePlayer);
	self->m_player2->setVisible(!setting().onHidePlayer);

	if ((setting().onAutoSafeMode || setting().onSafeMode) && setting().cheatsCount > 0) safeModeON(), setting().isSafeMode = true;
	else if (!setting().onSafeMode) safeModeOFF(), setting().isSafeMode = false;

	if (setting().onLockCursor && !setting().show && !self->m_hasLevelCompletedMenu && !self->m_isDead) {
		HWND hwnd = WindowFromDC(wglGetCurrentDC());
		RECT winSize; GetWindowRect(hwnd, &winSize);
		auto width = winSize.right - winSize.left;
		auto height = winSize.bottom - winSize.top;
		auto centerX = width / 2.f + winSize.left;
		auto centerY = height / 2.f + winSize.top;
		SetCursorPos(centerX, centerY);
	}

	updateShowHitboxes(self);

	if (setting().onShowLayout) {
		self->m_backgroundSprite->setColor(ccc3(setting().levelBGColorR, setting().levelBGColorG, setting().levelBGColorB));
		self->m_bottomGround->updateGround01Color(ccc3(setting().levelGColorR, setting().levelGColorG, setting().levelGColorB));
		self->m_bottomGround->updateGround02Color(ccc3(setting().levelGColorR, setting().levelGColorG, setting().levelGColorB));
		self->m_bottomGround->updateLineColor({ 255, 255, 255 });
		self->m_topGround->updateGround01Color(ccc3(setting().levelGColorR, setting().levelGColorG, setting().levelGColorB));
		self->m_topGround->updateGround02Color(ccc3(setting().levelGColorR, setting().levelGColorG, setting().levelGColorB));
		self->m_topGround->updateLineColor({ 255, 255, 255 });

		self->m_backgroundFlashNode->setVisible(false);

		for (int i = self->m_firstVisibleSection - 1; i <= self->m_lastVisibleSection + 1; i++) {
			if (i < 0) continue;
			if (i >= self->m_levelSections->count()) break;

			auto objectAtIndex = self->m_levelSections->objectAtIndex(i);
			auto objArr = reinterpret_cast<CCArray*>(objectAtIndex);

			for (int j = 0; j < objArr->count(); j++) {
				auto obj = reinterpret_cast<gd::GameObject*>(objArr->objectAtIndex(j));
				if (obj->m_objectType == gd::kGameObjectTypeDecoration && obj->isVisible() && (obj->m_objectID != 10 && obj->m_objectID != 11 && obj->m_objectID != 12 && obj->m_objectID != 13 && obj->m_objectID != 38 && obj->m_objectID != 44 && obj->m_objectID != 45 && obj->m_objectID != 46 && obj->m_objectID != 47 && obj->m_objectID != 99 && obj->m_objectID != 101 && obj->m_objectID != 111 && obj->m_objectID != 286 && obj->m_objectID != 287 && obj->m_objectID != 660 && obj->m_objectID != 745 && obj->m_objectID != 749) && obj != self->m_endPortal)
					obj->setVisible(false);

				obj->setObjectColor({ 255, 255, 255 });
				if (obj->m_detailSprite) obj->m_detailSprite->setColor({ 255, 255, 255 });
				obj->m_detailColorID = 1011;
			}
		}
	}

	if (setting().onDeveloperMode) {
		updateCheatIndicator(self);

		auto playerInfo = static_cast<CCLabelBMFont*>(self->m_uiLayer->getChildByTag(4901));
		if (playerInfo) {
			playerInfo->setString(CCString::createWithFormat("FPS: %.0f X: %f Y: %f yVel: %f xVel: %f SlopeVel: %f Speed: %f", ImGui::GetIO().Framerate, self->m_player->getPositionX(), self->m_player->getPositionY(), self->m_player->m_yVelocity, self->m_player->m_xVelocity, self->m_player->m_slopeYVel, self->m_player->m_playerSpeed)->getCString());
		}
	}

	const float playerPercentPos = self->m_player->getPositionX() / self->m_levelLength * 100.f;

	if (setting().onAutoKill && (setting().killPercentage <= playerPercentPos)) {
		if (!self->m_isDead)
			self->destroyPlayer(self->m_player);
	}

	if ((setting().onAutoDeafen && !m_deafenPressed) && /*(setting().deafenPercent > m_startPercent) &&*/ (playerPercentPos > setting().deafenPercent) && !self->m_isDead && !self->m_hasCompletedLevel) {
		if ((self->m_isPracticeMode && !setting().onPracticeDeafen) || (self->m_isTestMode && !setting().onTestmodeDeafen)) return;

		m_deafenPressed = true;
		keybd_event(VK_MENU, 0x38, 0, 0);
		keybd_event(setting().g_autoDeafenKey, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(setting().g_autoDeafenKey, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	}
}

void __fastcall PlayLayer::destroyPlayerH(gd::PlayLayer* self, void*, gd::PlayerObject* player) {
	if (!setting().onNoclip) PlayLayer::destroyPlayer(self, player);

	if (m_deafenPressed) {
		m_deafenPressed = false;
		keybd_event(VK_MENU, 0x38, 0, 0);
		keybd_event(setting().g_autoDeafenKey, 0x50, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(setting().g_autoDeafenKey, 0x50, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	}

	if (setting().onRespawnTime) {
		float respawnTime = setting().respawnValue / 1000.f;

		if (auto* respawnSequence = self->getActionByTag(0x10)) {
			self->stopAction(respawnSequence);

			auto* delayedSequence = CCSequence::create(CCDelayTime::create(respawnTime), CCCallFunc::create(self, callfunc_selector(gd::PlayLayer::delayedResetLevel)), nullptr);

			delayedSequence->setTag(0x10);
			self->runAction(delayedSequence);
		}
	}
}

void __fastcall PlayLayer::resetLevelH(gd::PlayLayer* self) {
	if (setting().onSmartStartPos)
		for (gd::StartPosObject* obj : m_startPositions)
			setupStartPos(obj);

	PlayLayer::resetLevel(self);

	if (m_deafenPressed) {
		m_deafenPressed = false;
		keybd_event(VK_MENU, 0x38, 0, 0);
		keybd_event(setting().g_autoDeafenKey, 0x50, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(setting().g_autoDeafenKey, 0x50, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	}

	if (setting().onPracticeBugFix) {
		if (self->m_isPracticeMode && checkpoints.size() > 0)
			checkpoints.back().restore(self);
	}

	if (setting().onCheckpointLagFix && (self->m_isPracticeMode || self->m_isTestMode)) smoothOut = 2;

	if (setting().onAutoPickupCoins) {
		for (auto* coin : m_coinsToPickup) {
			if (coin == nullptr) continue;

			static_cast<gd::GameObject*>(coin)->destroyObject();
			self->pickupItem(coin);
		}
	}
}

void __fastcall PlayLayer::togglePracticeModeH(gd::PlayLayer* self, void* edx, bool practice) {
	if (setting().onPracticeBugFix) {
		checkpoints.clear();
	}
	PlayLayer::togglePracticeMode(self, practice);

	if (setting().onHidePracticeButtons)
		self->m_uiLayer->m_checkpointMenu->setVisible(!setting().onHidePracticeButtons);
}

void __fastcall PlayLayer::createCheckpointH(gd::PlayLayer* self) {
	if (setting().onPracticeBugFix) {
		if (self->m_player != nullptr) {
			checkpoints.push_back({
				CheckPoint::from(self)
				});
		}
	}
	PlayLayer::createCheckpoint(self);
}

void __fastcall PlayLayer::removeLastCheckpointH(gd::PlayLayer* self) {
	if (setting().onPracticeBugFix) {
		if (checkpoints.size() > 0) {
			checkpoints.pop_back();
		}
	}
	PlayLayer::removeLastCheckpoint(self);
}

void __fastcall PlayLayer::onQuitH(gd::PlayLayer* self) {
	if (setting().onPracticeBugFix) {
		checkpoints.clear();
	}
	PlayLayer::onQuit(self);
	layers().PauseLayerObject = nullptr;
}

void __fastcall PlayLayer::levelCompleteH(gd::PlayLayer* self) {
	if (setting().onPracticeBugFix) {
		checkpoints.clear();
	}
	PlayLayer::levelComplete(self);

	if (m_deafenPressed) {
		m_deafenPressed = false;
		keybd_event(VK_MENU, 0x38, 0, 0);
		keybd_event(setting().g_autoDeafenKey, 0x50, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(setting().g_autoDeafenKey, 0x50, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	}
}

void __fastcall PlayLayer::addObjectH(gd::PlayLayer* self, void*, gd::GameObject* obj) {
	PlayLayer::addObject(self, obj);

	if (obj->m_objectID == 31) {
		startPosObjects.push_back(reinterpret_cast<gd::StartPosObject*>(obj));
	}

	switch (obj->m_objectID)
	{
	case 31:
		m_startPositions.push_back(static_cast<gd::StartPosObject*>(obj));
		break;
	case 12:
	case 13:
	case 47:
	case 111:
	case 660:
	case 745: m_gamemodePortals.push_back(obj);
		break;
	case 45:
	case 46: m_mirrorPortals.push_back(obj);
		break;
	case 99:
	case 101: m_miniPortals.push_back(obj);
		break;
	case 286:
	case 287: m_dualPortals.push_back(obj);
		break;
	case 200:
	case 201:
	case 202:
	case 203: m_speedChanges.push_back(obj);
		break;
	default: break;
	}

	if (obj->m_objectID == 142 || obj->m_objectID == 1329)
		m_coinsToPickup.push_back(static_cast<gd::EffectGameObject*>(obj));
}

void __fastcall PlayLayer::createObjectsFromSetupH(gd::PlayLayer* self, void*, gd::string objects) {
	PlayLayer::createObjectsFromSetup(self, objects);
	if (startPosObjects.empty()) return;

	std::ranges::sort(startPosObjects, [](gd::GameObject* a, gd::GameObject* b) {
		return a->getPositionX() < b->getPositionX();
		});

	currentStartPos = -1;
	if (self->m_startPosObject) {
		auto it = std::ranges::find(startPosObjects, self->m_startPosObject);
		if (it != startPosObjects.end())
			currentStartPos = static_cast<int32_t>(std::distance(startPosObjects.begin(), it));
	}
}

void __fastcall PlayLayer::lightningFlashH(gd::PlayLayer* self, void*, CCPoint p0, _ccColor3B p1) {
	if (!setting().onShowLayout) PlayLayer::lightningFlash(self, p0, p1);
}

void __fastcall PlayLayer::updateVisibilityH(gd::PlayLayer* self) {
	PlayLayer::updateVisibility(self);
	if (setting().onNoWavePulse) {
		self->m_player->m_audioScale = 1.f;
		self->m_player2->m_audioScale = 1.f;
	}
}

void __fastcall PlayLayer::spawnPlayer2H(gd::PlayLayer* self) {
	PlayLayer::spawnPlayer2(self);
	if (setting().onInvisibleDualFix) self->m_player2->setVisible(true);
}

void __fastcall PlayLayer::pauseGameH(gd::PlayLayer* self, void*, bool idk) {
	PlayLayer::pauseGame(self, idk);

	if (setting().onPauseUndeafen && m_deafenPressed) {
		m_deafenPressed = false;
		keybd_event(VK_MENU, 0x38, 0, 0);
		keybd_event(setting().g_autoDeafenKey, 0x50, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(setting().g_autoDeafenKey, 0x50, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	}
}

void __fastcall PlayLayer::showNewBestH(gd::PlayLayer* self) {
	if (!setting().onNoNewBest) PlayLayer::showNewBest(self);
}

static inline void updateSwing(gd::PlayerObject* self, const float dt) {
}

void PlayLayer::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x16ab80), PlayLayer::initH, reinterpret_cast<void**>(&PlayLayer::init));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x170f30), PlayLayer::updateH, reinterpret_cast<void**>(&PlayLayer::update));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x17b560), PlayLayer::destroyPlayerH, reinterpret_cast<void**>(&PlayLayer::destroyPlayer));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x17c930), PlayLayer::resetLevelH, reinterpret_cast<void**>(&PlayLayer::resetLevel));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x17d900), PlayLayer::togglePracticeModeH, reinterpret_cast<void**>(&PlayLayer::togglePracticeMode));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x17c0e0), PlayLayer::createCheckpointH, reinterpret_cast<void**>(&PlayLayer::createCheckpoint));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x17c780), PlayLayer::removeLastCheckpointH, reinterpret_cast<void**>(&PlayLayer::removeLastCheckpoint));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x17de80), PlayLayer::onQuitH, reinterpret_cast<void**>(&PlayLayer::onQuit));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x16c830), PlayLayer::levelCompleteH, reinterpret_cast<void**>(&PlayLayer::levelComplete));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x16fc00), PlayLayer::addObjectH, reinterpret_cast<void**>(&PlayLayer::addObject));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x16f700), PlayLayer::createObjectsFromSetupH, reinterpret_cast<void**>(&PlayLayer::createObjectsFromSetup));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x176470), PlayLayer::updateVisibilityH, reinterpret_cast<void**>(&PlayLayer::updateVisibility));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x179ef0), PlayLayer::spawnPlayer2H, reinterpret_cast<void**>(&PlayLayer::spawnPlayer2));
	//MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x16e110), PlayLayer::lightningFlashH, reinterpret_cast<void**>(&PlayLayer::lightningFlash));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x17dbb0), PlayLayer::pauseGameH, reinterpret_cast<void**>(&PlayLayer::pauseGame));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x16d770), PlayLayer::showNewBestH, reinterpret_cast<void**>(&PlayLayer::showNewBest));
}