#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <gd.h>

namespace gd {

	// jesus fucking christ (painfully written by @hjfod)
	enum GameObjectType {
		kGameObjectTypeSolid = 0,
		kGameObjectTypeHazard = 2,
		kGameObjectTypeInverseGravityPortal = 3,
		kGameObjectTypeNormalGravityPortal = 4,
		kGameObjectTypeShipPortal = 5,
		kGameObjectTypeCubePortal = 6,
		kGameObjectTypeDecoration = 7,
		kGameObjectTypeYellowJumpPad = 8,
		kGameObjectTypePinkJumpPad = 9,
		kGameObjectTypeGravityPad = 10,
		kGameObjectTypeYellowJumpRing = 11,
		kGameObjectTypePinkJumpRing = 12,
		kGameObjectTypeGravityRing = 13,
		kGameObjectTypeInverseMirrorPortal = 14,
		kGameObjectTypeNormalMirrorPortal = 15,
		kGameObjectTypeBallPortal = 16,
		kGameObjectTypeRegularSizePortal = 17,
		kGameObjectTypeMiniSizePortal = 18,
		kGameObjectTypeUfoPortal = 19,
		kGameObjectTypeModifier = 20,
		kGameObjectTypeBreakable = 21,
		kGameObjectTypeSecretCoin = 22,
		kGameObjectTypeDualPortal = 23,
		kGameObjectTypeSoloPortal = 24,
		kGameObjectTypeSlope = 25,
		kGameObjectTypeWavePortal = 26,
		kGameObjectTypeRobotPortal = 27,
		kGameObjectTypeTeleportPortal = 28,
		kGameObjectTypeGreenRing = 29,
		kGameObjectTypeCollectible = 30,
		kGameObjectTypeUserCoin = 31,
	};

	class CCSpritePlus;
	class OBB2D;
	class GJSpriteColor;

	class GameObject : public CCSpritePlus {
	public:
		PAD(0x24)
		bool m_editor; // 0x1e8
		bool m_groupDisable; // 0x1e9
		PAD(2)
		int m_baseColorID; // 0x1ec
		int m_detailColorID; // 0x1f0
		PAD(0xC)
		bool m_tintTrigger; // 0x200
		bool m_isFlippedX; // 0x201
		bool m_isFlippedY; // 0x202
		PAD(0x1)
		PAD(4) // 0x204
		PAD(4) // 0x208
		PAD(4) // 0x20c
		PAD(4) // 0x210
		PAD(4) // 0x214
		OBB2D* m_OBB2D; // 0x218
		bool m_oriented; // 0x21c
		PAD(3)
		cocos2d::CCSprite* m_glowSprite; // 0x220
		PAD(0x4)
		cocos2d::CCAction* m_action; // 0x228
		bool m_isRotatingObject; // 0x22c
		bool m_objectPoweredOn; // 0x22d
		bool m_hideObject; // 0x22e
		PAD(1)
		float m_orientedBoxWidth; // 0x230
		float m_orientedBoxHeight; // 0x234
		bool m_isActive; // 0x238
		bool m_hasGlow; // 0x239
		bool m_isDestroyed; // 0x23a
		PAD(1)
		cocos2d::CCParticleSystemQuad* m_particleSystem; // 0x23c
		std::string m_effectPlistName; // 0x240
		PAD(0x34)
		bool m_isObjectRectDirty; // 0x28c
		bool m_isOrientedRectDirty; // 0x28d
		bool m_hasBeenActivated; // 0x28e
		bool m_hasBeenActivatedP2; // 0x28f
		PAD(0xC)
		cocos2d::CCSprite* m_detailSprite; // 0x29c
		bool m_ignoreScreenCheck; // 0x2a0
		PAD(3)
		float m_objectRadius; // 0x2a4
		bool m_isRotatedSide; // 0x2a8
		PAD(3)
		float m_scaleModX; // 0x2ac
		float m_scaleModY; // 0x2b0
		int m_uniqueID; // 0x2b4
		int m_objectType; // 0x2b8
		int m_section; // 0x2bcs
		bool m_touchTriggered; // 0x2c0
		bool m_spawnTriggered; // 0x2c1
		PAD(0x2)
		cocos2d::CCPoint m_startPosition; // 0x2c4
		std::string m_textureName; // 0x2cc
		bool m_useAudioScale; // 0x2e4
		bool m_sleeping; // 0x2e5
		PAD(0x2)
		float m_rotation; // 0x2e8
		cocos2d::CCSize m_obStartScale; // 0x2ec
		bool m_startFlipX; // 0x2f4
		bool m_startFlipY; // 0x2f5
		bool m_shouldHide; // 0x2f6
		PAD(0x1)
		float m_spawnXPos; // 0x2f8
		bool m_isInvisible; // 0x2fc
		float m_enterAngle; // 0x300
		int m_activeEnterEffect; // 0x304
		int m_colorTriggerID; // 0x308
		float m_scale; // 0x30c
		int m_objectID; // 0x310
		bool m_dontTransform; // 0x314
		bool m_dontFade; // 0x315
		bool m_ignoreEnter; // 0x316
		bool m_ignoreFade; // 0x317
		bool m_dontFadeTinted; // 0x318
		bool m_isTintObject; // 0x319
		bool m_isDetailColorObject; // 0x31a
		bool m_isDontFade; // 0x31b
		int m_stateVar; // 0x31c
		int m_defaultZOrder; // 0x320
		bool m_addToBatch2; // 0x324
		bool m_colorOnTop; // 0x325
		bool m_customAudioScale; // 0x326
		PAD(0x1)
		float m_minAudioScale; // 0x328
		float m_maxAudioScale; // 0x32c
		int m_secretCoinID; // 0x330
		PAD(0x4)
		bool m_invisibleMode; // 0x338
		bool m_glowUseBGColor; // 0x339
		bool m_useSpecialLight; // 0x33a
		PAD(0x1)
		float m_glowOpacityMod; // 0x33c
		bool m_upSlope; // 0x340
		PAD(0x3)
		int m_slopeType; // 0x344
		float m_slopeAngle; // 0x348
		bool m_hazardousSlope; // 0x34c
		PAD(0x3)
		GJSpriteColor* m_baseColor; // 0x350
		GJSpriteColor* m_detailColor; // 0x354
		bool m_addedToBlend; // 0x358
		PAD(3)
		int m_zLayer; // 0x35c
		int m_customZLayer; // 0x360
		int m_customObjectZ; // 0x364
		std::string m_textObjectString; // 0x368
		bool m_editorSelected; // 0x380
		bool m_wasSelected; // 0x381
		bool m_isSelected; // 0x382
		PAD(0x1)
		int m_globalClickCounter; // 0x384
		PAD(0x10)
		bool m_groupParent; // 0x398
		PAD(3)
		PAD(0x4)
		int m_groupCount; // 0x3a0
		int m_editorLayer; // 0x3a4
		int m_editorLayer2; // 0x3a8
		PAD(32)
		ColorActionSprite* m_colorActionSpriteBase; // 0x3d4
		ColorActionSprite* m_colorActionSpriteDetail; // 0x3d8
		GJEffectManager* m_effectManager; // 0x3dc

	public:
		OBB2D* getOrientedBox() {
			return reinterpret_cast<OBB2D*(__thiscall*)(GameObject*)>(base + 0xb7af0)(this);
		}

		void updateOrientedBox() {
			return reinterpret_cast<void(__thiscall*)(GameObject*)>(base + 0xb7b50)(this);
		}

		float getObjectRadius() {
			float radius = m_objectRadius;
			if (m_scale != 1.f) radius *= m_scale;
			return radius;
		}

		cocos2d::CCRect const& getObjectRect() {
			return *reinterpret_cast<cocos2d::CCRect*(__thiscall*)(GameObject*)>(base + 0xb1340)(this);
		}

		bool canRotateFree() {
			return (
				m_objectType != GameObjectType::kGameObjectTypeSolid &&
				m_objectType != GameObjectType::kGameObjectTypeBreakable &&
				m_objectType != GameObjectType::kGameObjectTypeSlope
				);
		}

		void calculateOrientedBox() {
			reinterpret_cast<void(__fastcall*)(GameObject*)>(base + 0xb7b30)(this);
		}

		void setObjectColor(const cocos2d::ccColor3B& color) {
			return reinterpret_cast<void(__thiscall*)(GameObject*, const cocos2d::ccColor3B&)>(base + 0xb7060)(this, color);
		}

		void setGlowColor(cocos2d::ccColor3B color) {
			if (!m_glowUseBGColor) {
				if (m_glowSprite) {
					m_glowSprite->setColor(color);
				}
			}
		}

		cocos2d::CCRepeatForever* createRotateAction(float f, int n) {
			__asm movss xmm1, f

			auto pRet = reinterpret_cast<cocos2d::CCRepeatForever * (__thiscall*)(GameObject*, int)>(
				base + 0xb12d0
				)(this, n);

			return pRet;
		}

		void updateSyncedAnimation(float f) {
			__asm movss xmm1, f
			reinterpret_cast<void(__thiscall*)(GameObject*)>(base + 0xb3170)(this);
		}

		void activateObject() {
			reinterpret_cast<void(__fastcall*)(GameObject*)>(base + 0xa5800)(this);
		}

		void setRScale(float scale) {
			reinterpret_cast<void(__thiscall*)(GameObject*, float)>(base + 0xb1c40)(this, scale);
		}

		void destroyObject() {
			reinterpret_cast<void(__fastcall*)(GameObject*)>(base + 0xb2340)(this);
		}
	};

	class AnimatedGameObject : public GameObject, AnimatedSpriteDelegate, SpritePartDelegate {
	public:
		void activateObject() {
			return reinterpret_cast<void(__fastcall*)(AnimatedGameObject*)>(base + 0x19dbc0)(this);
		}
	};
}

#endif