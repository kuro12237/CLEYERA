#include"Utility/pch.h"
#include"Converter/TextureConverter.h"

enum Argument {
	kApplicationPath,
	kFilePath,
	NumArgument
};

int main(int argc, char* argv[]) {

	if (argc<NumArgument)
	{
		TextureConverter::OutputUsage(); 
		return 0;
	}

	CoInitializeEx(0, COINIT_MULTITHREADED);

	system("pause");

	assert(argc >= NumArgument);

	TextureConverter converter;
	//png作成
	int numOptions = argc - NumArgument;
	char** options = argv + NumArgument;

	converter.ConvertTextureWICToDDS(argv[kFilePath],numOptions,options);


	printf("変換完了\n アプリケーションを終了してください\n\n");

	system("pause");
	CoUninitialize();
	return 0;
}