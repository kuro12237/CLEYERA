#pragma once
#include"Pch.h"

/// <summary>
/// –¼‘OƒNƒ‰ƒX
/// </summary>
class INameable {
public:
    INameable() = default;
    virtual ~INameable() = default;

#pragma region Set
    void SetName(const string& name) { name_ = name; }
#pragma endregion

#pragma region Get
    string GetName()const { return name_; }
#pragma endregion

protected:

    string name_ = "";

};