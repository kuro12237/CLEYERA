#include "SceneFileLoader.h"

SceneFileLoader* SceneFileLoader::GetInstance()
{
    static SceneFileLoader instance;
    return &instance;
}

void SceneFileLoader::ReLoad(const string& filePath)
{
    if (deserialized)
    {
        deserialized.clear();
    }

    ifstream file = FileLoader::JsonLoadFile(filePath);
    file >> deserialized;
}
