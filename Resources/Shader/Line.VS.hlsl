#include"primitives.hlsli"

VertexShaderOutput main(VertexShaderInput input) 
{
    VertexShaderOutput output;
    output.position = input.position;
    
	return output;
}