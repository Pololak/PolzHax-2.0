#pragma once
#include "pch.h"

struct Labels {
	static Labels* get() {
		Labels* ret;
		return ret;
	}

	gd::PlayLayer* getPlayLayer() {
		return gd::GameManager::sharedState()->getPlayLayer();
	}

	void updatePositions();
	void updateFont();

	std::string keyToFont(int);

	void createAttemptsLabel();
};