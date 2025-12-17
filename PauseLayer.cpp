#include "PauseLayer.h"
#include "state.h"

CCMenu* m_togglerMenu = nullptr;

void PauseLayer::Callback::onShowPercentage(CCObject*) {
    gd::GameManager::sharedState()->toggleGameVariable("0040");
    auto playLayer = gd::GameManager::sharedState()->getPlayLayer();
    if (playLayer) {
        playLayer->m_percentLabel->setVisible(gd::GameManager::sharedState()->getGameVariable("0040"));
        playLayer->updateProgressBar();
    }
}

void __fastcall PauseLayer::onProgressBarH(gd::PauseLayer* self, void*, CCObject* obj) {
    const auto bar = gd::GameManager::sharedState()->getProgressBar();
    auto size = CCDirector::sharedDirector()->getWinSize();
    auto playLayer = gd::GameManager::sharedState()->getPlayLayer();

    if (playLayer) {
        auto percentLabel = playLayer->m_percentLabel;
        if (percentLabel) {
            percentLabel->setAnchorPoint({ bar ? 0.5f : 0.f, 0.5f });
            percentLabel->setPosition({ size.width / 2.f + (bar ? 0.f : 110.2f), size.height - 8.f });
        }
    }

    PauseLayer::onProgressBar(self, obj);

    if (playLayer) {
        auto percentLabel = playLayer->m_percentLabel;
        if (percentLabel) {
            percentLabel->setVisible(gd::GameManager::sharedState()->getGameVariable("0040"));
        }
    }
} // Horrible thing

auto showPercentageTogglerSpr(CCSprite* toggleOn, CCSprite* toggleOff) {
    return (gd::GameManager::sharedState()->getGameVariable("0040")) ? toggleOn : toggleOff;
}

void __fastcall PauseLayer::customSetupH(gd::PauseLayer* self) {
	m_togglerMenu = nullptr;
	PauseLayer::customSetup(self);
	layers().PauseLayerObject = self;
    self->setVisible(!setting().onHidePauseMenu);

    auto director = CCDirector::sharedDirector();
    auto winSize = director->getWinSize();

    CCLabelBMFont* barText = nullptr;
    if (self->getChildren()->count() > 20) {
        barText = reinterpret_cast<CCLabelBMFont*>(self->getChildren()->objectAtIndex(14));
    }
    else {
        barText = reinterpret_cast<CCLabelBMFont*>(self->getChildren()->objectAtIndex(11));
    }
    barText->setString("Bar");
    barText->setScale(0.42f);

    auto toggleOn = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
    auto toggleOff = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");

    auto PercentageButton = gd::CCMenuItemToggler::create(showPercentageTogglerSpr(toggleOn, toggleOff), showPercentageTogglerSpr(toggleOff, toggleOn), self, menu_selector(PauseLayer::Callback::onShowPercentage));
    auto PercentageLabel = CCLabelBMFont::create("%", "bigFont.fnt");
    PercentageButton->setScale(0.6f);
    PercentageButton->setPosition({m_togglerMenu->convertToNodeSpace({(winSize.width / 2) + 155.f, +25}) });
    PercentageLabel->setScale(0.4f);
    PercentageLabel->setPosition({ (winSize.width / 2) + 170.5f, +25 });
    PercentageLabel->setAnchorPoint({ 0.f, 0.5f });
    m_togglerMenu->addChild(PercentageButton);
    self->addChild(PercentageLabel);
}

void __fastcall PauseLayer::onRestartH(CCObject* object) {
    CCEGLView::sharedOpenGLView()->showCursor(gd::GameManager::sharedState()->getGameVariable("0024"));
    layers().PauseLayerObject = nullptr;
    PauseLayer::onRestart(object);
}

void __fastcall PauseLayer::togglerMenuH() {
    __asm {
        mov m_togglerMenu, eax
    }
    PauseLayer::togglerMenu();
}

class ExitAlertProtocol : public gd::FLAlertLayerProtocol {
protected:
    void FLAlert_Clicked(gd::FLAlertLayer* layer, bool btn2) override
    {
        if (btn2)
        {
            gd::GameManager::sharedState()->getPlayLayer()->onQuit();
            gd::GameSoundManager::sharedState()->playSound("quitSound_01.ogg");
        }
    }
};

ExitAlertProtocol exitAlertProtocol;

void __fastcall PauseLayer::onQuitH(gd::PauseLayer* self, void*, CCObject* obj) {
    if (setting().onConfirmExit) {
        gd::FLAlertLayer::create(&exitAlertProtocol, "Confirm", "Cancel", "Exit", 320.f, "Are you sure you want to <cr>exit</c> the level?")->show();
    }
    PauseLayer::onQuit(self, obj);
}

void PauseLayer::mem_init() {
    MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x15b710), PauseLayer::customSetupH, reinterpret_cast<void**>(&PauseLayer::customSetup));
    MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x15be9f), PauseLayer::togglerMenuH, reinterpret_cast<void**>(&PauseLayer::togglerMenu));
    MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x15d210), PauseLayer::onRestartH, reinterpret_cast<void**>(&PauseLayer::onRestart));
    MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x15d5f0), PauseLayer::onQuitH, reinterpret_cast<void**>(&PauseLayer::onQuit));
    MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x15d700), PauseLayer::onProgressBarH, reinterpret_cast<void**>(&PauseLayer::onProgressBar));
}