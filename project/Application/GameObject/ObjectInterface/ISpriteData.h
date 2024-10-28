#pragma once
#include"Sprite/Sprite.h"
#include"Utility/ObjectManager/GameObjectManager.h"
#include"Utility/GlobalVariables/GlobalVariables.h"

/// <summary>
/// 2d��Sprite�̒��ۃN���X
/// </summary>
class ISpriteData
{
public:
	ISpriteData();
	virtual ~ISpriteData() {};

	/// <summary>
	/// ImGui�X�V����
	/// </summary>
	virtual void ImGuiUpdate() = 0;

	/// <summary>
	/// Json�g���쐬
	/// </summary>
	void CreateJsonData();

	/// <summary>
	/// �قڃ����ڂ�o�^
	/// </summary>
	template<typename T>
	void AddJsonItem(string itemName, T value) { return globalVariables_->AddItem(name_, itemName, value); }

	/// <summary>
	/// Json�f�[�^�����
	/// </summary>
	template<typename T>
	T GetJsonItem(string itemName) { return globalVariables_->GetValue<T>(name_, itemName); }

	/// <summary>
	/// SpriteWorldTransform�Ȃǂ̃f�[�^��Json��쐬
	/// </summary>
	void CreateJsonSpriteData();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw2d();

	/// <summary>
	/// �A���J�[���v�Z
	/// </summary>
	void CalcAnkerPos();

#pragma region Get

	Engine::Transform::WorldTransform& GetWorldTransform() { return worldTransform_; }

#pragma endregion


private:

	string prevFileName_ = "";

protected:
	void CreateObject();
	void UpdateData();

	string name_ = "";

	GlobalVariables* globalVariables_ = nullptr;
	GameObjectManager* gameObjectManager_ = nullptr;

	unique_ptr<Engine::Objects::Sprite>sprite_ = nullptr;
	Engine::Transform::WorldTransform worldTransform_ = {};
	string fileName_ = "";

	uint32_t texHandle_ = 0;
	Math::Vector::Vector2 ankerPos_ = {};
};
