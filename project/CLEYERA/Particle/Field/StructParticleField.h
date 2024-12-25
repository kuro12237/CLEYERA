#pragma once
#include"Particle/GpuParticle.h"

namespace Engine::Particle
{
    namespace FieldType
    {
        /// <summary>
        /// 吸い込み
        /// </summary>
        struct FieldSuction
        {
            Math::Vector::Vector3 translate;
            Math::Vector::Vector3 scale;
            Math::Vector::Vector3 rotate;

            int32_t use;

            Math::Vector::Vector3 sizeMin;
            Math::Vector::Vector3 sizeMax;

            float suctionPower;
        };

        /// <summary>
        /// 重力
        /// </summary>
        struct FieldGravity
        {
            Math::Vector::Vector3 translate;
            Math::Vector::Vector3 scale;
            Math::Vector::Vector3 rotate;

            int32_t use;

            Math::Vector::Vector3 sizeMin;
            Math::Vector::Vector3 sizeMax;

            float gravity;
        };
        
        
        /// <summary>
        /// 重力
        /// </summary>
        struct FieldHitBox
        {
            Math::Vector::Vector3 translate;
            Math::Vector::Vector3 scale;
            Math::Vector::Vector3 rotate;

            int32_t use;

            Math::Vector::Vector3 sizeMin;
            Math::Vector::Vector3 sizeMax;
        };
    }
}