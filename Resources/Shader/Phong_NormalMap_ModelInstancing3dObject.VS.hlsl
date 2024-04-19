#include"LightingObject3d.hlsli"

StructuredBuffer<TransformationMatrix> gTransformationMatrix : register(t0);

ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);


struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
    float32_t3 worldPosition : WORLDPOSITION0;

};

VertexShaderOutput main(VertexShaderInput input, uint32_t instanceId : SV_InstanceID)
{
    VertexShaderOutput output;
    float32_t4x4 resultMatrix;

    float32_t4x4 CameraMatrix = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
	//view変換
    resultMatrix = mul(gTransformationMatrix[instanceId].WVP, CameraMatrix);

    output.position = mul(input.position, resultMatrix);
    output.texcoord = input.texcoord;

    output.normal = normalize(mul(input.normal, (float32_t3x3) gTransformationMatrix[instanceId].World));
    output.worldPosition = mul(input.position, gTransformationMatrix[instanceId].WVP).xyz;
    output.worldMatrix = resultMatrix;
    return output;
}