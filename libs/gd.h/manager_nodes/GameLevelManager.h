#ifndef __GAMELEVELMANAGER_H__
#define __GAMELEVELMANAGER_H__

#include <gd.h>

namespace gd {
    class GJGameLevel;

    class GameLevelManager : public cocos2d::CCNode {
    public:
        cocos2d::CCDictionary *m_mainLevels;
        cocos2d::CCDictionary *m_valueDict;
        cocos2d::CCDictionary *m_savedLevelsDict;
        cocos2d::CCDictionary *m_timerDict;
        cocos2d::CCDictionary *m_userValues;
        cocos2d::CCDictionary *m_storedLevels;
        cocos2d::CCDictionary *m_pageInfo;
        cocos2d::CCDictionary *m_unknownDict;
        cocos2d::CCDictionary *m_savedPacks;
        cocos2d::CCDictionary *m_activeDownloads;
        cocos2d::CCDictionary *m_activeUploads;

        static GameLevelManager* sharedState() {
            return reinterpret_cast<GameLevelManager * (__stdcall*)()>(gd::base + 0x7e830)();
        }

        static gd::GJGameLevel* createNewLevel() {
            return reinterpret_cast<gd::GJGameLevel * (__stdcall*)()>(gd::base + 0x7fa40)();
        }

        void makeTimeStamp(char const* key) {
            return reinterpret_cast<void(__thiscall*)(GameLevelManager*, char const*)>(base + 0x81c90)(this, key);
        }

        void resetTimerForKey(char const* key) {
            return reinterpret_cast<void(__thiscall*)(GameLevelManager*, char const*)>(gd::base + 0x82070)(this, key);
        }

        const char* getLevelKey(int levelID) {
            return cocos2d::CCString::createWithFormat("%i", levelID)->getCString();
        }

        //void saveLevel(GJGameLevel* level) {
        //    reinterpret_cast<void(__thiscall*)(GameLevelManager*, GJGameLevel*)>(base + 0x)
        //}
    };
}

#endif