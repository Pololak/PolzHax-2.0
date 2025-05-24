#ifndef __PLAYEROBJECT_H__
#define __PLAYEROBJECT_H__

#include <gd.h>

namespace gd {

	class GameObject;
	class AnimatedSpriteDelegate;
	class GhostTrailEffect {};
	class OBB2D;
	class HardStreak;

	class GJRobotSprite : public CCAnimatedSprite {
	public:
	};

	class PlayerObject : public GameObject, AnimatedSpriteDelegate {
	public:
		PAD(20)
		cocos2d::CCNode* m_unkNode; // 0x3f4
		cocos2d::CCDictionary* m_collisionLog; // 0x3f8
		cocos2d::CCDictionary* m_collisionLog1; // 0x3fc
		GameObject* m_collidedSlope; // 0x400
		PAD(0x3c)
		cocos2d::CCArray* m_particleSystems; // 0x43c
		PAD(0x8)
		int m_hasGhostTrail; // 0x448
		GhostTrailEffect* m_ghostTrail; // 0x44c
		cocos2d::CCSprite* m_iconSprite; // 0x450
		cocos2d::CCSprite* m_iconSpriteSecondary; // 0x454
		cocos2d::CCSprite* m_iconGlowSprite; // 0x458
		cocos2d::CCSprite* m_vehicleSprite; // 0x45c
		cocos2d::CCSprite* m_vehicleSpriteSecondary; // 0x460
		cocos2d::CCSprite* m_vehicleSpriteThird; // 0x464
		cocos2d::CCSprite* m_vehicleGlowSprite; // 0x468
		cocos2d::CCSprite* m_unkSpr; // 0x46c
		cocos2d::CCMotionStreak* m_motionStreak; // 0x470
		HardStreak* m_hardStreak; // 0x474
		double m_xVelocity; // 0x478
		double m_jumpAccel; // 0x480
		double m_gravity; // 0x488
		PAD(0x50)
		GJRobotSprite* m_robotSprite; // 0x4e4
		PAD(0x4)
		cocos2d::CCParticleSystemQuad* m_playerGroundParticles; // 0x4ec
		cocos2d::CCParticleSystemQuad* m_unkP; // 0x4f0
		cocos2d::CCParticleSystemQuad* m_shipBoostParticles; // 0x4f4
		cocos2d::CCParticleSystemQuad* m_vehicleGroundParticles; // 0x4f8
		cocos2d::CCParticleSystemQuad* m_unkP2; // 0x4fc
		cocos2d::CCParticleSystemQuad* m_robotJumpParticles; // 0x500
		PAD(0x4)
		cocos2d::CCParticleSystemQuad* m_unkP3; // 0x508
		cocos2d::CCParticleSystemQuad* m_unkP4; // 0x50c
		PAD(48)
		double m_yVelocity; // 0x540
		bool m_isOnSlope; // 0x548
		bool m_wasOnSlope; // 0x549
		PAD(0x2)
		float m_slopeYVel; // 0x54c
		bool m_isShip; // 0x550
		bool m_isBird; // 0x551
		bool m_isRoll; // 0x552
		bool m_isDart; // 0x553
		bool m_isRobot; // 0x554
		bool m_isFlipped; // 0x555
		bool m_isDead; // 0x556
		bool m_isOnGround; // 0x557
		float m_vehicleSize; // 0x558
		float m_playerSpeed; // 0x55c
		cocos2d::CCPoint m_playerPos; // 0x560
		cocos2d::CCPoint m_lastPortalPos; // 0x568
		cocos2d::CCLayer* m_gameLayer; // 0x570
		bool m_isSliding; // 0x574
		bool m_isJumping; // 0x575
		bool m_isLocked; // 0x576
		PAD(0x1)
		cocos2d::CCPoint m_lastGroundedPos; // 0x578
		cocos2d::CCArray* m_touchingRings; // 0x580
		GameObject* m_lastActivatedPortal; // 0x584
		bool m_hasJumped; // 0x588
		bool m_hasRingJumped; // 0x589
		PAD(2)
		PAD(4)
		cocos2d::CCPoint m_realPlayerPos; // 0x590
		bool m_isSecondPlayer; // 0x598
		bool m_dualMode; // 0x599
		PAD(2)
		double m_clkTimer; // 0x5a0
		bool m_disableEffects; // 0x5a8
		PAD(3)
		float m_audioScale; // 0x5ac
		float m_groundHeight; // 0x5b0
		float m_lastYVel; // 0x5b4

		virtual void setVisible(bool visible) {
			return reinterpret_cast<void(__thiscall*)(PlayerObject*, bool)>(
				base + 0x1FA860
				)(this, visible);
		}
		void pushButton(int button) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, int)>(base + 0x164e40)(this, button);
		}
		void releaseButton(int button) {
			reinterpret_cast<void(__thiscall*)(PlayerObject*, int)>(base + 0x164f10)(this, button);
		}

		OBB2D* getOrientedBox() {
			return reinterpret_cast<OBB2D * (__fastcall*)(PlayerObject*)>(base + 0x168880)(this);
		}
	};
}

#endif