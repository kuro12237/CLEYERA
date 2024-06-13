
struct Well
{
    float32_t4x4 skeletonSpaceMatrix;
    float32_t4x4 skeletonSpaceInverseTransposeMatrix;
};

struct Skinned
{
    float32_t4 pos;
    float32_t2 texcoord;
    float32_t3 normal;
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
    uint32_t4 index;
};
struct SkinningInfomation
{
    uint32_t numVertices;
};

StructuredBuffer<Well> gMatrixPalette : register(t0);
StructuredBuffer<Vertex> gInputVertices : register(t1);
StructuredBuffer<VertexInfluence> gInfluences : register(t2);
RWStructuredBuffer<Vertex> gOutputVertices : register(u0);
ConstantBuffer<SkinningInfomation> gSkinningInformation : register(b0);

//Skinned Skinning(VertexInfluence infuluence,Vertex input)
//{
//    Skinned skinned;

//	//à íuÇÃïœä∑
//    skinned.pos = mul(input.position, gMatrixPalette[infuluence.index.x].skeletonSpaceMatrix) * infuluence.weight.x;
//    skinned.pos += mul(input.position, gMatrixPalette[infuluence.index.y].skeletonSpaceMatrix) * infuluence.weight.y;
//    skinned.pos += mul(input.position, gMatrixPalette[infuluence.index.z].skeletonSpaceMatrix) * infuluence.weight.z;
//    skinned.pos += mul(input.position, gMatrixPalette[infuluence.index.w].skeletonSpaceMatrix) * infuluence.weight.w;
//    skinned.pos.w = 1.0f;

//	//ñ@ê¸ÇÃïœä∑
//    skinned.normal = mul(input.normal, (float32_t3x3) gMatrixPalette[infuluence.index.x].skeletonSpaceInverseTransposeMatrix) * infuluence.weight.x;
//    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPalette[infuluence.index.y].skeletonSpaceInverseTransposeMatrix) * infuluence.weight.y;
//    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPalette[infuluence.index.z].skeletonSpaceInverseTransposeMatrix) * infuluence.weight.z;
//    skinned.normal += mul(input.normal, (float32_t3x3) gMatrixPalette[infuluence.index.w].skeletonSpaceInverseTransposeMatrix) * infuluence.weight.w;
//    skinned.normal = normalize(skinned.normal);

//    return skinned;
//}

[numthreads(1024, 1, 1)]
void main(uint32_t DTid : SV_DispatchThreadID)
{
    //uint32_t vertexindex = DTid;
    //if (vertexindex < gSkinningInformation.numVertices)
    //{
    //    Skinned skinned = Skinning(gInfluences[vertexindex],gInputVertices[vertexindex]);
    //    skinned.texcoord = gInputVertices[vertexindex].texcoord;
    //    gOutputVertices[vertexindex] = skinned;
    //}

}