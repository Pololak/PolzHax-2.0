#include "LevelEditorLayer.h"

#include "Hitboxes.h"

#include "state.h"
#include "RotateSaws.h"

bool __fastcall LevelEditorLayer::initH(gd::LevelEditorLayer* self, void*, gd::GJGameLevel* level) {
	if (!LevelEditorLayer::init(self, level)) return false;

	if (setting().onHitboxBugFix) {
		if (self->m_levelSections) {
			for (int i = 0; i <= self->m_levelSections->count(); i++) {
				if (i < 0) continue;
				if (i >= self->m_levelSections->count()) break;

				auto objectAtIndex = self->m_levelSections->objectAtIndex(i);
				auto objArr = reinterpret_cast<CCArray*>(objectAtIndex);

				for (int j = 0; j < objArr->count(); j++) {
					auto obj = reinterpret_cast<gd::GameObject*>(objArr->objectAtIndex(j));
					if (obj && obj->canRotateFree()) {
						if ((obj->getRotation() / 90.f) != 0.f) {
							obj->calculateOrientedBox();
						}
					}
				}
			}
		}
	}

	auto playerDrawNode = CCDrawNode::create();
	self->m_objectLayer->addChild(playerDrawNode, 1000, 124);
	auto objectDrawNode = CCDrawNode::create();
	self->m_objectLayer->addChild(objectDrawNode, 1000, 125);

	updatePlayerColors(self);

	return true;
}

void __fastcall LevelEditorLayer::updateVisibilityH(gd::LevelEditorLayer* self, void*, float dt) {
	LevelEditorLayer::updateVisibility(self, dt);

	auto playerDrawNode = static_cast<CCDrawNode*>(self->m_objectLayer->getChildByTag(124));
	playerDrawNode->clear();
	auto objectDrawNode = static_cast<CCDrawNode*>(self->m_objectLayer->getChildByTag(125));
	objectDrawNode->clear();

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
				if (!obj) return;
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

namespace gd {
	class SpriteAnimationManager : public cocos2d::CCNode {
	public:
		void runAnimation(std::string anim) {
			reinterpret_cast<void(__thiscall*)(SpriteAnimationManager*, std::string)>(base + 0x2c4f0)(this, anim);
		}
	};
}

void __fastcall LevelEditorLayer::updateH(gd::LevelEditorLayer* self, void*, float dt) {
	LevelEditorLayer::update(self, dt);

	auto playerDrawNode = static_cast<CCDrawNode*>(self->m_objectLayer->getChildByTag(124));
	playerDrawNode->clear();

	if (setting().onHitboxes) {
		if (setting().onEnablePlayerHitboxes) {
			if (self->m_player) Hitboxes::drawPlayerHitbox(self->m_player, playerDrawNode);
			if (self->m_player2) Hitboxes::drawPlayerHitbox(self->m_player2, playerDrawNode);
		}
	}
}

void LevelEditorLayer::updatePlayerColors(gd::LevelEditorLayer* self) {
	auto gm = gd::GameManager::sharedState();

	if (!self->m_player2) return;

	self->m_player2->setColor(setting().onSameDualColor ? gm->colorForIdx(gm->m_playerColor) : gm->colorForIdx(gm->m_playerColor2));
	self->m_player2->setSecondColor(setting().onSameDualColor ? gm->colorForIdx(gm->m_playerColor2) : gm->colorForIdx(gm->m_playerColor));

	self->m_player2->updateGlowColor();
}

//void __fastcall LevelEditorLayer::onStopPlaytestH(gd::LevelEditorLayer* self) {
//	LevelEditorLayer::onStopPlaytest(self);
//
//	self->m_editorUI->m_currentGroupLabel->setVisible(false);
//}

void __fastcall DrawGridLayer::drawH(gd::DrawGridLayer* self) {
	DrawGridLayer::draw(self);

	if (setting().onDurationLines) {
		for (int i = self->m_editorLayer->m_firstVisibleSection + 1; i <= self->m_editorLayer->m_lastVisibleSection - 1; i++) {
			if (i < 0) continue;
			if (i >= self->m_editorLayer->m_levelSections->count()) break;

			auto objectAtIndex = self->m_editorLayer->m_levelSections->objectAtIndex(i);
			auto objArr = reinterpret_cast<CCArray*>(objectAtIndex);

			for (int j = 0; j < objArr->count(); j++) {
				auto obj = reinterpret_cast<gd::GameObject*>(objArr->objectAtIndex(j));

				switch (obj->m_objectID) {
				case 29: case 30: case 900: case 915: case 105: case 744: case 899: case 1007: case 901:
					gd::EffectGameObject * trig = static_cast<gd::EffectGameObject*>(obj);
					auto triggerTimePos = self->m_editorLayer->timeForXPos(trig->getPositionX());
					auto triggerFadeEnd = self->xPosForTime(triggerTimePos + trig->m_triggerDuration);

					if (trig->m_triggerDuration > 0) {
						glLineWidth(2);
						ccDrawColor4B(100, 100, 100, 75);
						ccDrawLine(trig->getPosition(), { triggerFadeEnd, trig->getPositionY() });
					}
					break;
				}

				if (obj->m_objectID == 1006) {
					gd::EffectGameObject* pulseTrig = static_cast<gd::EffectGameObject*>(obj);
					auto pulseTimePos = self->m_editorLayer->timeForXPos(pulseTrig->getPositionX());
					float totalTime = (pulseTimePos + pulseTrig->m_fadeInTime + pulseTrig->m_holdTime + pulseTrig->m_fadeOutTime);
					auto pulseTimeEnd = self->xPosForTime(totalTime);

					//if () {
					//	glLineWidth(2);
					//	ccDrawColor4B(100, 100, 100, 75);
					//	ccDrawLine(pulseTrig->getPosition(), { pulseTimeEnd, pulseTrig->getPositionY() });
					//}
				}
			}
		}
	}
}

void LevelEditorLayer::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0xed990), LevelEditorLayer::initH, reinterpret_cast<void**>(&LevelEditorLayer::init));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0xf18b0), LevelEditorLayer::updateVisibilityH, reinterpret_cast<void**>(&LevelEditorLayer::updateVisibility));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0xfb840), LevelEditorLayer::updateH, reinterpret_cast<void**>(&LevelEditorLayer::update));

	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0xfa670), LevelEditorLayer::onPlaytestH, reinterpret_cast<void**>(&LevelEditorLayer::onPlaytest));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0xfadd0), LevelEditorLayer::onResumePlaytestH, reinterpret_cast<void**>(&LevelEditorLayer::onResumePlaytest));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0xfad20), LevelEditorLayer::onPausePlaytestH, reinterpret_cast<void**>(&LevelEditorLayer::onPausePlaytest));
	//MH_CreateHook(reinterpret_cast<void*>(gd::base + 0xfafa0), LevelEditorLayer::onStopPlaytestH, reinterpret_cast<void**>(&LevelEditorLayer::onStopPlaytest));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0xf1040), LevelEditorLayer::addSpecialH, reinterpret_cast<void**>(&LevelEditorLayer::addSpecial));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0xf0510), LevelEditorLayer::removeObjectH, reinterpret_cast<void**>(&LevelEditorLayer::removeObject));
}