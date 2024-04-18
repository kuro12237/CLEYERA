#pragma once
#include"Pch.h"

struct soundData
{
	IXAudio2SourceVoice* pSourcevoice = {};
	uint32_t index = {};
	std::string fileName;
	WAVEFORMATEX wfex = {};
	BYTE* pBuffer = {};
	unsigned int bufferSize;
	std::vector<BYTE>mediaData;
	IMFSourceReader* MFSourceReader;
	IMFMediaType * mediaType;
};

class AudioDataResource
{
public:
	AudioDataResource(string filepath,soundData soundData);
	~AudioDataResource();

	soundData GetSoundData() { return soundData_; }

private:

	string filepath_{};
	soundData soundData_{};

};

