#include "TextureConverter.h"
//#include <stringapiset.h>
#include <Windows.h>

TextureConverter::TextureConverter()
{
}

TextureConverter::~TextureConverter()
{
}

void TextureConverter::ConvertTextureWICToDDS(const std::string& filePath)
{

	//テクスチャファイルを読み込む
	LoadWICTextureFromFile(filePath);
	//DDS形式で変換して書き出す


}

void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{
	//1.ファイルパスワイルド文字列に変換
	std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);

}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{

	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	//ワイルド文字数
	std::wstring wString;
	wString.resize(filePathBufferSize);

	//ワイルド文字列に変換
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), 1, &wString[0], filePathBufferSize);

	return std::wstring();
}
