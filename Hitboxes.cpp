#include "Hitboxes.h"
#include "state.h"

void Hitboxes::drawRect(CCDrawNode* drawer, CCRect const& rect, ccColor4F col) {
    constexpr size_t N = 4;
    CCPoint vert[N];

    vert[0] = CCPointMake(rect.getMinX(), rect.getMinY());
    vert[1] = CCPointMake(rect.getMinX(), rect.getMaxY());
    vert[2] = CCPointMake(rect.getMaxX(), rect.getMaxY());
    vert[3] = CCPointMake(rect.getMaxX(), rect.getMinY());

    auto colorA = ccc4FFromccc4B(ccc4(col.r, col.g, col.b, 0));

    drawer->drawPolygon(vert, N, colorA, .5f, col);
}

void Hitboxes::drawTriangleObj(CCDrawNode* drawer, gd::GameObject* ob, ccColor4F col) {
    constexpr size_t N = 3;
    CCPoint points[N];
    int i = 0;
    ob->updateOrientedBox();
    if (ob->m_OBB2D) {
        auto obb = ob->m_OBB2D;
        if (ob->m_isFlippedX || !ob->m_isFlippedY) points[i++] = obb->m_p1_1;
        if (!ob->m_isFlippedX || !ob->m_isFlippedY) points[i++] = obb->m_p1_2;
        if (!ob->m_isFlippedX || ob->m_isFlippedY) points[i++] = obb->m_p1_3;
        if (ob->m_isFlippedX || ob->m_isFlippedY) points[i++] = obb->m_p1_4;
    }
    else {
        auto rect = ob->getObjectRect();
        if (ob->m_isFlippedX || !ob->m_isFlippedY) points[i++] = CCPointMake(rect.getMinX(), rect.getMinY());
        if (!ob->m_isFlippedX || !ob->m_isFlippedY) points[i++] = CCPointMake(rect.getMinX(), rect.getMaxY());
        if (!ob->m_isFlippedX || ob->m_isFlippedY) points[i++] = CCPointMake(rect.getMaxX(), rect.getMaxY());
        if (ob->m_isFlippedX || ob->m_isFlippedY) points[i++] = CCPointMake(rect.getMaxX(), rect.getMinY());
    }

    drawer->drawPolygon(points, 3, { 0, 0, 0, 0 }, 0.5, col);
}

void Hitboxes::drawRectObj(CCDrawNode* drawer, gd::GameObject* ob, ccColor4F col) {
    ob->updateOrientedBox();

    CCPoint vert[4];

    if (ob->m_OBB2D) {
        vert[0] = ob->m_OBB2D->m_p1_1;
        vert[1] = ob->m_OBB2D->m_p1_2;
        vert[2] = ob->m_OBB2D->m_p1_3;
        vert[3] = ob->m_OBB2D->m_p1_4;
    }

    drawer->drawPolygon(vert, 4, { 0, 0, 0, 0 }, .5f, col);
}

void Hitboxes::drawCircleObj(CCDrawNode* drawer, gd::GameObject* ob, ccColor4F col) {
    ob->updateOrientedBox();
    if (!ob->m_OBB2D) return;
    auto rad = ob->getObjectRadius();

    constexpr size_t N = 64;
    constexpr float PI = 3.14159265;

    CCPoint vert[N];
    for (size_t i = 0; i < N; ++i) {
        vert[i] = ob->m_OBB2D->m_center + CCPointMake(std::cos(2 * PI * i / N), std::sin(2 * PI * i / N)) * rad;
    }
    drawer->drawPolygon(vert, N, { 0, 0, 0, 0 }, 0.5, col);
}

void Hitboxes::drawPlayerHitbox(gd::PlayerObject* player, CCDrawNode* drawNode)
{
    auto rect = player->getObjectRect();
    CCPoint pointRectangle[4];
    CCRect rectRectangle;
    CCRect rectRectangleSmall;
    pointRectangle[0] = CCPointMake(rect.getMinX(), rect.getMinY());
    pointRectangle[1] = CCPointMake(rect.getMinX(), rect.getMaxY());
    pointRectangle[2] = CCPointMake(rect.getMaxX(), rect.getMaxY());
    pointRectangle[3] = CCPointMake(rect.getMaxX(), rect.getMinY());

    auto p1x = pointRectangle[0].x - pointRectangle[1].x;
    auto p1y = pointRectangle[0].y - pointRectangle[1].y;
    auto distance1 = sqrt(p1x * p1x + p1y * p1y);

    auto p2x = pointRectangle[1].x - pointRectangle[2].x;
    auto p2y = pointRectangle[1].y - pointRectangle[2].y;
    auto distance2 = sqrt(p2x * p2x + p2y * p2y);

    auto distanceS1 = distance1 / 4;
    auto distanceS2 = distance2 / 4;

    rectRectangle.setRect(player->getPositionX() - distance1 / 2, player->getPositionY() - distance2 / 2, distance1, distance2);
    rectRectangleSmall.setRect(player->getPositionX() - distanceS1 / 2, player->getPositionY() - distanceS2 / 2, distanceS1, distanceS2);

    CCPoint vert[4];

    if (player->getOrientedBox()) {
        vert[0] = player->getOrientedBox()->m_p1_1;
        vert[1] = player->getOrientedBox()->m_p1_2;
        vert[2] = player->getOrientedBox()->m_p1_3;
        vert[3] = player->getOrientedBox()->m_p1_4;
    }

    Hitboxes::drawRect(drawNode, rectRectangleSmall, { setting().solidHitboxesR / 255.f, setting().solidHitboxesG / 255.f, setting().solidHitboxesB / 255.f, setting().hitboxesOpacity / 255.f });
    drawNode->drawPolygon(vert, 4, { 0, 0, 0, 0 }, .5, { (setting().hazardHitboxesR / 255.f) / 2.f, (setting().hazardHitboxesG / 255.f) / 2.f, (setting().hazardHitboxesB / 255.f) / 2.f, setting().hitboxesOpacity / 255.f });
    Hitboxes::drawRect(drawNode, rectRectangle, { setting().hazardHitboxesR / 255.f, setting().hazardHitboxesG / 255.f, setting().hazardHitboxesB / 255.f, setting().hitboxesOpacity / 255.f });
}

void Hitboxes::drawSolidsObjectHitbox(gd::GameObject* obj, CCDrawNode* drawNode) {
    if (obj->m_groupDisable || obj->m_isDestroyed) return;
    switch (obj->m_objectType)
    {
    case gd::GameObjectType::kGameObjectTypeSolid:
    case gd::GameObjectType::kGameObjectTypeBreakable:
        Hitboxes::drawRectObj(drawNode, obj, { setting().solidHitboxesR / 255.f, setting().solidHitboxesG / 255.f, setting().solidHitboxesB / 255.f, setting().hitboxesOpacity / 255.f }); break;
    case gd::GameObjectType::kGameObjectTypeSlope:
        Hitboxes::drawTriangleObj(drawNode, obj, { setting().solidHitboxesR / 255.f, setting().solidHitboxesG / 255.f, setting().solidHitboxesB / 255.f, setting().hitboxesOpacity / 255.f }); break;
    }
}

void Hitboxes::drawHazardsObjectHitbox(gd::GameObject* obj, CCDrawNode* drawNode) {
    if (obj->m_groupDisable || obj->m_isDestroyed) return;
    if ((obj->getObjectRadius() > 0) && obj->m_objectType == gd::GameObjectType::kGameObjectTypeHazard)
        Hitboxes::drawCircleObj(drawNode, obj, { setting().hazardHitboxesR / 255.f, setting().hazardHitboxesG / 255.f, setting().hazardHitboxesB / 255.f, setting().hitboxesOpacity / 255.f });
    else if (obj->m_objectType == gd::GameObjectType::kGameObjectTypeHazard)
        Hitboxes::drawRectObj(drawNode, obj, { setting().hazardHitboxesR / 255.f, setting().hazardHitboxesG / 255.f, setting().hazardHitboxesB / 255.f, setting().hitboxesOpacity / 255.f });
}

void Hitboxes::drawSpecialsObjectHitbox(gd::GameObject* obj, CCDrawNode* drawNode) {
    if (obj->m_groupDisable || obj->m_isDestroyed) return;
    switch (obj->m_objectType)
    {
    case gd::GameObjectType::kGameObjectTypeInverseGravityPortal:
    case gd::GameObjectType::kGameObjectTypeNormalGravityPortal:
    case gd::GameObjectType::kGameObjectTypeShipPortal:
    case gd::GameObjectType::kGameObjectTypeCubePortal:
    case gd::GameObjectType::kGameObjectTypeYellowJumpPad:
    case gd::GameObjectType::kGameObjectTypePinkJumpPad:
    case gd::GameObjectType::kGameObjectTypeGravityPad:
    case gd::GameObjectType::kGameObjectTypeYellowJumpRing:
    case gd::GameObjectType::kGameObjectTypePinkJumpRing:
    case gd::GameObjectType::kGameObjectTypeGravityRing:
    case gd::GameObjectType::kGameObjectTypeInverseMirrorPortal:
    case gd::GameObjectType::kGameObjectTypeNormalMirrorPortal:
    case gd::GameObjectType::kGameObjectTypeBallPortal:
    case gd::GameObjectType::kGameObjectTypeRegularSizePortal:
    case gd::GameObjectType::kGameObjectTypeMiniSizePortal:
    case gd::GameObjectType::kGameObjectTypeUfoPortal:
    case gd::GameObjectType::kGameObjectTypeSecretCoin:
    case gd::GameObjectType::kGameObjectTypeDualPortal:
    case gd::GameObjectType::kGameObjectTypeSoloPortal:
    case gd::GameObjectType::kGameObjectTypeWavePortal:
    case gd::GameObjectType::kGameObjectTypeRobotPortal:
    case gd::GameObjectType::kGameObjectTypeTeleportPortal:
    case gd::GameObjectType::kGameObjectTypeGreenRing:
    case gd::GameObjectType::kGameObjectTypeCollectible:
    case gd::GameObjectType::kGameObjectTypeUserCoin:
        Hitboxes::drawRectObj(drawNode, obj, { setting().specialHitboxesR / 255.f, setting().specialHitboxesG / 255.f, setting().specialHitboxesB / 255.f, setting().hitboxesOpacity / 255.f }); break;
    }
    switch (obj->m_objectID)
    {
    case 200:
    case 201:
    case 202:
    case 203:
    case 749:
        Hitboxes::drawRectObj(drawNode, obj, { setting().specialHitboxesR / 255.f, setting().specialHitboxesG / 255.f, setting().specialHitboxesB / 255.f, setting().hitboxesOpacity / 255.f }); break;
    }
}