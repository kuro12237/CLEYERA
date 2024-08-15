#include"PhongObject3d.hlsli"

ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);

VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;
    float32_t4x4 resultMatrix;

    float32_t4x4 CameraMatrix = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
	//view変換
    resultMatrix = mul(gTransformationMatrix.WVP, CameraMatrix);

    output.position = mul(input.position, resultMatrix);
    output.texcoord = input.texcoord;

    output.normal = normalize(mul(input.normal, (float32_t3x3) gTransformationMatrix.World));
    output.worldPosition = mul(input.position, gTransformationMatrix.WVP).xyz;
    
    return output;
}