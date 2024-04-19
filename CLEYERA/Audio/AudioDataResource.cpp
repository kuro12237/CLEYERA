#include"AudioDataResource.h"



AudioDataResource::~AudioDataResource()
{
	delete[] soundData_.pBuffer;
	delete soundData_.pSourcevoice;
	soundData_.bufferSize = 0;
	soundData_.pBuffer = 0;
	soundData_.wfex;
}
