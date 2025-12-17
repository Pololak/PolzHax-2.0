#ifndef __SETGROUPIDLAYER_H__
#define __SETGROUPIDLAYER_H__

#include <gd.h>

namespace gd {
    class GameObject;
    class CCTextInputNode;

    enum class ZLayer {
        Default = 0,
        Bot = 1,
        Mid = 3,
        Top = 5,
    };

    class SetGroupIDLayer : public FLAlertLayer, TextInputDelegate {
    public:
        GameObject* m_targetObject; // 0x1cc
        cocos2d::CCArray* m_targetObjects; // 0x1d0
        cocos2d::CCArray* m_array0; // 0x1d4
        cocos2d::CCArray* m_array1; // 0x1d8
        cocos2d::CCLabelBMFont* m_editorLayerLabel; // 0x1dc
        cocos2d::CCLabelBMFont* m_editorLayer2Label; // 0x1e0
        cocos2d::CCLabelBMFont* m_zOrderLabel; // 0x1e4
        CCTextInputNode* m_groupIDInput; // 0x1e8
        int m_groupID; // 0x1ec
        int m_editorLayer; // 0x1f0
        int m_editorLayer2; // 0x1f4
        int m_zOrder; // 0x1f8
        ZLayer m_zLayer; // 0x1fc
        PAD(0x2)
        bool m_dontFade; // 0x202
        PAD(0x5)
        bool m_groupParent; // 0x208
        PAD(0x3)
        bool m_unkInt; // 0x20c

        void updateGroupIDLayer() {
            reinterpret_cast<void(__fastcall*)(SetGroupIDLayer*)>(base + 0x18dfd0)(this);
        }

        void onZLayer(cocos2d::CCObject* obj) {
            reinterpret_cast<void(__thiscall*)(SetGroupIDLayer*, cocos2d::CCObject*)>(base + 0x18da20)(this, obj);
        }

        void updateEditorLayerID() {
            reinterpret_cast<void(__fastcall*)(SetGroupIDLayer*)>(base + 0x18db20)(this);
        }

        void updateEditorLayerID2() {
            reinterpret_cast<void(__fastcall*)(SetGroupIDLayer*)>(base + 0x18db90)(this);
        }

        void updateZOrder() {
            reinterpret_cast<void(__fastcall*)(SetGroupIDLayer*)>(base + 0x18df40)(this);
        }
    };
}

#endif