#include"primitives.hlsli"

ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);
ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b2);
StructuredBuffer<float32_t3> gLine : register(t0);

VertexShaderOutput main(VertexShaderInput input, uint32_t instanceId : SV_InstanceID)
{
    VertexShaderOutput output;
    
    float32_t4x4 vp = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
    float32_t4x4 wvp = mul(gTransformationMatrix.WVP, vp);
    output.position = mul(float32_t4(gLine[input.vertexId + (instanceId * 2)].xyz, 1.0f), wvp);
	return output;
}