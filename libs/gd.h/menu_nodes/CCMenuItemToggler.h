#ifndef __CCMENUITEMTOGGLER_H__
#define __CCMENUITEMTOGGLER_H__

#include <gd.h>

namespace gd {
	class CCMenuItemToggler : public cocos2d::CCMenuItem {
	public:
		CCMenuItemSpriteExtra* m_pOnButton;
		CCMenuItemSpriteExtra* m_pOffButton;
		bool m_bOn;
		bool m_bUnknown;

		static CCMenuItemToggler* create(cocos2d::CCNode* off, cocos2d::CCNode* on,
			cocos2d::CCObject* target, cocos2d::SEL_MenuHandler callback) {
			auto pRet = reinterpret_cast<CCMenuItemToggler* (__fastcall*)(cocos2d::CCNode*,
				cocos2d::CCNode*, cocos2d::CCObject*, cocos2d::SEL_MenuHandler)>(
					base + 0x15e40
					)(off, on, target, callback);
			__asm add esp, 0x8
			return pRet;
		}

		void setSizeMult(float mult) {
			__asm movss xmm1, mult
			return reinterpret_cast<void(__thiscall*)(CCMenuItemToggler*)>(
				base + 0x19850
				)(this);
		}

		void toggle(bool on) {
			return reinterpret_cast<void(__thiscall*)(CCMenuItemToggler*, bool)>(
				base + 0x199B0
				)(this, on);
		}
	};
}

#endif