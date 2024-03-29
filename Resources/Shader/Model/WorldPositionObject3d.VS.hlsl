#include "DeferredShadingObject3d.hlsli"

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b1);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);

struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
};

WorldPositionVertexShaderOutput main(VertexShaderInput input)
{
    WorldPositionVertexShaderOutput output;
    float4x4 resultMatrix;
    float4x4 CameraMatrix = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
    resultMatrix = mul(gTransformationMatrix.WVP, CameraMatrix);
  
    output.position = mul(input.position, resultMatrix);
    output.normal = normalize(mul(input.normal, (float32_t3x3) resultMatrix));
    output.texcoord = input.texcoord;
    output.worldMatrix = resultMatrix;
    return output;
}
