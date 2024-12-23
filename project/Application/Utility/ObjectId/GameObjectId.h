#pragma once
#include"Pch.h"

/// <summary>
/// オブジェクトのid設定
/// </summary>

namespace ObjectId {

	const static uint32_t kOnlyCollideWithBlocksid = 0b000000000;

	const static uint32_t kNormalBlock = 0b000000001;      // 1
	const static uint32_t kPlayerId = 0b000000010;         // 2
	const static uint32_t kPlayerBullet = 0b000000100;     // 4

	const static uint32_t kEnemyWalkId = 0b000001000;      // 8
	const static uint32_t kGoalId = 0b000010000;           // 16


	const static uint32_t kGunEnemyId = 0b000100000;
	const static uint32_t kGunEnemyBulletId = 0b000100001;

	const static uint32_t kPortalIds[] = {
		0b000100000,  // 32
		0b001000000,  // 64
		0b010000000,  // 128
		0b100000000,  // 256
		0b100000001   // 257
	};

	const static uint32_t kStoneItem = 0b0001000000;       // 512

	const static uint32_t kWarpGateId = 0b0000000011;       // 
	const static uint32_t IStageCoinId = 0b0000000111;
}