#include "PostEffect.hlsli"

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<DirectionLightParam> gDirectionParam : register(b5);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);

struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
};

VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    float32_t4x4 resultMatrix;
    //float32_t4x4 DirectionalLightVP = mul(gDirectionParam.mat, gTransformationViewMatrix.orthographic);
    float32_t4x4 CameraVP = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
   
    float32_t4 pos = mul(mul(input.position, gTransformationMatrix.world),CameraVP);
    output.position = pos;
 
    output.texcoord = input.texcoord;
    return output;
}