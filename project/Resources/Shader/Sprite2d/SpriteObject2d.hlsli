struct VertexShaderOutput {
	float32_t4 position : SV_POSITION;
	float32_t2 texcoord : TEXCOORD0;
};


struct Material
{
    float32_t4 color;
    float32_t4x4 uv;
    
    float32_t shininess;
    
    float32_t supecular;
    float32_t metalness;
    float32_t roughness;
    
    float32_t scatterCoefficient;
    float32_t absorptionCoefficient;
    float32_t scatterDistance;
    
    float32_t grayFactor;

    float32_t dissolveMask;
    float32_t2 dissolveEdgeMinMax;
    float32_t4 dissolveEdgeColor;
};