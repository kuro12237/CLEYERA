

float32_t Harf_Lambert(float32_t3 normal, float32_t3 lightDir)
{
    return (dot(normal, lightDir)) * 0.5f + 0.5f;
}

float32_t SchlickFresnel(float32_t f0, float32_t f90, float32_t cosine)
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

float32_t3 DisneyFresnel(float32_t LdotH,float32_t3 baseColor,float32_t metalness,float32_t specular)
{
    float luminannce = 0.3f * baseColor.r + 0.6f * baseColor.g + 0.1f * baseColor.b;
    float32_t3 tintColor = baseColor / luminannce;
    float32_t3 nonMetalColor = specular * 0.08f * tintColor;
    float32_t3 color = lerp(nonMetalColor, baseColor, metalness);
    return SchlickFresnel3(color, float32_t3(1, 1, 1), LdotH);
};
float32_t GeometricSmith(float32_t cosine,float32_t roughness)
{
    float k = roughness + 1.0f;
    k = k * k / 8.0f;
    return cosine / (cosine * (1.0f - k) + k);
}

float32_t DistributionGGX(float32_t alpha, float32_t NdoH,float32_t PI)
{
    float alpha2 = alpha * alpha;
    float t = NdoH * NdoH * (alpha2 - 1.0f) + 1.0f;
    return alpha2 / (PI * t * t);
}



