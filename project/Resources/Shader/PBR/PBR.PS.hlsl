#include"../LightingObject3d.hlsli"

#include"PBR.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b1);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b2);

StructuredBuffer<PointLight> gPointLight : register(t0);
Texture2D<float32_t4> gTexture : register(t1);
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


float32_t3 CookTorranceSpecular(float32_t NdotL, float32_t NdoH, float32_t LdoH)
{
    //D
    float32_t Ds = DistributionGGX(roughness * roughness, NdoH, PI);
    //F
    float32_t3 Fs = DisneyFresnel(LdoH,baseColor,metalness,Supecular);
    //G
    float32_t Gs = GeometricSmith(NdotL,roughness) * GeometricSmith(NdotV,roughness);
    //m
    float32_t m = 4.0f * NdotL * NdotV;
    return Fs * Ds * Gs / m;
};
//計算
float32_t3 BRDF(float32_t3 L, float32_t3 V)
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

    float32_t3 diffuseColor = diffuseReflectance * Fd * baseColor.rgb * (1 - metalness) * pCos;
  
    float32_t3 spe = CookTorranceSpecular(NdotL, NdoH, LdotH);
    return diffuseColor + spe;
}

PixelShaderOutput main(VertexShaderOutput input)
{

    PixelShaderOutput output;
    N = input.normal;
 
    
    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);

    float32_t3 totalColor = float32_t3(0, 0, 0);

    for (int32_t i = 0; i < gNowLightTotal.count; i++)
    {
		//点光源
        metalness = gMaterial.metalness;
        roughness = gMaterial.roughness;
        baseColor = (gMaterial.color.rgb * textureColor.rgb);
        Supecular = gMaterial.supecular;
        float32_t distance = length(gPointLight[i].position - input.worldPosition);
        float32_t factor = pow(saturate(-distance / gPointLight[i].radious + 1.0f), gPointLight[i].decay);
        LightDir = normalize(input.worldPosition - gPointLight[i].position);
        
        totalColor += BRDF(normalize(gPointLight[i].position), toEye) * gPointLight[i].color.rgb * gPointLight[i].intensity * factor;
    }

    output.color.rgb = totalColor;
    output.color.a = gMaterial.color.a * textureColor.a;
    output.dfColor = gMaterial.color * textureColor;
    output.normalColor = float32_t4(N.rgb, 1);
    output.posColor = input.position;
    return output;
}