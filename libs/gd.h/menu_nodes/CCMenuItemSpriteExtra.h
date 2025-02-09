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
		static auto* create(cocos2d::CCSprite* activatedSpr, cocos2d::CCSprite* deactivatedSpr, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler callback) {
			auto ret = reinterpret_cast<CCMenuItemSpriteExtra * (__fastcall*)(cocos2d::CCNode*, cocos2d::CCNode*, cocos2d::CCObject*, cocos2d::SEL_MenuHandler)>
				(base + 0x15900)(activatedSpr, deactivatedSpr, target, callback);
			__asm add esp, 0x8;
			return ret;
		}

		void setSizeMult(float mult) {
			__asm movss xmm1, mult
			return reinterpret_cast<void(__thiscall*)(CCMenuItemSpriteExtra*)>(
				base + 0x19080
				)(this);
		}
	};
	#pragma runtime_checks("s", restore)
}

#endif