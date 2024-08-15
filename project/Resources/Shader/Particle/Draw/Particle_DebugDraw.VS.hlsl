#include"../Particle.hlsli"

RWStructuredBuffer<Particle> gParticle : register(u0);

ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b0);

VertexShaderOutput main(VertexShaderInput input, uint32_t instanceId : SV_InstanceID)
{
    VertexShaderOutput output;
    
    float32_t4x4 CameraMatrix = mul(gTransformationViewMatrix.view, gTransformationViewMatrix.projection);
    float32_t4x4 wvpMat = (float32_t4x4) 0;
    if (gParticle[instanceId].isDraw)
    {
        wvpMat = mul(gParticle[instanceId].matWorld, CameraMatrix);
    }

    output.position = mul(input.position, wvpMat);
    output.texcoord = input.texcoord;
    output.normal = normalize(mul(input.normal, (float32_t3x3) wvpMat));
    output.instanceId = instanceId;
    
    return output;
}