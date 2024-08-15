#include "GeometryCollision.h"

using namespace Math::Matrix;
using namespace Math::Vector;

namespace GeometryCollision {

	// OBBのワールドマトリックス作成
	Math::Matrix::Matrix4x4 CreateOBBWorldMatrix(const OBB& obb) {

		Matrix4x4 worldMatrix{};

		for (int i = 0; i < 3; ++i) {
			worldMatrix.m[i][0] = obb.orientations[i].x;
			worldMatrix.m[i][1] = obb.orientations[i].y;
			worldMatrix.m[i][2] = obb.orientations[i].z;
			worldMatrix.m[i][3] = 0.0f;
		}

		worldMatrix.m[3][0] = obb.center.x;
		worldMatrix.m[3][1] = obb.center.y;
		worldMatrix.m[3][2] = obb.center.z;
		worldMatrix.m[3][3] = 1.0f;


		return worldMatrix;
	}


	// 射影の重複チェック
	bool TestAxis(const Vector3& axis, const OBB& obb1, const OBB& obb2) {

		// OBBの射影を計算
		auto projection1 = obbProjection(obb1, axis);
		auto projection2 = obbProjection(obb2, axis);

		// 射影が重なっているかチェック
		return projectionOverlap(projection1, projection2);
	}


	// 実際に重なってるかの計算
	bool projectionOverlap(const std::pair<float, float>& projection1, const std::pair<float, float>& projection2) {

		// 射影が重なっているかチェック
		return projection1.second >= projection2.first && projection2.second >= projection1.first;
	}


	// 頂点を軸に射影
	std::pair<float, float> obbProjection(const OBB& obb, const Vector3& axis) {

		float val = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z); // 正規化
		float newAxis = 0.0f;
		newAxis = newAxis / val;

		// OBB上の頂点を取得
		std::array<Vector3, 8> vertices{};
		for (int i = 0; i < 8; ++i) {
			Vector3 sign = { (i & 1) ? 1.0f : -1.0f, (i & 2) ? 1.0f : -1.0f, (i & 4) ? 1.0f : -1.0f };
			vertices[i] = {
				obb.center.x + obb.orientations[0].x * sign.x * obb.halfSize.x +
							  obb.orientations[1].x * sign.y * obb.halfSize.y +
							  obb.orientations[2].x * sign.z * obb.halfSize.z,
				obb.center.y + obb.orientations[0].y * sign.x * obb.halfSize.x +
							  obb.orientations[1].y * sign.y * obb.halfSize.y +
							  obb.orientations[2].y * sign.z * obb.halfSize.z,
				obb.center.z + obb.orientations[0].z * sign.x * obb.halfSize.x +
							  obb.orientations[1].z * sign.y * obb.halfSize.y +
							  obb.orientations[2].z * sign.z * obb.halfSize.z
			};
		}

		// 頂点を軸に射影
		std::array<float, 8> projections{};
		for (int i = 0; i < 8; ++i) {
			projections[i] = vertices[i].x * axis.x + vertices[i].y * axis.y + vertices[i].z * axis.z;
		}

		auto minmax = std::minmax_element(projections.begin(), projections.end());
		return std::make_pair(*minmax.first, *minmax.second);
	}


	// OBBの設定
	OBB SettingOBBProperties(OBBCollider* c) {

		OBB result{};

		result.center = c->GetWorldPosition();

		Matrix4x4 rotateMat = Math::Matrix::RotateXYZMatrix(c->GetRotate().x, c->GetRotate().y, c->GetRotate().z);
		result.orientations[0].x = rotateMat.m[0][0];
		result.orientations[0].y = rotateMat.m[0][1];
		result.orientations[0].z = rotateMat.m[0][2];
		result.orientations[1].x = rotateMat.m[1][0];
		result.orientations[1].y = rotateMat.m[1][1];
		result.orientations[1].z = rotateMat.m[1][2];
		result.orientations[2].x = rotateMat.m[2][0];
		result.orientations[2].y = rotateMat.m[2][1];
		result.orientations[2].z = rotateMat.m[2][2];

		result.halfSize = {
			.x = c->GetSize().x / 2.0f,
			.y = c->GetSize().y / 2.0f,
			.z = c->GetSize().z / 2.0f,
		};

		return result;
	}

	// AABBの設定
	AABB SettingAABBProperties(AABBCollider* c) {

		AABB result{};

		result.min = {
			.x = c->GetWorldPosition().x - (c->GetSize().x / 2.0f),
			.y = c->GetWorldPosition().y - (c->GetSize().y / 2.0f),
			.z = c->GetWorldPosition().z - (c->GetSize().z / 2.0f),
		};
		result.max = {
			.x = c->GetWorldPosition().x + (c->GetSize().x / 2.0f),
			.y = c->GetWorldPosition().y + (c->GetSize().y / 2.0f),
			.z = c->GetWorldPosition().z + (c->GetSize().z / 2.0f),
		};

		return result;
	}
}