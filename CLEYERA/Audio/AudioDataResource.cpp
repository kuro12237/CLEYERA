#include"AudioDataResource.h"

AudioDataResource::~AudioDataResource()
{
	delete[] soundData_.pBuffer;
	soundData_.bufferSize = 0;
	soundData_.pBuffer = 0;
	soundData_.wfex;
}
