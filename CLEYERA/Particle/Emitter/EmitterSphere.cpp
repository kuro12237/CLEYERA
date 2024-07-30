#include "EmitterSphere.h"

void EmitterSphere::Create(ParticleEmitter*e)
{

	sphereBuf_ = make_unique<BufferResource<SEmitterSphere>>();
	sphereBuf_->CreateResource(e->GetEmitMax());
	sphereBuf_->CreateInstancingResource(e->GetEmitMax(), e->GetEmitName(), sizeof(EmitterSphere));

}

void EmitterSphere::Update(ParticleEmitter* e)
{
	e;
	//sphereBuf_->Setbuffer(e->GetSphereParam());
}

void EmitterSphere::Dispatch()
{
	

}

void EmitterSphere::Emit()
{
}
