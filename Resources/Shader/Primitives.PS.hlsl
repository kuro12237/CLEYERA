#include"primitives.hlsli"

ConstantBuffer<Material> gMaterial: register(b0);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    output.color = gMaterial.color;
    return output;
}
