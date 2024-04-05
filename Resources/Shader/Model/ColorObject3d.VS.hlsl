#include"DeferredShadingObject3d.hlsli"

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b1);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);

struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
};

ColorVertexShaderOutput main(VertexShaderInput input)
{
    ColorVertexShaderOutput output;
    float4x4 resultMatrix;
    float4x4 CameraMatrix = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
    resultMatrix = mul(gTransformationMatrix.WVP, CameraMatrix);

    output.position = mul(input.position, resultMatrix);
    output.texcoord = input.texcoord;
    return output;
}