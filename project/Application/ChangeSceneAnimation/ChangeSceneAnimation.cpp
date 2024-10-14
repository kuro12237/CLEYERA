#include "ChangeSceneAnimation.h"

ChangeSceneAnimation* ChangeSceneAnimation::GetInstance()
{
	static ChangeSceneAnimation instance;
	return &instance;
}

void ChangeSceneAnimation::Initialize()
{
	if (initializeLock_)
	{
		return;
	}
	initializeLock_ = true;

	///�m�C�Y�̃e�N�X�`����ǂݍ���
	noiseTex_.resize(1);
	noiseTex_[0] = TextureManager::LoadPngTexture("GameObject/Noise/Noise.png");


	titleName2d_ = make_unique<TitleName2d>();
	titleName2d_->Initialize(noiseTex_[0]);
	titleName2d_->SetP_DissolveMask(dissolveMask_);

	titleBack2d_ = make_unique<TitleBack2d>();
	titleBack2d_->Initialize(noiseTex_[0]);
	titleBack2d_->SetP_DissolveMask(dissolveMask_);

	rodingIcon_ = make_unique<RodingIcon2d>();
	rodingIcon_->Initialize(noiseTex_[0]);
	rodingIcon_->SetP_DissolveMask(dissolveMask_);

	fireEmberParticle_ = make_unique<FireEmber2dParticle>();
	fireEmberParticle_->Initialize();

}

void ChangeSceneAnimation::ImGuiUpdate()
{
	titleBack2d_->ImGuiUpdate();
	titleName2d_->ImGuiUpdate();
	rodingIcon_->ImGuiUpdate();
	fireEmberParticle_->ImGuiUpdate();
}

void ChangeSceneAnimation::Update()
{


	fireEmberParticle_->Emit();
	fireEmberParticle_->Update();
	if (isCompliteFlag_)
	{
		//fireEmberParticle_->SetUseFlag(false);
		//fireEmberParticle_->Update();
		return;
	}
	else
	{

		//fireEmberParticle_->SetUseFlag(true);
	}


	isChangeSceneFlag_ = false;
	//�X�^�[�g��
	if (isUpdateFlag_)
	{
		flame_ += 1.0f / 120.0f;
	}
	//�O��
	if (isStartFlag_)
	{
		dissolveMask_ = Math::Vector::EaseOutQuad(dissolveMax_, 0.0f, flame_);

		if (dissolveMask_ <= 0.0f)
		{
			flame_ = 0.0f;
			isStartFlag_ = false;
			isEndFlag_ = true;
			isChangeSceneFlag_ = true;
		}
	}
	//�㔼
	if (isEndFlag_)
	{
		dissolveMask_ = Math::Vector::EaseOutQuad(0.0f, dissolveMax_, flame_);
		if (dissolveMask_ >= dissolveMax_)
		{
			flame_ = 0.0f;
			isEndFlag_ = false;
			isUpdateFlag_ = false;
			isCompliteFlag_ = true;
		}
	}
	//fireEmberParticle_->Emit();
	//fireEmberParticle_->Update();

	titleName2d_->Update();
	titleBack2d_->Update();
	rodingIcon_->Update();
}

void ChangeSceneAnimation::Draw()
{

	if (isCompliteFlag_)
	{
		return;
	}

	titleBack2d_->Draw2d();
	fireEmberParticle_->Draw();
	titleName2d_->Draw2d();
	rodingIcon_->Draw2d();
}

void ChangeSceneAnimation::ChangeStart()
{
	if (isCompliteFlag_)
	{
		isStartFlag_ = true;
		isUpdateFlag_ = true;
		isEndFlag_ = false;
		isCompliteFlag_ = false;
	}
}
