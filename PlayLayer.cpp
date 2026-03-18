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

CCNode* m_labelsNode = nullptr;
CCLabelBMFont* m_cheatIndicatorLabel = nullptr;
CCLabelBMFont* m_messageLabel = nullptr;
CCLabelBMFont* m_attemptsLabel = nullptr;
CCLabelBMFont* m_fpsCounterLabel = nullptr;
CCLabelBMFont* m_cpsCounterLabel = nullptr;
bool m_hasClicked;
bool m_isHolding;
std::vector<time_t> m_clickFrames;
int m_totalClicks;
CCLabelBMFont* m_jumpsLabel = nullptr;
CCLabelBMFont* m_sessionTimeLabel = nullptr;
CCLabelBMFont* m_bestRunLabel = nullptr;
int m_lastRun;
int m_bestRunPercentage;
CCLabelBMFont* m_clockLabel = nullptr;
std::time_t clockTime;
SYSTEMTIME st;

bool m_cheatingBeforeRestart;

bool PlayLayer::getCheatingBeforeRestart() {
	return m_cheatingBeforeRestart;
}

bool PlayLayer::isCheating() {
	return
		setting().onInstantMirror ||
		setting().onNoMirror ||
		setting().onAutoPickupCoins ||
		setting().onEverythingHurts ||
		setting().onHitboxes ||
		setting().onJumpHack ||
		setting().onNoHitbox ||
		setting().onNoclip ||
		setting().onShowLayout ||
		setting().onSpeedhack;
}

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
	if (playLayer->m_isPracticeMode) return;

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

void updateCheatIndicator() {
	bool isCheating = PlayLayer::isCheating();
	bool cheatingBeforeRestart = PlayLayer::getCheatingBeforeRestart();

	if (m_cheatIndicatorLabel && m_cheatIndicatorLabel->isVisible()) {
		if (!cheatingBeforeRestart && !setting().isSafeMode) {
			m_cheatIndicatorLabel->setColor(ccGREEN);
		}
		else if (!cheatingBeforeRestart && setting().isSafeMode) {
			m_cheatIndicatorLabel->setColor(ccYELLOW);
		}
		else if ((!isCheating || isCheating) && cheatingBeforeRestart && setting().isSafeMode) {
			m_cheatIndicatorLabel->setColor(ccORANGE);
		}
		else if (isCheating || cheatingBeforeRestart && !setting().isSafeMode) {
			m_cheatIndicatorLabel->setColor(ccRED);
		}
	}
}

void updateMessageLabel() {
	if (m_messageLabel && m_messageLabel->isVisible()) {
		m_messageLabel->setString(setting().message.c_str());
	}
}

void updateAttemptsLabel() {
	if (m_attemptsLabel && m_attemptsLabel->isVisible()) {
		auto playLayer = gd::GameManager::sharedState()->getPlayLayer();

		std::string prefix;

		if (setting().attemptsPrefix) {
			prefix = "Attempt ";
		}
		else {
			prefix.clear();
		}

		m_attemptsLabel->setString((prefix + std::to_string(playLayer->m_currentAttempt)).c_str());
	}
}

void updateFPSLabel() {
	if (m_fpsCounterLabel && m_fpsCounterLabel->isVisible()) {
		std::string prefix;

		if (setting().fpsPrefix) {
			prefix = " FPS";
		}
		else {
			prefix.clear();
		}

		m_fpsCounterLabel->setString((std::to_string(static_cast<int>(ImGui::GetIO().Framerate)) + prefix).c_str());
	}
}

void updateCPSLabel() {
	if (m_cpsCounterLabel && m_cpsCounterLabel->isVisible()) {
		std::string prefix;

		if (setting().cpsPrefix) {
			prefix = " CPS";
		}
		else {
			prefix.clear();
		}

		//std::string cpsMax;

		//if (setting().cpsMax) {
		//	cpsMax = "/" + std::to_string(m_totalClicks);
		//}
		//else {
		//	cpsMax.clear();
		//}

		std::string cpsTotal;

		if (setting().cpsTotal) {
			cpsTotal = "/" + std::to_string(m_totalClicks);
		}

		if (m_isHolding) {
			m_cpsCounterLabel->setColor(ccc3(64, 255, 64));
		}
		else {
			m_cpsCounterLabel->setColor(ccc3(255, 255, 255));
		}

		m_cpsCounterLabel->setString((std::to_string(m_clickFrames.size()) + cpsTotal + prefix).c_str());
	}
}

void updateJumpsLabel() {
	if (m_jumpsLabel && m_jumpsLabel->isVisible()) {
		auto playLayer = gd::GameManager::sharedState()->getPlayLayer();

		std::string prefix;

		if (setting().jumpsPrefix) {
			prefix = " Jumps";
		}
		else {
			prefix.clear();
		}

		m_jumpsLabel->setString((std::to_string(playLayer->m_jumpsCount) + prefix).c_str());
	}
}

void updateSessionTimeLabel() {
	if (m_sessionTimeLabel && m_sessionTimeLabel->isVisible()) {
		auto playLayer = gd::GameManager::sharedState()->getPlayLayer();

		m_sessionTimeLabel->setString(CCString::createWithFormat("%.01fs", playLayer->m_totalTime)->getCString());
	}
}

void updateBestRunLabel() {
	if (m_bestRunLabel && m_bestRunLabel->isVisible()) {
		auto playLayer = gd::GameManager::sharedState()->getPlayLayer();

		std::string prefix;

		if (setting().bestRunPrefix) {
			prefix = "Best Run: ";
		}
		else {
			prefix.clear();
		}

		int newBest = m_lastRun;

		if (newBest >= m_bestRunPercentage) {
			m_bestRunPercentage = newBest;
			m_bestRunLabel->setString((prefix + std::to_string(newBest) + "%").c_str());
		}
	}
}

void updateClockLabel() {
	if (m_clockLabel && m_clockLabel->isVisible()) {
		clockTime = std::time(nullptr);
		auto tm = *std::localtime(&clockTime);
		std::ostringstream s;
		s << std::put_time(&tm, "%H:%M:%S");
		m_clockLabel->setString(s.str().c_str());
	}
}

std::string keyToFont(int key) {
	switch (key) {
	default:
	case 0:
		return "bigFont.fnt";
	case 1:
		return "chatFont.fnt";
	case 2:
		return "gjFont01.fnt";
	case 3:
		return "gjFont02.fnt";
	case 4:
		return "gjFont03.fnt";
	case 5:
		return "gjFont04.fnt";
	case 6:
		return "gjFont05.fnt";
	case 7:
		return "gjFont06.fnt";
	case 8:
		return "gjFont07.fnt";
	case 9:
		return "gjFont08.fnt";
	case 10:
		return "gjFont09.fnt";
	case 11:
		return "gjFont10.fnt";
	case 12:
		return "gjFont11.fnt";
	}
}

void PlayLayer::updateStatusLabels() {
	auto self = gd::GameManager::sharedState()->getPlayLayer();

	if (!self) return;

	auto director = CCDirector::sharedDirector();

	auto leftStatusXPos = (setting().labelsScale < 1.f) ? director->getScreenLeft() + setting().labelsScale * 5 : director->getScreenLeft() + 5;
	auto rightStatusXPos = (setting().labelsScale < 1.f) ? director->getScreenRight() - setting().labelsScale * 5 : director->getScreenRight() - 5;

	m_labelsNode->setVisible(!setting().onHideLabels);

	m_cheatIndicatorLabel->setVisible(setting().onCheatIndicator);
	m_cheatIndicatorLabel->setTag(setting().cheatIndicatorPos);

	m_messageLabel->setVisible(setting().onMessageLabel);
	m_messageLabel->setTag(setting().messagePos);

	m_attemptsLabel->setVisible(setting().onAttemptsLabel);
	m_attemptsLabel->setTag(setting().attemptsPos);

	m_fpsCounterLabel->setVisible(setting().onFPSCounter);
	m_fpsCounterLabel->setTag(setting().fpsCounterPos);

	m_cpsCounterLabel->setVisible(setting().onCPSCounter);
	m_cpsCounterLabel->setTag(setting().cpsCounterPos);

	m_jumpsLabel->setVisible(setting().onJumpsLabel);
	m_jumpsLabel->setTag(setting().jumpsPos);

	m_sessionTimeLabel->setVisible(setting().onSessionTime);
	m_sessionTimeLabel->setTag(setting().sessionTimePos);

	m_bestRunLabel->setVisible(setting().onBestRunLabel);
	m_bestRunLabel->setTag(setting().bestRunPos);

	m_clockLabel->setVisible(setting().onClockLabel);
	m_clockLabel->setTag(setting().clockPos);

	int topLeftLabelsCount = 0;
	int topRightLabelsCount = 0;
	int bottomRightLabelsCount = 0;
	int bottomLeftLabelsCount = 0;

	for (int i = 0; i < m_labelsNode->getChildrenCount(); i++) {
		auto label = static_cast<CCLabelBMFont*>(m_labelsNode->getChildren()->objectAtIndex(i));
		if (label && label->isVisible()) {
			label->setScale((1.f - .6f) * setting().labelsScale);
			if (label != m_cheatIndicatorLabel) {
				label->setOpacity((255 - 191) * setting().labelsOpacity);
			}
			label->setFntFile(keyToFont(setting().labelsFont).c_str());

			if (label->getTag() == 0) { // Top-Left
				label->setAnchorPoint(ccp(0.f, 1.f));
				if (label != m_cheatIndicatorLabel) {
					label->m_pAlignment = kCCTextAlignmentLeft;
				}
				label->setPosition(leftStatusXPos, (director->getScreenTop() - 2.f) - (topLeftLabelsCount * setting().labelsScale * 13.f));
				topLeftLabelsCount++;
			}

			if (label->getTag() == 1) { // Top-Right
				label->setAnchorPoint(ccp(1.f, 1.f));
				if (label != m_cheatIndicatorLabel) {
					label->m_pAlignment = kCCTextAlignmentRight;
				}
				label->setPosition(rightStatusXPos, (director->getScreenTop() - 2.f) - (topRightLabelsCount * setting().labelsScale * 13.f));
				topRightLabelsCount++;
			}

			if (label->getTag() == 2) { // Bottom-Right
				label->setAnchorPoint(ccp(1.f, 0.f));
				if (label != m_cheatIndicatorLabel) {
					label->m_pAlignment = kCCTextAlignmentRight;
				}
				label->setPosition(rightStatusXPos, (director->getScreenBottom() + 2.f) + (bottomRightLabelsCount * setting().labelsScale * 13.f));
				bottomRightLabelsCount++;
			}

			if (label->getTag() == 3) { // Bottom-Left
				label->setAnchorPoint(ccp(0.f, 0.f));
				if (label != m_cheatIndicatorLabel) {
					label->m_pAlignment = kCCTextAlignmentLeft;
				}
				label->setPosition(leftStatusXPos, (director->getScreenBottom() + 2.f) + (bottomLeftLabelsCount * setting().labelsScale * 13.f));
				bottomLeftLabelsCount++;
			}
		}
	}

	updateCheatIndicator();
	updateMessageLabel();
	updateAttemptsLabel();
	updateFPSLabel();
	updateCPSLabel();
	updateJumpsLabel();
	updateSessionTimeLabel();
	updateBestRunLabel();
	updateClockLabel();
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
	m_hasClicked = false;
	m_clickFrames.clear();
	m_totalClicks = 0;
	m_isHolding = false;
	m_lastRun = 0;
	m_bestRunPercentage = 0;
	m_cheatingBeforeRestart = PlayLayer::isCheating();

	if (!PlayLayer::init(self, level)) return false;

	if ((setting().onAutoSafeMode && (PlayLayer::isCheating() || m_cheatingBeforeRestart)) || setting().onSafeMode) {
		safeModeON();
		setting().isSafeMode = true;
	}
	else {
		safeModeOFF();
		setting().isSafeMode = false;
	}

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

		auto playerInfo = CCLabelBMFont::create("FPS: X: Y: yVel: xVel: SlopeVel: Speed: ", "chatFont.fnt");
		playerInfo->setAnchorPoint({ 0.f, 0.f });
		playerInfo->setScale(.5f);
		playerInfo->setOpacity(100);
		self->m_uiLayer->addChild(playerInfo, 99, 4901);
	}

	updatePlayerColors(self);

	m_labelsNode = CCNode::create();
	self->addChild(m_labelsNode, 99);

	m_cheatIndicatorLabel = CCLabelBMFont::create(". ", "bigFont.fnt");
	static_cast<CCSprite*>(m_cheatIndicatorLabel->getChildren()->objectAtIndex(0))->setScale(3.f);
	static_cast<CCSprite*>(m_cheatIndicatorLabel->getChildren()->objectAtIndex(0))->setAnchorPoint(ccp(.25f, .25f));
	m_labelsNode->addChild(m_cheatIndicatorLabel);

	m_messageLabel = CCLabelBMFont::create("", "bigFont.fnt");
	m_labelsNode->addChild(m_messageLabel);

	m_bestRunLabel = CCLabelBMFont::create("", "bigFont.fnt");
	m_labelsNode->addChild(m_bestRunLabel);

	m_attemptsLabel = CCLabelBMFont::create("", "bigFont.fnt");
	m_labelsNode->addChild(m_attemptsLabel);

	m_fpsCounterLabel = CCLabelBMFont::create("", "bigFont.fnt");
	m_labelsNode->addChild(m_fpsCounterLabel);

	m_cpsCounterLabel = CCLabelBMFont::create("", "bigFont.fnt");
	m_labelsNode->addChild(m_cpsCounterLabel);

	m_jumpsLabel = CCLabelBMFont::create("", "bigFont.fnt");
	m_labelsNode->addChild(m_jumpsLabel);

	m_clockLabel = CCLabelBMFont::create("", "bigFont.fnt");
	m_labelsNode->addChild(m_clockLabel);

	m_sessionTimeLabel = CCLabelBMFont::create("", "bigFont.fnt");
	m_labelsNode->addChild(m_sessionTimeLabel);

	PlayLayer::updateStatusLabels();

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

	if (PlayLayer::isCheating()) {
		m_cheatingBeforeRestart = PlayLayer::isCheating();
	}

	if ((setting().onAutoSafeMode && (PlayLayer::isCheating() || m_cheatingBeforeRestart)) || setting().onSafeMode) {
		safeModeON();
		setting().isSafeMode = true;
	}
	else {
		safeModeOFF();
		setting().isSafeMode = false;
	}

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

	time_t currentTick = time::getTime();
	m_clickFrames.erase(std::remove_if(m_clickFrames.begin(), m_clickFrames.end(), [currentTick](float tick) {
		return currentTick - tick > 1000;
		}), m_clickFrames.end());
	m_hasClicked = false;

	updateCheatIndicator();
	updateMessageLabel();
	updateAttemptsLabel();
	updateFPSLabel();
	updateCPSLabel();
	updateJumpsLabel();
	updateSessionTimeLabel();
	updateClockLabel();
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

	if (!self->m_isPracticeMode && !self->m_isTestMode && !setting().onNoclip) {
		m_lastRun = self->m_player->getPositionX() / self->m_levelLength * 100.f;
	}

	updateBestRunLabel();
}

void __fastcall PlayLayer::resetLevelH(gd::PlayLayer* self) {
	if (setting().onSmartStartPos)
		for (gd::StartPosObject* obj : m_startPositions)
			setupStartPos(obj);

	m_clickFrames.clear();
	m_totalClicks = 0;

	PlayLayer::resetLevel(self);

	m_cheatingBeforeRestart = PlayLayer::isCheating();

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

void __fastcall PlayLayer::pushButtonH(gd::PlayLayer* self, void*, int p0, bool p1) {
	m_isHolding = true;
	if (!m_hasClicked) {
		m_clickFrames.push_back(time::getTime());
		m_totalClicks++;
		m_hasClicked = true;
	}
	PlayLayer::pushButton(self, p0, p1);
}

void __fastcall PlayLayer::releaseButtonH(gd::PlayLayer* self, void*, int p0, bool p1) {
	m_isHolding = false;
	PlayLayer::releaseButton(self, p0, p1);
}

void __fastcall PlayLayer::destructorH(gd::PlayLayer* self) {
	PlayLayer::destructor(self);
	m_labelsNode = nullptr;
	m_cheatIndicatorLabel = nullptr;
	m_messageLabel = nullptr;
	m_attemptsLabel = nullptr;
	m_fpsCounterLabel = nullptr;
	m_cpsCounterLabel = nullptr;
	m_jumpsLabel = nullptr;
	m_sessionTimeLabel = nullptr;
	m_clockLabel = nullptr;
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

	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x17bac0), PlayLayer::pushButtonH, reinterpret_cast<void**>(&PlayLayer::pushButton));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x17bbb0), PlayLayer::releaseButtonH, reinterpret_cast<void**>(&PlayLayer::releaseButton));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x16a630), PlayLayer::destructorH, reinterpret_cast<void**>(&PlayLayer::destructor));
}