#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"Transform/STransformQua.h"
#include"Animation/SAnimation.h"

const uint32_t kNumMaxInfluence = 4;
struct VertexInfluence
{
	std::array<float, kNumMaxInfluence>weights;
	std::array<int32_t, kNumMaxInfluence>jointIndicess;
};

struct WellForGPU
{
	Math::Matrix::Matrix4x4 skeletonSpaceMatrix;
	Math::Matrix::Matrix4x4 skeletonSpaceInverseTransposeMatrix;
};
struct SkinCluster
{
	std::vector<Math::Matrix::Matrix4x4>inverseBindMatrices;
	ComPtr<ID3D12Resource>influenceResource;
	D3D12_VERTEX_BUFFER_VIEW influenceBufferView;
	std::span<VertexInfluence>mappedInfluence;
	uint32_t srvIndex;
};
struct  VertexData
{
	Math::Vector::Vector4 position;
	Math::Vector::Vector2 texcoord;
	Math::Vector::Vector3 normal;
};
struct LightData
{
	Math::Vector::Vector4 color;
	Math::Vector::Vector3 direction;
	float intensity;
};

struct  TransformationViewMatrix
{
	Math::Matrix::Matrix4x4 view;
	Math::Matrix::Matrix4x4 viewProjection;
	Math::Matrix::Matrix4x4 orthographic;
	Math::Matrix::Matrix4x4 InverseViewProjection;
	Math::Matrix::Matrix4x4 InverseProjection;
	Math::Vector::Vector3 position;
};

struct TransformationMatrix {
	Math::Matrix::Matrix4x4 WVP;
	Math::Matrix::Matrix4x4 world;
	Math::Vector::Vector3 worldPos;
};

struct ParticleData {
	Math::Matrix::Matrix4x4 WVP;
	Math::Matrix::Matrix4x4 world;
	Math::Vector::Vector4 color;
	Math::Matrix::Matrix4x4 uvTransform;
};
struct MaterialData
{
	uint32_t handle{};
	string textureFilePath{};
};

struct NodeData
{
	Math::Matrix::Matrix4x4 localMatrix;
	std::string name;
	std::vector<NodeData>children;
	Engine::Transform::TransformQua transform;
	SAnimation::Skeleton skeleton;
};

struct VetexWeightData
{
	float weight;
	uint32_t vertexIndex;
};

struct JointWeightData
{
	Math::Matrix::Matrix4x4 inverseBindPoseMatrix;
	std::vector<VetexWeightData>vertexWeights;
};

struct  SModelData
{
	vector<VertexData> vertices;
	std::vector<uint32_t>indecs;
	MaterialData material;

#pragma region Skinning
	NodeData node;
	std::map<std::string, JointWeightData>skinClusterData;
	std::vector<Math::Matrix::Matrix4x4>inverseBindMatrices;
	SAnimation::Skeleton skeleton;
	bool skinningFlag_ = false;
#pragma endregion

	string normalilePath;
	uint32_t normalTexHandle;
	string basefilePath;
	uint32_t baseTexHandle;
	string fileFormat;
};

struct PostEffectParam
{
	Math::Matrix::Matrix4x4 uvMatrix;
	Math::Vector::Vector2 texSize = { 0.0f,0.0f };

};

struct DefferredMaterial
{
	Math::Vector::Vector4 color = { 1,1,1,1 };
};

struct PostEffectAdjustedColorParam
{
	/// <summary>
	/// モノクロ
	/// </summary>
	bool grayScaleFlag = false;
	float GrayFactor = 0.0f;

	/// <summary>
	/// 反転
	/// </summary>
	bool InvertFlag = false;
	float InvertFactor = 0.0f;

	/// <summary>
	/// 明度
	/// </summary>
	bool BringhtnessFlag = false;
	float BringhtnessFactor = 0.0f;

	/// <summary>
	/// コントラスト
	/// </summary>
	bool ContrastFlag = false;
	float ContrastFactor = 0.0f;

	/// <summary>
	/// 色相
	/// </summary>
	bool HueFlag = false;
	float HueFactor = 0.0f;

	/// <summary>
	/// ビネット
	/// </summary>
	bool vignetteFlag = false;
	float vignetteFactor = 0.0f;
	float vignetteScale = 0.0f;
	Math::Vector::Vector3 viganetteColor_ = { 1,0,0 };

	float fogScale_ = 1.0f;
	float fogAttenuationRate_ = 1.0f;
	float fogStart = 10.0f;
	float fogEnd = 100.0f;
};

struct  PostEffectBlurParam
{
	bool UseFlag = false;
	float Intensity = 0.0f;

};

struct  Material
{
	Math::Vector::Vector4 color = { 1,1,1,1 };
	Math::Matrix::Matrix4x4 uvTransform;

	float PerlinNoiseScale = 0.0f;
	float perlinNoiseFactor = 0.0f;
	Math::Vector::Vector2 perlinNoisePos = {};

	float shininess = 70.0f;
	float specular_ = 1.0f;
	float metalness_ = 1.0f;
	float roughness_ = 1.0f;

	float scatterCoefficient = 0.5f;
	float absorptionCoefficient = 0.5f;
	float scatterDistance = 0.5f;
	float grayFactor = 0.0f;

	float dissolveMask = 0.0f;
	Math::Vector::Vector2 dissolveEdgeMinMax = {};
	float pad1;

	Math::Vector::Vector4 dissolveEdgeColor = { 1.0f,1.0f,1.0f,1.0f };

	Math::Matrix::Matrix4x4 noiseUvTransform = {};
	float perlinNoiseTimer = 0.0f;
};


namespace Engine::Buffer
{
	/// <summary>
	/// バッファ作製クラス
	/// </summary>
	class CreateResources
	{
	public:

		/// <summary>
		/// Resource作成
		/// </summary>
		/// <param name="device"></param>
		/// <param name="sizeInbyte"></param>
		/// <returns></returns>
		static ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInbyte);

		static void CreateBufferResource(size_t sizeInbyte, ComPtr<ID3D12Resource>& Resource);


		/// <summary>
		/// BufferView��쐬
		/// </summary>
		/// <param name="sizeInbyte"></param>
		/// <param name="Resource"></param>
		/// <returns></returns>
		static D3D12_VERTEX_BUFFER_VIEW VertexCreateBufferView(size_t sizeInbyte, ID3D12Resource* Resource, int size);
		/// <summary>
		/// index��BufferView
		/// </summary>
		/// <param name="NumVertex"></param>
		/// <returns></returns>
		static D3D12_INDEX_BUFFER_VIEW IndexCreateBufferView(size_t sizeInbyte, ComPtr<ID3D12Resource> Resource);

	private:

		ID3D12Resource* resource_ = nullptr;
	};
}