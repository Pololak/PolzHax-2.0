#include "GJScaleControl.hpp"

class CustomScaleInput : public CCLayer, gd::TextInputDelegate {
protected:
	gd::GJScaleControl* m_scaleControl;

	bool init(gd::GJScaleControl* scaleControl) {
		m_scaleControl = scaleControl;
		if (!CCLayer::init()) return false;

		auto label = CCLabelBMFont::create("Scale:", "bigFont.fnt");
		label->setScale(.5f);
		label->setPositionX(-20.f);
		this->addChild(label);

		auto inputBg = extension::CCScale9Sprite::create("square02_small.png");
		inputBg->setOpacity(100);
		inputBg->setContentSize({ 50.f, 30.f });
		inputBg->setPositionX(30.f);
		inputBg->setScale(.8f);
		this->addChild(inputBg, -1);

		m_inputNode = gd::CCTextInputNode::create("Val", this, "bigFont.fnt", 45.f, 30.f);
		m_inputNode->setDelegate(this);
		m_inputNode->setLabelPlaceholderColor(ccc3(150, 150, 150));
		m_inputNode->setLabelPlaceholderScale(.5f);
		m_inputNode->setMaxLabelLength(5);
		m_inputNode->setAllowedChars("0123456789.");
		m_inputNode->setMaxLabelScale(.5f);
		m_inputNode->setPositionX(30.f);
		this->addChild(m_inputNode);

		return true;
	}

	virtual void textChanged(gd::CCTextInputNode* input) {

	}

public:
	gd::CCTextInputNode* m_inputNode;

	static CustomScaleInput* create(gd::GJScaleControl* scaleControl) {
		CustomScaleInput* ret = new CustomScaleInput();
		if (ret && ret->init(scaleControl)) {
			ret->autorelease();
			return ret;
		}
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
};

bool __fastcall GJScaleControl::initH(gd::GJScaleControl* self, void*) {
	if (!GJScaleControl::init(self)) return false;

	self->m_label->setOpacity(0);
	auto scaleInput = CustomScaleInput::create(self);
	scaleInput->setPositionY(30.f);
	self->addChild(scaleInput);

	return true;
}

void GJScaleControl::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x74290), GJScaleControl::initH, reinterpret_cast<void**>(&GJScaleControl::init));
}