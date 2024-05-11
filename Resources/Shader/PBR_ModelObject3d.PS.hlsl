#include"LightingObject3d.hlsli"

ConstantBuffer<Material>gMaterial :register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);
StructuredBuffer<PointLight> gPointLight : register(t0);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);
Texture2D<float32_t4>gTexture : register(t1);
Texture2D<float32_t4> gNormalTexture : register(t2);
SamplerState gSampler : register(s0);

static float32_t3 N;
static float32_t PI = 3.1415926535f;
static float32_t metalness;
static float32_t roughness;
static float32_t NdotV;
static float32_t3 baseColor;
static float32_t Supecular;
static float32_t3 LightDir;

float32_t Harf_Lambert(float32_t3 normal, float32_t3 lightDir)
{
    return (dot(normal, lightDir)) * 0.5f + 0.5f;
}

float32_t SchlickFresnel(float32_t f0,float32_t f90,float32_t cosine)
{
    float m = saturate(1 - cosine);
    float m2 = m * m;
    float m5 = m2 * m2 * m;
    return lerp(f0, f90, m5);
}
float32_t3 SchlickFresnel3(float32_t3 f0, float32_t3 f90, float32_t cosine)
{
    float m = saturate(1 - cosine);
    float m2 = m * m;
    float m5 = m2 * m2 * m;
    return lerp(f0, f90, m5);
}

float32_t3 DisneyFresnel(float32_t LdotH)
{
    float luminannce = 0.3f * baseColor.r + 0.6f * baseColor.g + 0.1f * baseColor.b;
    float32_t3 tintColor = baseColor / luminannce;
    float32_t3 nonMetalColor = Supecular *0.08f* tintColor;
    float32_t3 color = lerp( nonMetalColor, baseColor, metalness);
    return SchlickFresnel3(color, float32_t3(1,1,1), LdotH);
};
float32_t GeometricSmith(float32_t cosine)
{
    float k = roughness+1.0f;
    k = k * k / 8.0f;
    return cosine / (cosine * (1.0f - k) + k);
}

float32_t DistributionGGX(float32_t alpha, float32_t NdoH)
{
    float alpha2 = alpha * alpha;
    float t = NdoH * NdoH * (alpha2 - 1.0f) + 1.0f;
    return alpha2 / (PI * t * t);
}
float32_t3 CookTorranceSpecular(float32_t NdotL, float32_t NdotV, float32_t NdoH,float32_t LdoH)
{
    float32_t Ds = DistributionGGX(roughness*roughness,NdoH);
    float32_t3 Fs = DisneyFresnel(LdoH);
    float32_t Gs = GeometricSmith(NdotL) * GeometricSmith(NdotV);
    float32_t m = 4.0f * NdotL * NdotV;
    return Fs * Ds * Gs / m;
};



float32_t3
    BRDF(float32_t3
    L, float32_t3
    V)
{
    float32_t NdotL = dot(N, L);
    NdotV = dot(N, V);
    float32_t3 H = normalize(L + V);
    float32_t NdoH = dot(N, H);
    float32_t LdotH = dot(L, H);

    if (NdotL < 0.0 || NdotV < 0.0)
    {
        return float32_t3(0, 0, 0);
    }

    float32_t enegyBias = 0.5f * roughness;
    float32_t Fd90 = enegyBias + 2 * LdotH * LdotH * roughness;
    float32_t FL = SchlickFresnel(1.0f, Fd90, NdotL);
    float32_t FV = SchlickFresnel(1.0f, Fd90, NdotV);
    float32_t enegyFactor = lerp(1.0f, 1.0f / 1.51f, roughness);
    float Fd = FL * FV * enegyFactor;
    float pCos = pow(NdotL * 0.5f + 0.5f, 2.0f);
    float diffuseReflectance = 1.0f / PI;

    float32_t3 diffuseColor = diffuseReflectance * Fd * baseColor.rgb * (1 - metalness)*pCos;
    //float32_t3 harfLambert = Harf_Lambert(N, L);
    float32_t3 spe = CookTorranceSpecular(NdotL, NdotV,NdoH,LdotH);
    return diffuseColor + spe;
}

PixelShaderOutput main(VertexShaderOutput input) {

	PixelShaderOutput output;

    N = gNormalTexture.Sample(gSampler, input.texcoord).rgb+input.normal;
    N = normalize(mul(N, (float32_t3x3) input.worldMatrix));
 
    float32_t3 finalColor = { 0.0f, 0.0f, 0.0f };
	float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
	float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);

	float32_t3 pTotalSpecular = 0;
	float32_t3 pTotalDffuse = 0;

	//for (int32_t i = 0; i < gNowLightTotal.count; i++)
	//{
	//	//点光源
 //       metalness =  gMaterial.metalness;
 //       roughness = gMaterial.roughness;
 //       baseColor = (gMaterial.color.rgb * textureColor.rgb);
 //       Supecular = gMaterial.supecular;
 //       LightDir = gPointLight[i].position - input.worldPosition;
 //       float32_t distance = length(LightDir);
 //       float32_t factor = pow(saturate(-distance / gPointLight[i].radious + 1.0f), gPointLight[i].decay);

 //       pTotalDffuse = pTotalDffuse + BRDF(normalize(gPointLight[i].position), toEye) * gPointLight[i].color.rgb * gPointLight[i].intensity * factor;
 //   }

    output.color.rgb = pTotalDffuse;
    //+pTotalSpecular;
	output.color.a = gMaterial.color.a * textureColor.a;

	return output;
}