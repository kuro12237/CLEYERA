#include "PostEffectManager.h"

PostEffectManager *PostEffectManager::GetInstance()
{
    static PostEffectManager instance;
    return &instance;
}

bool PostEffectManager::CheckData(const string& name)
{
    if (data_.find(name)==data_.end())
    {
        return true;
    }

    return false;
}

SPostEffectData PostEffectManager::GetData(const string& name)
{
    return data_[name]->GetData();
}

void PostEffectManager::SetData(const string& name, SPostEffectData data)
{
    data_[name] = make_unique<PostEffectData>(data);
}
