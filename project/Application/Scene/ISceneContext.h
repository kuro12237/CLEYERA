#pragma once
#include"Pch.h"

/// <summary>
/// Scene���܂����f�[�^
/// </summary>
class ISceneContext {
public:
    ISceneContext() = default;
    ~ISceneContext() = default;

    // �f�[�^���擾����
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

    // �f�[�^��ݒ肷��
    template<typename T>
    void SetData(T data) {
        data_ = std::move(data); 
    }

private:
    std::any data_; 
};