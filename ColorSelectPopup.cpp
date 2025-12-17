#include "ColorSelectPopup.h"
#include "RGBColorInputWidget.hpp"
#include "ColorLiveEditPopup.h"
#include "state.h"

RGBColorInputWidget* m_colorInputWidget{ nullptr };

void doDefaultAction(gd::ColorSelectPopup* self, gd::GJEffectManager* effectManager, int colorID) {
	auto colorAction = effectManager->getColorAction(colorID);
	if (colorAction) {
		self->m_colorPicker->setColorValue(colorAction->m_fromColor);

		if (self->m_isBlending != colorAction->m_blending)
			self->onToggleTintMode(nullptr);

		self->m_opacity = colorAction->m_fromOpacity;

		self->updateOpacityLabel();

		if (self->m_opacitySlider)
			self->m_opacitySlider->setValue(self->m_opacity);
	}
}

void ColorSelectPopup::Callback::onDefault(CCObject* obj) {
	auto editorLayer = gd::GameManager::sharedState()->getLevelEditorLayer();
	if (!editorLayer) return;

	auto effectManager = editorLayer->m_levelSettings->m_effectManager;

	switch (this->m_targetObject->m_objectID)
	{
	case 29:
		doDefaultAction(this, effectManager, 1000); break;
	case 30:
		doDefaultAction(this, effectManager, 1001); break;
	case 900:
		doDefaultAction(this, effectManager, 1009); break;
	case 915:
		doDefaultAction(this, effectManager, 1002); break;
	case 105:
		doDefaultAction(this, effectManager, 1004); break;
	case 744:
		doDefaultAction(this, effectManager, 1003); break;
	case 899:
		doDefaultAction(this, effectManager, this->m_colorID); break;
	default: return;
		break;
	}
}

void ColorSelectPopup::Callback::onLiveEdit(CCObject*) {
	//gd::GameManager::sharedState()->getLevelEditorLayer()->m_editorUI->addChild(ColorLiveEditPopup::create(this->m_colorAction->m_colorID));
}

bool __fastcall ColorSelectPopup::initH(gd::ColorSelectPopup* self, void*, gd::GameObject* obj, CCArray* objs, void* colorAction) {
	if (!ColorSelectPopup::init(self, obj, objs, colorAction)) return false;

	auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();

	m_colorInputWidget = RGBColorInputWidget::create(self);
	self->getLayer()->addChild(m_colorInputWidget);

	m_colorInputWidget->setPosition({ winSize.width / 2.f - 155.f, winSize.height / 2.f + 34.f });

	m_colorInputWidget->setVisible(!from<bool>(self, 0x271));

	if (setting().onDeveloperMode) {
		auto liveEditSpr = extension::CCScale9Sprite::create("square02_small.png");
		liveEditSpr->setOpacity(100);
		liveEditSpr->setScale(.3f);
		auto liveEditSprPlus = CCLabelBMFont::create("+", "bigFont.fnt");
		liveEditSprPlus->setPosition(liveEditSpr->getContentSize().width / 2.f + 2.f, liveEditSpr->getContentSize().height / 2.f + 2.f);
		liveEditSprPlus->setScale(1.4f);
		liveEditSpr->addChild(liveEditSprPlus);

		auto onLiveEdit = gd::CCMenuItemSpriteExtra::create(liveEditSpr, self, menu_selector(ColorSelectPopup::Callback::onLiveEdit));
		onLiveEdit->setPosition(90.f, 260.f);
		self->m_pButtonMenu->addChild(onLiveEdit, 0, 9807);
	}

	if (self->m_fadeTimeSlider && self->m_targetObject) {
		auto onDefaultSpr = gd::ButtonSprite::create("Default", 0x28, false, "goldFont.fnt", "GJ_button_04.png", 30.f, .6f);
		auto onDefault = gd::CCMenuItemSpriteExtra::create(onDefaultSpr, self, menu_selector(ColorSelectPopup::Callback::onDefault));
		onDefault->setPosition(190.f, 178.f);
		self->m_pButtonMenu->addChild(onDefault);
	}

	return true;
}

void __fastcall ColorSelectPopup::colorValueChangedH(gd::ColorSelectPopup* self, void*, ccColor3B color) {
	ColorSelectPopup::colorValueChanged(self, color);
	if (m_colorInputWidget != nullptr)
		m_colorInputWidget->update_labels(true, true);
}

void __fastcall ColorSelectPopup::closeColorSelectH(gd::ColorSelectPopup* self, void*, CCObject* obj) {
	ColorSelectPopup::closeColorSelect(self, obj);
	m_colorInputWidget = nullptr;
}

void __fastcall ColorSelectPopup::updateCopyColorTextInputLabelH(gd::ColorSelectPopup* self) {
	ColorSelectPopup::updateCopyColorTextInputLabel(self);
	if (m_colorInputWidget != nullptr)
		m_colorInputWidget->setVisible(!from<bool>(self, 0x271));
}

bool __fastcall SetupPulsePopup::initH(gd::SetupPulsePopup* self, void*, gd::EffectGameObject* obj, CCArray* objs) {
	if (!SetupPulsePopup::init(self, obj, objs)) return false;

	auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();

	m_colorInputWidget = RGBColorInputWidget::create(reinterpret_cast<gd::ColorSelectPopup*>(self));
	self->getLayer()->addChild(m_colorInputWidget);

	self->m_colorPicker->setPositionX(self->m_colorPicker->getPositionX() + 3.7f);
	m_colorInputWidget->setPosition({ winSize.width / 2.f - 132.f, winSize.height / 2.f + 32.f });

	auto square_width = from<CCSprite*>(self, 0x208)->getContentSize().width * from<CCSprite*>(self, 0x208)->getScaleX();
	auto x = m_colorInputWidget->getPositionX() - square_width / 2.f;

	from<CCSprite*>(self, 0x208)->setPosition({ x + 20.0f, winSize.height / 2.f + 85.f });
	from<CCSprite*>(self, 0x20c)->setPosition({ x + 20.0f + square_width, winSize.height / 2.f + 85.f });

	m_colorInputWidget->setVisible(from<int>(self, 0x274) == 0);

	return true;
}

void __fastcall SetupPulsePopup::colorValueChangedH(gd::SetupPulsePopup* self) {
	SetupPulsePopup::colorValueChanged(self);
	if (m_colorInputWidget != nullptr)
		m_colorInputWidget->update_labels(true, true);
}

void __fastcall SetupPulsePopup::closeColorSelectH(gd::SetupPulsePopup* self, void*, CCObject* obj) {
	SetupPulsePopup::closeColorSelect(self, obj);
	m_colorInputWidget = nullptr;
}

void __fastcall SetupPulsePopup::updatePulseModeH(gd::SetupPulsePopup* self) {
	SetupPulsePopup::updatePulseMode(self);
	if (m_colorInputWidget != nullptr)
		m_colorInputWidget->setVisible(from<int>(self, 0x274) == 0);
}

void ColorSelectPopup::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x39e40), ColorSelectPopup::initH, reinterpret_cast<void**>(&ColorSelectPopup::init));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x3cf90), ColorSelectPopup::colorValueChangedH, reinterpret_cast<void**>(&ColorSelectPopup::colorValueChanged));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x3ce80), ColorSelectPopup::closeColorSelectH, reinterpret_cast<void**>(&ColorSelectPopup::closeColorSelect));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x3d910), ColorSelectPopup::updateCopyColorTextInputLabelH, reinterpret_cast<void**>(&ColorSelectPopup::updateCopyColorTextInputLabel));
}

void SetupPulsePopup::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x191e20), SetupPulsePopup::initH, reinterpret_cast<void**>(&SetupPulsePopup::init));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x1957b0), SetupPulsePopup::closeColorSelectH, reinterpret_cast<void**>(&SetupPulsePopup::closeColorSelect));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x195940), SetupPulsePopup::colorValueChangedH, reinterpret_cast<void**>(&SetupPulsePopup::colorValueChanged));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x195f70), SetupPulsePopup::updatePulseModeH, reinterpret_cast<void**>(&SetupPulsePopup::updatePulseMode));
}