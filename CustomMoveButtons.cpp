#include "EditorUI.h"
#include "moveForCommand.h"
#include "CircleToolPopup.h"

void EditorUI::Callback::onCircleTool(CCObject*) {
	if (this->getSelectedObjects()->count())
		CircleToolPopup::create()->show();
	else
		gd::FLAlertLayer::create(nullptr, "Circle Tool", "OK", nullptr, "You must first select the objects.")->show();
}

void __fastcall EditorUI::createMoveMenuH(gd::EditorUI* self) {
	EditorUI::createMoveMenu(self);

	auto halfLabel = CCLabelBMFont::create("1/2", "bigFont.fnt");
	halfLabel->setScale(0.5f);
	halfLabel->setPosition({ 20.f, 10.f });

	auto halfUp = self->getSpriteButton("edit_upBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(halfUp->getChildren()->objectAtIndex(0))->addChild(halfLabel, 5);
	halfUp->setTag(static_cast<int>(moveForCommand::kEditCommandHalfUp));
	self->m_moveButtonBar->m_buttonArray->addObject(halfUp);

	auto halfDown = self->getSpriteButton("edit_downBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(halfDown->getChildren()->objectAtIndex(0))->addChild(halfLabel, 5);
	halfDown->setTag(static_cast<int>(moveForCommand::kEditCommandHalfDown));
	self->m_moveButtonBar->m_buttonArray->addObject(halfDown);

	auto halfLeft = self->getSpriteButton("edit_leftBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(halfLeft->getChildren()->objectAtIndex(0))->addChild(halfLabel, 5);
	halfLeft->setTag(static_cast<int>(moveForCommand::kEditCommandHalfLeft));
	self->m_moveButtonBar->m_buttonArray->addObject(halfLeft);

	auto halfRight = self->getSpriteButton("edit_rightBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(halfRight->getChildren()->objectAtIndex(0))->addChild(halfLabel, 5);
	halfRight->setTag(static_cast<int>(moveForCommand::kEditCommandHalfRight));	
	self->m_moveButtonBar->m_buttonArray->addObject(halfRight);

	auto quarterLabel = CCLabelBMFont::create("1/4", "bigFont.fnt");
	quarterLabel->setScale(0.5f);
	quarterLabel->setPosition({ 20.f, 10.f });

	auto quarterUp = self->getSpriteButton("edit_upBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(quarterUp->getChildren()->objectAtIndex(0))->addChild(quarterLabel, 5);
	quarterUp->setTag(static_cast<int>(moveForCommand::kEditCommandQuarterUp));
	self->m_moveButtonBar->m_buttonArray->addObject(quarterUp);

	auto quarterDown = self->getSpriteButton("edit_downBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(quarterDown->getChildren()->objectAtIndex(0))->addChild(quarterLabel, 5);
	quarterDown->setTag(static_cast<int>(moveForCommand::kEditCommandQuarterDown));
	self->m_moveButtonBar->m_buttonArray->addObject(quarterDown);

	auto quarterLeft = self->getSpriteButton("edit_leftBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(quarterLeft->getChildren()->objectAtIndex(0))->addChild(quarterLabel, 5);
	quarterLeft->setTag(static_cast<int>(moveForCommand::kEditCommandQuarterLeft));
	self->m_moveButtonBar->m_buttonArray->addObject(quarterLeft);

	auto quarterRight = self->getSpriteButton("edit_rightBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(quarterRight->getChildren()->objectAtIndex(0))->addChild(quarterLabel, 5);
	quarterRight->setTag(static_cast<int>(moveForCommand::kEditCommandQuarterRight));
	self->m_moveButtonBar->m_buttonArray->addObject(quarterRight);

	auto eightLabel = CCLabelBMFont::create("1/8", "bigFont.fnt");
	eightLabel->setScale(0.5f);
	eightLabel->setPosition({ 20.f, 10.f });

	auto eightUp = self->getSpriteButton("edit_upBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(eightUp->getChildren()->objectAtIndex(0))->addChild(eightLabel, 5);
	eightUp->setTag(static_cast<int>(moveForCommand::kEditCommandEightUp));
	self->m_moveButtonBar->m_buttonArray->addObject(eightUp);

	auto eightDown = self->getSpriteButton("edit_downBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(eightDown->getChildren()->objectAtIndex(0))->addChild(eightLabel, 5);
	eightDown->setTag(static_cast<int>(moveForCommand::kEditCommandEightDown));
	self->m_moveButtonBar->m_buttonArray->addObject(eightDown);

	auto eightLeft = self->getSpriteButton("edit_leftBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(eightLeft->getChildren()->objectAtIndex(0))->addChild(eightLabel, 5);
	eightLeft->setTag(static_cast<int>(moveForCommand::kEditCommandEightLeft));
	self->m_moveButtonBar->m_buttonArray->addObject(eightLeft);

	auto eightRight = self->getSpriteButton("edit_rightBtn2_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(eightRight->getChildren()->objectAtIndex(0))->addChild(eightLabel, 5);
	eightRight->setTag(static_cast<int>(moveForCommand::kEditCommandEightRight));
	self->m_moveButtonBar->m_buttonArray->addObject(eightRight);

	auto unitLabel = CCLabelBMFont::create("Unit", "bigFont.fnt");
	unitLabel->setScale(0.5f);
	unitLabel->setPosition({ 20.f, 10.f });

	auto unitUp = self->getSpriteButton("edit_upBtn_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(unitUp->getChildren()->objectAtIndex(0))->addChild(unitLabel, 5);
	unitUp->setTag(static_cast<int>(moveForCommand::kEditCommandUnitUp));
	self->m_moveButtonBar->m_buttonArray->addObject(unitUp);

	auto unitDown = self->getSpriteButton("edit_downBtn_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(unitDown->getChildren()->objectAtIndex(0))->addChild(unitLabel, 5);
	unitDown->setTag(static_cast<int>(moveForCommand::kEditCommandUnitDown));
	self->m_moveButtonBar->m_buttonArray->addObject(unitDown);

	auto unitLeft = self->getSpriteButton("edit_leftBtn_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(unitLeft->getChildren()->objectAtIndex(0))->addChild(unitLabel, 5);
	unitLeft->setTag(static_cast<int>(moveForCommand::kEditCommandUnitLeft));
	self->m_moveButtonBar->m_buttonArray->addObject(unitLeft);

	auto unitRight = self->getSpriteButton("edit_rightBtn_001.png", menu_selector(EditorUI::Callback::onCustomMoveObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(unitRight->getChildren()->objectAtIndex(0))->addChild(unitLabel, 5);
	unitRight->setTag(static_cast<int>(moveForCommand::kEditCommandUnitRight));
	self->m_moveButtonBar->m_buttonArray->addObject(unitRight);

	auto rotate265Label = CCLabelBMFont::create("26", "bigFont.fnt");
	rotate265Label->setScale(.45f);
	rotate265Label->setPosition({ 20.f, 22.f });

	auto rotate265CW = self->getSpriteButton("edit_cwBtn_001.png", menu_selector(EditorUI::Callback::onCustomTransformObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(rotate265CW->getChildren()->objectAtIndex(0))->addChild(rotate265Label, 5);
	rotate265CW->setTag(static_cast<int>(rotationForCommand::kEditCommandRotate265CW));
	self->m_moveButtonBar->m_buttonArray->addObject(rotate265CW);

	auto rotate265CCW = self->getSpriteButton("edit_ccwBtn_001.png", menu_selector(EditorUI::Callback::onCustomTransformObject), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(rotate265CCW->getChildren()->objectAtIndex(0))->addChild(rotate265Label, 5);
	rotate265CCW->setTag(static_cast<int>(rotationForCommand::kEditCommandRotate265CCW));
	self->m_moveButtonBar->m_buttonArray->addObject(rotate265CCW);

	auto circleToolLabel = CCLabelBMFont::create("Circle\nTool", "bigFont.fnt", 0.f, CCTextAlignment::kCCTextAlignmentCenter);
	circleToolLabel->setScale(.35f);
	circleToolLabel->setPosition({ 20.f, 22.f });
	auto circleTool = self->getSpriteButton("edit_ccwBtn_001.png", menu_selector(EditorUI::Callback::onCircleTool), nullptr, .9f);
	static_cast<gd::ButtonSprite*>(circleTool->getChildren()->objectAtIndex(0))->addChild(circleToolLabel, 5);
	self->m_moveButtonBar->m_buttonArray->addObject(circleTool);

	auto rows = gd::GameManager::sharedState()->getIntGameVariable("0049");
	auto cols = gd::GameManager::sharedState()->getIntGameVariable("0050");
	self->m_moveButtonBar->loadFromItems(self->m_moveButtonBar->m_buttonArray, rows, cols, self->m_moveButtonBar->m_idk);
}

CCPoint* __fastcall EditorUI::moveForCommandH(gd::EditorUI* self, void* edx, CCPoint* pos, gd::EditCommand com) {
	float gridSize = self->m_activeGridSize;
	switch (com) // Taken from HJFod https://github.com/HJfod/BetterEdit/blob/v4/tools/EditTab/moveForCommand.cpp
	{
	case moveForCommand::kEditCommandHalfLeft:
		*pos = CCPoint(-1.f / 2.f, 0.f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandHalfRight:
		*pos = CCPoint(1.f / 2.f, 0.0f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandHalfUp:
		*pos = CCPoint(0.f, 1.f / 2.f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandHalfDown:
		*pos = CCPoint(0.f, -1.f / 2.f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandQuarterLeft:
		*pos = CCPoint(-1.f / 4.f, 0.f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandQuarterRight:
		*pos = CCPoint(1.f / 4.f, 0.f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandQuarterUp:
		*pos = CCPoint(0.f, 1.f / 4.f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandQuarterDown:
		*pos = CCPoint(0.f, -1.f / 4.f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandEightLeft:
		*pos = CCPoint(-1.f / 8.f, 0.f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandEightRight:
		*pos = CCPoint(1.f / 8.f, 0.f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandEightUp:
		*pos = CCPoint(0.f, 1.f / 8.f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandEightDown:
		*pos = CCPoint(0.f, -1.f / 8.f) * gridSize;
		return pos;
		break;
	case moveForCommand::kEditCommandUnitLeft:
		*pos = CCPoint(-.1f, 0.f);
		return pos;
		break;
	case moveForCommand::kEditCommandUnitRight:
		*pos = CCPoint(.1f, 0.f);
		return pos;
		break;
	case moveForCommand::kEditCommandUnitUp:
		*pos = CCPoint(0.f, .1f);
		return pos;
		break;
	case moveForCommand::kEditCommandUnitDown:
		*pos = CCPoint(0.f, -.1f);
		return pos;
		break;
	}

	return EditorUI::moveForCommand(self, pos, com);
}

void __fastcall EditorUI::transformObjectH(gd::EditorUI* self, void* edx, gd::GameObject* obj, gd::EditCommand com, bool idk) {
	CCArray* selectedObjects = self->getSelectedObjects();
	auto selectedObjCount = selectedObjects->count();
	if (obj->canRotateFree()) {
		switch (com)
		{
		case rotationForCommand::kEditCommandRotate265CW:
			self->rotateObjects(selectedObjects, (26.f / selectedObjCount), { 0,0 });
			break;
		case rotationForCommand::kEditCommandRotate265CCW:
			self->rotateObjects(selectedObjects, -(26.f / selectedObjCount), { 0,0 });
			break;
		}
	}

	return EditorUI::transformObject(self, obj, com, idk);
}

gd::GameObject* m_obj;

void __fastcall EditorUI::toggleSpecialEditButtonsH(gd::EditorUI* self) {
	return EditorUI::toggleSpecialEditButtons(self);
}

void EditorUI::Callback::onCustomMoveObject(CCObject* obj) {
	auto editorUI = gd::GameManager::sharedState()->getLevelEditorLayer()->m_editorUI;
	if (editorUI) {
		auto buttonTag = static_cast<gd::CCMenuItemSpriteExtra*>(obj)->getTag();
		editorUI->moveObjectCall(static_cast<gd::EditCommand>(buttonTag));
	}
}

void EditorUI::Callback::onCustomTransformObject(CCObject* obj) {
	auto editorUI = gd::GameManager::sharedState()->getLevelEditorLayer()->m_editorUI;
	if (editorUI) {
		auto buttonTag = static_cast<gd::CCMenuItemSpriteExtra*>(obj)->getTag();
		editorUI->transformObjectCall(static_cast<gd::EditCommand>(buttonTag));
	}
}