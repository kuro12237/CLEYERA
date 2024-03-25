#include"AudioDataResource.h"

AudioDataResource::AudioDataResource(string filepath, soundData soundData)
{
	filepath_ = filepath;
	soundData_ = soundData;

}

AudioDataResource::~AudioDataResource()
{
	delete[] soundData_.pBuffer;
	soundData_.bufferSize = 0;
	soundData_.pBuffer = 0;
	soundData_.wfex = {};
}
