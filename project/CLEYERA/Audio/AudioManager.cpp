#include"AudioManager.h"

using namespace SSound;
using namespace Engine::Manager;

AudioManager* AudioManager::GetInstance()
{
	static AudioManager instance;
	return &instance;
}

void AudioManager::Initialize()
{
	HRESULT hr{};
	if (!InitializeFlag)
	{
		InitializeFlag = true;
	}
	else {
		LogManager::Log("Audio::Initialize_ERROR\n");
		assert(0);
	}

	CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);
	MFStartup(MF_VERSION, MFSTARTUP_NOSOCKET);

	hr = XAudio2Create(&xAudio, 0);
	assert(SUCCEEDED(hr));
	//masterVoiceの作成
	hr = xAudio->CreateMasteringVoice(&masterVoice);
	assert(SUCCEEDED(hr));

#ifdef _DEBUG

	//XAUDIO2_DEBUG_CONFIGURATION debug{};
	//debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
	//debug.BreakMask = XAUDIO2_LOG_ERRORS;
	//xAudio->SetDebugConfiguration(&debug, 0);

#endif // _DEBUG

}

void AudioManager::Finalize()
{
	SoundAllUnLoad();
	xAudio.Reset();

	MFShutdown();
	CoUninitialize();
}

string AudioManager::SoundLoadWave(const string& filename)
{
	if (CheckAudioDatas(filename))
	{
		AudioIndex++;

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
	}
	return filename;
}

string AudioManager::SoundLoadMp3(const string& fileName)
{

	if (CheckAudioDatas(fileName))
	{
		AudioDataResource resource;
		AudioDatas_[fileName] = resource;

		//文字列変換
		int wideStrSize = MultiByteToWideChar(CP_UTF8, 0, fileName.c_str(), -1, NULL, 0);
		WCHAR* wideStr = new WCHAR[wideStrSize];
		HRESULT hr = MultiByteToWideChar(CP_UTF8, 0, fileName.c_str(), -1, wideStr, wideStrSize);
		assert(SUCCEEDED(hr));

		//ソースリーダーの作成
		MFCreateSourceReaderFromURL(wideStr, nullptr, &AudioDatas_[fileName].soundData_.MFSourceReader);

		//メディアタイプ
		MFCreateMediaType(&AudioDatas_[fileName].soundData_.mediaType);
		AudioDatas_[fileName].soundData_.mediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		AudioDatas_[fileName].soundData_.mediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);

		AudioDatas_[fileName].soundData_.MFSourceReader->SetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), nullptr, AudioDatas_[fileName].soundData_.mediaType);

		AudioDatas_[fileName].soundData_.mediaType->Release();
		AudioDatas_[fileName].soundData_.mediaType = nullptr;
		AudioDatas_[fileName].soundData_.MFSourceReader->GetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), &AudioDatas_[fileName].soundData_.mediaType);
	
		//mp3の中身解析
		while (true)
		{
			IMFSample* sample = nullptr;
			DWORD dwStreamFlags = 0;

			hr = AudioDatas_[fileName].soundData_.MFSourceReader->ReadSample(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, nullptr, &dwStreamFlags, nullptr, &sample);
			assert(SUCCEEDED(hr));

			if (dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM)
			{
				break;
			}

			IMFMediaBuffer* mediaBuff = nullptr;
			DWORD cbCurrentLength = 0;
			hr = sample->ConvertToContiguousBuffer(&mediaBuff);
			assert(SUCCEEDED(hr));

			BYTE* pbuffer = nullptr;
			hr = mediaBuff->Lock(&pbuffer, nullptr, &cbCurrentLength);
			assert(SUCCEEDED(hr));

			AudioDatas_[fileName].soundData_.mediaData.resize(AudioDatas_[fileName].soundData_.mediaData.size() + cbCurrentLength);
			memcpy(AudioDatas_[fileName].soundData_.mediaData.data() + AudioDatas_[fileName].soundData_.mediaData.size() - cbCurrentLength, pbuffer, cbCurrentLength);

			hr = mediaBuff->Unlock();
			assert(SUCCEEDED(hr));

			mediaBuff->Release();
			sample->Release();
		}
		

		AudioDatas_[fileName].soundData_.buffer.pAudioData = AudioDatas_[fileName].soundData_.mediaData.data();
		AudioDatas_[fileName].soundData_.buffer.AudioBytes = sizeof(BYTE) * static_cast<UINT32>(AudioDatas_[fileName].soundData_.mediaData.size());

		return fileName;
	}
	return fileName;
}

void AudioManager::SoundAllUnLoad()
{
	AudioDatas_.clear();
}

void AudioManager::AudioPlayWave(const string& FileName)
{
	FileName;
	HRESULT result{};
	IXAudio2SourceVoice* sourceVoice = {};

	soundData soundData;

	result = xAudio->CreateSourceVoice(&sourceVoice, &soundData.wfex);
	assert(SUCCEEDED(result));

	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	result = sourceVoice->SubmitSourceBuffer(&buf);
	result = sourceVoice->SetVolume(1.0f);
	result = sourceVoice->Start();

	assert(SUCCEEDED(result));
}

void AudioManager::AudioPlayMp3(const string& FileName,const float &Volume)
{
	WAVEFORMATEX* waveFormat{};
	MFCreateWaveFormatExFromMFMediaType(AudioDatas_[FileName].soundData_.mediaType, &waveFormat, nullptr);

	xAudio->CreateSourceVoice(&AudioDatas_[FileName].soundData_.pSourcevoice, waveFormat);

	AudioDatas_[FileName].soundData_.pSourcevoice->SubmitSourceBuffer(&AudioDatas_[FileName].soundData_.buffer);
	AudioDatas_[FileName].soundData_.pSourcevoice->SetVolume(Volume);
	AudioDatas_[FileName].soundData_.pSourcevoice->Start();

}

bool AudioManager::CheckAudioDatas(string filepath)
{
	if (AudioDatas_.find(filepath) == AudioDatas_.end())
	{
		return true;
	}
	return false;
}

bool AudioManager::ChackRiff(RiffHeader& riff)
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
