#pragma once
#include "Animation/AnimationManager.h"
#include "Game3dObjectDesc.h"
#include "Graphics/PipelineManager/GraphicsPipelineManager.h"
#include "Light/DirectionLIght.h"
#include "ModelManager.h"

#include "Graphics/CallPipline/PipelineHandler.h"

namespace Engine::Objects
{

/// <summary>
/// ゲームオブジェクトクラスmodelをセットすることで3dモデルを表示できる
/// </summary>
class Game3dObject
{
public:
  Game3dObject() {};
  ~Game3dObject() {};

  /// <summary>
  /// 作製
  /// </summary>
  /// <param name="piplineSelect"></param>
  void Create(unique_ptr<IPipelineCommand> piplineSelect = nullptr);

  /// <summary>
  /// モデルを設定
  /// </summary>
  /// <param name="index"></param>
  void SetModel(uint32_t index);

  /// <summary>
  /// パイプライン切替
  /// </summary>
  /// <param name="piplineSelect"></param>
  void ChangePipline(unique_ptr<IPipelineCommand> piplineSelect);

  /// <summary>
  /// 描画
  /// </summary>
  /// <param name="worldTransform"></param>
  void Draw(Engine::Transform::WorldTransform worldTransform);

  /// <summary>
  /// スキニング用のバッファーを作製
  /// </summary>
  void CreateSkinningParameter();

  /// <summary>
  /// 骨更新
  /// </summary>
  /// <param name="fileName"></param>
  /// <param name="t"></param>
  void SkeletonUpdate();

  /// <summary>
  /// 好き人ぐ更新
  /// </summary>
  void SkinningUpdate();

  /// <summary>
  /// オブジェクトの名前を設定
  /// </summary>
  /// <param name="name"></param>
  void SetObjectName(const string &name) { name_ = name; }

#pragma region Set

  void SetDesc(const Game3dObjectDesc &desc) { game3dObjectDesc_ = &desc; }

  void SetName(string name) { name_ = name; }

  void SetSkinningFlag(bool f) { skinningFlag_ = f; }

  void SetTexHandle(uint32_t texHandle) { modelData_.material.handle = texHandle; }

#pragma endregion

#pragma region Get

  SAnimation::Skeleton &GetSkeleton() { return skeleton_; }

  bool GetSkinningFlag() { return skinningFlag_; }

#pragma endregion

private:
  string name_ = "";

  Engine::Objects::Model *model_ = nullptr;
  SModelData modelData_ = {};
  uint32_t prevModelIndex_ = 0;

  unique_ptr<PipelineHandler> piplineHandler_ = nullptr;

  unique_ptr<Engine::Buffer::BufferResource<Material>> MaterialBuffer_ = nullptr;
  Material material_ = {};

  Material MaterialConverter();
  unique_ptr<Engine::Buffer::BufferResource<SkinCluster>> cSkinCluster_ = nullptr;

#pragma region Skinning
  bool skinningFlag_ = false;
  SAnimation::Skeleton skeleton_;
  std::vector<Math::Matrix::Matrix4x4> inverseBindMatrices;
  unique_ptr<Engine::Buffer::BufferResource<WellForGPU>> palette_ = nullptr;
  vector<WellForGPU> paletteParam_;
#pragma endregion

  const Game3dObjectDesc *game3dObjectDesc_{};
};
} // namespace Engine::Objects
