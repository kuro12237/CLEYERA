#pragma once
#include"Pch.h"

/// <summary>
/// Sceneをまたぐデータ
/// </summary>
class ISceneContext {
public:
    ISceneContext() = default;
    ~ISceneContext() = default;

    // データを取得する
    template<typename T>
    T* GetData() {
        if (!data_.has_value()) {
            return nullptr;
        }

        try {
            return &std::any_cast<T&>(data_);
        }
        catch (const std::bad_any_cast&) {
            throw std::runtime_error("Invalid type requested for GetData.");
        }
    }

    // データを設定する
    template<typename T>
    void SetData(T data) {
        data_ = std::move(data); 
    }

private:
    std::any data_; 
};