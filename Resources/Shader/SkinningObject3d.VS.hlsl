#include"LightingObject3d.hlsli"

struct Well
{
    float32_t4x4 skeltonSpaceMatrix;
    float32_t4x4 skeltonSpaceInverseTransposeMatrix;
};

struct Skinned
{
    float32_t4 pos;
    float32_t3 normal;
};
StructuredBuffer<Well> gMatrixPallate : register(t7);

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);


Skinned Skinning(VertexShaderInput input)
{
    Skinned skinned;

    skinned.pos = mul(input.position, gMatrixPallate[input.index.x].skeltonSpaceMatrix) * input.weight.x;
    skinned.pos += mul(input.position, gMatrixPallate[input.index.y].skeltonSpaceMatrix) * input.weight.y;
    skinned.pos += mul(input.position, gMatrixPallate[input.index.z].skeltonSpaceMatrix) * input.weight.z;
    skinned.pos += mul(input.position, gMatrixPallate[input.index.w].skeltonSpaceMatrix) * input.weight.w;
    skinned.pos.w = 1.0f;
    
    //float32_t4x4 inver =
    skinned.normal = mul(input.normal, (float32_t3x3) gMatrixPallate[input.index.x].skeltonSpaceInverseTransposeMatrix) * input.weight.x;
    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPallate[input.index.y].skeltonSpaceInverseTransposeMatrix) * input.weight.y;
    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPallate[input.index.z].skeltonSpaceInverseTransposeMatrix) * input.weight.z;
    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPallate[input.index.w].skeltonSpaceInverseTransposeMatrix) * input.weight.w;
    skinned.normal = normalize(skinned.normal);
    
    return skinned;
}

VertexShaderOutput main(VertexShaderInput input,uint32_t vertexId : SV_VertexID)
{
    VertexShaderOutput output;
    input.index = vertexId;
    Skinned skinned = Skinning(input);
    float32_t4x4 CameraMatrix = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
	//view変換
    float32_t4x4 worldMat = mul(gTransformationMatrix.WVP, CameraMatrix);

    output.position = mul(input.position, worldMat);
    output.worldPosition = mul(skinned.pos, worldMat).xyz;
    output.texcoord = input.texcoord;
    output.normal = input.normal; //normalize(mul(skinned.normal,(float32_t3x3)gTransformationMatrix.Wor))
    
    return output;
}


