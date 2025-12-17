#ifndef __EDITORUI_H__
#define __EDITORUI_H__

#include <gd.h>
#include "level_nodes/ColorAction.h"

namespace gd {
	class CCBlockLayer;
	class LevelEditorLayer;
	class CCMenuItemToggler;
	class FLAlertLayer;
	class GameObject;
	class EffectGameObject;
	class CreateMenuItem;
	class ButtonSprite;
	class ColorChannelSprite;
	class UndoObject;
	class FLAlertLayerProtocol;

	class GJRotationControl : public cocos2d::CCLayer {
	public:
		void finishTouch() {
			reinterpret_cast<void(__fastcall*)(GJRotationControl*)>(base + 0x73fa0)(this);
		}
	};

	class BoomScrollLayer : public cocos2d::CCNode {};
	class ButtonPage : public cocos2d::CCNode {};
	class ExtendedLayer : public cocos2d::CCNode {};
	class Slider;

	class GJScaleControl : public cocos2d::CCLayer {
	public:
		Slider* m_slider; // 0x118
		int m_touchID; // 0x11c
		float m_value; // 0x120
		bool m_snapTo1; // 0x124 
		cocos2d::CCLabelBMFont* m_label; // 0x128
		GJScaleControlDelegate* m_delegate; // 0x12ñ
	};

	enum class EditCommand {};

	class EditButtonBar : public cocos2d::CCNode {
	public:
		cocos2d::CCPoint m_position; // 0xe8
		PAD(4)
		bool m_idk; // 0xf4
		cocos2d::CCArray* m_buttonArray; // 0xf8
		BoomScrollLayer* m_scrollLayer; // 0xfc
		cocos2d::CCArray* m_pagesArray; // 0x100

		void loadFromItems(cocos2d::CCArray* buttons, int rowCount, int columnCount, bool idk) {
			reinterpret_cast<void(__thiscall*)(
				EditButtonBar*, cocos2d::CCArray*, int, int, bool
				)>(
					base + 0x56060
					)(
						this, buttons, rowCount, columnCount, idk
						);
		}
	};

	class EditorPauseLayer : public CCBlockLayer, public FLAlertLayerProtocol {
	public:
		PAD(4)
		CCMenuItemSpriteExtra* m_audioOnBtn; // 0x1a0
		CCMenuItemSpriteExtra* m_audioOffBtn; // 0x1a4
		LevelEditorLayer* m_editorLayer; // 0x1a8

		void saveLevel() {
			reinterpret_cast<void(__fastcall*)(EditorPauseLayer*)>(base + 0x5c290)(this);
		}

		void onResume(cocos2d::CCObject* obj) {
			reinterpret_cast<void(__thiscall*)(EditorPauseLayer*, cocos2d::CCObject*)>(base + 0x5c270)(this, obj);
		}
	};

	class EditorUI : public cocos2d::CCLayer, FLAlertLayerProtocol, ColorSelectDelegate, GJRotationControlDelegate, GJScaleControlDelegate, MusicDownloadDelegate {
	public:
		EditButtonBar* m_customObjButtonBar; // 0x12c
		PAD(4) // something related to FLAlerts
		cocos2d::CCArray* m_hideableUIElement; // 0x134
		float m_activeGridSize; // 0x138
		int m_playerTouchID; // 0x13c
		int m_player2TouchID; // 0x140
		bool m_playtestMusic; // 0x144
		PAD(0x3)
		UndoObject* m_storedUndoObject; // 0x148
		PAD(4)
		int m_rotationTouchID; // 0x150
		int m_scaleTouchID; // 0x154
		int m_touchID; // 0x158
		cocos2d::CCLabelBMFont* m_objectInfo; // 0x15c
		GJRotationControl* m_rotationControl; // 0x160
		cocos2d::CCPoint m_scaleControlPos; // 0x164
		float m_idkFloat16c; // 0x16c
		GJScaleControl* m_scaleControl; // 0x170
		cocos2d::CCDictionary* m_editButtonDict; // 0x174
		EditButtonBar* m_buildButtonBar; // 0x178 // first tab
		EditButtonBar* m_moveButtonBar; // 0x17c
		Slider* m_slider; // 0x180
		PAD(12)
		bool m_swipeEnabled; // 0x190
		PAD(3)
		bool m_freeMoveEnabled; // 0x194
		PAD(11)
		PAD(12)
		cocos2d::CCArray* m_selectedObjects; // 0x1ac
		cocos2d::CCMenu* m_deleteMenu; // 0x1b0
		PAD(4)
		CCMenuItemSpriteExtra* m_deleteModeBtn; // 0x1b8
		CCMenuItemSpriteExtra* m_buildModeBtn; // 0x1bc
		CCMenuItemSpriteExtra* m_editModeBtn; // 0x1c0
		CCMenuItemSpriteExtra* m_swipeBtn; // 0x1c4
		CCMenuItemSpriteExtra* m_freeMoveBtn; // 0x1c8
		CCMenuItemSpriteExtra* m_deselectBtn; // 0x1cc
		CCMenuItemSpriteExtra* m_snapBtn; // 0x1d0
		CCMenuItemSpriteExtra* m_rotateBtn; // 0x1d4
		CCMenuItemSpriteExtra* m_playbackBtn; // 0x1d8
		CCMenuItemSpriteExtra* m_playtestBtn; // 0x1dc
		CCMenuItemSpriteExtra* m_playtestStopBtn; // 0x1e0
		CCMenuItemSpriteExtra* m_trashBtn; // 0x1e4
		CCMenuItemSpriteExtra* m_undoBtn; // 0x1e8
		CCMenuItemSpriteExtra* m_redoBtn; // 0x1ec
		CCMenuItemSpriteExtra* m_editObjectBtn; // 0x1f0
		CCMenuItemSpriteExtra* m_editGroupBtn; // 0x1f4
		CCMenuItemSpriteExtra* m_copyPasteBtn; // 0x1f8
		CCMenuItemSpriteExtra* m_copyBtn; // 0x1fc
		CCMenuItemSpriteExtra* m_pasteBtn; // 0x200
		CCMenuItemToggler* m_guideToggle; // 0x204
		cocos2d::CCArray* m_createButtonBars; // 0x208
		cocos2d::CCMenu* m_tabsMenu; // 0x20c
		cocos2d::CCArray* m_tabsArray; // 0x210
		cocos2d::CCSprite* m_unusedSpr; // 0x214
		cocos2d::CCSprite* m_deleteFilterSprite; // 0x218
		CCMenuItemSpriteExtra* m_deleteBtn; // 0x21c
		CCMenuItemSpriteExtra* m_deleteFilterBtn; // 0x220
		CCMenuItemSpriteExtra* m_deleteFilterNone; // 0x224
		CCMenuItemSpriteExtra* m_deleteFilterStatic; // 0x228
		CCMenuItemSpriteExtra* m_deleteFilterDetails; // 0x22c
		CCMenuItemSpriteExtra* m_deleteFilterCustom; // 0x230
		cocos2d::CCLabelBMFont* m_currentGroupLabel; // 0x234
		CCMenuItemSpriteExtra* m_groupNextBtn; // 0x238
		CCMenuItemSpriteExtra* m_groupPrevBtn; // 0x23c
		PAD(8)
		int m_selectedCreateObjectID; // 0x248
		cocos2d::CCArray* m_pCreateButtonArray;  // 0x24c
		cocos2d::CCArray* m_pCustomObjectButtonArray; // 0x250
		int m_selectedMode; // 0x254
		LevelEditorLayer* m_editorLayer; // 0x258
		cocos2d::CCPoint m_lastClickPos; // 0x25c
		cocos2d::CCPoint m_swipeStartPos; // 0x264
		cocos2d::CCPoint m_swipeEndPos; // 0x26c
		cocos2d::CCPoint m_lastClickPosMove; // 0x274 idk how to name it properly
		cocos2d::CCPoint m_lastClickOnGameLayer; // 0x27c
		GameObject* m_selectedObject; // 0x284
		GameObject* m_movingObject; // 0x288
		PAD(4)
		std::string m_clipboard; // 0x290
		PAD(4)
		int m_selectedTab; // 0x2ac
		int m_clicks; // 0x2b0

		CCMenuItemSpriteExtra* getSpriteButton(
			const char* sprite,
			cocos2d::SEL_MenuHandler callback,
			cocos2d::CCMenu* menu,
			float scale
		) {
			return reinterpret_cast<CCMenuItemSpriteExtra * (__thiscall*)(
				EditorUI*, const char*, cocos2d::SEL_MenuHandler,
				cocos2d::CCMenu*, float
				)>(
					base + 0x5f340
					)(
						this, sprite, callback, menu, scale
						);
		}

		void moveObjectCall(cocos2d::CCObject* sender) {
			reinterpret_cast<void(__thiscall*)(EditorUI*, cocos2d::CCObject*)>(
				base + 0x6e190
				)(this, sender);
		}

		void moveObjectCall(EditCommand command) {
			reinterpret_cast<void(__thiscall*)(EditorUI*, EditCommand)>(
				base + 0x6e1b0
				)(this, command);
		}

		void transformObjectCall(cocos2d::CCObject* sender) {
			reinterpret_cast<void(__thiscall*)(EditorUI*, cocos2d::CCObject*)>(
				base + 0x6e520
				)(this, sender);
		}

		void transformObjectCall(EditCommand command) {
			reinterpret_cast<void(__thiscall*)(EditorUI*, EditCommand)>(
				base + 0x6e540
				)(this, command);
		}

		cocos2d::CCArray* getSelectedObjects() {
			return reinterpret_cast<cocos2d::CCArray * (__thiscall*)(EditorUI*)>(
				base + 0x6a7f0
				)(this);
		}

		void rotateObjects(cocos2d::CCArray* objects, float angle, cocos2d::CCPoint center) {
			__asm movss xmm2, angle;
			reinterpret_cast<void(__thiscall*)(
				EditorUI*, cocos2d::CCArray*, cocos2d::CCPoint
				)>(base + 0x6f410)(this, objects, center);
		}

		cocos2d::CCArray* pasteObjects(const std::string& str) {
			return reinterpret_cast<cocos2d::CCArray*(__thiscall*)(EditorUI*, std::string)>(base + 0x6bd20)(this, str);
		}

		void updateButtons() {
			reinterpret_cast<void(__thiscall*)(EditorUI*)>(base + 0x5ed00)(this);
		}

		void updateZoom(float amt) {
			reinterpret_cast<void(__vectorcall*)(float, float, EditorUI*)>(base + 0x6b4e0)(0.f, amt, this);
		}
		void onDuplicate(CCObject* sender) {
			return reinterpret_cast<void(__thiscall*)(EditorUI*, CCObject*)>(base + 0x6b830)(this, sender);
		}
		void selectObjects(cocos2d::CCArray* arr) {
			return reinterpret_cast<void(__thiscall*)(EditorUI*, cocos2d::CCArray*)>(base + 0x6a5a0)(this, arr);
		}
		CreateMenuItem* getCreateBtn(int id, int bg) {
			auto ret = reinterpret_cast<CreateMenuItem * (__thiscall*)(
				EditorUI*, int, int
				)>(
					base + 0x69380
					)(
						this, id, bg
						);

			return ret;
		}

		void constrainGameLayerPosition(float x = -3.0f, float y = -6.0f) {
			__asm {
				movss xmm1, x
				movss xmm2, y
			}

			reinterpret_cast<void(__fastcall*)(EditorUI*)>(
				base + 0x6fc80
				)(this);
		}

		void updateObjectInfoLabel() {
			reinterpret_cast<void(__thiscall*)(EditorUI*)>(base + 0x5fb70)(this);
		}

		void deactivateRotationControl() {
			m_rotationTouchID = -1;
			if (m_rotationControl->isVisible()) {
				m_rotationControl->setVisible(false);
				m_rotationControl->finishTouch();
			}
		}

		void deactivateScaleControl() {
			reinterpret_cast<void(__thiscall*)(EditorUI*)>(base + 0x6c2f0)(this);
		}

		void onStopPlaytest(CCObject* sender) {
			reinterpret_cast<void(__thiscall*)(EditorUI*, cocos2d::CCObject*)>(base + 0x6b310)(this, sender);
		}

		void moveObject(GameObject* obj, cocos2d::CCPoint position) {
			reinterpret_cast<void(__thiscall*)(EditorUI*, GameObject*, cocos2d::CCPoint)>(base + 0x6e330)(this, obj, position);
		}
	};

	class ConfigureHSVWidget : public cocos2d::CCNode {
	public:
		cocos2d::CCLabelBMFont* m_hueLabel; // 0xe8
		cocos2d::CCLabelBMFont* m_saturationLabel; // 0xec
		cocos2d::CCLabelBMFont* m_brightnessLabel; // 0xf0
		Slider* m_hueSlider; // 0xf4
		Slider* m_saturationSlider; // 0xf8
		Slider* m_brightnessSlider; // 0xfc
		cocos2d::ccHSVValue m_value; // 0x100
	};

	class HSVWidgetPopup : public FLAlertLayer {
	public:
		ConfigureHSVWidget* m_configureWidget;
		HSVWidgetPopupDelegate* m_delegate;
	};

	class ColorSelectPopup : public FLAlertLayer {
	public:
		PAD(12)
		cocos2d::extension::CCControlColourPicker* m_colorPicker; // 0x1d4
		PAD(4)
		cocos2d::CCLabelBMFont* m_opacityLabel; // 0x1dc
		Slider* m_fadeTimeSlider; // 0x1e0
		Slider* m_opacitySlider; // 0x1e4
		EffectGameObject* m_targetObject; // 0x1e8
		cocos2d::CCArray* m_targetObjects; // 0x1ec
		CCMenuItemToggler* m_playerColorToggler; // 0x1f0
		CCMenuItemToggler* m_playerColor2Toggler; // 0x1f4
		cocos2d::ccColor3B m_lastColor; // 0x1f8
		PAD(0x1)
		cocos2d::CCSprite* m_colorOldRef; // 0x1fc
		cocos2d::CCSprite* m_colorNewRef; // 0x200
		cocos2d::ccColor3B m_selectedColor; // 0x204
		PAD(0x1)
		void* m_colorSetupLayer; // 0x208
		float m_fadeTime; // 0x20c
		int m_playerColor; // 0x210
		bool m_isBlending; // 0x214
		PAD(0x3)
		float m_opacity; // 0x218
		ColorAction* m_colorAction; // 0x21ñ
		CCTextInputNode* m_colorIDInput; // 0x220
		bool m_unkBool; // 0x224 // activates when moving slider?
		bool m_touchTriggered; // 0x225
		bool m_hasTintGround; // 0x226
		bool m_tintGround; // 0x227
		bool m_hasOpacity; // 0x228
		bool m_isColorTrigger; // 0x229 applied only for 899 object
		PAD(0x2)
		int m_colorID; // 0x22c
		bool m_unkBool2; // 0x230
		PAD(0x3)
		int m_copyColorID; // 0x234
		bool m_copyOpacity; // 0x238
		PAD(0x3)
		ConfigureHSVWidget* m_hsvWidget; // 0x23c
		PAD(16)

		auto getPickerColor() { return *reinterpret_cast<cocos2d::ccColor3B*>(reinterpret_cast<uintptr_t>(m_colorPicker) + 0x140); }
		void setPickerColor(cocos2d::ccColor3B color) {
			// fod spent like 5 hours trying to get this working on cocos-headers, so fuck it
			const static auto address = GetProcAddress(
				GetModuleHandleA("libExtensions.dll"),
				"?setColorValue@CCControlColourPicker@extension@cocos2d@@UAEXABU_ccColor3B@3@@Z"
			);
			reinterpret_cast<void(__thiscall*)(cocos2d::extension::CCControlColourPicker*, const cocos2d::ccColor3B&)>(address)(m_colorPicker, color);
		}

		void onToggleTintMode(cocos2d::CCObject* sender) {
			reinterpret_cast<void(__thiscall*)(ColorSelectPopup*, cocos2d::CCObject*)>(base + 0x3c6d0)(this, sender);
		}

		void updateOpacityLabel() {
			if (this->m_opacityLabel)
				this->m_opacityLabel->setString(cocos2d::CCString::createWithFormat("Opacity: %.02f", this->m_opacity)->getCString());
		}
	};

	class SetupPulsePopup : public FLAlertLayer {
	public:
		PAD(12)
		cocos2d::extension::CCControlColourPicker* m_colorPicker; // 0x1d4
	};

	class CustomizeObjectLayer : public FLAlertLayer, public TextInputDelegate, public HSVWidgetPopupDelegate, public ColorSelectDelegate, public ColorSetupDelegate {
	public:
		GameObject* m_targetObject; // 0x1d8
		cocos2d::CCArray* m_targetObjects; // 0x1dc
		cocos2d::CCArray* m_colorButtons; // 0x1e0
		cocos2d::CCArray* m_colorNodes; // 0x1e4
		cocos2d::CCArray* m_textInputNodes; // 0x1e8
		cocos2d::CCArray* m_unkArray; // 0x1ec
		cocos2d::CCArray* m_unkArray2; // 0x1f0
		int m_selectedMode; // 0x1f4
		int m_customColorChannel; // 0x1f8
		PAD(0x4)
		CCMenuItemSpriteExtra* m_baseButton; // 0x200
		CCMenuItemSpriteExtra* m_detailButton; // 0x204
		CCMenuItemSpriteExtra* m_textButton; // 0x208
		CCMenuItemSpriteExtra* m_baseColorHSV; // 0x20c
		CCMenuItemSpriteExtra* m_detailColorHSV; // 0x210
		cocos2d::CCLabelBMFont* m_titleLabel; // 0x214
		cocos2d::CCLabelBMFont* m_selectedColorLabel; // 0x218
		CCTextInputNode* m_customColorInput; // 0x21c
		CCTextInputNode* m_textInput; // 0x220
		ButtonSprite* m_customColorButtonSprite; // 0x224
		CCMenuItemSpriteExtra* m_customColorButton; // 0x228
		CCMenuItemSpriteExtra* m_arrowDown; // 0x22c
		CCMenuItemSpriteExtra* m_arrowUp; // 0x230
		cocos2d::extension::CCScale9Sprite* m_customColorInputBG; // 0x234
		ColorChannelSprite* m_colorSprite; // 0x238
		CCMenuItemSpriteExtra* m_colorSpriteButton; // 0x240

		void onSelectColor(cocos2d::CCObject* obj) {
			reinterpret_cast<void(__thiscall*)(CustomizeObjectLayer*, cocos2d::CCObject*)>(base + 0x45920)(this, obj);
		}

		int getActiveMode(bool unknown) {
			return reinterpret_cast<int(__thiscall*)(CustomizeObjectLayer*, bool)>(base + 0x45320)(this, unknown);
		}
	};

	class ColorChannelSprite : public cocos2d::CCSprite {
	public:
		static ColorChannelSprite* create() {
			return reinterpret_cast<ColorChannelSprite*(__stdcall*)()>(
				base + 0xc33b0
			)();
		}

		void updateOpacity(float opacity) {
			__asm movss xmm1, opacity

			reinterpret_cast<void(__thiscall*)(ColorChannelSprite*)>(
				base + 0xc3630
				)(this);
		}
		void updateCopyLabel(int channel, bool unk) {
			reinterpret_cast<void(__thiscall*)(ColorChannelSprite*, int, bool)>(
				base + 0xc34b0
				)(this, channel, unk);
		}
		void updateBlending(bool enabled) {
			reinterpret_cast<void(__thiscall*)(ColorChannelSprite*, bool)>(
				base + 0xc3780
				)(this, enabled);
		}

		void updateValues(ColorAction* action) {
			if (!action) {
				this->setColor(cocos2d::ccWHITE);
				this->updateCopyLabel(0, false);
				this->updateOpacity(1.f);
				this->updateBlending(false);
				return;
			}
			this->updateCopyLabel(action->m_copyID, action->m_copyColorLoop);
			this->updateOpacity(action->m_fromOpacity);
			this->updateBlending(action->m_blending);
			if (action->m_copyID != 0 && !action->m_copyOpacity) this->setColor(cocos2d::ccGRAY);
			else this->setColor(action->m_fromColor);
		}
	};
}

#endif