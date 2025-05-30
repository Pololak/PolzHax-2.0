#include "EditorOptionsLayer.h"
#include "state.h"
#include "patching.h"

void EditorOptionsLayer::Callback::onExtraObjectInfo(CCObject*) {
	setting().onExtraObjectInfo = !setting().onExtraObjectInfo;
}

auto extraObjectInfoToggleSpr(CCSprite* on, CCSprite* off) {
	return (setting().onExtraObjectInfo) ? on : off;
}

void EditorOptionsLayer::Callback::onSelectFilter(CCObject*) {
	setting().onSelectFilter = !setting().onSelectFilter;
}

auto selectFilterToggleSpr(CCSprite* on, CCSprite* off) {
	return (setting().onSelectFilter) ? on : off;
}

void EditorOptionsLayer::Callback::onUnusedObjects(CCObject*) {
	setting().onUnusedObjects = !setting().onUnusedObjects;
}

auto unusedObjectsToggleSpr(CCSprite* on, CCSprite* off) {
	return (setting().onUnusedObjects) ? on : off;
}

void __fastcall EditorOptionsLayer::initH(gd::EditorOptionsLayer* self) {
	// this patch lowers the nodes 
	sequence_patch((uint32_t)gd::base + 0xd9cae, { 0xf0, 0xcd, 0x60, 0x00 }); // Buttons Rows
	sequence_patch((uint32_t)gd::base + 0xd9a48, { 0xf0, 0xcd, 0x60, 0x00 }); // Buttons Per Row

	EditorOptionsLayer::init(self);

	std::cout << "EditorOptionsLayer::init" << std::endl;

	auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();

	auto toggleOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
	auto toggleOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");

	auto onExtraObjectInfo = gd::CCMenuItemToggler::create(
		extraObjectInfoToggleSpr(toggleOn, toggleOff),
		extraObjectInfoToggleSpr(toggleOff, toggleOn),
		self,
		menu_selector(EditorOptionsLayer::Callback::onExtraObjectInfo));
	
	onExtraObjectInfo->setPosition({ -160.f, 40.f });
	onExtraObjectInfo->setScale(.8f);
	self->m_pButtonMenu->addChild(onExtraObjectInfo);

	auto onExtraObjectInfoLabel = CCLabelBMFont::create("Extra object info", "bigFont.fnt");
	onExtraObjectInfoLabel->setPosition({ winSize.width / 2.f - 139.f, winSize.height / 2.f + 40.f });
	onExtraObjectInfoLabel->setAnchorPoint({ 0.f ,.5f });
	onExtraObjectInfoLabel->setScale(.385f);
	self->m_pLayer->addChild(onExtraObjectInfoLabel);

	auto onSelectFilter = gd::CCMenuItemToggler::create(
		selectFilterToggleSpr(toggleOn, toggleOff),
		selectFilterToggleSpr(toggleOff, toggleOn),
		self,
		menu_selector(EditorOptionsLayer::Callback::onSelectFilter));

	onSelectFilter->setPosition({ 32.f, 40.f });
	onSelectFilter->setScale(.8f);
	self->m_pButtonMenu->addChild(onSelectFilter);

	auto onSelectFilterLabel = CCLabelBMFont::create("Select filter", "bigFont.fnt");
	onSelectFilterLabel->setPosition({ winSize.width / 2.f + 54.f, winSize.height / 2.f + 40.f });
	onSelectFilterLabel->setAnchorPoint({ 0.f ,.5f });
	onSelectFilterLabel->setScale(.485f);
	self->m_pLayer->addChild(onSelectFilterLabel);

	auto onUnusedObjects = gd::CCMenuItemToggler::create(
		unusedObjectsToggleSpr(toggleOn, toggleOff),
		unusedObjectsToggleSpr(toggleOff, toggleOn),
		self,
		menu_selector(EditorOptionsLayer::Callback::onUnusedObjects));

	onUnusedObjects->setPosition({ -160.f, 0.f });
	onUnusedObjects->setScale(.8f);
	self->m_pButtonMenu->addChild(onUnusedObjects);

	auto onUnusedObjectsLabel = CCLabelBMFont::create("Unused objects", "bigFont.fnt");
	onUnusedObjectsLabel->setPosition({ winSize.width / 2.f - 139.f, winSize.height / 2.f + 0.f });
	onUnusedObjectsLabel->setAnchorPoint({ 0.f, .5f });
	onUnusedObjectsLabel->setScale(.485f);
	self->m_pLayer->addChild(onUnusedObjectsLabel);
}