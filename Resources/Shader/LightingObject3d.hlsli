
struct VertexShaderInput
{
    float32_t4 position : POSITION0;
    float32_t2 texcoord : TEXCOORD0;
    float32_t3 normal : NORMAL0;
    float32_t4 weight : WEIGHT0;
    int32_t4 index : INDEX0;
};

struct VertexShaderOutput {
	float32_t4 position : SV_POSITION;
	float32_t2 texcoord : TEXCOORD0;
	float32_t3 normal : NORMAL0;
    float32_t3 worldPosition : WORLDPOSITION0;
	float32_t4 color : COLOR0;
    float32_t4x4 worldMatrix : WORLDMATRIX0 ;

};

struct TransformationMatrix
{
    float32_t4x4 WVP;
    float32_t4x4 World;
};
struct TransformationViewMatrix {
	float32_t4x4 view;
	float32_t4x4 projection;
	float32_t4x4 orthographic;
	float32_t3 CameraPosition;
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

float32_t3 ComputeGrayscale(float32_t factor,float32_t3 color)
{
    float32_t grayscaleFactor = dot(color, float32_t3(0.2125f, 0.7154f, 0.0721f));
    float32_t3 grayscaleColor = lerp(color, float32_t3(grayscaleFactor, grayscaleFactor, grayscaleFactor), factor);
    return grayscaleColor;
}