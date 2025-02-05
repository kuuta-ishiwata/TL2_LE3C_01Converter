#include "TextureConverter.h"
//#include <stringapiset.h>
#include <Windows.h>
using namespace DirectX;

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
	SaveDDSTextureToFile();

}


void TextureConverter::LoadWICTextureFromFile(const std::string& filePath)
{

	//1.ファイルパスワイルド文字列に変換
	std::wstring wFilePath = ConvertMultiByteStringToWideString(filePath);
	//2 テクスチャを読み込む
	HRESULT result = DirectX::LoadFromWICFile(wFilePath.c_str(), DirectX::WIC_FLAGS_NONE,&metadata_,scratchImage_);
	assert(SUCCEEDED(result));
	//フォルダパスとファイルを分離する
	SeparateFilePath(wFilePath);

}

void TextureConverter::SeparateFilePath(const std::wstring& filePath)
{


	size_t pos1;
	std::wstring exceptExt;
	//区切り文字'_'がでてくる
	pos1 = filePath.rfind('.');

	//検索がヒットしたら
	if (pos1 != std::wstring::npos)
	{
		//区切り文字の後ろをファイル拡張子として保存
		fileExt_ = filePath.substr(pos1 + 1, filePath.size() - pos1 - 1);
		//区切り文字の前までを抜き出す
		exceptExt = filePath.substr(0, pos1);
	}
	else
	{
		fileExt_ = L"";
		exceptExt = filePath;
	}
	
	//区切り文字がでてくる一番最後の部分を検索
	pos1 = exceptExt.rfind('\\');
	if (pos1 != std::wstring::npos)
	{
		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイルとして保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 -1);
		return;

	}

	pos1 = exceptExt.rfind('/');
	if (pos1 != std::wstring::npos)
	{

		//区切り文字の前までをディレクトリパスとして保存
		directoryPath_ = exceptExt.substr(0, pos1 + 1);
		//区切り文字の後ろをファイルとして保存
		fileName_ = exceptExt.substr(pos1 + 1, exceptExt.size() - pos1 - 1);
		return;
	}

	//区切りがないのでファイル名のみとして扱う
	directoryPath_ = L"";
	fileName_ = exceptExt;

}


void TextureConverter::SaveDDSTextureToFile()
{
	
	HRESULT result;

	std::wstring filePath = directoryPath_ + fileName_ + L".dds";

	ScratchImage mipChain;

	result = GenerateMipMaps(scratchImage_.GetImages(), scratchImage_.GetImageCount(), scratchImage_.GetMetadata(), TEX_FILTER_DEFAULT, 0, mipChain);

	if (SUCCEEDED(result))
	{
		scratchImage_ = std::move(mipChain);
		metadata_ = scratchImage_.GetMetadata();
	}
	

	ScratchImage converted;
	result = Compress(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DXGI_FORMAT_BC7_UNORM_SRGB, TEX_COMPRESS_BC7_QUICK | TEX_COMPRESS_SRGB_OUT | TEX_COMPRESS_PARALLEL, 1.0f, converted);
	if (SUCCEEDED(result))
	{
		scratchImage_ = std::move(converted);
		metadata_ = scratchImage_.GetMetadata();
	}

	// 読み込んだテクスチャをSRGBとして扱う
	metadata_.format = MakeSRGB(metadata_.format);
	//DDSファイル書き出し
	result = SaveToDDSFile(scratchImage_.GetImages(), scratchImage_.GetImageCount(), metadata_, DDS_FLAGS_NONE, filePath.c_str());

}

std::wstring TextureConverter::ConvertMultiByteStringToWideString(const std::string& mString)
{

	int filePathBufferSize = MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, nullptr, 0);

	//ワイルド文字数
	std::wstring wString;
	wString.resize(filePathBufferSize);

	//ワイルド文字列に変換
	//ワイルド文字列に変換
	MultiByteToWideChar(CP_ACP, 0, mString.c_str(), -1, &wString[0], filePathBufferSize);

	return wString;

}
