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

    void Initialize();

    void Finalize();

    string SoundLoadWave(const string& filename);

    string SoundLoadMp3(const string& fileName);

    void SoundAllUnLoad();

	/// <summary>
	/// 音再生
	/// </summary>
	/// <param name="soundHandle"></param>
	void AudioPlayWave(const string& FileName);

	void AudioPlayMp3(const string& FileName);
private:

	bool CheckAudioDatas(string filepath);

	bool ChackRiff(RiffHeader &riff);

	ComPtr<IXAudio2> xAudio=nullptr;
	IXAudio2MasteringVoice* masterVoice = nullptr;
	uint32_t soundDataCount_{};

	bool InitializeFlag = false;

	uint32_t AudioIndex = 0;
	uint32_t AudioIndex2 = 0;
	map<string, unique_ptr<AudioDataResource>>AudioDatas_;

#pragma region Mp3

#pragma endregion

#pragma region Singleton
	AudioManager() = default;
	~AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	const AudioManager& operator=(const AudioManager&) = delete;
#pragma endregion
};

