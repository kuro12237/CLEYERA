#include"SkyBox.hlsli"

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);


VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    float32_t4x4 CameraMatrix = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
	//view変換
    float32_t4x4 resultMatrix = mul(gTransformationMatrix.WVP, CameraMatrix);

    output.position = mul(input.position, resultMatrix).xyww;
    output.texcoord = input.position.xyz;
    output.normal = input.normal;
    return output;
}