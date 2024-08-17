#include"SpriteObject2d.hlsli"


ConstantBuffer<Material>gMaterial :register(b0);

Texture2D<float32_t4>gTexture : register(t0);
SamplerState gSampler : register(s0);

struct PixelShaderOutput {

	float32_t4  color : SV_TARGET0;
};

PixelShaderOutput main(VertexShaderOutput input) {

	PixelShaderOutput output;
	float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uv);
	float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

	if (textureColor.a == 0.0f)
	{
		//discard;
	}

	output.color.rgb = gMaterial.color.rgb * textureColor.rgb;
	output.color.a = gMaterial.color.a * textureColor.a;

	return output;
}