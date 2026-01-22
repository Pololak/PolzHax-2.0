#define NOMINMAX
#include "EditorUI.h"
#include "moveForCommand.h"
#include "utils.hpp"
#include "GlobalClipboard.h"
#include "state.h"
#include "patching.h"
#include "RotateSaws.h"
#include "EditorLayerInput.h"

gd::EditorUI* editorUI = nullptr;
EditorLayerInput* m_editorLayerInput = nullptr;

void updateInputNode();

// 2.1 func
// decomp taken from 2.2074 geode bindings
// https://github.com/geode-sdk/bindings/blob/7c92e5e02de296f31bfb1e89909553c5b7ca37af/bindings/2.2074/GeometryDash.bro#L6723
int EditorUI::editorLayerForArray(cocos2d::CCArray* objects, bool layer2) {
	if (!objects) return 0;

	auto previousLayer = -1;
	auto currentLayer = -1;

	for (int i = 0; i < objects->count(); i++) {
		auto obj = reinterpret_cast<gd::GameObject*>(objects->objectAtIndex(i));

		currentLayer = layer2 ? obj->m_editorLayer2 : obj->m_editorLayer;

		if (previousLayer != -1 && previousLayer != currentLayer) return 0;

		previousLayer = currentLayer;
	}

	return currentLayer != -1 ? currentLayer : 0;
}

void EditorUI::Callback::onGoToLayer(CCObject*) { // decomp from 2.1
	if ((this->m_selectedObject == nullptr) && this->getSelectedObjects()->count() == 0) return;

	int uVar2 = 0;
	int uVar3 = 0;
	int uVar4 = 0;
	int uVar5 = 0;
	int uVar6 = 0;

	auto obj = this->m_selectedObject;
	uVar6 = this->m_editorLayer->m_groupIDFilter;

	if (obj == nullptr) {
		uVar2 = editorLayerForArray(this->getSelectedObjects(), false);
		uVar3 = editorLayerForArray(this->getSelectedObjects(), true);
	}
	else {
		uVar2 = obj->m_editorLayer;
		uVar3 = obj->m_editorLayer2;
	}

	uVar5 = 1 - uVar2;

	if (1 < uVar2) {
		uVar5 = 0;
	}
	if (uVar3 == 0) {
		uVar5 = 0;
	}
	else {
		uVar5 = uVar5 & 1;
	}
	uVar4 = uVar3;
	if (uVar5 != 0) {
		uVar4 = 0;
		uVar2 = uVar3;
	}
	uVar3 = uVar4;
	if (uVar4 != 0) {
		uVar3 = 1;
	}
	if (uVar6 == uVar4) {
		uVar3 = 0;
	}
	else {
		uVar3 = uVar3 & 1;
	}
	if (uVar3 != 0) {
		uVar2 = uVar4;
	}

	this->m_editorLayer->m_groupIDFilter = uVar2;
	this->m_currentGroupLabel->setString(CCString::createWithFormat("%i", uVar2)->getCString());
	updateInputNode();
}

void updateInputNode() {
	if (m_editorLayerInput) {
		if (editorUI->m_editorLayer->m_groupIDFilter < 0) {
			m_editorLayerInput->m_input->setString("All");
		}
		else {
			m_editorLayerInput->m_input->setString(std::to_string(editorUI->m_editorLayer->m_groupIDFilter).c_str());
		}
	}
}

void EditorUI::updateObjectHitbox(gd::EditorUI* eui) {
	gd::LevelEditorLayer* self = eui->m_editorLayer;
	for (int i = self->m_firstVisibleSection + 1; i <= self->m_lastVisibleSection - 1; i++) {
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

void EditorUI::Callback::onNextFreeEditorLayer(CCObject*) { // BEv4
	auto objs = this->m_editorLayer->m_objects;

	std::set<int> layers;

	CCARRAY_FOREACH_B_TYPE(objs, obj, gd::GameObject) {
		layers.insert(obj->m_editorLayer);
		layers.insert(obj->m_editorLayer2);
	}

	int last = -1;
	for (auto const& layer : layers) {
		if (last + 1 != layer) break;
		last = layer;
	}

	this->m_editorLayer->m_groupIDFilter = last + 1;
	this->m_currentGroupLabel->setString(CCString::createWithFormat("%d", last + 1)->getCString());

	auto btn = static_cast<gd::CCMenuItemSpriteExtra*>(static_cast<CCMenu*>(this->m_copyBtn->getParent())->getChildByTag(45001));
	if (btn) {
		btn->setVisible(true);
		btn->setEnabled(true);
	}

	updateInputNode();
}

void EditorUI::Callback::onAllEditorLayer(CCObject*) {
	from<int>(this->m_editorLayer, 0x1d8) = -1;
	this->m_currentGroupLabel->setString("All");
	auto btn = static_cast<gd::CCMenuItemSpriteExtra*>(static_cast<CCMenu*>(this->m_copyBtn->getParent())->getChildByTag(45001));
	if (btn) {
		btn->setVisible(false);
		btn->setEnabled(false);
	}

	updateInputNode();
}

bool __fastcall EditorUI::initH(gd::EditorUI* self, void*, gd::LevelEditorLayer* editorLayer) {
	editorUI = self;
	setting().groupIDOffset = 1;
	if (!EditorUI::init(self, editorLayer)) return false;

	auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();

	self->setVisible(!setting().onHideUI);

	loadClipboard(self);

	auto rightMenu = static_cast<CCMenu*>(self->m_copyBtn->getParent());

	self->m_groupPrevBtn->setPositionX(self->m_groupPrevBtn->getPositionX() - 10.f);
	self->m_groupNextBtn->setPositionX(self->m_groupNextBtn->getPositionX() - 10.f);
	self->m_guideToggle->setPositionX(self->m_guideToggle->getPositionX() - 20.f);
	self->m_currentGroupLabel->setPositionX(self->m_currentGroupLabel->getPositionX() - 10.f);

	auto onBaseLayerSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
	auto onBaseLayerBtn = gd::CCMenuItemSpriteExtra::create(onBaseLayerSpr, nullptr, self, menu_selector(EditorUI::Callback::onAllEditorLayer));
	onBaseLayerBtn->setTag(45001);
	onBaseLayerBtn->setPosition({ -90.f, -172.f });
	onBaseLayerSpr->setScale(.5f);
	onBaseLayerSpr->setOpacity(175);
	rightMenu->addChild(onBaseLayerBtn);
	self->m_hideableUIElement->addObject(onBaseLayerBtn);
	if (self->m_editorLayer->m_groupIDFilter == -1) {
		onBaseLayerBtn->setVisible(false);
		onBaseLayerBtn->setEnabled(false);
	}

	auto onFreeLayerSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_02_001.png");
	auto onFreeLayerBtn = gd::CCMenuItemSpriteExtra::create(onFreeLayerSpr, nullptr, self, menu_selector(EditorUI::Callback::onNextFreeEditorLayer));
	onFreeLayerBtn->setPosition({ 10.f, -172.f });
	onFreeLayerSpr->setScale(.5f);
	onFreeLayerSpr->setFlipX(true);
	onFreeLayerSpr->setOpacity(175);
	rightMenu->addChild(onFreeLayerBtn);
	self->m_hideableUIElement->addObject(onFreeLayerBtn);

	auto previewModePopup = extension::CCScale9Sprite::create("square02_small.png");
	previewModePopup->setScale(.5f);
	previewModePopup->setPosition({ director->getScreenLeft() + 10.f, director->getScreenTop() - 5.f });
	previewModePopup->setAnchorPoint({ 0.f, 1.f });
	previewModePopup->setContentSize({ 130.f, 40.f });
	previewModePopup->setOpacity(0);
	self->addChild(previewModePopup, 100, 1125);
	auto previewModeLabel = CCLabelBMFont::create("", "chatFont.fnt");
	previewModeLabel->setPosition({ previewModePopup->getContentSize() / 2.f });
	previewModeLabel->setColor({ 0, 255, 0 });
	previewModePopup->addChild(previewModeLabel);
	previewModeLabel->setOpacity(0);

	m_editorLayerInput = EditorLayerInput::create(self);
	m_editorLayerInput->setPosition(self->m_currentGroupLabel->getPosition());
	self->m_hideableUIElement->addObject(m_editorLayerInput);
	self->addChild(m_editorLayerInput);
	self->m_currentGroupLabel->setOpacity(0);

	auto onGoToLayerSpr = CCSprite::create("GJ_goToGroupBtn_001.png");
	onGoToLayerSpr->setScale(.75f);
	auto onGoToGroup = gd::CCMenuItemSpriteExtra::create(onGoToLayerSpr, self, menu_selector(EditorUI::Callback::onGoToLayer));
	onGoToGroup->setPosition(self->m_deselectBtn->getPositionX() - 84.f, self->m_deselectBtn->getPositionY() - 1.f);
	onGoToGroup->setVisible(false);
	onGoToGroup->setEnabled(false);
	rightMenu->addChild(onGoToGroup, 0, 45002);

	return true;
}

void __fastcall EditorUI::dtorH(gd::EditorUI* self) {
	saveClipboard(self);
	EditorUI::dtor(self);
	editorUI = nullptr;
	m_editorLayerInput = nullptr;
}

void __fastcall EditorUI::onCopyH(gd::EditorUI* self, void*, CCObject* obj) {
	if (setting().onRotateSaws) RotateSaws::stopRotations(self->m_editorLayer);
	EditorUI::onCopy(self, obj);
	if (setting().onRotateSaws) RotateSaws::beginRotations(self->m_editorLayer);
	clipboard::write(self->m_clipboard);
}

void __fastcall EditorUI::scrollWheelH(gd::EditorUI* _self, void* edx, float dy, float dx) { // From BEv4
	auto self = reinterpret_cast<gd::EditorUI*>(reinterpret_cast<uintptr_t>(_self) - 0xf8);
	
	float prevScale = self->m_editorLayer->m_objectLayer->getScale();
	auto swipeStart = self->m_editorLayer->m_objectLayer->convertToNodeSpace(self->m_swipeStartPos) * prevScale;

	auto kb = CCDirector::sharedDirector()->m_pKeyboardDispatcher;

	if (kb->getControlKeyPressed()) {
		auto zoom = self->m_editorLayer->m_objectLayer->getScale();
		zoom = static_cast<float>(std::pow(2.71828182845904523536, std::log(std::max(zoom, 0.001f)) - dy * 0.01f));
		zoom = std::max(zoom, 0.1f);
		zoom = std::min(zoom, 1000000.f);
		self->updateZoom(zoom);

		auto winSize = CCDirector::sharedDirector()->getWinSize();
		auto winSizePx = CCDirector::sharedDirector()->getOpenGLView()->getViewPortRect();
		auto ratio_w = winSize.width / winSizePx.size.width;
		auto ratio_h = winSize.height / winSizePx.size.height;

		auto mpos = CCDirector::sharedDirector()->getOpenGLView()->getMousePosition();
		mpos.y = winSizePx.size.height - mpos.y;

		mpos.x *= ratio_w;
		mpos.y *= ratio_h;

		mpos = mpos - winSize / 2.f;

		if (dy > 0.f) mpos = -mpos * .5f;

		self->m_editorLayer->m_objectLayer->setPosition(
			self->m_editorLayer->m_objectLayer->getPosition() - mpos / std::max(zoom, 5.f)
		);

		self->constrainGameLayerPosition();
		self->m_editorLayer->updateGroundWidth();
	}
	else if (kb->getShiftKeyPressed()) {
		self->m_editorLayer->m_objectLayer->setPositionX(self->m_editorLayer->m_objectLayer->getPositionX() - dy * 1.f);
	}
	else {
		EditorUI::scrollWheel(_self, dy, dx);
	}
}

void __fastcall EditorUI::moveObjectH(gd::EditorUI* self, void*, gd::GameObject* object, CCPoint to) {
	if (object == nullptr) return;
	EditorUI::moveObject(self, object, to);
}

void showEditorColorNotification() {
	auto gm = gd::GameManager::sharedState();
	auto popup = static_cast<extension::CCScale9Sprite*>(editorUI->getChildByTag(1125));

	if (!popup) return;

	auto label = static_cast<CCLabelBMFont*>(popup->getChildren()->objectAtIndex(1));

	if (!label) return;

	popup->setOpacity(100);
	popup->stopAllActions();
	popup->runAction(CCSequence::create(CCDelayTime::create(.5f), CCFadeTo::create(.5f, 0), nullptr));
	label->setOpacity(255);
	label->stopAllActions();
	label->runAction(CCSequence::create(CCDelayTime::create(.5f), CCFadeTo::create(.5f, 0), nullptr));

	if (gm->getGameVariable("0036")) {
		label->setString("Preview Mode: On");
	}
	else {
		label->setString("Preview Mode: Off");
	}
}

void toggleEditorColorMode() {
	gd::GameManager::sharedState()->toggleGameVariable("0036");
	gd::GameManager::sharedState()->getLevelEditorLayer()->updateEditorMode();
	showEditorColorNotification();
}

void __fastcall EditorUI::keyDownH(gd::EditorUI* _self, void*, enumKeyCodes key) {
	gd::EditorUI* self = reinterpret_cast<gd::EditorUI*>(reinterpret_cast<uintptr_t>(_self) - 0xf4);
	if (key == KEY_F3) toggleEditorColorMode();
	else if (key == KEY_Up) {
		std::cout << "Up" << std::endl;
		if (self->m_editorLayer->m_playerState == 1) {
			self->m_editorLayer->pushButton(1, true);
		}
	}
	else EditorUI::keyDown(_self, key);
}

void __fastcall EditorUI::keyUpH(gd::EditorUI* _self, void*, enumKeyCodes key) {
	gd::EditorUI* self = reinterpret_cast<gd::EditorUI*>(reinterpret_cast<uintptr_t>(_self) - 0xf4);
	if (key == KEY_Up) {
		if (self->m_editorLayer->m_playerState == 1) {
			self->m_editorLayer->releaseButton(1, true);
		}
	}
	else EditorUI::keyUp(_self, key);
}

void __fastcall EditorUI::selectObjectH(gd::EditorUI* self, void*, gd::GameObject* object) {
	auto selectedCustomMode = gd::GameManager::sharedState()->getIntGameVariable("0005");
	if (selectedCustomMode != 3) gd::GameManager::sharedState()->setIntGameVariable("0006", 0);
	int selectFilterObject = gd::GameManager::sharedState()->getIntGameVariable("0006");

	if ((selectFilterObject != 0) && setting().onSelectFilter) {
		if (object->m_objectID == selectFilterObject) return EditorUI::selectObject(self, object);
	}
	else {
		EditorUI::selectObject(self, object);
	}
}

void __fastcall EditorUI::selectObjectsH(gd::EditorUI* self, void*, CCArray* objects) {
	auto selectedCustomMode = gd::GameManager::sharedState()->getIntGameVariable("0005");
	if (selectedCustomMode != 3) gd::GameManager::sharedState()->setIntGameVariable("0006", 0);
	int selectFilterObject = gd::GameManager::sharedState()->getIntGameVariable("0006");

	if ((selectFilterObject != 0) && setting().onSelectFilter) {
		auto filteredObjects = CCArray::create();
		for (int i = 0; i < objects->count(); i++) {
			if (reinterpret_cast<gd::GameObject*>(objects->objectAtIndex(i))->m_objectID == selectFilterObject) {
				filteredObjects->addObject(objects->objectAtIndex(i));
			}
		}
		return EditorUI::selectObjects(self, filteredObjects);
	}
	else return EditorUI::selectObjects(self, objects);

	EditorUI::selectObjects(self, objects);
}

std::string typeToString(gd::GameObjectType type) {
	switch (type) {
	case gd::GameObjectType::kGameObjectTypeSolid: return "Solid"; break;
	case gd::GameObjectType::kGameObjectTypeHazard: return "Hazard"; break;
	case gd::GameObjectType::kGameObjectTypeInverseGravityPortal: return "Inverse Gravity Portal"; break;
	case gd::GameObjectType::kGameObjectTypeNormalGravityPortal: return "Normal Gravity Portal"; break;
	case gd::GameObjectType::kGameObjectTypeShipPortal: return "Ship Portal"; break;
	case gd::GameObjectType::kGameObjectTypeCubePortal: return "Cube Portal"; break;
	case gd::GameObjectType::kGameObjectTypeDecoration: return "Decoration"; break;
	case gd::GameObjectType::kGameObjectTypeYellowJumpPad: return "Yellow Jump Pad"; break;
	case gd::GameObjectType::kGameObjectTypePinkJumpPad: return "Pink Jump Pad"; break;
	case gd::GameObjectType::kGameObjectTypeGravityPad: return "Gravity Pad"; break;
	case gd::GameObjectType::kGameObjectTypeYellowJumpRing: return "Yellow Jump Ring"; break;
	case gd::GameObjectType::kGameObjectTypePinkJumpRing: return "Pink Jump Ring"; break;
	case gd::GameObjectType::kGameObjectTypeGravityRing: return "Gravity Ring"; break;
	case gd::GameObjectType::kGameObjectTypeInverseMirrorPortal: return "Inverse Mirror Portal"; break;
	case gd::GameObjectType::kGameObjectTypeNormalMirrorPortal: return "Normal Mirror Portal"; break;
	case gd::GameObjectType::kGameObjectTypeBallPortal: return "Ball Portal"; break;
	case gd::GameObjectType::kGameObjectTypeRegularSizePortal: return "Regular Size Portal"; break;
	case gd::GameObjectType::kGameObjectTypeMiniSizePortal: return "Mini Size Portal"; break;
	case gd::GameObjectType::kGameObjectTypeUfoPortal: return "UFO Portal"; break;
	case gd::GameObjectType::kGameObjectTypeModifier: return "Modifier"; break;
	case gd::GameObjectType::kGameObjectTypeBreakable: return "Breakable"; break;
	case gd::GameObjectType::kGameObjectTypeSecretCoin: return "Secret Coin"; break;
	case gd::GameObjectType::kGameObjectTypeDualPortal: return "Dual Portal"; break;
	case gd::GameObjectType::kGameObjectTypeSoloPortal: return "Solo Portal"; break;
	case gd::GameObjectType::kGameObjectTypeSlope: return "Slope"; break;
	case gd::GameObjectType::kGameObjectTypeWavePortal: return "Wave Portal"; break;
	case gd::GameObjectType::kGameObjectTypeRobotPortal: return "Robot Portal"; break;
	case gd::GameObjectType::kGameObjectTypeTeleportPortal: return "Teleport Portal"; break;
	case gd::GameObjectType::kGameObjectTypeGreenRing: return "Green Ring"; break;
	case gd::GameObjectType::kGameObjectTypeCollectible: return "Collectible"; break;
	case gd::GameObjectType::kGameObjectTypeUserCoin: return "User Coin"; break;
	default: return "Unknown"; break;
	}
}

void __fastcall EditorUI::updateObjectInfoLabelH(gd::EditorUI* self) {
	EditorUI::updateObjectInfoLabel(self);

	if (!setting().onExtraObjectInfo) return;

	if (self->m_selectedObject) { // taken from HJFod's BEv4
		auto baseColor = self->m_selectedObject->m_baseColor;
		auto detailColor = self->m_selectedObject->m_detailColor;

		std::stringstream ss;

		ss << self->m_objectInfo->getString();

		if (baseColor)
			ss << "HSV: "
			<< baseColor->hue << ","
			<< baseColor->saturation << (baseColor->saturationChecked ? " (a)" : "") << ","
			<< baseColor->brightness << (baseColor->brightnessChecked ? " (a)" : "") << "\n";

		if (detailColor)
			ss << "HSV 2: "
			<< detailColor->hue << ","
			<< detailColor->saturation << (detailColor->saturationChecked ? " (a)" : "") << ","
			<< detailColor->brightness << (detailColor->brightnessChecked ? " (a)" : "") << "\n";

		ss << "Rot: " << self->m_selectedObject->getRotation() << "\n";
		ss << "Scale: " << self->m_selectedObject->getScale() << "\n";
		ss << "X: " << self->m_selectedObject->getPositionX() << "\n";
		ss << "Y: " << self->m_selectedObject->getPositionY() << "\n";
		ss << "ID: " << self->m_selectedObject->m_objectID << "\n";
		ss << "Type: " << typeToString(static_cast<gd::GameObjectType>(self->m_selectedObject->m_objectType)) << "\n";
		ss << "Time: " << self->m_editorLayer->timeForXPos(self->m_selectedObject->getPositionX()) << "\n";
		ss << "Addr: 0x" << std::hex << reinterpret_cast<uintptr_t>(self->m_selectedObject) << std::dec << "\n";

		self->m_objectInfo->setString(ss.str().c_str());
	}

	if (self->m_selectedObjects->count() > 1) {
		std::stringstream ss;

		ss << self->m_objectInfo->getString();

		ss << "Objects: " << self->m_selectedObjects->count() << "\n";

		self->m_objectInfo->setString(ss.str().c_str());
	}
}

void __fastcall EditorUI::onGroupUpH(gd::EditorUI* self, void*, CCObject* obj) {
	EditorUI::onGroupUp(self, obj);
	auto btn = static_cast<gd::CCMenuItemSpriteExtra*>(static_cast<CCMenu*>(self->m_copyBtn->getParent())->getChildByTag(45001));
	if (btn) {
		btn->setVisible(true);
		btn->setEnabled(true);
	}

	updateInputNode();
}

void __fastcall EditorUI::onGroupDownH(gd::EditorUI* self, void*, CCObject* obj) {
	EditorUI::onGroupDown(self, obj);
	auto btn = static_cast<gd::CCMenuItemSpriteExtra*>(static_cast<CCMenu*>(self->m_copyBtn->getParent())->getChildByTag(45001));
	if (btn) {
		if (self->m_editorLayer->m_groupIDFilter == -1) {
			btn->setVisible(false);
			btn->setEnabled(false);
		}
	}

	updateInputNode();
}

void __fastcall EditorUI::moveObjectCallH(gd::EditorUI* self, void*, gd::EditCommand command) {
	EditorUI::moveObjectCall(self, command);
	self->updateObjectInfoLabel();
}

void __fastcall EditorUI::transformObjectCallH(gd::EditorUI* self, void*, gd::EditCommand command) {
	EditorUI::transformObjectCall(self, command);
	self->updateObjectInfoLabel();
	// if (setting().onHitboxBugFix) updateObjectHitbox(self);
}

bool m_isHoldingInEditor;

bool touchIntersectsInput(gd::CCTextInputNode* input, CCTouch* touch) {
	if (!input) return false;

	auto inputSize = CCSize({ input->getScaleX() * input->getContentSize().width, input->getScaleY() * input->getContentSize().height });

	auto rect = CCRect{
		input->getPositionX() - inputSize.width / 2,
		input->getPositionY() - inputSize.height / 2,
		inputSize.width,
		inputSize.height
	};

	if (!rect.containsPoint(input->getParent()->convertTouchToNodeSpace(touch))) {
		input->m_textField->detachWithIME();
		return false;
	}
	else
		return true;

	updateInputNode();
}

bool __fastcall EditorUI::ccTouchBeganH(gd::EditorUI* _self, void*, CCTouch* touch, CCEvent* event) {
	m_isHoldingInEditor = true;
	if (m_editorLayerInput) {
		if (touchIntersectsInput(m_editorLayerInput->m_input, touch)) return true;
	}
	return EditorUI::ccTouchBegan(_self, touch, event);
}

void __fastcall EditorUI::ccTouchEndedH(gd::EditorUI* self, void*, CCTouch* touch, CCEvent* event) {
	m_isHoldingInEditor = false;
	return EditorUI::ccTouchEnded(self, touch, event);
}

void __fastcall EditorUI::onPlaytestH(gd::EditorUI* self, void*, CCObject* obj) {
	if (!m_isHoldingInEditor) EditorUI::onPlaytest(self, obj);
}

void __fastcall EditorUI::onStopPlaytestH(gd::EditorUI* self, void*, CCObject* obj) {
	EditorUI::onStopPlaytest(self, obj);
}

void __fastcall EditorUI::angleChangedH(gd::EditorUI* _self, void*, float angle) {
	EditorUI::angleChanged(_self, angle);
	gd::EditorUI* self = reinterpret_cast<gd::EditorUI*>(reinterpret_cast<uintptr_t>(_self) - 0x120);
	// if (setting().onHitboxBugFix) updateObjectHitbox(self);
}

void __fastcall EditorUI::onPasteH(gd::EditorUI* self, void*, CCObject* sender) {
	EditorUI::onPaste(self, sender);
	// if (setting().onHitboxBugFix) updateObjectHitbox(self);
}

void __fastcall EditorUI::onDuplicateH(gd::EditorUI* self, void*, CCObject* sender) {
	if (setting().onRotateSaws) RotateSaws::stopRotations(self->m_editorLayer);
	EditorUI::onDuplicate(self, sender);
	if (setting().onRotateSaws) RotateSaws::beginRotations(self->m_editorLayer);
	// if (setting().onHitboxBugFix) updateObjectHitbox(self);
}

//CCArray* __fastcall EditorUI::pasteObjectsH(gd::EditorUI* self, void*, std::string objs) {
//	return EditorUI::pasteObjects(self, objs);
//	if (setting().onHitboxBugFix) updateObjectHitbox(self);
//}

void __fastcall EditorUI::onCreateObjectH(gd::EditorUI* self, void*, int id) {
	EditorUI::onCreateObject(self, id);
	// if (setting().onHitboxBugFix) updateObjectHitbox(self);
}

void __fastcall EditorUI::updateButtonsH(gd::EditorUI* self) {
	EditorUI::updateButtons(self);
	auto btn = static_cast<gd::CCMenuItemSpriteExtra*>(static_cast<CCMenu*>(self->m_copyBtn->getParent())->getChildByTag(45001));
	if (btn) {
		if (self->m_editorLayer->m_groupIDFilter == -1) {
			btn->setVisible(false);
			btn->setEnabled(false);
		}
	}

	auto gtg = static_cast<gd::CCMenuItemSpriteExtra*>(static_cast<CCMenu*>(self->m_copyBtn->getParent())->getChildByTag(45002));
	if (gtg) {
		gtg->setVisible(self->getSelectedObjects()->count() == 1);
		gtg->setEnabled(self->getSelectedObjects()->count() == 1);
	}
}

void __fastcall EditorUI::scaleObjectsH(gd::EditorUI* self, void*, CCArray* objs, CCPoint center) { // HJFod / Alk1m123 (altalk23)
	float scale;
	__asm movss scale, xmm2;
	CCObject* obj;

	if (scale > -.01f && scale < .01f)
		scale = std::copysign(.01f, scale);

	CCARRAY_FOREACH(objs, obj) {
		auto object = reinterpret_cast<gd::GameObject*>(obj);
		auto pos = object->getPosition();
		float newScale = from<float>(object, 0x394) * scale;
		float newMultiplier = newScale / object->m_scale;
		auto newPos = (pos - center) * newMultiplier + (center - pos);

		object->m_scale = newScale;
		object->setRScale(1.f);
		from<bool>(object, 0x274) = true;
		object->m_isObjectRectDirty = true;

		self->moveObject(object, newPos);
	}
}

void __fastcall GJScaleControl::ccTouchMovedH(gd::GJScaleControl* self, void*, CCTouch* touch, CCEvent* event) {
	GJScaleControl::ccTouchMoved(self, touch, event);
	gd::GameManager::sharedState()->getLevelEditorLayer()->m_editorUI->updateObjectInfoLabel();
}

CCArray* objArr;

void addObject(int id) {
	auto obj = editorUI->getCreateBtn(id, 4);
	objArr->addObject(obj);
}

bool __fastcall EditButtonBar::initH(gd::EditButtonBar* self, void*, CCArray* objs, int page, bool isObjects, int rows, int columns, CCPoint pos) {
	objArr = objs;

	if (editorUI && setting().onUnusedObjects && isObjects) {
		switch (page)
		{
		case 0:
			addObject(160);
			addObject(161);
			addObject(162);
			addObject(163);
			addObject(164);
			addObject(165);
			addObject(166);
			addObject(167);
			addObject(168);
			addObject(169);
			addObject(193);
			addObject(737);
			break;
		case 3:
			addObject(371);
			addObject(372);
			addObject(373);
			addObject(374);
			addObject(886);
			addObject(887);
			break;
		case 8:
			addObject(461);
			addObject(462);
			addObject(463);
			addObject(464);
			addObject(465);
			addObject(466);
			addObject(725);
			break;
		case 11:
			addObject(55);
			addObject(34);
			break;
		default:
			break;
		}
	}

	if (!EditButtonBar::init(self, objs, page, isObjects, rows, columns, pos)) return false;
	return true;
}

void EditorUI::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x5d3e0), EditorUI::initH, reinterpret_cast<void**>(&EditorUI::init));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6cf60), EditorUI::createMoveMenuH, reinterpret_cast<void**>(&EditorUI::createMoveMenu));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6def0), EditorUI::moveForCommandH, reinterpret_cast<void**>(&EditorUI::moveForCommand));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6e810), EditorUI::transformObjectH, reinterpret_cast<void**>(&EditorUI::transformObject));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6bad0), EditorUI::onCopyH, reinterpret_cast<void**>(&EditorUI::onCopy));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x5d170), EditorUI::dtorH, reinterpret_cast<void**>(&EditorUI::dtor));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x72960), EditorUI::scrollWheelH, reinterpret_cast<void**>(&EditorUI::scrollWheel));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6e330), EditorUI::moveObjectH, reinterpret_cast<void**>(&EditorUI::moveObject));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x71ad0), EditorUI::keyDownH, reinterpret_cast<void**>(&EditorUI::keyDown));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x72910), EditorUI::keyUpH, reinterpret_cast<void**>(&EditorUI::keyUp));

	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6a540), EditorUI::selectObjectH, reinterpret_cast<void**>(&EditorUI::selectObject));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6a5a0), EditorUI::selectObjectsH, reinterpret_cast<void**>(&EditorUI::selectObjects));

	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x5fb70), EditorUI::updateObjectInfoLabelH, reinterpret_cast<void**>(&EditorUI::updateObjectInfoLabel));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6de70), EditorUI::onGroupDownH, reinterpret_cast<void**>(&EditorUI::onGroupDown));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6de00), EditorUI::onGroupUpH, reinterpret_cast<void**>(&EditorUI::onGroupUp));

	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6e1b0), EditorUI::moveObjectCallH, reinterpret_cast<void**>(&EditorUI::moveObjectCall));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6e540), EditorUI::transformObjectCallH, reinterpret_cast<void**>(&EditorUI::transformObjectCall));

	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x74780), GJScaleControl::ccTouchMovedH, reinterpret_cast<void**>(&GJScaleControl::ccTouchMoved));

	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x70a20), EditorUI::ccTouchBeganH, reinterpret_cast<void**>(&EditorUI::ccTouchBegan));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x71340), EditorUI::ccTouchEndedH, reinterpret_cast<void**>(&EditorUI::ccTouchEnded));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6b200), EditorUI::onPlaytestH, reinterpret_cast<void**>(&EditorUI::onPlaytest));

	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x70390), EditorUI::angleChangedH, reinterpret_cast<void**>(&EditorUI::angleChanged));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6bbd0), EditorUI::onPasteH, reinterpret_cast<void**>(&EditorUI::onPaste));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6b830), EditorUI::onDuplicateH, reinterpret_cast<void**>(&EditorUI::onDuplicate));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x699c0), EditorUI::onCreateObjectH, reinterpret_cast<void**>(&EditorUI::onCreateObject));

	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x5ed00), EditorUI::updateButtonsH, reinterpret_cast<void**>(&EditorUI::updateButtons));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6f6e0), EditorUI::scaleObjectsH, reinterpret_cast<void**>(&EditorUI::scaleObjects));

	//MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6bd20), EditorUI::pasteObjectsH, reinterpret_cast<void**>(&EditorUI::pasteObjects));

	//MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x6cbf0), EditorUI::toggleSpecialEditButtonsH, reinterpret_cast<void**>(&EditorUI::toggleSpecialEditButtons));
}

void EditButtonBar::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x55fd0), EditButtonBar::initH, reinterpret_cast<void**>(&EditButtonBar::init));
}