#include "RotateSaws.h"
#include <array>
#include "utils.hpp"
#include "LevelEditorLayer.h"
#include "state.h"

// HJFod

std::map<gd::GameObject*, float> g_startRotations; 
std::array<int, 100> g_sawIDs = {
	88, 89, 98,
	397, 398, 399,
	675, 676, 677,
	186, 187, 188,
	740, 741, 742,
	678, 679, 680,
	183, 184, 185,
	85, 86, 87, 97,
	137, 138, 139,
	154, 155, 156,
	180, 181, 182,
	222, 223, 224,
	375, 376, 377, 378,
	394, 395, 396,
	997, 998, 999, 1000,
	1019, 1020, 1021,
	1055, 1056, 1057,
	1058, 1059, 1060, 1061,
	1022,
};

namespace RotateSaws {
	bool objectIsSaw(gd::GameObject* obj) {
		for (auto id : g_sawIDs)
			if (id == obj->m_objectID)
				return true;

		return false;
	}

	void beginRotateSaw(gd::GameObject* obj) {
		if (obj->m_action)
			return;

		CCAction* r;
		r = obj->createRotateAction(360.f, 0);
		r->setTag(9957);
		g_startRotations[obj] = obj->getRotation();
		obj->m_action = r;
		obj->m_action->retain();
		obj->runAction(r);
	}

	void beginRotations(gd::LevelEditorLayer* self) {
		CCARRAY_FOREACH_B_TYPE(self->m_objects, obj, gd::GameObject)
			if (objectIsSaw(obj)) beginRotateSaw(obj);
	}

	void stopRotateSaw(gd::GameObject* obj) {
		std::cout << "Stop Rotate Saw" << std::endl;
		obj->stopActionByTag(9957);
		if (g_startRotations.count(obj)) {
			obj->setRotation(g_startRotations[obj]);
			g_startRotations.erase(obj);
		}
		if (obj->m_action)
			obj->m_action->release();
		obj->m_action = nullptr;
	}

	void stopRotations(gd::LevelEditorLayer* self) {
		CCARRAY_FOREACH_B_TYPE(self->m_objects, obj, gd::GameObject)
			if (objectIsSaw(obj)) stopRotateSaw(obj);

		g_startRotations.clear();
	}

	void resumeRotations(gd::LevelEditorLayer* self) {
		CCARRAY_FOREACH_B_TYPE(self->m_objects, obj, gd::GameObject)
			if (objectIsSaw(obj))
				if (obj->m_action)
					obj->runAction(obj->m_action);
	}

	void pauseRotations(gd::LevelEditorLayer* self) {
		CCARRAY_FOREACH_B_TYPE(self->m_objects, obj, gd::GameObject)
			if (objectIsSaw(obj)) obj->stopActionByTag(9957);
	}
}

void __fastcall LevelEditorLayer::onPlaytestH(gd::LevelEditorLayer* self) {
	LevelEditorLayer::onPlaytest(self);

	LevelEditorLayer::updateOrientedHitboxes(self);

	if (setting().onRotateSaws) RotateSaws::beginRotations(self);
}

void __fastcall LevelEditorLayer::onResumePlaytestH(gd::LevelEditorLayer* self) {
	LevelEditorLayer::onResumePlaytest(self);

	LevelEditorLayer::updateOrientedHitboxes(self);

	if (setting().onRotateSaws) RotateSaws::resumeRotations(self);
}

void __fastcall LevelEditorLayer::onPausePlaytestH(gd::LevelEditorLayer* self) {
	LevelEditorLayer::onPausePlaytest(self);

	LevelEditorLayer::updateOrientedHitboxes(self);

	if (setting().onRotateSaws) RotateSaws::pauseRotations(self);
}

void __fastcall LevelEditorLayer::addSpecialH(gd::LevelEditorLayer* self, void*, gd::GameObject* obj) {
	LevelEditorLayer::addSpecial(self, obj);
	if (setting().onRotateSaws && RotateSaws::objectIsSaw(obj)) RotateSaws::beginRotateSaw(obj);

	//if (setting().onSmartStartPos) {
	//	switch (obj->m_objectID)
	//	{
	//	case 31:
	//		m_startPositions.push_back(static_cast<gd::StartPosObject*>(obj));
	//		break;
	//	case 12:
	//	case 13:
	//	case 47:
	//	case 111:
	//	case 660:
	//	case 745: m_gamemodePortals.push_back(obj);
	//		break;
	//	case 45:
	//	case 46: m_mirrorPortals.push_back(obj);
	//		break;
	//	case 99:
	//	case 101: m_miniPortals.push_back(obj);
	//		break;
	//	case 286:
	//	case 287: m_dualPortals.push_back(obj);
	//		break;
	//	case 200:
	//	case 201:
	//	case 202:
	//	case 203: m_speedChanges.push_back(obj);
	//		break;
	//	default: break;
	//	}
	//}
}

void __fastcall LevelEditorLayer::removeObjectH(gd::LevelEditorLayer* self, void*, gd::GameObject* obj, bool idk) {
	LevelEditorLayer::removeObject(self, obj, idk);
	if (setting().onRotateSaws && RotateSaws::objectIsSaw(obj)) RotateSaws::stopRotateSaw(obj);
}