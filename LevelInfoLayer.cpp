#include "LevelInfoLayer.h"
#include "state.h"

void LevelInfoLayer::Callback::onMoveToTop(CCObject*) {
	auto glm = gd::GameLevelManager::sharedState();
	std::cout << glm->m_savedLevelsDict->valueForKey(glm->getLevelKey(this->m_level->m_levelID)) << std::endl;
}

bool __fastcall LevelInfoLayer::initH(gd::LevelInfoLayer* self, void*, gd::GJGameLevel* level) {
	if (!LevelInfoLayer::init(self, level)) return false;
	if (setting().onCopyHack) if (self->m_copyBtn) self->m_copyBtn->setVisible(true);

	auto director = CCDirector::sharedDirector();
	auto winSize = director->getWinSize();

	auto rightMenu = static_cast<CCMenu*>(self->m_likeBtn->getParent());

	if (setting().onDeveloperMode) {
		auto levelInfoLabel = CCLabelBMFont::create("", "chatFont.fnt");
		levelInfoLabel->setScale(.6f);
		levelInfoLabel->setPosition(director->getScreenLeft() + 60.f, winSize.height / 2.f + 120.f);
		levelInfoLabel->setAnchorPoint({ 0.f, 1.f });
		self->addChild(levelInfoLabel);

		std::stringstream levelInfo;

		levelInfo << "LevelID: " << level->m_levelID << "\n";
		levelInfo << "UserID: " << level->m_userID << "\n";
		levelInfo << "AccountID: " << level->m_accountID << "\n";
		levelInfo << "Difficulty: " << level->m_difficulty << "\n";
		levelInfo << "LevelRev: " << level->m_levelRev << "\n";
		levelInfo << "Order: " << level->m_order << "\n";
		levelInfo << "Ratings: " << level->m_ratings << "\n";
		levelInfo << "RatingsSum: " << level->m_ratingsSum << "\n";
		levelInfo << "Completes: " << level->m_completes << "\n";
		levelInfo << "Level Version: " << level->m_levelVersion << "\n";
		levelInfo << "Game Version: " << level->m_gameVersion << "\n";
		levelInfo << "Likes: " << level->m_likes << "\n";
		levelInfo << "Dislikes: " << level->m_dislikes << "\n";
		levelInfo << "Featured: " << level->m_featured << "\n";
		levelInfo << "Password: " << level->m_password << "\n";
		levelInfo << "Requested Stars: " << level->m_requestedStars << "\n";
		levelInfo << "Star Ratings: " << level->m_starRatings << "\n";
		levelInfo << "Star RatingsSum: " << level->m_starRatingsSum << "\n";
		levelInfo << "Max Star Ratings: " << level->m_maxStarRatings << "\n";
		levelInfo << "Min Star Ratings: " << level->m_minStarRatings << "\n";
		levelInfo << "Demon Votes: " << level->m_demonVotes << "\n";
		levelInfo << "Rate Stars: " << level->m_rateStars << "\n";
		levelInfo << "Rate Feature: " << level->m_rateFeature << "\n";
		levelInfo << "Rate User: " << level->m_rateUser.c_str() << "\n";

		levelInfoLabel->setString(levelInfo.str().c_str());


		auto moveToTop = gd::CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("edit_upBtn_001.png"),
			self,
			menu_selector(LevelInfoLayer::Callback::onMoveToTop));

		moveToTop->setPosition(rightMenu->convertToNodeSpace({ director->getScreenRight() - 100.f, director->getScreenBottom() + 80.f }));

		rightMenu->addChild(moveToTop);
	}

	return true;
}

void __fastcall LevelInfoLayer::levelDownloadFinishedH(gd::LevelInfoLayer* self, void*, gd::GJGameLevel* level) {
	LevelInfoLayer::levelDownloadFinished(self, level);
	if (setting().onCopyHack) if (self->m_copyBtn) self->m_copyBtn->setVisible(true);
}

void LevelInfoLayer::mem_init() {
	MH_CreateHook(reinterpret_cast<void*>(gd::base + 0x107740), LevelInfoLayer::initH, reinterpret_cast<void**>(&LevelInfoLayer::init));
}