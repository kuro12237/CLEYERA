#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"Transform/STransformQua.h"
#include"Animation/SAnimation.h"

struct  VertexData
{
	Vector4 position;
    Vector2 texcoord;
	Vector3 normal;
};
struct LightData
{
	Vector4 color;
	Vector3 direction;
	float intensity;
};

struct  TransformationViewMatrix
{
	Matrix4x4 view;
	Matrix4x4 viewProjection;
	Matrix4x4 orthographic;
	Vector3 position;
	float pad[1];
	Matrix4x4 InverseViewProjection;
	Matrix4x4 InverseProjection;
};

struct TransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 world;
};

struct ParticleData{
	Matrix4x4 WVP;
	Matrix4x4 world;
	Vector4 color;
	Matrix4x4 uvTransform;
};
struct MaterialData
{
	uint32_t handle{};
	string textureFilePath{};
};

struct NodeData 
{
	Matrix4x4 localMatrix;
	std::string name;
	std::vector<NodeData>children;
	TransformQua transform;
	SAnimation::Skeleton skeleton;
};

struct VetexWeightData
{
	float weight;
	uint32_t vertexIndex;
};

struct JointWeightData
{
	Matrix4x4 inverseBindPoseMatrix;
	std::vector<aiVertexWeight>vertexWeights;
};

struct  SModelData
{
	std::map<std::string, JointWeightData>skinClusterData;
	vector<VertexData> vertices;
	std::vector<uint32_t>indecs;
	MaterialData material;
	NodeData node;
	string texFilePath;
	uint32_t texHandle;
	string normalilePath;
	uint32_t normalTexHandle;
	string basefilePath;
	uint32_t baseTexHandle;
};

struct PostEffectParam
{
	Matrix4x4 uvMatrix;
	Vector2 texSize = { 0.0f,0.0f };

};

struct DefferredMaterial
{
	Vector4 color = { 1,1,1,1 };
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
};

struct  PostEffectBlurParam
{
	bool UseFlag = false;
	float Intensity = 0.0f;

};


struct ResourcePeroperty
{
	D3D12_VERTEX_BUFFER_VIEW BufferView;
	D3D12_INDEX_BUFFER_VIEW IndexBufferView;
	ComPtr<ID3D12Resource> Index;
	ComPtr<ID3D12Resource> Vertex;
	ComPtr<ID3D12Resource> Material;
	ComPtr<ID3D12Resource> wvpResource;
	ComPtr<ID3D12Resource> Light;
	ComPtr<ID3D12Resource> instancingResource;
};

struct  Material
{
	Vector4 color;
	Matrix4x4 uvTransform;
	float shininess = 70.0f;
	float specular_ = 1.0f;
	float metalness_ = 1.0f;
	float roughness_ = 1.0f;
	float scatterCoefficient=0.5f;
	float absorptionCoefficient=0.5f;
	float scatterDistance=0.5f;
};



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
