#include "IParticleEmitDraw.h"

void IParticleEmitDraw::Create(PrimitiveType type, string name)
{
	name_ = name;
	if (type == SPHERE)
	{
		CreateSphereVertex();
	}
}

void IParticleEmitDraw::Update()
{
}

void IParticleEmitDraw::Draw(const WorldTransform& w)
{
	line_->SetWorldMat(w.matWorld);
	line_->SetMaterial({ 0.0f,0.0f,0.0f,1.0f });
	line_->Draw();
}

void IParticleEmitDraw::CreateSphereVertex()
{
	//ï™äÑêî
	const uint32_t SUBDIVISION = 8;
	line_ = make_unique<Primitive::LineModel>();
	line_->Create(name_,(SUBDIVISION * SUBDIVISION * SUBDIVISION) / 2);

	//lat
	const float LON_EVERY = 2.0f * static_cast<float>(std::numbers::pi) / float(SUBDIVISION);
	//lon
	const float LAT_EVERY = static_cast<float>(std::numbers::pi) / float(SUBDIVISION);
	float thetaD = static_cast<float>(std::numbers::pi) / SUBDIVISION;
	float phiD = 2.0f * static_cast<float>(std::numbers::pi) / SUBDIVISION;
	const float radius = 1.0f;

	size_t index = 0;
	for (uint32_t latIndex = 0; latIndex < SUBDIVISION; ++latIndex) {
		float lat = -static_cast<float>(std::numbers::pi) / 2.0f + LAT_EVERY * latIndex;
		for (uint32_t lonIndex = 0; lonIndex < SUBDIVISION; ++lonIndex) {
			//åªç›ÇÃåoìx
			float lon = lonIndex * LON_EVERY;
			Math::Vector::Vector3 a, b, c = {};

			a = { radius * (cosf(lat) * cosf(lon)),
				radius * (sinf(lat)),
				radius * (cosf(lat) * sinf(lon))
			};

			b = { radius * (cosf(lat + thetaD) * cosf(lon)),
				radius * (sinf(lat + thetaD)),
				radius * (cosf(lat + thetaD) * sinf(lon))
			};

			c = { radius * (cosf(lat) * cosf(lon + phiD)),
				radius * (sinf(lat)),
				radius * (cosf(lat) * sinf(lon + phiD))
			};

			line_->PushBack(a, b, index);
			line_->PushBack(a, c, index);
		}
	}
}

