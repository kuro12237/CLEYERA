#include"../Particle.hlsli"

RWStructuredBuffer<Particle> gParticle : register(u0);

ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b0);

VertexShaderOutput main(VertexShaderInput input, uint32_t instanceId : SV_InstanceID)
{
    VertexShaderOutput output;
  
    float32_t4x4 worldMat = (float32_t4x4) 0;
    
    if (gParticle[instanceId].isDraw)
    {
        worldMat = mul(gParticle[instanceId].matWorld, gTransformationViewMatrix.orthographic);
    }
 
    output.position = mul(input.position, worldMat);
    output.texcoord = input.texcoord;
    output.normal = normalize(mul(input.normal, (float32_t3x3) worldMat));
    output.instanceId = instanceId;
    
    return output;
}