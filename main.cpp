#include <cstdio>
#include <cstdlib>
#include <cassert>
#include "TextureConverter.h"
#include  "Windows.h"
enum Argument
{
	kApplicationPath, //�A�v���P�[�V�����̃p�X
	kFilePath,//�n���ꂽ�t�@�C���p�X

	NumArgument
};

int main(int argc, char* argv[])
{
	assert(argc >= NumArgument);

	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	//�e�N�X�`���R���o�[�^�[
	TextureConverter textureConverter;
	//�e�N�X�`���ϊ�
	textureConverter.ConvertTextureWICToDDS(argv[kFilePath]);

	//COM ���C�u�����̏I��
	CoUninitialize();

	//printf("Hellow,World!\n");
	system("pause");
	return 0;
}