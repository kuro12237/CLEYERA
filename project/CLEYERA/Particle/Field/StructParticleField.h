#pragma once
#include"Particle/GpuParticle.h"

namespace Particle
{
    namespace FieldType
    {
        /// <summary>
        /// ãzÇ¢çûÇ›
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
    }
}