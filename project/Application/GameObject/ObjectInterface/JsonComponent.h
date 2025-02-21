#pragma once
#include"Pch.h"
#include"Utility/GlobalVariables/GlobalVariables.h"

class JsonComponent
{
public:

	JsonComponent() { globalVariables_ = GlobalVariables::GetInstance(); }
	~JsonComponent() = default;

	void CreateJsonData() { globalVariables_->CreateGroup(jsonGropName_); }

	template<typename T>
	void AddJsonItem(string itemName, T value) { return globalVariables_->AddItem(jsonGropName_, itemName, value); }

	template<typename T>
	T GetJsonItem(string itemName) { return globalVariables_->GetValue<T>(jsonGropName_, itemName); }

	void SaveFile() { globalVariables_->SaveFile(jsonGropName_); }

protected:

	string jsonGropName_ = "";

	GlobalVariables* globalVariables_ = nullptr;
};

