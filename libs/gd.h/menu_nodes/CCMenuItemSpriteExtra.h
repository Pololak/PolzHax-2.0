#ifndef __CCMENUITEMSPRITEEXTRA_H__
#define __CCMENUITEMSPRITEEXTRA_H__

#include <gd.h>

namespace gd {
	#pragma runtime_checks("s", off)
	class CCMenuItemSpriteExtra : public cocos2d::CCMenuItemSprite {
	protected:
		float m_fUnknown;
		float m_fUnknown2;

	public:
		static auto* create(cocos2d::CCNode* activatedSpr, cocos2d::CCNode* deactivatedSpr, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler callback) {
			auto ret = reinterpret_cast<CCMenuItemSpriteExtra * (__fastcall*)(cocos2d::CCNode*, cocos2d::CCNode*, cocos2d::CCObject*, cocos2d::SEL_MenuHandler)>
				(base + 0x15900)(activatedSpr, deactivatedSpr, target, callback);
			__asm add esp, 0x8;
			return ret;
		}

		static auto* create(cocos2d::CCNode* sprite, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler callback) {
			return create(sprite, nullptr, target, callback);
		}

		void setSizeMult(float mult) {
			__asm movss xmm1, mult
			return reinterpret_cast<void(__thiscall*)(CCMenuItemSpriteExtra*)>(
				base + 0x19080
				)(this);
		}
	};

	class CreateMenuItem : public CCMenuItemSpriteExtra {
	public:

	};

	#pragma runtime_checks("s", restore)
}

#endif