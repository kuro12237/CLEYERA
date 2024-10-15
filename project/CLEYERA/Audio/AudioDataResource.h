#pragma once
#include"Pch.h"

/// <summary>
/// �T�E���h�̃f�[�^
/// </summary>
namespace SSound
{
	/// <summary>
	/// ���f�[�^�\����
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
	/// �ۑ��N���X
	/// </summary>
	struct AudioDataResource
	{
		~AudioDataResource();

		soundData GetSoundData() { return soundData_; }

		string filepath_{};
		soundData soundData_{};

	};
}
