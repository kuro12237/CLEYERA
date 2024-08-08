#include "StructGpuParticleEmitter.h"

void Particle::System::CreateSphere(unique_ptr<Primitive::LineModel>& lines, string name)
{
	//分割数
	const uint32_t SUBDIVISION = 8;
	lines = make_unique<Primitive::LineModel>();
	lines->Create(name, (SUBDIVISION * SUBDIVISION * SUBDIVISION) / 2);
	lines->resize((SUBDIVISION * SUBDIVISION * SUBDIVISION / 2));
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
			//現在の経度
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

			lines->SetVec(a, b, index);
			lines->SetVec(a, c, index);
		}
	}
}

void Particle::System::CreateBox(unique_ptr<Primitive::LineModel>& lines, string name)
{
	//分割数
	const uint32_t SUBDIVISION = 8;
	lines = make_unique<Primitive::LineModel>();
	lines->Create(name, 24);
	lines->resize(24);

	Math::Vector::Vector3 min = { -1.0f, -1.0f, -1.0f };
	Math::Vector::Vector3 max = { 1.0f, 1.0f, 1.0f };

	Math::Vector::Vector3 vertices[8] = {
		{ min.x, max.y, min.z },  // Front Left Top
		{ max.x, max.y, min.z },  // Front Right Top
		{ min.x, min.y, min.z },  // Front Left Bottom
		{ max.x, min.y, min.z },  // Front Right Bottom
		{ min.x, max.y, max.z },  // Back Left Top
		{ max.x, max.y, max.z },  // Back Right Top
		{ min.x, min.y, max.z },  // Back Left Bottom
		{ max.x, min.y, max.z }   // Back Right Bottom
	};

	// 手前
	lines->SetVec(vertices[0], vertices[1], 0);
	lines->SetVec(vertices[1], vertices[3], 2);
	lines->SetVec(vertices[3], vertices[2], 4);
	lines->SetVec(vertices[2], vertices[0], 6);

	// 奥
	lines->SetVec(vertices[4], vertices[5], 8);
	lines->SetVec(vertices[5], vertices[7], 10);
	lines->SetVec(vertices[7], vertices[6], 12);
	lines->SetVec(vertices[6], vertices[4], 14);

	// 縦方向
	lines->SetVec(vertices[0], vertices[4], 16);
	lines->SetVec(vertices[1], vertices[5], 18);
	lines->SetVec(vertices[2], vertices[6], 20);
	lines->SetVec(vertices[3], vertices[7], 22);
}

void Particle::System::UpdateBox(unique_ptr<Primitive::LineModel>& lines, EmitType::BoxParam box)
{
	Math::Vector::Vector3 min = box.sizeMin;
	Math::Vector::Vector3 max = box.sizeMax;

	const Math::Vector::Vector3 vertices[8] = {
		{ min.x, max.y, min.z },  // Front Left Top
		{ max.x, max.y, min.z },  // Front Right Top
		{ min.x, min.y, min.z },  // Front Left Bottom
		{ max.x, min.y, min.z },  // Front Right Bottom
		{ min.x, max.y, max.z },  // Back Left Top
		{ max.x, max.y, max.z },  // Back Right Top
		{ min.x, min.y, max.z },  // Back Left Bottom
		{ max.x, min.y, max.z }   // Back Right Bottom
	};

	// 手前
	lines->SetVec(vertices[0], vertices[1], 0);
	lines->SetVec(vertices[1], vertices[3], 2);
	lines->SetVec(vertices[3], vertices[2], 4);
	lines->SetVec(vertices[2], vertices[0], 6);

	// 奥
	lines->SetVec(vertices[4], vertices[5], 8);
	lines->SetVec(vertices[5], vertices[7], 10);
	lines->SetVec(vertices[7], vertices[6], 12);
	lines->SetVec(vertices[6], vertices[4], 14);

	// 縦方向
	lines->SetVec(vertices[0], vertices[4], 16);
	lines->SetVec(vertices[1], vertices[5], 18);
	lines->SetVec(vertices[2], vertices[6], 20);
	lines->SetVec(vertices[3], vertices[7], 22);
}

void Particle::System::UpdateSphere(unique_ptr<Primitive::LineModel>& lines, EmitType::SphereParam sphere)
{
	//分割数
	const uint32_t SUBDIVISION = 8;
	//lat
	const float LON_EVERY = 2.0f * static_cast<float>(std::numbers::pi) / float(SUBDIVISION);
	//lon
	const float LAT_EVERY = static_cast<float>(std::numbers::pi) / float(SUBDIVISION);
	float thetaD = static_cast<float>(std::numbers::pi) / SUBDIVISION;
	float phiD = 2.0f * static_cast<float>(std::numbers::pi) / SUBDIVISION;
	const float radius = sphere.radious;

	size_t index = 0;
	for (uint32_t latIndex = 0; latIndex < SUBDIVISION; ++latIndex) {
		float lat = -static_cast<float>(std::numbers::pi) / 2.0f + LAT_EVERY * latIndex;
		for (uint32_t lonIndex = 0; lonIndex < SUBDIVISION; ++lonIndex) {
			//現在の経度
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

			lines->SetVec(a, b, index);
			index += 2;
			lines->SetVec(a, c, index);
			index += 2;
		}
	}
}
