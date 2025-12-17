#ifndef __EDITLEVELLAYER_H__
#define __EDITLEVELLAYER_H__

#include <gd.h>

namespace gd {
	class GJGameLevel;
	class TextArea;
	enum class GJLevelType;

	class EditLevelLayer : public cocos2d::CCLayer, FLAlertLayerProtocol, TextInputDelegate, UploadActionDelegate, UploadPopupDelegate {
	public:
		cocos2d::CCMenu* m_buttonMenu; // 0x128
		GJGameLevel* m_level; // 0x12c
		TextArea* m_descInput; // 0x130
		cocos2d::CCArray* m_textInputs; // 0x134
		bool m_isLoadingLevel; // 0x138
		GJLevelType m_levelType; // 0x13c
		std::string m_levelName; // 0x140

		GJGameLevel* level() {
			return from<GJGameLevel*>(this, 0x12c);
		}
		static auto scene(GJGameLevel* level) {
			return reinterpret_cast<cocos2d::CCScene*(__fastcall*)(GJGameLevel*)>(base + 0x56f00)(level);
		}
	};
}

#endif