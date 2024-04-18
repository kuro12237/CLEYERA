#include"AudioManager.h"

AudioManager* AudioManager::GetInstance()
{
	static AudioManager instance;
	return &instance;
}

void AudioManager::Initialize()
{
	HRESULT hr{};
	if (!AudioManager::GetInstance()->InitializeFlag)
	{
		AudioManager::GetInstance()->InitializeFlag = true;
	}
	else {
		LogManager::Log("Audio::Initialize_ERROR\n");
		assert(0);
	}

	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	MFStartup(MF_VERSION, MFSTARTUP_NOSOCKET);

	hr = XAudio2Create(&AudioManager::GetInstance()->xAudio, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(hr));
	//masterVoiceの作成
	hr = AudioManager::GetInstance()->xAudio->CreateMasteringVoice(&AudioManager::GetInstance()->masterVoice);
	assert(SUCCEEDED(hr));

#ifdef _DEBUG

	XAUDIO2_DEBUG_CONFIGURATION debug{};
	debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
	debug.BreakMask = XAUDIO2_LOG_ERRORS;
	AudioManager::GetInstance()->xAudio->SetDebugConfiguration(&debug, 0);

#endif // _DEBUG

}

void AudioManager::Finalize()
{
	SoundAllUnLoad();
	AudioManager::GetInstance()->xAudio.Reset();
}

uint32_t AudioManager::SoundLoadWave(const char* filename)
{
	uint32_t index = 0;
	if (ChackAudioDatas(filename))
	{
		AudioManager::GetInstance()->AudioIndex++;

		ifstream file;
		file.open(filename, std::ios_base::binary);
		assert(SUCCEEDED(file.is_open()));

		RiffHeader riff = {};
		file.read((char*)&riff, sizeof(riff));

		if (strncmp(riff.chunk.id, "RIFF", 4) != 0)
		{
			LogManager::Log("RIFF_ERROR");
			assert(0);
		}
		if (strncmp(riff.Type, "WAVE", 4) != 0)
		{
			LogManager::Log("WAVE_ERROR");
			assert(0);
		}

		FormatChunk format = {};
		
		file.read((char*)&format, sizeof(ChunkHeader));
		if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
			assert(0);
		}

		assert(format.chunk.size <= sizeof(format.fmt));
		file.read((char*)&format.fmt, format.chunk.size);

		ChunkHeader data = {};
		file.read((char*)&data, sizeof(data));
		if (strncmp(data.id, "JUNK", 4) == 0) {

			file.seekg(data.size, ios_base::cur);
			file.read((char*)&data, sizeof(data));
		}
		if (strncmp(data.id, "data", 4) != 0)
		{
			assert(0);
		}
		char* pBuffer = new char[data.size];
		file.read(pBuffer, data.size);
		file.close();

		//サウンドデータの作成
		soundData soundData;
		soundData.wfex = format.fmt;
		soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
		soundData.bufferSize = data.size;
		soundData.index = AudioManager::GetInstance()->AudioIndex;
		AudioManager::GetInstance()->AudioDatas_[filename] = make_unique<AudioDataResource>(filename, soundData);

		index = AudioManager::GetInstance()->AudioIndex;
	}
	else
	{
		index = AudioManager::GetInstance()->AudioDatas_[filename].get()->GetSoundData().index;
	}

	return index;
}

uint32_t AudioManager::SoundLoadMp3(const string& fileName)
{

	if (ChackAudioDatas(fileName))
	{
		IMFSourceReader* MFSourceReader = nullptr;
		IMFMediaType* MFMediaType = nullptr;
		//文字列変換
		int wideStrSize = MultiByteToWideChar(CP_UTF8, 0, fileName.c_str(), -1, NULL, 0);
		WCHAR* wideStr = new WCHAR[wideStrSize];
		HRESULT hr = MultiByteToWideChar(CP_UTF8, 0, fileName.c_str(), -1, wideStr, wideStrSize);
		assert(SUCCEEDED(hr));

		//ソースリーダーの作成
		MFCreateSourceReaderFromURL(wideStr,nullptr, &MFSourceReader);

		//メディアタイプ
		MFCreateMediaType(&MFMediaType);
		MFMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		MFMediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
		MFSourceReader->SetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), nullptr, MFMediaType);

		MFMediaType->Release();
		MFMediaType = nullptr;
		MFSourceReader->GetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), &MFMediaType);
		WAVEFORMATEX *waveFormat = nullptr;
		MFCreateWaveFormatExFromMFMediaType(MFMediaType, &waveFormat, nullptr);

		//mp3の中身解析
		std::vector<BYTE>mediaData;
		while (true)
		{
			IMFSample* sample = nullptr;
			DWORD dwStreamFlags = 0;

			MFSourceReader->ReadSample(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, nullptr,& dwStreamFlags, nullptr, &sample);

			if (dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM)
			{
				break;
			}

			IMFMediaBuffer* mediaBuff = nullptr;
			DWORD cbCurrentLength = 0;
			sample->ConvertToContiguousBuffer(&mediaBuff);

			BYTE* pbuffer = nullptr;
			mediaBuff->Lock(&pbuffer, nullptr, &cbCurrentLength);
			mediaData.resize(mediaData.size() + cbCurrentLength);
			std::memcpy(mediaData.data() + mediaData.size() - cbCurrentLength, pbuffer, cbCurrentLength);

			mediaBuff->Unlock();

			mediaBuff->Release();
			sample->Release();
		}

		soundData soundData;
		soundData.wfex = move(*waveFormat);
		soundData.mediaData = mediaData;
		soundData.pBuffer = soundData.mediaData.data();
		soundData.bufferSize = unsigned int(mediaData.size());
		soundData.index = AudioManager::GetInstance()->AudioIndex;
		soundData.MFSourceReader = MFSourceReader;
		soundData.mediaType = MFMediaType;

		//登録
		AudioManager::GetInstance()->AudioDatas_[fileName] = make_unique<AudioDataResource>(fileName, soundData);
		return AudioManager::GetInstance()->AudioIndex;
	}
	else
	{
		return AudioManager::GetInstance()->AudioDatas_[fileName].get()->GetSoundData().index;
	}

	//return 0;
}

void AudioManager::SoundAllUnLoad()
{
	AudioManager::GetInstance()->AudioDatas_.clear();
}

void AudioManager::AudioPlayWave(uint32_t soundHandle)
{ 
	for (const auto& [key, s] : AudioManager::GetInstance()->AudioDatas_)
	{
		key;
		if (s.get()->GetSoundData().index == soundHandle)
		{
		
			HRESULT result{};
			IXAudio2SourceVoice* pSourcevoice = {};
			
			WAVEFORMATEX wfex = s.get()->GetSoundData().wfex;
			result = AudioManager::GetInstance()->xAudio->CreateSourceVoice(&pSourcevoice,&wfex);
			assert(SUCCEEDED(result));
			s.get()->SetsoundResource(pSourcevoice);
			s.get()->SetsoundWfex(wfex);
		
			XAUDIO2_BUFFER buf{};
			buf.pAudioData = s.get()->GetSoundData().pBuffer;
			buf.AudioBytes = s.get()->GetSoundData().bufferSize;
			buf.Flags = XAUDIO2_END_OF_STREAM;
			result = s.get()->GetSoundData().pSourcevoice->SubmitSourceBuffer(&buf);
			result = s.get()->GetSoundData().pSourcevoice->SetVolume(1.0f);
			result = s.get()->GetSoundData().pSourcevoice->Start();

			assert(SUCCEEDED(result));
		}
	}
}

void AudioManager::AudioStopWave(uint32_t soundHandle)
{
	for (const auto& [key, s] : AudioManager::GetInstance()->AudioDatas_)
	{
		key;
		if (s.get()->GetSoundData().index == soundHandle)
		{
			HRESULT result{};
			
			result = s.get()->GetSoundData().pSourcevoice->Stop();
			assert(SUCCEEDED(result));
		
		}
	}
	
}

void AudioManager::AudioVolumeControl(UINT soundHandle, float volume)
{
	for (const auto& [key, s] : AudioManager::GetInstance()->AudioDatas_)
	{
		key;
		if (s.get()->GetSoundData().index == soundHandle)
		{
			HRESULT result{};

			result = s.get()->GetSoundData().pSourcevoice->SetVolume(volume);
			assert(SUCCEEDED(result));

		}
	}
}

void AudioManager::AudioPlayMp3(const uint32_t& soundHandle)
{
	for (const auto& [key, s] : AudioManager::GetInstance()->AudioDatas_)
	{
		if (s.get()->GetSoundData().index == soundHandle)
		{
			HRESULT result{};
			IXAudio2SourceVoice* pSourcevoice = {};

			soundData soundData = AudioManager::GetInstance()->AudioDatas_[key]->GetSoundData();

			result = AudioManager::GetInstance()->xAudio->CreateSourceVoice(&pSourcevoice, &soundData.wfex);
			assert(SUCCEEDED(result));
		
			XAUDIO2_BUFFER buf{};
			buf.pAudioData = soundData.pBuffer;
			buf.AudioBytes = soundData.bufferSize;
			buf.Flags = XAUDIO2_END_OF_STREAM;

			result = pSourcevoice->SubmitSourceBuffer(&buf);
			assert(SUCCEEDED(result));
			result = pSourcevoice->SetVolume(1.0f);
			assert(SUCCEEDED(result));
			result = pSourcevoice->Start();
			assert(SUCCEEDED(result));
		}
	}

}

bool AudioManager::ChackAudioDatas(string filepath)
{
	if (AudioManager::GetInstance()->AudioDatas_.find(filepath)==AudioManager::GetInstance()->AudioDatas_.end())
	{
		return true;
	}
	return false;
}

bool AudioManager::ChackRiff(RiffHeader &riff)
{
	bool flag = true;
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0)
	{
		LogManager::Log("RIFF_ERROR");
		flag = false;
	}
	if (strncmp(riff.Type, "WAVE", 4) != 0)
	{
		LogManager::Log("WAVE_ERROR");
		flag = false;
	}
	return flag;
}
