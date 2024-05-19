#include"primitives.hlsli"

ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);
ConstantBuffer<TransformationMatrix> gTransformationMatrix : register(b2);

VertexShaderOutput main(VertexShaderInput input) 
{
    VertexShaderOutput output;
    
    float32_t4x4 vp = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
    float32_t4x4 wvp = mul(gTransformationMatrix.WVP, vp);
    output.position = mul(input.position,wvp);
    
	return output;
}