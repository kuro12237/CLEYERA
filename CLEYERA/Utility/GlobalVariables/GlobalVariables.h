#pragma once
#include"Pch.h"
#include"Transform/STransformQua.h"

class GlobalVariables {
public:
	static GlobalVariables* GetInstance();

	bool GetIsSave() { return isSave_; }

	template<typename T>
	T GetValue(const std::string& groupName, const std::string& key);

	template<typename T>
	void SetValue(const std::string& groupName, const std::string& key, T value);

	template<typename T>
	void AddItem(const std::string& groupName, const std::string& key, T value);

	/// <summary>
	/// グループの生成
	/// </summary>
	/// <param name="groupName">グループ名</param>
	void CreateGroup(const std::string& groupName);

	/// <summary>
	/// ファイルに書き出し
	/// </summary>
	/// <param name="groupName"></param>
	void SaveFile(const std::string& groupName);

	/// <summary>
	/// ファイルから読み込む
	/// </summary>
	void LoadFile(const std::string& groupName);

	/// <summary>
	/// ディレクトリの全ファイル読み込み
	/// </summary>
	void LoadFiles();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

private:
	GlobalVariables() = default;
	~GlobalVariables() = default;
	GlobalVariables(const GlobalVariables& obj) = delete;
	GlobalVariables& operator=(const GlobalVariables& obj) = delete;

public:
	// 項目
	struct Item {
		// 項目の値
		std::variant<int32_t, float,bool, Vector2, Vector3, Vector4,TransformQua> value;
	};
	// グループ
	struct Group {
		std::map<std::string, Item> items;
	};
	// 全データ
	std::map<std::string, Group> datas_;

	// グローバル変数の保存先ファイルパス
	const std::string kDirectoryPath = "resources/GlobalVariables/";

	bool isSave_;
};

template<typename T>
inline T GlobalVariables::GetValue(const std::string& groupName, const std::string& key)
{
	// 指定したグループが存在するかをassertで確認
	assert(datas_.find(groupName) != datas_.end());

	// 指定したグループの参照を取得
	Group& group = datas_[groupName];

	// 指定したキーが存在するかをassertで確認
	assert(group.items.find(key) != group.items.end());

	// 指定したグループから指定したキーの値を取得して返す
	return std::get<T>(group.items[key].value);
}

template<typename T>
inline void GlobalVariables::SetValue(const std::string& groupName, const std::string& key, T value)
{ 
		// グループの参照を取得
		Group& group = datas_[groupName];
		// 新しい項目のデータを設定
		Item newItem{};
		newItem.value = value;
		// 設定した項目をstd::mapに追加
		group.items[key] = newItem;
}

template<typename T>
inline void GlobalVariables::AddItem(const std::string& groupName, const std::string& key, T value)
{
	// 指定したグループの参照を取得
	Group& group = datas_[groupName];
	// 項目が未登録なら
	if (group.items.find(key) == group.items.end()) {
		SetValue(groupName, key, value);
	}
}

