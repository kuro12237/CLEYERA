#pragma once
#include "Pch.h"
#include "Utility/GlobalVariables/GlobalVariables.h"

///変数を文字列に変換するマクロ
#define VAR_NAME(var) (#var)

/// <summary>
/// json使うようのクラス
/// </summary>
class JsonComponent
{
 public:
   JsonComponent() { globalVariables_ = GlobalVariables::GetInstance(); }
   ~JsonComponent() = default;

   /// <summary>
   /// gruop作成
   /// </summary>
   void CreateJsonData() { globalVariables_->CreateGroup(jsonGropName_); }

   /// <summary>
   /// 追加
   /// </summary>
   template <typename T> void AddJsonItem(string itemName, T value)
   {
      return globalVariables_->AddItem(jsonGropName_, itemName, value);
   }

   /// <summary>
   /// 入手
   /// </summary>
   template <typename T> T GetJsonItem(string itemName)
   {
      return globalVariables_->GetValue<T>(jsonGropName_, itemName);
   }


   void SaveFile() { globalVariables_->SaveFile(jsonGropName_); }

 protected:
   string jsonGropName_ = "";

   GlobalVariables *globalVariables_ = nullptr;
};
