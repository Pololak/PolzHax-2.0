#ifndef __LEVELINFOLAYER_H__
#define __LEVELINFOLAYER_H__

#include <gd.h>

namespace gd {
    class GJGameLevel;
    class CCMenuItemSpriteExtra;
    class LoadingCircle;
    enum class GJLevelType;

    class LevelInfoLayer : public cocos2d::CCLayer,
        LevelDownloadDelegate,
        LevelUpdateDelegate,
        RateLevelDelegate,
        LikeItemDelegate,
        public FLAlertLayerProtocol,
        LevelDeleteDelegate,
        NumberInputDelegate {
    public:
        bool m_willExitScene; // 0x134
        cocos2d::CCMenu* m_playButtonMenu; // 0x138
        GJGameLevel* m_level; // 0x13c
        cocos2d::CCArray* m_coinsSprites; // 0x140
        PAD(0x4)
        CCMenuItemSpriteExtra* m_likeBtn; // 0x148
        CCMenuItemSpriteExtra* m_starRateBtn; // 0x14c
        PAD(0x4)
        cocos2d::CCLabelBMFont* m_lengthLabel; // 0x154
        cocos2d::CCLabelBMFont* m_downloadsLabel; // 0x158
        cocos2d::CCLabelBMFont* m_likesLabel; // 0x15c
        CCMenuItemSpriteExtra* m_copyBtn; // 0x160
        PAD(0x4)
        cocos2d::CCSprite* m_likeIcon; // 0x168
        GJLevelType m_levelType; // 0x16c
        bool m_levelNeedsDownload; // 0x170
        LoadingCircle* m_loadingCircle; // 0x174
        cocos2d::CCSprite* m_difficultyIcon; // 0x178
        cocos2d::CCSprite* m_starIcon; // 0x17c
        cocos2d::CCLabelBMFont* m_starsLabel; // 0x180
        cocos2d::CCSprite* m_featuredCoin; // 0x184
    };

};

#endif