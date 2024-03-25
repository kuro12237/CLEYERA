#include"SpriteObject3d.hlsli"

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
ConstantBuffer<Material>gMaterial :register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);
StructuredBuffer<PointLight> gPointLight : register(t0);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);
Texture2D<float32_t4> gTexture : register(t1);
Texture2D<float32_t4> gNormalTexture : register(t2);
SamplerState gSampler : register(s0);

PixelShaderOutput main(VertexShaderOutput input) {

	PixelShaderOutput output;
	float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
	float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

	if (textureColor.a == 0.0f)
	{
		//discard;
	}

	output.color.rgb = gMaterial.color.rgb * textureColor.rgb;
	output.color.a = gMaterial.color.a * textureColor.a;
	
	return output;
}