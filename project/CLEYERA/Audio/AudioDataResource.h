#pragma once
#include"Pch.h"

struct soundData
{
	IXAudio2SourceVoice* pSourcevoice = {};
	WAVEFORMATEX wfex = {};
	BYTE* pBuffer = {};
	unsigned int bufferSize;
	std::vector<BYTE>mediaData;
	IMFSourceReader* MFSourceReader;
	IMFMediaType * mediaType;
	XAUDIO2_BUFFER buffer = {};
};

struct AudioDataResource
{
	~AudioDataResource();

	soundData GetSoundData() { return soundData_; }

	string filepath_{};
	soundData soundData_{};

};

