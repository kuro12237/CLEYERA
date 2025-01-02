#pragma once
#include"Pch.h"
#include"Transform/STransformQua.h"
#include"Transform/STransformEular.h"
#include"Particle/Emitter/StructGpuParticleEmitter.h"
#include"Particle/Emitter/ParticleEmitter.h"
#include"Particle/Field/ParticleField.h"

class GlobalVariables {
public:

	static GlobalVariables* GetInstance();

	/// <summary>
	/// グループの生成
	/// </summary>
	/// <param name="groupName">グループ名</param>
	void CreateGroup(const std::string& groupName, const string& DirectoryPath = "");

	/// <summary>
	/// ファイルに書き出し
	/// </summary>
	/// <param name="groupName"></param>
	void SaveFile(const std::string& groupName);

	/// <summary>
	/// ファイルから読み込む
	/// </summary>
	void LoadFile(const string& DirectoryPath,const std::string& groupName);

	/// <summary>
	/// ディレクトリの全ファイル読み込み
	/// </summary>
	void LoadFiles(const string& DirectoryPath);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// 入力した文字列の中にprefixの文字列があるか
	/// </summary>
	/// <param name="input"></param>
	/// <param name="prefix"></param>
	/// <returns></returns>
	bool StartsWith(const std::string& input, const std::string& prefix) {
		return input.find(prefix) == 0;
	}

	/// <summary>
	/// 切替の際にvectorの中のDirectryを読む
	/// </summary>
	void ChangeSceneLoadFiles();

	/// <summary>
	/// dataの中を削除
	/// </summary>
	void Clear() { datas_.clear(); }

#pragma region Get
	bool GetIsSave() { return isSave_; }
	template<typename T>
	T GetValue(const std::string& groupName, const std::string& key);

	vector<string>GetAllDataKey();


#pragma endregion

#pragma region Set
	template<typename T>
	void SetValue(const std::string& groupName, const std::string& key, T value);
	template<typename T>
	void AddItem(const std::string& groupName, const std::string& key, T value);

	void unUseDirectryPathFlag(const bool& f) { isUseDirectryPath_ = f; };

	void SetDirectoryFilePath(const string& filePath) { kDirectoryPath = filePath; }
	void SetChangeSceneLoadFilesName(const string& filePath);

#pragma endregion

private:

#pragma region Singleton
	GlobalVariables() = default;
	~GlobalVariables() = default;
	GlobalVariables(const GlobalVariables& obj) = delete;
	GlobalVariables& operator=(const GlobalVariables& obj) = delete;
#pragma endregion

	void WriteVector3(string name,Math::Vector::Vector3 &T);


	// 項目
	struct Item {
		// 項目の値
		std::variant<int32_t, float, bool, Math::Vector::Vector2, Math::Vector::Vector3, Math::Vector::Vector4, Engine::Transform::TransformQua, Engine::Transform::TransformEular, string,Engine::Particle::EmitType::BoxParam> value;
	};
	// グループ
	struct Group {
		std::map<std::string, Item> items;
		std::string DirectryPath = "";
	};
	// 全データ
	std::map<std::string, Group> datas_;

	// グローバル変数の保存先ファイルパス
	std::string kDirectoryPath = "Resources/GlobalVariables/";

	bool isUseDirectryPath_ = false;

	bool isSave_;

	vector<string>changeSceneLoadFilePaths_{};
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

