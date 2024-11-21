#pragma once
#include"Pch.h"
#include"LogManager.h"
#include"Audio/AudioDataResource.h"

/// <summary>
/// wavChank
/// </summary>
struct ChunkHeader
{
	char id[4];
	int32_t size;
};

/// <summary>
/// wavRiff
/// </summary>
struct RiffHeader
{
	ChunkHeader chunk;
	char Type[4];
};

/// <summary>
/// wavFormat
/// </summary>
struct FormatChunk
{
	ChunkHeader chunk;
	WAVEFORMATEX fmt;
};

namespace Engine::Manager
{


	/// <summary>
	/// オーディオ管理クラス
	/// </summary>
	class AudioManager
	{
	public:
		static AudioManager* GetInstance();

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 終わり
		/// </summary>
		void Finalize();

		/// <summary>
		/// waveの読み込み
		/// </summary>
		/// <param name="filename"></param>
		/// <returns></returns>
		string SoundLoadWave(const string& filename);

		/// <summary>
		/// mp3の読み込み
		/// </summary>
		/// <param name="fileName"></param>
		/// <returns></returns>
		string SoundLoadMp3(const string& fileName);

		/// <summary>
		/// dataの削除
		/// </summary>
		void SoundAllUnLoad();

		/// <summary>
		/// wave音再生
		/// </summary>
		/// <param name="soundHandle"></param>
		void AudioPlayWave(const string& FileName);

		/// <summary>
		/// mp3再生
		/// </summary>
		/// <param name="FileName"></param>
		/// <param name="Volume"></param>
		void AudioPlayMp3(const string& FileName, const float& Volume = 1.0f);
	private:

		/// <summary>
		/// すでに読んだことがあるかをチェック
		/// </summary>
		/// <param name="filepath"></param>
		/// <returns></returns>
		bool CheckAudioDatas(string filepath);

		/// <summary>
		/// Riffチェック
		/// </summary>
		/// <param name="riff"></param>
		/// <returns></returns>
		bool ChackRiff(RiffHeader& riff);

		ComPtr<IXAudio2> xAudio = nullptr;
		IXAudio2MasteringVoice* masterVoice = nullptr;
		uint32_t soundDataCount_{};

		bool InitializeFlag = false;

		uint32_t AudioIndex = 0;
		uint32_t AudioIndex2 = 0;
		map<string, SSound::AudioDataResource>AudioDatas_;

#pragma region Singleton
		AudioManager() = default;
		~AudioManager() = default;
		AudioManager(const AudioManager&) = delete;
		const AudioManager& operator=(const AudioManager&) = delete;
#pragma endregion
	};

}