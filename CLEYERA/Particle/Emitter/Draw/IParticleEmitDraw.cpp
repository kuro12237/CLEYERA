#include "IParticleEmitDraw.h"

void IParticleEmitDraw::Create(PrimitiveType type)
{
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
	for (auto it = lines_.begin(); it != lines_.end(); ++it) {
		(*it)->SetWorldMat(w.matWorld);
		(*it)->Draw();
	}
}

void IParticleEmitDraw::CreateSphereVertex()
{
	//30.20.30
	//ï™äÑêî
	const uint32_t SUBDIVISION = 10;
	//lat
	const float LON_EVERY = 2.0f * static_cast<float>(std::numbers::pi) / float(SUBDIVISION);
	//lon
	const float LAT_EVERY = static_cast<float>(std::numbers::pi) / float(SUBDIVISION);
	float thetaD = static_cast<float>(std::numbers::pi) / SUBDIVISION;
	float phiD = 2.0f * static_cast<float>(std::numbers::pi) / SUBDIVISION;
	const float radius = 1.0f;

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

			unique_ptr<LineModel>lineA = make_unique<LineModel>();
			lineA->Create();
			//ab
			lineA->SetStartEndPos(a, b);

			unique_ptr<LineModel>lineB = make_unique<LineModel>();
			lineB->Create();
			//ac
			lineB->SetStartEndPos(a, c);

			lines_.push_back(move(lineA));
			lines_.push_back(move(lineB));
		}
	}
}

