#include"PhongObject3d.hlsli"


ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<TransformationViewMatrix> gTransformationViewMatrix : register(b2);
ConstantBuffer<NowLightTotal> gNowLightTotal : register(b4);

StructuredBuffer<PointLight> gPointLight : register(t0);
Texture2D<float32_t4> gTexture : register(t1);
Texture2D<float32_t4> gNormalTexture : register(t2);
Texture2D<float32_t> gNoiseTexture : register(t3);

SamplerState gSampler : register(s0);

static float32_t3 N;


float32_t4 CalcEdgeColor(Material material,float32_t4 color)
{
    float32_t min = gMaterial.dissolveMask + gMaterial.dissolveEdgeMinMax.x;
    float32_t max = gMaterial.dissolveMask + gMaterial.dissolveEdgeMinMax.y;
 
    float32_t edge = 1.0f - smoothstep(min, max, material.dissolveMask);
    return edge * material.dissolveEdgeColor;
}

float32_t3 RimLight(float32_t3 LightDir, float3 ToEye, float rimPower, float rimIntensity, float3 LightColor)
{
    //角度
    float rim = dot(N, ToEye);
    
    rim = saturate(pow(rim, rimPower));

    float3 rimColor = rimIntensity * rim * LightColor;
    return rimColor;
}
PixelShaderOutput main(VertexShaderOutput input)
{

    PixelShaderOutput output;

    float32_t4 textureColor = gTexture.Sample(gSampler, input.texcoord);
    float32_t4 normalColor = gNormalTexture.Sample(gSampler, input.texcoord);
    float32_t3 toEye = normalize(gTransformationViewMatrix.CameraPosition - input.worldPosition);
    float32_t mask = gNoiseTexture.Sample(gSampler, input.texcoord);
   
    if (mask <= gMaterial.dissolveMask)
    {
        discard;
    }
    
      // エッジカラーを計算して適用
    float32_t min = gMaterial.dissolveMask + gMaterial.dissolveEdgeMinMax.x;
    float32_t max = gMaterial.dissolveMask + gMaterial.dissolveEdgeMinMax.y;
 
    float32_t edge = 1.0f - smoothstep(min, max, mask);
    textureColor.rgb += edge * gMaterial.dissolveEdgeColor.rgb;
  
    float32_t3 pTotalSpecular = 0;
    float32_t3 pTotalDffuse = 0;
    float32_t3 pTotalRimColor = 0;
 
    //法線を行列で調整
    
    N = normalize(input.normal);
   // N = normalColor.rgb * 2.0f + N - 1.0f;
    N = normalize(N);
    for (int32_t i = 0; i < gNowLightTotal.count; i++)
    {
		//点光源
        float32_t distance = length(gPointLight[i].position - input.worldPosition);
        float32_t factor = pow(saturate(-distance / gPointLight[i].radious + 1.0f), gPointLight[i].decay);

        float32_t3 pLightDir = normalize(input.worldPosition - gPointLight[i].position);
        float32_t3 pRefrectLight = reflect(pLightDir, N);
        float32_t3 pHalfVector = normalize(-pLightDir + toEye);

        float pNdotL = dot(N, -normalize(pLightDir));
        float pCos = pow(pNdotL * 0.5f + 0.5f, 2.0f);
        float pNdotH = dot(N, pHalfVector);
        float pSpecularPow = pow(saturate(pNdotH), gMaterial.shininess);

   
		//拡散
        float32_t3 pDiffuse = gMaterial.color.rgb * textureColor.rgb * gPointLight[i].color.rgb * pCos * gPointLight[i].intensity * factor;
		//鏡面
        float32_t3 pSpecular = gPointLight[i].color.rgb * gPointLight[i].intensity * factor * pSpecularPow * float32_t3(1.0f, 1.0f, 1.0f);
        
        pTotalDffuse = pTotalDffuse + pDiffuse;
        pTotalSpecular = pTotalSpecular + pSpecular;

    }

    float32_t4 resultColor;
    resultColor.rgb = pTotalDffuse  + pTotalSpecular;
    resultColor.a = gMaterial.color.a * textureColor.a;
    
    // グレースケール変換
    float32_t grayscaleFactor = dot(resultColor.rgb, float32_t3(0.2125f, 0.7154f, 0.0721f));
    float32_t3 grayscaleColor = lerp(resultColor.rgb, float32_t3(grayscaleFactor, grayscaleFactor, grayscaleFactor), gMaterial.grayFactor);
    output.color.rgb = grayscaleColor;
    output.color.a = resultColor.a;
    
    output.dfColor = gMaterial.color * textureColor;
    output.normalColor = float32_t4(N.rgb, 1);
    output.posColor = input.position;
    return output;
}