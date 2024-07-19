
struct Well
{
    float32_t4x4 skeletonSpaceMatrix;
    float32_t4x4 skeletonSpaceInverseTransposeMatrix;
};


struct Vertex
{
    float32_t4 position;
    float32_t2 texcoord;
    float32_t3 normal;
};

struct VertexInfluence
{
    float32_t4 weight;
    int32_t4 index;
};
struct SkinningInfomation
{
    uint32_t numVertices;
};

StructuredBuffer<Well> gMatrixPalette : register(t0);
StructuredBuffer<Vertex> gInputVertices : register(t1);
StructuredBuffer<VertexInfluence> gInfluences : register(t2);
ConstantBuffer<SkinningInfomation> gSkinningInformation : register(b0);

RWStructuredBuffer<Vertex> gOutputVertices : register(u0);

Vertex Skinning(VertexInfluence infuluence, Vertex input)
{
    Vertex skinned;

	//à íuÇÃïœä∑
    skinned.position = mul(input.position, gMatrixPalette[infuluence.index.x].skeletonSpaceMatrix) * infuluence.weight.x;
    skinned.position += mul(input.position, gMatrixPalette[infuluence.index.y].skeletonSpaceMatrix) * infuluence.weight.y;
    skinned.position += mul(input.position, gMatrixPalette[infuluence.index.z].skeletonSpaceMatrix) * infuluence.weight.z;
    skinned.position += mul(input.position, gMatrixPalette[infuluence.index.w].skeletonSpaceMatrix) * infuluence.weight.w;
    skinned.position.w = 1.0f;

	//ñ@ê¸ÇÃïœä∑
    skinned.normal = mul(input.normal, (float32_t3x3) gMatrixPalette[infuluence.index.x].skeletonSpaceInverseTransposeMatrix) * infuluence.weight.x;
    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPalette[infuluence.index.y].skeletonSpaceInverseTransposeMatrix) * infuluence.weight.y;
    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPalette[infuluence.index.z].skeletonSpaceInverseTransposeMatrix) * infuluence.weight.z;
    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPalette[infuluence.index.w].skeletonSpaceInverseTransposeMatrix) * infuluence.weight.w;
    skinned.normal = normalize(skinned.normal);

    return skinned;
}

[numthreads(1024, 1, 1)]
void main(uint32_t3 DTid : SV_DispatchThreadID)
{
    uint32_t vertexindex = DTid.x;
    if (vertexindex < gSkinningInformation.numVertices)
    {
       Vertex skinned = Skinning(gInfluences[vertexindex], gInputVertices[vertexindex]);
       skinned.texcoord = gInputVertices[vertexindex].texcoord;
        gOutputVertices[vertexindex] = skinned;
    }
}