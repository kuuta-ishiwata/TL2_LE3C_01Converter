#pragma once
#include <string>
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
/// 

	static std::wstring ConvertMultiByteStringToWideString(const std::string& mString);


};

