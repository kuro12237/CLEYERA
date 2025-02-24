#include "GlobalVariables.h"

#include "GlobalVariables.h"
#include "ImGuiManager.h"
#include <fstream>
#include<json.hpp>

using namespace Math::Vector;
using namespace Engine::Transform;


GlobalVariables* GlobalVariables::GetInstance() {
	static GlobalVariables instance;
	return &instance;
}

void GlobalVariables::CreateGroup(const std::string& groupName, const string& DirectoryPath)
{
	datas_[groupName];
	if (DirectoryPath == "")
	{
		datas_[groupName].DirectryPath = kDirectoryPath;
	}
	else
	{
		const string filePath = "Resources/LevelData/ParamData/";
		datas_[groupName].DirectryPath = filePath + DirectoryPath;
	}
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
	auto& goupItem = itGroup->second;
	for (std::map<std::string, Item>::iterator itItem = goupItem.items.begin(); itItem != goupItem.items.end(); ++itItem)
	{
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
			// TransformQuaternion登録
			TransformQua value = std::get<TransformQua>(item.value);

			nlohmann::json json = value;
			std::string json_as_string = json.dump();
			nlohmann::json back_json = nlohmann::json::parse(json_as_string);
			root[groupName][itemName] = back_json.get<TransformQua>();
		}
		if (std::holds_alternative<TransformEular>(item.value)) {
			// TransformQuaternion登録
			TransformEular value = std::get<TransformEular>(item.value);

			nlohmann::json json = value;
			std::string json_as_string = json.dump();
			nlohmann::json back_json = nlohmann::json::parse(json_as_string);
			root[groupName][itemName] = back_json.get<TransformEular>();
		}
		if (std::holds_alternative<Engine::Particle::EmitType::BoxParam>(item.value)) {
			Engine::Particle::EmitType::BoxParam value = std::get<Engine::Particle::EmitType::BoxParam>(item.value);

			nlohmann::json json = value;
			std::string json_as_string = json.dump();
			nlohmann::json back_json = nlohmann::json::parse(json_as_string);
			root[groupName][itemName] = back_json.get<Engine::Particle::EmitType::BoxParam>();
		}
		if (std::holds_alternative<string>(item.value)) {
			// string
			string value = std::get<string>(item.value);
			root[groupName][itemName] = std::get<string>(item.value);
		}
	}

	string directoryPath = datas_[groupName].DirectryPath;

	// ディレクトリがなければ作成する
	std::filesystem::path dir(directoryPath);
	if (!std::filesystem::exists(directoryPath)) {
		std::filesystem::create_directory(directoryPath);
	}

	// 書き込むJSONファイルのフルパスを合成する
	std::string filePath = directoryPath + groupName + ".json";

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
	ofs.close();
}

void GlobalVariables::LoadFile(const string& DirectoryPath, const std::string& groupName)
{
	// 読み込むJSONファイルのフルパスを合成する
	std::string filePath = DirectoryPath + groupName + ".json";
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

	ifs >> root;
	ifs.close();

	// グループを検索
	nlohmann::json::iterator itGroup = root.find(groupName);

	// 未登録チェック
	assert(itGroup != root.end());
	// 各アイテムについて
	for (nlohmann::json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {
		// アイテム名を取得
		const std::string& itemName = itItem.key();
		Group& group = datas_[groupName];
		group.DirectryPath = DirectoryPath;

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
			TransformEular value = itItem.value();
			SetValue(groupName, itemName, value);
		}
		else if (itItem->is_object() && itItem->size() == 4) {
			TransformQua value = itItem.value();
			SetValue(groupName, itemName, value);
		}
		else if (itItem->is_object() && itItem->size() == 15) {
			Engine::Particle::EmitType::BoxParam value = itItem.value();
			SetValue(groupName, itemName, value);
		}
		else if (itItem->is_string())
		{
			string value = itItem.value();
			SetValue(groupName, itemName, value);
		}
	}
}

void GlobalVariables::LoadFiles(const string& DirectoryPath)
{
	// ディレクトリがなければスキップする
	std::filesystem::path dir(DirectoryPath);
	if (!std::filesystem::exists(DirectoryPath)) {
		return;
	}

	std::filesystem::directory_iterator dir_it(DirectoryPath);
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
		LoadFile(DirectoryPath, filePath.stem().string());
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

	static char gropNameBuf[256] = "";
	static char directoryNameBuf[256] = "";
	ImGui::InputText("group", gropNameBuf, sizeof(gropNameBuf));
	ImGui::InputText("directory", directoryNameBuf, sizeof(directoryNameBuf));
	string groupName = gropNameBuf;
	string directoryName = directoryNameBuf;

	string bottonName = "groupName::" + groupName + "  " + "directory::" + directoryNameBuf;

	if (ImGui::Button(bottonName.c_str()))
	{
		this->CreateGroup(groupName, directoryName);
	}

	ImGui::Separator();

	//string prevFilePath = "";
	for (std::map<std::string, Group>::iterator itGroup = datas_.begin(); itGroup != datas_.end(); ++itGroup) {
		// グループ名を取得
		const std::string& groupName = itGroup->first;
		// グループの参照を取得
		Group& group = itGroup->second;

		if (groupName == "")
		{
			continue;
		}


		if (ImGui::TreeNode(groupName.c_str()))
		{
			char buffer[256] = { 0 };
			std::memcpy(buffer, group.DirectryPath.c_str(), std::min(group.DirectryPath.size(), sizeof(buffer) - 1));

			if (ImGui::InputText("DirectryPath", buffer, sizeof(buffer)))
			{
				group.DirectryPath = std::string(buffer);
			}

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
				}//bool値
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

						ImGui::DragFloat3(Name.c_str(), reinterpret_cast<float*>(&ptr->rotate));
						ImGui::TreePop();
					}
				}
				else if (std::holds_alternative<TransformEular>(item.value)) {
					TransformEular* ptr = std::get_if<TransformEular>(&item.value);
					string  Name = itemName;
					if (ImGui::TreeNode(itemName.c_str()))
					{
						Name = itemName + "scale";
						ImGui::DragFloat3(Name.c_str(), reinterpret_cast<float*>(&ptr->scale));
						Name = itemName + "rotate";
						ImGui::DragFloat3(Name.c_str(), reinterpret_cast<float*>(&ptr->rotate));
						Name = itemName + "translate";
						ImGui::DragFloat3(Name.c_str(), reinterpret_cast<float*>(&ptr->translate));
						ImGui::TreePop();
					}
				}
				else if (std::holds_alternative<string>(item.value))
				{
					static char buffer[256] = "";
					ImGui::InputText("text", buffer, sizeof(buffer));

					if (ImGui::Button("Confirm"))
					{
						string* ptr = std::get_if<string>(&item.value);
						*ptr = buffer;
					}
				}
				else if (std::holds_alternative<Engine::Particle::EmitType::BoxParam>(item.value)) {

					Engine::Particle::EmitType::BoxParam* ptr = std::get_if<Engine::Particle::EmitType::BoxParam>(&item.value);
					string  Name = itemName;
					if (ImGui::TreeNode(itemName.c_str()))
					{
						ImGui::DragInt("count", reinterpret_cast<int*>(&ptr->count), 0, 100);
						ImGui::Text("Transform");
						Name = itemName + "translate";
						WriteVector3(Name, ptr->translate);
						Name = itemName + "rotate";
						WriteVector3(Name, ptr->rotate);
						ImGui::Text("Emitter");
						Name = itemName + "SizeMin";
						WriteVector3(Name, ptr->sizeMin);
						Name = itemName + "SizeMax";
						WriteVector3(Name, ptr->sizeMax);
					
						Name = itemName + "velocityMin";
						WriteVector3(Name, ptr->velocityMin);

						Name = itemName + "velocityMax";
						WriteVector3(Name, ptr->velocityMax);

						ImGui::Separator();
						ImGui::DragFloat4("colorDecayMin", &ptr->colorDecayMin.x, 0.1f);
						ImGui::DragFloat4("colorDecayMax", &ptr->colorDecayMax.x, 0.1f);
						ImGui::Separator();
						Name = itemName + "scaleVelocityMin";
						WriteVector3(Name, ptr->scaleVelocityMin);
						ImGui::Separator();
						Name = itemName + "scaleVelocityMax";
						WriteVector3(Name, ptr->scaleVelocityMax);
						ImGui::Separator();
						Name = itemName + "scaleSizeMin";
						WriteVector3(Name, ptr->scaleSizeMin);
						ImGui::Separator();
						Name = itemName + "scaleSizeMax";
						WriteVector3(Name, ptr->scaleSizeMax);

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
			ImGui::TreePop();
		}

	}

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

}

void GlobalVariables::ChangeSceneLoadFiles()
{
	for (const string& path : changeSceneLoadFilePaths_)
	{
		LoadFiles(path);
	}
}

vector<string> GlobalVariables::GetAllDataKey()
{
	std::vector<std::string> keys;
	// data_の各キーを走査して追加
	for (const auto& [key, _] : datas_) {
		keys.push_back(key);
	}
	return keys;
}

void GlobalVariables::SetChangeSceneLoadFilesName(const string& filePath)
{
	// すでに存在するか確認
	if (std::find(this->changeSceneLoadFilePaths_.begin(), this->changeSceneLoadFilePaths_.end(), filePath) == this->changeSceneLoadFilePaths_.end())
	{
		// 存在しなければ追加
		this->changeSceneLoadFilePaths_.push_back(filePath);
	}
}

void GlobalVariables::WriteVector3(string name, Math::Vector::Vector3& T)
{
	ImGui::DragFloat3(name.c_str(), reinterpret_cast<float*>(&T));
}
