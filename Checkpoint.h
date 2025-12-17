#pragma once

#include "pch.h"

struct CheckPointStorage {
    float rot;
    float rot_2;
    double velocity;

    static CheckPointStorage from(gd::PlayerObject* player) {
        return (CheckPointStorage({
            *(float*)((size_t)player + 0x18), // rot
            *(float*)((size_t)player + 0x1C), // rot
            *(double*)((size_t)player + 0x540)
            }));
    }

    void restore(gd::PlayerObject* player) {
        *(double*)((size_t)player + 0x540) = velocity;
        *(float*)((size_t)player + 0x018) = rot;
        *(float*)((size_t)player + 0x01c) = rot_2;
    }
};

struct CheckPoint {
    CheckPointStorage p1;
    CheckPointStorage p2;

    static CheckPoint from(gd::PlayLayer* playLayer) {
        gd::PlayerObject* player1 = playLayer->m_player;
        gd::PlayerObject* player2 = playLayer->m_player2;

        return (
            CheckPoint({
                CheckPointStorage::from(player1),
                CheckPointStorage::from(player2)
                })
            );
    }

    void restore(gd::PlayLayer* playLayer) {
        p1.restore(playLayer->m_player);
        p2.restore(playLayer->m_player2);
    }
};