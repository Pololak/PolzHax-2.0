#pragma once
#include "pch.h"
#include <string>
#include <iostream>
#include "schema.hpp"

struct LayersStruct {
	CCLayer* PauseLayerObject;
};

struct SettingStruct {
	void loadState();
	void saveState();

	bool show;
	bool explorer;

	float Overlaycolor[4] = { 0.235f, 0.235f, 0.235f, 1.f };
	float BGcolor[4] = { 0.f, 0.f, 0.f, 0.902f };
	float UISize = 1.0f;
	float overlayCol = 0.235f;
	float overlayCol2 = 0.235f;
	float overlayCol3 = 0.235f;
	float overlayCol4 = 1.f;

	int cheatsCount = 0;
	int beforeRestartCheatsCount = 0;
	bool isSafeMode;

	bool onAutoSave = true;

	bool onCharFilter;
	bool onIcons;
	bool onLoadFailed;
	bool onMainLevels;
	bool onSliderLimit;
	bool onTextLength;
	bool onTheVault;

	bool onAlwaysNewBest;
	bool onShowCoinsUncollected;
	bool onPracticeCoins;
	bool onForceDontEnter;
	bool onForceDontFade;
	bool onForceObjectsInvisible;
	bool onHideAttempts;
	bool onHidePauseButton;
	bool onHidePauseMenu;
	bool onHidePlayer;
	bool onHidePracticeButtons;
	bool onInstantMirror;
	bool onInversedTrail;
	bool onNoAnimations;
	bool onNoBackgroundFlash;
	bool onNoDeathEffect;
	bool onNoEffectCircle;
	bool onNoGhostEffect;
	bool onNoGlow;
	bool onNoGravityEffect;
	bool onNoMiniIcon;
	bool onNoMirror;
	bool onNoNewBest;
	bool onNoOrbRing;
	bool onNoParticles;
	bool onNoLightning;
	bool onNoPortalShine;
	bool onNoPulse;
	bool onNoRespawnFlash;
	bool onNoRobotFire;
	bool onNoWavePulse;
	bool onNoWaveTrail;
	bool onNoWaveTrailBehind;
	bool onPracticePulse;
	bool onSameDualColor;
	bool onSolidPlayerTrail;
	bool onSolidWaveTrail;
	bool onTrailAlwaysOff;
	bool onTrailAlwaysOn;
	bool onTrailBugFix;
	bool onWavePulseSize;
	float wavePulseSize = 2.1f;
	bool onWaveTrailOnDeath;

	bool onAbsolutePosition;
	bool onCopyHack;
	bool onCustomObjectBypass;
	bool onDefaultSongBypass;
	bool onEditorExtension;
	bool onFreeScroll;
	bool onHideGrid;
	bool onHidePreviewLine;
	bool onHideTriggerLines;
	bool onHideUI;
	bool onHitboxBugFix;
	bool onLevelEdit;
	bool onNoCMark;
	bool onNoDeathX;
	bool onObjectBypass;
	bool onPlaceOver;
	bool onRotationHack;
	bool onScaleSnapBypass;
	bool onSmoothTrail;
	bool onToolboxBypass;
	bool onVerifyHack;
	bool onZOrderBypass;
	bool onZoomBypass;

	bool onAutoDeafen;
	bool onPauseUndeafen = true;
	bool onPracticeDeafen;
	bool onTestmodeDeafen;
	float deafenPercent = 50.f;
	float undeafenPercent = 100.f;
	bool onAutoKill;
	float killPercentage = 50.f;
	bool onBallRotatingBugFix;
	bool onCheckpointLagFix;
	bool onConfirmExit;
	bool onCorrectiveMusicSync;
	bool onEverythingHurts;
	bool onHighFPSRotationFix;
	bool onInvisibleDualFix;
	bool onJumpHack;
	bool onNoclip;
	bool onNoHitbox;
	bool onNoSpikes;
	bool onPauseDuringComplete;
	bool onPracticeBugFix;
	bool onPracticeMusic;
	bool onLastCheckpoint;
	bool onRespawnTime;
	float respawnValue = 1000.f;
	bool onShowLayout;
	bool onSmartStartPos;
	bool onStartPosSwitcher;

	float fps = 60.f;
	bool onFPSBypass;
	float pitch = 0.8f;
	bool onPitchShifter;
	bool onAllowLowVolume;
	bool onAntiCheatBypass;
	bool onAutoSafeMode;
	bool onDisableSongAlert;
	bool onFastAltTab;
	bool onForceVisibility;
	bool onFreeWindowResize;
	bool onLockCursor;
	bool onNoTransition;
	bool onRetryKeybind;
	bool onSafeMode;
	bool onShowRestartButton;
	bool onTransparentBG;
	bool onTransparentLists;
	bool onZeroDelay;

	float speedhack = 1.f;
	bool onSpeedhack;
	bool onSpeedhackMusic;
	bool onClassicMode;

	bool onSelectFilter;
	bool onExtraObjectInfo;
	bool onUnusedObjects;
	bool onRotateSaws;
	bool onDurationLines;
	
	// Hitboxes
	bool onHitboxes;
	bool onHitboxesOnDeath;

	bool onEnablePlayerHitboxes = true;
	bool onEnableSolidHitboxes = true;
	bool onEnableHazardHitboxes = true;
	bool onEnableSpecialHitboxes = true;

	int solidHitboxesR = 0;
	int solidHitboxesG = 0;
	int solidHitboxesB = 255;
	int hazardHitboxesR = 255;
	int hazardHitboxesG = 0;
	int hazardHitboxesB = 0;
	int specialHitboxesR = 0;
	int specialHitboxesG = 255;
	int specialHitboxesB = 0;
	int hitboxesOpacity = 255;

	// Show Layout
	int levelBGColorR = 40;
	int levelBGColorG = 125;
	int levelBGColorB = 255;
	int levelGColorR = 0;
	int levelGColorG = 102;
	int levelGColorB = 255;

	int groupIDOffset;
	bool onDeveloperMode;
	int g_autoDeafenKey;
	int g_retryKey = 0x52;

	int g_previousStartPos = 0x25;
	int g_nextStartPos = 0x27;

	bool onDrawDivide;

	int g_p1Click;
	int g_p2Click;

	int g_priority = 2;
	bool onThreadPriority;
	bool onBackupFix;
};

LayersStruct& layers();
SettingStruct& setting();

DEF_SCHEMA(
	SettingStruct,
	cheatsCount,
	beforeRestartCheatsCount,
	isSafeMode,

	onAutoSave,

	onCharFilter,
	onTheVault,
	onIcons,
	onLoadFailed,
	onMainLevels,
	onSliderLimit,
	onTextLength,

	onAlwaysNewBest,
	onShowCoinsUncollected,
	onPracticeCoins,
	onForceDontEnter,
	onForceDontFade,
	onForceObjectsInvisible,
	onHideAttempts,
	onHidePauseButton,
	onHidePauseMenu,
	onHidePlayer,
	onHidePracticeButtons,
	onInstantMirror,
	onInversedTrail,
	onNoAnimations,
	onNoBackgroundFlash,
	onNoDeathEffect,
	onNoEffectCircle,
	onNoGhostEffect,
	onNoGlow,
	onNoGravityEffect,
	onNoMiniIcon,
	onNoMirror,
	onNoNewBest,
	onNoOrbRing,
	onNoParticles,
	onNoLightning,
	onNoPortalShine,
	onNoPulse,
	onNoRespawnFlash,
	onNoRobotFire,
	onNoWavePulse,
	onNoWaveTrail,
	onNoWaveTrailBehind,
	onPracticePulse,
	onSameDualColor,
	onSolidPlayerTrail,
	onSolidWaveTrail,
	onTrailAlwaysOff,
	onTrailAlwaysOn,
	onTrailBugFix,
	onWavePulseSize,
	wavePulseSize,
	onWaveTrailOnDeath,

	onAbsolutePosition,
	onCopyHack,
	onCustomObjectBypass,
	onDefaultSongBypass,
	onEditorExtension,
	onFreeScroll,
	onHideGrid,
	onHidePreviewLine,
	onHideTriggerLines,
	onHideUI,
	onHitboxBugFix,
	onLevelEdit,
	onNoCMark,
	onNoDeathX,
	onObjectBypass,
	onPlaceOver,
	onRotationHack,
	onScaleSnapBypass,
	onSmoothTrail,
	onToolboxBypass,
	onVerifyHack,
	onZOrderBypass,
	onZoomBypass,

	onAutoDeafen,
	onPauseUndeafen,
	onPracticeDeafen,
	onTestmodeDeafen,
	deafenPercent,
	undeafenPercent,
	onAutoKill,
	killPercentage,
	onBallRotatingBugFix,
	onConfirmExit,
	onCorrectiveMusicSync,
	onEverythingHurts,
	onHighFPSRotationFix,
	onInvisibleDualFix,
	onJumpHack,
	onNoclip,
	onNoHitbox,
	onNoSpikes,
	onPauseDuringComplete,
	onPracticeBugFix,
	onPracticeMusic,
	onLastCheckpoint,
	onRespawnTime,
	respawnValue,
	onShowLayout,
	onSmartStartPos,
	onStartPosSwitcher,

	fps,
	onFPSBypass,
	onAllowLowVolume,
	onAntiCheatBypass,
	onAutoSafeMode,
	onDisableSongAlert,
	onFastAltTab,
	onForceVisibility,
	onFreeWindowResize,
	onLockCursor,
	onNoTransition,
	onRetryKeybind,
	onSafeMode,
	onShowRestartButton,
	onTransparentBG,
	onTransparentLists,
	onZeroDelay,

	speedhack,
	onSpeedhack,
	onSpeedhackMusic,
	onClassicMode,

	onSelectFilter,
	onExtraObjectInfo,
	onUnusedObjects,
	onRotateSaws,
	onDurationLines,

	onHitboxes,
	onHitboxesOnDeath,

	onEnablePlayerHitboxes,
	onEnableSolidHitboxes,
	onEnableHazardHitboxes,
	onEnableSpecialHitboxes,

	solidHitboxesR,
	solidHitboxesG,
	solidHitboxesB,
	hazardHitboxesR,
	hazardHitboxesG,
	hazardHitboxesB,
	specialHitboxesR,
	specialHitboxesG,
	specialHitboxesB,
	hitboxesOpacity,

	levelBGColorR,
	levelBGColorG,
	levelBGColorB,
	levelGColorR,
	levelGColorG,
	levelGColorB,

	onDeveloperMode,
	g_autoDeafenKey,
	g_retryKey,
	g_previousStartPos,
	g_nextStartPos,
	onDrawDivide,
	g_p1Click,
	g_p2Click,
	g_priority,
	onThreadPriority,
	onBackupFix
)
