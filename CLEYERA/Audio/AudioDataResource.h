#pragma once
#include"Pch.h"

struct soundData
{
	IXAudio2SourceVoice* pSourcevoice = {};
	uint32_t index = {};
	WAVEFORMATEX wfex = {};
	BYTE* pBuffer = {};
	unsigned int bufferSize;
};

class AudioDataResource
{
public:
	AudioDataResource(string filepath,soundData soundData);
	~AudioDataResource();

	soundData GetSoundData() { return soundData_; }
	void SetsoundResource(IXAudio2SourceVoice* pSourcevoice) { soundData_.pSourcevoice = pSourcevoice; }
	void SetsoundWfex(WAVEFORMATEX wfex) { soundData_.wfex = wfex; }
private:

	string filepath_{};
	soundData soundData_{};

};

