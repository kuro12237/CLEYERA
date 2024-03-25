#include "NormalMap.h"

NormalMap* NormalMap::GetInstance()
{
    static NormalMap instance;
    return &instance;
}

std::vector<vector<CreateTex_param>>  NormalMap::CreateNormalMapTex(SModelData &normals, int32_t width, int32_t height)
{
    vector<vector<CreateTex_param>> normalMapPixels(height+1, vector<CreateTex_param>(width+1));
    for (int32_t y = 0; y < height; y++)
    {
        for (int32_t x = 0; x < width; x++) {
            // 法線データを元にテクスチャのピクセルデータを計算
            Vector4 pixelColor = { 1,1,1,1 };
            normalMapPixels[y][x].color = pixelColor;
        }
    }

    for (int i = 0; i < normals.vertices.size(); i++)
    {
        Vector2 pos = normals.vertices[i].texcoord;
        Vector4 color =
        {
            normals.vertices[i].normal.x,
            normals.vertices[i].normal.y,
            normals.vertices[i].normal.z,
        };

        pos = { pos.x * width,pos.y * height };

        normalMapPixels[int32_t(pos.y)][int32_t(pos.x)].pos = pos;
        normalMapPixels[int32_t(pos.y)][int32_t(pos.x)].color=color;

    }


    normals;
    return normalMapPixels;
}



uint32_t NormalMap::LoadNormalMap(vector<Vector3> normals)
{
    return 0;
}
