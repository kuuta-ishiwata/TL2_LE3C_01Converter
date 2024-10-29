#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "TextureConverter.h"
#include  "Windows.h"
enum Argument
{
	kApplicationPath, //アプリケーションのパス
	kFilePath,//渡されたファイルパス

	NumArgument
};

int main(int argc, char* argv[])
{
	assert(argc >= NumArgument);

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//テクスチャコンバーター
	TextureConverter textureConverter;
	//テクスチャ変換
	textureConverter.ConvertTextureWICToDDS(argv[kFilePath]);

	//COM ライブラリの終了
	CoUninitialize();

	//printf("Hellow,World!\n");
	system("pause");
	return 0;
}