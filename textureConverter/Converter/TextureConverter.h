#pragma once
#include"../Utility/pch.h"

class TextureConverter
{
public:
	TextureConverter() {};
	~TextureConverter() {};

	/// <summary>
	/// DDSÇ…ïœä∑
	/// </summary>
	/// <param name="directory"></param>
	/// <param name="filePath"></param>
	void ConvertTextureWICToDDS(const std::string& filePath, int numOptions = 0, char* options[] = nullptr);

	//6ñáÇÃpngÇcubeMapÇ…ïœä∑
	void ConvertTextureWICToCubemap(const std::string& directorys, const std::vector<std::string>& filePaths);

	/// <summary>
	/// ñ¢äÆê¨
	/// </summary>
	/// <param name="directorys"></param>
	/// <param name="filePath"></param>
	void ConvertTextureHdrToDDS(const std::string directorys, const std::string& filePath);

	std::wstring ConvertStringToWstring(const std::string& name);

	void SeparateFilePath(std::wstring& filePath);

	void CreateCubeMapFromTextures(
		const std::wstring& posY,
		const std::wstring& negY,
		const std::wstring& negX,
		const std::wstring& posZ,
		const std::wstring& posX,
		const std::wstring& negZ,
		const std::wstring& outputName);

	static void OutputUsage();


private:

	void SaveDDSTextureToFile(int numOptions = 0, char* options[] = nullptr);

	void SaveHdrToDDSTextureToFile();

	DirectX::TexMetadata metadata_;
	DirectX::ScratchImage scratchImage_;

	std::wstring directryPath_;
	std::wstring fileName_;
	std::wstring fileExt_;
};