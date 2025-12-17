#include "FindLevelPopup.h"

bool FindLevelPopup::init() {
	if (!this->initWithColor({ 0, 0, 0, 150 })) return false;

	this->m_bNoElasticity = true;

	auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();
	director->m_pTouchDispatcher->incrementForcePrio(69);
	this->registerWithTouchDispatcher();

	auto layer = CCLayer::create();
	auto menu = CCMenu::create();
	this->m_pLayer = layer;
	this->m_pButtonMenu = menu;

	layer->addChild(menu);
	this->addChild(layer);

	menu->setPosition({ winSize.width / 2.f, winSize.height / 2.f + 10.f });

	auto bg = extension::CCScale9Sprite::create("GJ_square01.png");
	bg->setContentSize({ 300.f, 150.f });
	bg->setPosition({ winSize.width / 2.f, winSize.height / 2.f + 60.f });
	layer->addChild(bg, -2);

	auto title = CCLabelBMFont::create("Find Level", "goldFont.fnt");
	title->setScale(.7f);
	title->setPosition({ winSize.width / 2.f, winSize.height / 2.f + 120.f });
	layer->addChild(title);

	auto inputBg = extension::CCScale9Sprite::create("square02_small.png");
	inputBg->setContentSize({ 200.f, 30.f });
	inputBg->setOpacity(100);
	inputBg->setColor({ 0, 0, 0 });
	inputBg->setPosition(bg->getPosition());
	layer->addChild(inputBg, -1);

	auto textInput = gd::CCTextInputNode::create("Search", this, "bigFont.fnt", 200.f, 40.f);
	textInput->setMaxLabelScale(.6f);
	textInput->m_width = 190.f;
	textInput->refreshLabel();
	textInput->setAllowedChars(" abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,-!?:;)(/\\\"'`*=+-_%[]<>|@&^#{}%$~");
	textInput->setLabelPlaceholderColor({ 120, 170, 240 });
	textInput->setLabelPlaceholderScale(.5f);
	textInput->setPosition(bg->getPosition());
	textInput->setDelegate(this);
	layer->addChild(textInput, 20);

	auto onCloseSpr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
	onCloseSpr->setScale(.8f);
	auto onClose = gd::CCMenuItemSpriteExtra::create(onCloseSpr, this, menu_selector(FindLevelPopup::onClose));
	onClose->setPosition({ -140.f, 115.f });
	menu->addChild(onClose);

	auto onSearchSpr = gd::ButtonSprite::create("OK", 0x28, true, "goldFont.fnt", "GJ_button_01.png", 30.f, .8f);
	auto onSearch = gd::CCMenuItemSpriteExtra::create(onSearchSpr, this, menu_selector(FindLevelPopup::onSearch));
	menu->addChild(onSearch);

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	return true;
}

void FindLevelPopup::keyBackClicked() {
	this->setTouchEnabled(false);
	this->removeFromParentAndCleanup(true);
}

void FindLevelPopup::onSearch(CCObject*) {
	std::cout << "LevelBrowserLayer: " << this->getUserData() << std::endl;
	gd::LevelBrowserLayer* lbl = static_cast<gd::LevelBrowserLayer*>(this->getUserData());
	if (lbl) {
		lbl->m_searchObject->m_searchQuery = m_inputString;
		lbl->loadPage(lbl->m_searchObject);
		std::cout << lbl->m_array->count() << std::endl;
	}
	this->keyBackClicked();
}

void FindLevelPopup::onClose(CCObject*) {
	this->keyBackClicked();
}

void FindLevelPopup::onResetValue(CCObject*) {
	
}

void FindLevelPopup::textChanged(gd::CCTextInputNode* input) {
	std::cout << input->getString() << std::endl;
	if (input->getString()) {
		m_inputString = input->getString();
	}
}