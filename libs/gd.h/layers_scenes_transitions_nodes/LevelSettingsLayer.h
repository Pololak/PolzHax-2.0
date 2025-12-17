#ifndef __LEVELSETTINGSLAYER_H__
#define __LEVELSETTINGSLAYER_H__

#include <gd.h>

namespace gd {
	class ColorChannelSprite;
	class LevelSettingsObject;
	class LevelSettingsDelegate;
	class LevelEditorLayer;
	class CCMenuItemSpriteExtra;
	class CustomSongWidget;
	class CCMenuItemToggler;

	class LevelSettingsLayer : public FLAlertLayer, FLAlertLayerProtocol, ColorSelectDelegate, SelectArtDelegate, CustomSongLayerDelegate {
	public:
		int m_song; // 0x1d8
		int m_speed; // 0x1dc
		ColorChannelSprite* m_bgChannelSprite; // 0x1e0
		ColorChannelSprite* m_gChannelSprite; // 0x1e4
		ColorChannelSprite* m_g2ChannelSprite; // 0x1e8
		ColorChannelSprite* m_lChannelSprite; // 0x1ec
		ColorChannelSprite* m_objChannelSprite; // 0x1f0
		ColorChannelSprite* m_dlChannelSprite; // 0x1f4
		cocos2d::CCSprite* m_colorBtnSprite; // 0x1f8
		cocos2d::CCSprite* m_bgSprite; // 0x1fc
		cocos2d::CCSprite* m_gSprite; // 0x200
		LevelSettingsObject* m_settingsObject; // 0x204
		cocos2d::CCLabelBMFont* m_selectedSongLabel; // 0x208
		cocos2d::CCArray* m_gameModeArray; // 0x20c
		cocos2d::CCArray* m_speedArray; // 0x210
		LevelSettingsDelegate* m_levelSettingsDelegate; // 0x214
		LevelEditorLayer* m_editorLayer; // 0x218
		cocos2d::CCArray* m_mainSongArray; // 0x21c
		cocos2d::CCArray* m_btnArray; // 0x220
		CCMenuItemSpriteExtra* m_mainSongBtn; // 0x224
		CCMenuItemSpriteExtra* m_customSongBtn; // 0x228
		CCMenuItemSpriteExtra* m_selectCustomSongBtn; // 0x22c
		CCMenuItemSpriteExtra* m_changeSongBtn; // 0x230
		CustomSongWidget* m_customSongWidget; // 0x234

		void createToggleButton(std::string caption, cocos2d::SEL_MenuHandler callback, bool var, cocos2d::CCMenu* menu, cocos2d::CCPoint point) {
			reinterpret_cast<void(__fastcall*)(LevelSettingsLayer*, std::string, cocos2d::SEL_MenuHandler, bool, cocos2d::CCMenu*, cocos2d::CCPoint)>(base + 0x104970)(this, caption, callback, var, menu, point);
		}

		void onGravityFlipped(cocos2d::CCObject* sender) {
			reinterpret_cast<void(__thiscall*)(LevelSettingsLayer*, cocos2d::CCObject*)>(base + 0x104c50)(this, sender);
		}
	};
}

#endif // !__LEVELSETTINGSLAYER_H__
