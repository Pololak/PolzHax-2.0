#ifndef __SLIDER_H__
#define __SLIDER_H__

namespace gd {
    class Slider;

    class SliderThumb : public cocos2d::CCMenuItemImage {
    public:
        void setValue(float val) {
            __asm movss xmm1, val

            reinterpret_cast<void(__fastcall*)(
                SliderThumb*
                )>(base + 0x2a920)(this);
        }
    };

    class SliderTouchLogic : public cocos2d::CCMenu {
    public:
        PAD(0x4)
        float m_length;
        SliderThumb* m_thumb;
        Slider* m_slider;
    };

    class Slider : public cocos2d::CCLayer {
    public:
        SliderTouchLogic* m_touchLogic; // 0x118
        cocos2d::CCSprite* m_sliderBar; // 0x11c
        float m_width; // 0x120
        float m_height; // 0x124

        cocos2d::CCSprite* getGroove() {
            return static_cast<cocos2d::CCSprite*>(this->m_sliderBar->getParent());
        }

        void setValue(float val) {
            __asm movaps xmm1, val

            return reinterpret_cast<void(__fastcall*)(Slider*)>(base + 0x2a920)(this);
        }

        void updateBar() {
            reinterpret_cast<void(__fastcall*)(Slider*)>(
                base + 0x2a9c0
                )(this);
        }

        static Slider* create(
            cocos2d::CCNode* target,
            cocos2d::SEL_MenuHandler click,
            const char* grooveSpr,
            const char* thumbSpr,
            const char* thumbSprSel,
            float scale
        ) {
            auto ret = reinterpret_cast<Slider * (__fastcall*)(
                cocos2d::CCNode*, cocos2d::SEL_MenuHandler, const char*,
                const char*, const char*, const char*, float
                )>(
                    base + 0x2a630
                    )(
                        target, click, nullptr, grooveSpr, thumbSpr, thumbSprSel, scale
                        );

            __asm add esp, 0x14

            return ret;
        }

        static Slider* create(
            cocos2d::CCNode* target,
            cocos2d::SEL_MenuHandler click,
            float scale
        ) {
            return create(target, click, "slidergroove.png", "sliderthumb.png", "sliderthumbsel.png", scale);
        }
    };
}

#endif