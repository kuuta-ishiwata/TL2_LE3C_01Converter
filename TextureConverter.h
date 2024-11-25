#pragma once
#include <string>
#include "External/DirectXTex/DirectXTex.h"

class TextureConverter
{

public:

	TextureConverter();
	~TextureConverter();
	///<summary>
	///テクスチャをWICからDDSを変換する
	/// </summary>
	///<param name = "filePath">ファイルパス＜/param＞
	void ConvertTextureWICToDDS(const std::string& filePath);



private:


	/// <summary>
	/// テクスチャファイル読み込み
	/// </summary>
	void LoadWICTextureFromFile(const std::string& filePath);

	///
	///
	

	//
	//フォルダパスとファイル名を分離する
	//
	void SeparateFilePath(const std::wstring& filePath);

	void SaveDDSTextureToFile();

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);

	DirectX::TexMetadata metadata_;

	DirectX::ScratchImage scratchImage_;

	//ディレクトリパス
	std::wstring directoryPath_;
	//ファイル名
	std::wstring fileName_;
	//ファイル拡張子
	std::wstring fileExt_;

};

