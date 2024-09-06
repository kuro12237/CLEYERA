#include"SkyBox.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);

TextureCube<float32_t4> gTexture : register(t1);
SamplerState gSampler : register(s0);
StructuredBuffer<PointLight> gPointLight : register(t0);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);

static float32_t3 N;

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);

 
    output.color = textureColor * gMaterial.color;
    output.dfColor = textureColor;
    output.normalColor = float32_t4(input.normal, 1.0f);
    output.posColor = input.position;
    return output;
}

