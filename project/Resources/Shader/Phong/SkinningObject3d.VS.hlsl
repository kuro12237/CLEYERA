#include"PhongObject3d.hlsli"

struct Well
{
    float32_t4x4 skeletonSpaceMatrix;
    float32_t4x4 skeletonSpaceInverseTransposeMatrix;
};

struct Skinned
{
    float32_t4 pos;
    float32_t3 normal;
};

StructuredBuffer<Well> gMatrixPalette : register(t3);
ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);

Skinned Skinning(SkinningVertexShaderInput input)
{
    Skinned skinned;

	//位置の変換
    skinned.pos = mul(input.position, gMatrixPalette[input.index.x].skeletonSpaceMatrix) * input.weight.x;
    skinned.pos += mul(input.position, gMatrixPalette[input.index.y].skeletonSpaceMatrix) * input.weight.y;
    skinned.pos += mul(input.position, gMatrixPalette[input.index.z].skeletonSpaceMatrix) * input.weight.z;
    skinned.pos += mul(input.position, gMatrixPalette[input.index.w].skeletonSpaceMatrix) * input.weight.w;
    skinned.pos.w = 1.0f;

	//法線の変換
    skinned.normal = mul(input.normal, (float32_t3x3) gMatrixPalette[input.index.x].skeletonSpaceInverseTransposeMatrix) * input.weight.x;
    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPalette[input.index.y].skeletonSpaceInverseTransposeMatrix) * input.weight.y;
    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPalette[input.index.z].skeletonSpaceInverseTransposeMatrix) * input.weight.z;
    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPalette[input.index.w].skeletonSpaceInverseTransposeMatrix) * input.weight.w;
    skinned.normal = normalize(skinned.normal);

    return skinned;
}

VertexShaderOutput main(SkinningVertexShaderInput input ,uint32_t vertexId : SV_VertexID)
{
    VertexShaderOutput output;
  
   
    Skinned skinned = Skinning(input);
    float32_t4x4 CameraMatrix = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
	//view変換
    float32_t4x4 worldMat = mul(gTransformationMatrix.World, CameraMatrix);

    output.position = mul(skinned.pos, worldMat);
    output.worldPosition = mul(skinned.pos, gTransformationMatrix.World).xyz;
    output.texcoord = input.texcoord;
    output.normal = normalize(mul(skinned.normal, (float32_t3x3) gTransformationMatrix.World));

    return output;
}


