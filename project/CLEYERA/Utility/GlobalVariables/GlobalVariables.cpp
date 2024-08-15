#include "GlobalVariables.h"

#include "GlobalVariables.h"
#include "ImGuiManager.h"
#include <fstream>
#include<json.hpp>

using namespace Math::Vector;

GlobalVariables* GlobalVariables::GetInstance() {
	static GlobalVariables instance;

	return &instance;
}

void GlobalVariables::CreateGroup(const std::string& groupName)
{
	datas_[groupName];
}

void GlobalVariables::SaveFile(const std::string& groupName)
{
	// グループを検索
	std::map<std::string, Group>::iterator itGroup = datas_.find(groupName);

	// 未登録チェック
	assert(itGroup != datas_.end());

	nlohmann::json root;
	root = nlohmann::json::object();

	// jsonオブジェクトの登録
	root[groupName] = nlohmann::json::object();
	// 各項目について
	for (std::map<std::string, Item>::iterator itItem = itGroup->second.items.begin();
		itItem != itGroup->second.items.end(); ++itItem) {
		// 項目名を取得
		const std::string& itemName = itItem->first;
		// 項目の参照を取得
		Item& item = itItem->second;

		// int32_tの値を保持している場合
		if (std::holds_alternative<int32_t>(item.value)) {
			// int32_tの値の登録
			root[groupName][itemName] = std::get<int32_t>(item.value);
		} // floatの値を保持している場合
		else if (std::holds_alternative<float>(item.value)) {
			// floatの値の登録
			root[groupName][itemName] = std::get<float>(item.value);
		} // Vector2の値を保持している場合
		if (std::holds_alternative<Vector2>(item.value)) {
			// Vector2の値の登録
			Vector2 value = std::get<Vector2>(item.value);
			root[groupName][itemName] = nlohmann::json::array({ value.x, value.y });
		} // Vector3の値を保持している場合
		if (std::holds_alternative<Vector3>(item.value)) {
			// Vector3の値の登録
			Vector3 value = std::get<Vector3>(item.value);
			root[groupName][itemName] = nlohmann::json::array({ value.x, value.y, value.z });
		}// Vector4の値を保持している場合
		if (std::holds_alternative<Vector4>(item.value)) {
			// Vector4の値の登録
			Vector4 value = std::get<Vector4>(item.value);
			root[groupName][itemName] = nlohmann::json::array({ value.x, value.y, value.z, value.w });
		}
		if (std::holds_alternative<TransformQua>(item.value)) {
			// Vector4の値の登録
			TransformQua value = std::get<TransformQua>(item.value);
			
			// convert to json, just by assigning:
			nlohmann::json json = value;
			// convert to string
			std::string json_as_string = json.dump();
			// string to json
			nlohmann::json back_json = nlohmann::json::parse(json_as_string);

			// json -> instance
			root[groupName][itemName] = back_json.get<TransformQua>();

			//root[groupName][itemName] = nlohmann::json::array({ value.scale, value.quaternion,value.translate});
		}
	}
	// ディレクトリがなければ作成する
	std::filesystem::path dir(kDirectoryPath);
	if (!std::filesystem::exists(kDirectoryPath)) {
		std::filesystem::create_directory(kDirectoryPath);
	}

	// 書き込むJSONファイルのフルパスを合成する
	std::string filePath = kDirectoryPath + groupName + ".json";
	// 書き込み用ファイルストリーム
	std::ofstream ofs{};
	// ファイルを書き込みように開く
	ofs.open(filePath);

	// ファイルオープン失敗？
	if (ofs.fail()) {
		std::string message = "Failed open data file for write.";
		MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		assert(0);
		return;
	}
	// ファイルにjson文字列を書き込む(インデント幅4)
	ofs << std::setw(4) << root << std::endl;
	// ファイルを閉じる
	ofs.close();

}

void GlobalVariables::LoadFile(const std::string& groupName)
{
	// 読み込むJSONファイルのフルパスを合成する
	std::string filePath = kDirectoryPath + groupName + ".json";
	// 読み込み用ファイルストリーム
	std::ifstream ifs;
	// ファイルを読み込み用に開く
	ifs.open(filePath);

	// ファイルオープン失敗?
	if (ifs.fail()) {
		std::string message = "Failed open data file for write.";
		MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
		assert(0);
		return;
	}

	nlohmann::json root;

	// json文字列からjsonのデータ構造に展開
	ifs >> root;
	// ファイルを閉じる
	ifs.close();

	// グループを検索
	nlohmann::json::iterator itGroup = root.find(groupName);

	// 未登録チェック
	assert(itGroup != root.end());
	// 各アイテムについて
	for (nlohmann::json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {
		// アイテム名を取得
		const std::string& itemName = itItem.key();

		// int32_tの値を保持している場合
		if (itItem->is_number_integer()) {
			// int型の値を登録
			int32_t value = itItem->get<int32_t>();
			SetValue(groupName, itemName, value);
		} // floatの値を保持している場合
		else if (itItem->is_number_float()) {
			// double型の値を登録
			double value = itItem->get<double>();
			SetValue(groupName, itemName, static_cast<float>(value));
		}
		else if (itItem->is_boolean()) {
			bool value = itItem->get<bool>();
			SetValue(groupName, itemName, static_cast<bool>(value));
		}// 要素数2の配列の場合
		else if (itItem->is_array() && itItem->size() == 2) {
			// float型の値を登録
			Vector2 value = { itItem->at(0), itItem->at(1) };
			SetValue(groupName, itemName, value);
		}// 要素数3の配列の場合
		else if (itItem->is_array() && itItem->size() == 3) {
			// float型の値を登録
			Vector3 value = { itItem->at(0), itItem->at(1), itItem->at(2) };
			SetValue(groupName, itemName, value);
		}// 要素数4の配列の場合
		else if (itItem->is_array() && itItem->size() == 4) {
			// float型の値を登録
			Vector4 value = { itItem->at(0), itItem->at(1), itItem->at(2), itItem->at(3) };

			SetValue(groupName, itemName, value);
		}
		else if (itItem->is_object() && itItem->size() == 3) {
			TransformQua value = itItem.value();
			SetValue(groupName, itemName, value);
		}


	}
}

void GlobalVariables::LoadFiles()
{
	// ディレクトリがなければスキップする
	std::filesystem::path dir(kDirectoryPath);
	if (!std::filesystem::exists(kDirectoryPath)) {
		return;
	}

	std::filesystem::directory_iterator dir_it(kDirectoryPath);
	for (const std::filesystem::directory_entry& entry : dir_it) {
		// ファイルパスを取得
		const std::filesystem::path& filePath = entry.path();

		// ファイル拡張子を取得
		std::string extension = filePath.extension().string();
		// .jsonファイル以外はスキップ
		if (extension.compare(".json") != 0) {
			continue;
		}
		// ファイル読み込み
		LoadFile(filePath.stem().string());
	}

}

void GlobalVariables::Update()
{
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.02f, 0.02f, 0.02f, 1.0f));
	if (!ImGui::Begin("Global Variables", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		return;
	}

	if (!ImGui::BeginMenuBar())
		return;

	for (std::map<std::string, Group>::iterator itGroup = datas_.begin(); itGroup != datas_.end();
		++itGroup) {
		// グループ名を取得
		const std::string& groupName = itGroup->first;
		// グループの参照を取得
		Group& group = itGroup->second;

		if (!ImGui::BeginMenu(groupName.c_str()))
			continue;

		// 各項目について
		for (std::map<std::string, Item>::iterator itItem = group.items.begin();
			itItem != group.items.end(); ++itItem) {
			// 各項目を取得
			const std::string& itemName = itItem->first;
			// 項目の参照を取得
			Item& item = itItem->second;
			// int32_tの値を保持している場合
			if (std::holds_alternative<int32_t>(item.value)) {
				int32_t* ptr = std::get_if<int32_t>(&item.value);
				ImGui::DragInt(itemName.c_str(), ptr, 0, 100);
			} // floatの値を保持している場合
			else if (std::holds_alternative<float>(item.value)) {
				float* ptr = std::get_if<float>(&item.value);
				ImGui::DragFloat(itemName.c_str(), ptr, 0, 100);
			}
			else if (std::holds_alternative<bool>(item.value)) {
				bool* ptr = std::get_if<bool>(&item.value);
				ImGui::Checkbox(itemName.c_str(), ptr);
			}// Vector2の値を保持している場合
			else if (std::holds_alternative<Vector2>(item.value)) {
				Vector2* ptr = std::get_if<Vector2>(&item.value);
				ImGui::DragFloat2(itemName.c_str(), reinterpret_cast<float*>(ptr), -10.0f, 10.0f);
			}// Vector3の値を保持している場合
			else if (std::holds_alternative<Vector3>(item.value)) {
				Vector3* ptr = std::get_if<Vector3>(&item.value);
				ImGui::DragFloat3(itemName.c_str(), reinterpret_cast<float*>(ptr), -10.0f, 10.0f);
			}// Vector4の値を保持している場合
			else if (std::holds_alternative<Vector4>(item.value)) {
				Vector4* ptr = std::get_if<Vector4>(&item.value);
				ImGui::ColorEdit4(itemName.c_str(), reinterpret_cast<float*>(ptr));
			}
			else if (std::holds_alternative<TransformQua>(item.value)) {
				TransformQua* ptr = std::get_if<TransformQua>(&item.value);
				string  Name = itemName;
				if (ImGui::TreeNode(itemName.c_str()))
				{
					Name = itemName + "scale";
						ImGui::DragFloat3(Name.c_str(), reinterpret_cast<float*>(&ptr->scale));
						Name = itemName + "quaternion";
						ImGui::DragFloat4(Name.c_str(), reinterpret_cast<float*>(&ptr->quaternion));
						Name = itemName + "translate";
						ImGui::DragFloat3(Name.c_str(), reinterpret_cast<float*>(&ptr->translate));
						ImGui::TreePop();
				}
			}
		}
	
		// 改行
		ImGui::Text("\n");

		if (ImGui::Button("Save")) {
			SaveFile(groupName);
			std::string message = std::format("{}.json saved.", groupName);
			MessageBoxA(nullptr, message.c_str(), "GlobalVariables", 0);
			isSave_ = true;
		}
		if (isSave_) {
			isSave_ = false;
		}
		ImGui::EndMenu();
	}
	ImGui::EndMenuBar();

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

}
