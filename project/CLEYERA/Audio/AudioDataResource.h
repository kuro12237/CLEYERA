#pragma once
#include"Pch.h"

/// <summary>
/// サウンドのデータ
/// </summary>
namespace SSound
{
	/// <summary>
	/// 音データ構造体
	/// </summary>
	struct soundData
	{
		IXAudio2SourceVoice* pSourcevoice = {};
		WAVEFORMATEX wfex = {};
		BYTE* pBuffer = {};
		unsigned int bufferSize;
		std::vector<BYTE>mediaData;
		IMFSourceReader* MFSourceReader;
		IMFMediaType* mediaType;
		XAUDIO2_BUFFER buffer = {};
	};

	/// <summary>
	/// 保存構造体
	/// </summary>
	struct AudioDataResource
	{
		~AudioDataResource();

		soundData GetSoundData() { return soundData_; }

		string filepath_{};
		soundData soundData_{};

	};
}
