#pragma once
#include<cstdint>

const uint32_t kCollisionAttributePlayer = 0b00001;
const uint32_t kCollisionAttributeEnemy  = 0b00010;
const uint32_t kCollisionAttributeFlag   = 0b00100;
const uint32_t kCollisionAttributeGround = 0b01000;

const uint32_t kCollisionMaskPlayer      = 0b11110;
const uint32_t kCollisionMaskEnemy       = 0b11101;
const uint32_t kCollisionMaskFlag        = 0b11011;
const uint32_t kCollisionMaskGround      = 0b10111;

const uint32_t playerID = 0b00001;
const uint32_t enemyID  = 0b00010;
const uint32_t flagID   = 0b00011;
const uint32_t groundID = 0b00100;
const uint32_t playerHammerID = 0b00101;
const uint32_t enemyAttackID = 0b00111;