#include "SetGroupIDLayer.h"
#include "utils.hpp"
#include "state.h"

class OffsetGroupInput : public cocos2d::CCLayer, gd::TextInputDelegate {
protected:
	bool init() {
		if (!CCLayer::init()) return false;

		auto textInput = gd::CCTextInputNode::create("ID", this, "bigFont.fnt", 28.f, 18.f);
		textInput->setMaxLabelLength(3);
		textInput->setMaxLabelWidth(28.f);
		textInput->setAllowedChars("0123456789");
		textInput->setLabelPlaceholderColor({ 120, 170, 240 });
		textInput->setLabelPlaceholderScale(.5f);
		textInput->setMaxLabelScale(.5f);
		textInput->setDelegate(this);
		textInput->setString(std::to_string(setting().groupIDOffset).c_str());
		this->addChild(textInput, 20);

		return true;
	}

	virtual void textChanged(gd::CCTextInputNode* input) override {
		setting().groupIDOffset = std::atoi(input->getString());
		
		auto bytes = intToBytes(setting().groupIDOffset);
		bytes.insert(bytes.begin(), 0xbe);

		sequence_patch(uint32_t(gd::base + 0xf2f7f), bytes);

		std::cout << "Offset: " << setting().groupIDOffset << std::endl;
	}

public:
	static OffsetGroupInput* create() {
		OffsetGroupInput* ret = new OffsetGroupInput();
		if (ret && ret->init()) {
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
};

class CustomInputs : public CCLayer, gd::TextInputDelegate {
protected:
	gd::SetGroupIDLayer* m_parent;

	bool init(gd::SetGroupIDLayer* parent) {
		m_parent = parent;
		if (!CCLayer::init()) return false;

		auto director = CCDirector::sharedDirector();
		auto winSize = director->getWinSize();

		auto elBg = extension::CCScale9Sprite::create("square02_small.png");
		elBg->setContentSize({ 50.f, 30.f });
		elBg->setOpacity(100);
		elBg->setPositionX(-125);
		this->addChild(elBg, -1);

		auto el2Bg = extension::CCScale9Sprite::create("square02_small.png");
		el2Bg->setContentSize({ 50.f, 30.f });
		el2Bg->setOpacity(100);
		this->addChild(el2Bg, -1);

		auto zoBg = extension::CCScale9Sprite::create("square02_small.png");
		zoBg->setContentSize({ 50.f, 30.f });
		zoBg->setOpacity(100);
		zoBg->setPositionX(125);
		this->addChild(zoBg, -1);

		m_editorLayerInput = gd::CCTextInputNode::create("EL", this, "bigFont.fnt", 45.f, 30.f);
		m_editorLayerInput->setDelegate(this);
		m_editorLayerInput->setMaxLabelLength(3);
		m_editorLayerInput->setAllowedChars("0123456789");
		m_editorLayerInput->setLabelPlaceholderColor(ccc3(150, 150, 150));
		m_editorLayerInput->setLabelPlaceholderScale(.6f);
		m_editorLayerInput->setPositionX(-125);
		m_editorLayerInput->setMaxLabelScale(.6f);
		this->addChild(m_editorLayerInput);

		m_editorLayer2Input = gd::CCTextInputNode::create("EL2", this, "bigFont.fnt", 45.f, 30.f);
		m_editorLayer2Input->setDelegate(this);
		m_editorLayer2Input->setMaxLabelLength(3);
		m_editorLayer2Input->setAllowedChars("0123456789");
		m_editorLayer2Input->setLabelPlaceholderColor(ccc3(150, 150, 150));
		m_editorLayer2Input->setLabelPlaceholderScale(.6f);
		m_editorLayer2Input->setMaxLabelScale(.6f);
		this->addChild(m_editorLayer2Input);

		m_zOrderInput = gd::CCTextInputNode::create("Z", this, "bigFont.fnt", 45.f, 30.f);
		m_zOrderInput->setDelegate(this);
		m_zOrderInput->setMaxLabelLength(4);
		m_zOrderInput->setAllowedChars("-0123456789");
		m_zOrderInput->setLabelPlaceholderColor(ccc3(150, 150, 150));
		m_zOrderInput->setPositionX(125);
		m_zOrderInput->setLabelPlaceholderScale(.6f);
		m_zOrderInput->setMaxLabelScale(.6f);
		this->addChild(m_zOrderInput);

		this->updateInputNode();

		return true;
	}

	virtual void textChanged(gd::CCTextInputNode* input) override {
		if (input == m_editorLayerInput) {
			if (!(std::string(input->getString()).find("Mixed") != std::string::npos)) {
				m_parent->m_editorLayer = std::atoi(input->getString());
				m_parent->updateEditorLayerID();
			}
		}
		else if (input == m_editorLayer2Input) {
			if (!(std::string(input->getString()).find("Mixed") != std::string::npos)) {
				m_parent->m_editorLayer2 = std::atoi(input->getString());
				m_parent->updateEditorLayerID2();
			}
		}
		else if (input == m_zOrderInput) {
			if (!(std::string(input->getString()).find("Mixed") != std::string::npos)) {
				m_parent->m_zOrder = std::atoi(input->getString());
				m_parent->updateZOrder();
			}
		}
	}

public:
	gd::CCTextInputNode* m_editorLayerInput;
	gd::CCTextInputNode* m_editorLayer2Input;
	gd::CCTextInputNode* m_zOrderInput;

	void updateInputNode() {
		if (m_parent->m_editorLayer == -1) m_editorLayerInput->setString("Mixed");
		else m_editorLayerInput->setString(std::to_string(m_parent->m_editorLayer).c_str());

		if (m_parent->m_editorLayer2 == -1) m_editorLayer2Input->setString("Mixed");
		else m_editorLayer2Input->setString(std::to_string(m_parent->m_editorLayer2).c_str());

		if (m_parent->m_zOrder == -1000) m_zOrderInput->setString("Mixed");
		else m_zOrderInput->setString(std::to_string(m_parent->m_zOrder).c_str());
	}

	static CustomInputs* create(gd::SetGroupIDLayer* parent) {
		CustomInputs* ret = new CustomInputs();
		if (ret && ret->init(parent)) {
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
};

bool __fastcall SetGroupIDLayer::initH(gd::SetGroupIDLayer* self, void*, gd::GameObject* obj, CCArray* objs) {
	bool result = SetGroupIDLayer::init(self, obj, objs);

	auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();

	auto offsetInputBG = extension::CCScale9Sprite::create("square02_small.png");
	offsetInputBG->setOpacity(100);
	offsetInputBG->setScale(.7f);
	offsetInputBG->setContentSize({ 45.f, 28.f });
	offsetInputBG->setPosition(winSize.width / 2.f - 83.f, winSize.height / 2.f + 43.f);
	self->m_pLayer->addChild(offsetInputBG, -1);

	auto offsetLabel = CCLabelBMFont::create("Offset", "goldFont.fnt");
	offsetLabel->setScale(.4f);
	offsetLabel->setPosition(offsetInputBG->getPositionX(), offsetInputBG->getPositionY() + 17.f);
	self->m_pLayer->addChild(offsetLabel);

	auto offsetInput = OffsetGroupInput::create();
	offsetInput->setPosition(offsetInputBG->getPosition());
	self->m_pLayer->addChild(offsetInput);

	auto customInputs = CustomInputs::create(self);
	customInputs->setPosition(self->m_editorLayer2Label->getPosition());
	customInputs->setTag(8590);
	self->m_pLayer->addChild(customInputs);

	self->m_editorLayerLabel->setVisible(false);
	self->m_editorLayer2Label->setVisible(false);
	self->m_zOrderLabel->setVisible(false);

	return result;
}

void __fastcall SetGroupIDLayer::onEditorLayerH(gd::SetGroupIDLayer* self, void*, CCObject* sender) {
	SetGroupIDLayer::onEditorLayer(self, sender);

	auto customInputs = static_cast<CustomInputs*>(self->m_pLayer->getChildByTag(8590));
	if (customInputs) customInputs->updateInputNode();
}

void __fastcall SetGroupIDLayer::onEditorLayer2H(gd::SetGroupIDLayer* self, void*, CCObject* sender) {
	SetGroupIDLayer::onEditorLayer2(self, sender);

	auto customInputs = static_cast<CustomInputs*>(self->m_pLayer->getChildByTag(8590));
	if (customInputs) customInputs->updateInputNode();
}

void __fastcall SetGroupIDLayer::onZOrderH(gd::SetGroupIDLayer* self, void*, CCObject* sender) {
	SetGroupIDLayer::onZOrder(self, sender);

	auto customInputs = static_cast<CustomInputs*>(self->m_pLayer->getChildByTag(8590));
	if (customInputs) customInputs->updateInputNode();
}

void SetGroupIDLayer::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x18b1b0), SetGroupIDLayer::initH, reinterpret_cast<void**>(&SetGroupIDLayer::init));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x18d070), SetGroupIDLayer::onEditorLayerH, reinterpret_cast<void**>(&SetGroupIDLayer::onEditorLayer));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x18d0f0), SetGroupIDLayer::onEditorLayer2H, reinterpret_cast<void**>(&SetGroupIDLayer::onEditorLayer2));
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x18d960), SetGroupIDLayer::onZOrderH, reinterpret_cast<void**>(&SetGroupIDLayer::onZOrder));
}