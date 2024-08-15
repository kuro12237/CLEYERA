struct VertexShaderOutput
{
    float32_t4 position : SV_POSITION;
    float32_t2 texcoord : TEXCOORD0;
};
struct Material
{
    float32_t4 color;
    float32_t4x4 uvTransform;
};
struct TransformationViewMatrix
{
    float32_t4x4 view;
    float32_t4x4 projection;
    float32_t4x4 orthographic;
    float32_t3 CameraPosition;
};

struct PointLight
{
    float32_t4 color;
    float32_t3 position;
    float intensity;
    float radious;
    float decay;
};

struct NowLightTotal
{
    int32_t count;
};
struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0;
};
ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);
StructuredBuffer<PointLight> gPointLight : register(t0);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);

SamplerState gSampler : register(s0);

PixelShaderOutput main(VertexShaderOutput input)
{

    PixelShaderOutput output;
    output.color.rgb = input.position.rgb;
    output.color.a = 1;
    return output;
}