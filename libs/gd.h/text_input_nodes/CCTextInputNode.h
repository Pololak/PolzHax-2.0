#ifndef __CCTEXTINPUTNODE_H__
#define __CCTEXTINPUTNODE_H__

#include <gd.h>

namespace gd {
	#pragma runtime_checks("s", off)
	class CCTextInputNode : public cocos2d::CCLayer, public cocos2d::CCIMEDelegate, public cocos2d::CCTextFieldDelegate {
	public:
		PAD(0x4)
		std::string m_caption; // 0x124
		PAD(0x8)
		std::string m_filter; // 0x144
		float m_width; // 0x15c
		float m_maxLabelScale; // 0x160
		float m_placeholderScale; // 0x164
		cocos2d::ccColor3B m_placeholderColor; // 0x168
		cocos2d::ccColor3B m_normalColor; // 0x16c
		cocos2d::CCLabelBMFont* m_cursor; // 0x170
		cocos2d::CCTextFieldTTF* m_textField; // 0x174
		TextInputDelegate* m_delegate; // 0x178
		int m_maxLabelLength; // 0x17c
		cocos2d::CCLabelBMFont* m_placeholderLabel; // 0x180
		bool m_unknown; // 0x184
		bool m_unknown2; // 0x185
		bool m_forceOffset; // 0x186

	public:
		//own vtable
		void onClickTrackNode(bool) {}

		static CCTextInputNode* create(const char* caption, cocos2d::CCObject* target, 
			const char* fntFile, float width, float height) {
			__asm {
				movss xmm0, width
				movss xmm1, height
			}
			auto pRet = reinterpret_cast<CCTextInputNode* (__thiscall*)
				(const char*, cocos2d::CCObject*, const char*)>(
				base + 0x1d6c0
			)(caption, target, fntFile);
			__asm add esp, 0x8
			return pRet;
		}
		void setLabelPlaceholderColor(cocos2d::ccColor3B color) {
			m_placeholderColor = color;
			this->refreshLabel();
		}
		void setLabelPlaceholderScale(float scale) {
			m_placeholderScale = scale;
			this->refreshLabel();
		}
		void setMaxLabelScale(float scale) {
			m_maxLabelScale = scale;
			this->refreshLabel();
		}
		void setMaxLabelWidth(float width) {
			m_width = width;
			this->refreshLabel();
		}
		void setMaxLabelLength(int length) { m_maxLabelLength = length; }
		void setAllowedChars(std::string filter) { m_filter = filter; }
		void refreshLabel() {
			return reinterpret_cast<void(__thiscall*)(CCTextInputNode*)>(
				base + 0x1dc60
				)(this);
		}
		void setString(const char* text) { m_textField->setString(text); }
		const char* getString() { return m_textField->getString(); }
		cocos2d::CCLabelBMFont* getPlaceholderLabel() { return m_placeholderLabel; }
		void setDelegate(TextInputDelegate* delegate) { m_delegate = delegate; }
	};
	#pragma runtime_checks("s", restore)
}

#endif