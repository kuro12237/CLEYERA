#include "IEmitterState.h"

void Particle::IEmitterState::SpownDraw()
{
	uint32_t index = 0;
	for (auto it = draws_.begin(); it != draws_.end(); ++it) {
		// イテレーターを使って LineModel オブジェクトにアクセス
		(*it)->Draw(wTs_[index]);
		index++;
	}
}

void Particle::IEmitterState::CreateEmitDraw(uint32_t num, string name)
{
	draws_.resize(num);
	for (size_t i = 0; i < num; i++)
	{
		draws_[i] = make_unique<ParticleEmitDraw>();
		draws_[i]->Initialize(name+to_string(i));
	}

	wTs_.resize(num);
	for (size_t i = 0; i < num; i++)
	{
		wTs_[i].Initialize();
	}
}
