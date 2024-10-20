#pragma once
#include"Pch.h"

/// <summary>
/// �Q�[���̓����蔻���mask�ݒ�
/// </summary>
namespace CollisionMask
{
	// Block-related definitions
	const static uint32_t kBlockMask = 0b111111111;        // 0b111111111 (511) (���ׂĂƓ�����)
	const static uint32_t kBlockAttribute = 0b000000001;   // 0b000000001 (1)

	// Player-related definitions
	const static uint32_t kPlayerMask = 0b111111101;       // 0b111111101 (253) (�v���C���[�̒e�ȊO�Ɠ�����)
	const static uint32_t kPlayerAttribute = 0b000000010;  // 0b000000010 (2)

	// Player bullet-related definitions
	const static uint32_t kPlayerBulletMask = 0b111111001; // 0b111111001 (249) (�v���C���[�ƃ|�[�^���ȊO�Ɠ�����)
	const static uint32_t kPlayerBulletAttribute = 0b000000100; // 0b000000100 (4)

	// Enemy-related definitions
	const static uint32_t kEnemyWalkMask = 0b111101111;    // 0b111101111 (487) (�|�[�^���ȊO�Ɠ�����)
	const static uint32_t kEnemyWalkAttribute = 0b000001000; // 0b000001000 (8)

	// Portal-related definitions
	const static uint32_t kPortalMask = 0b111101111;       // 0b111101111 (487) (�v���C���[�̒e�ƃG�l�~�[�ȊO�Ɠ�����)
	const static uint32_t kPortalAttribute = 0b000010000;  // 0b000010000 (16)

	// Player only (�v���C���[�Ƃ���������Ȃ�)
	const static uint32_t kWarpGateMask = 0b000000010;    // 0b000000010 (2) (�v���C���[�Ƃ���������Ȃ�)
	const static uint32_t kWarpGateAttribute = 0b001000000; // 0b001000000 (64)
}