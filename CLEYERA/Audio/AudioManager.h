#pragma once
#include"Pch.h"
#include"LogManager.h"
#include"Audio/AudioDataResource.h"

struct ChunkHeader
{
	char id[4];
	int32_t size;
};

struct RiffHeader
{
	ChunkHeader chunk;
	char Type[4];
};

struct FormatChunk
{
	ChunkHeader chunk;
	WAVEFORMATEX fmt;
};

class AudioManager
{
public:


	static AudioManager* GetInstance();

	static void Initialize();

	static void Finalize();

	static uint32_t SoundLoadWave(const char* filename);

	static uint32_t SoundLoadMp3(const char* fileName);

	static void SoundAllUnLoad();

	/// <summary>
	/// 音再生
	/// </summary>
	/// <param name="soundHandle"></param>
	static void AudioPlayWave(uint32_t soundHandle);
	static void AudioStopWave(uint32_t soundHandle);
	static void AudioVolumeControl(UINT soundHandle, float volume);
private:

	static bool ChackAudioDatas(string filepath);

	static bool ChackRiff(RiffHeader &riff);

	ComPtr<IXAudio2> xAudio=nullptr;
	IXAudio2MasteringVoice* masterVoice = nullptr;
	uint32_t soundDataCount_{};

	bool InitializeFlag = false;

	uint32_t AudioIndex = 0;
	uint32_t AudioIndex2 = 0;
	map<string, unique_ptr<AudioDataResource>>AudioDatas_;

#pragma region Singleton
	AudioManager() = default;
	~AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	const AudioManager& operator=(const AudioManager&) = delete;
#pragma endregion
};

