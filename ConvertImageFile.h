#pragma once
#include <wincodec.h>
#include <wrl/client.h>

#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "ole32.lib")
class ConvertImageFile
{
private:
	// 변환 파일 저장 위치
	CString strCvrtPath;
	// 기존 파일명
	CString strOriginName;
	// 기존 경로
	CString strOriginPath;
	// 기존 확장자 (0: jpg, 1: jpeg, 2:png, 3: bmp, 4: gif);
	int intExtension;

	BOOL MakeConvertedImage(LPCTSTR InSourceImageFileName, LPCTSTR InDestImageFileName,
		const CRect& InSourceRect, REFGUID InImageFormatToMake);

public:
	bool ConvertImagExtension(LPCTSTR InSourceImageFileName, LPCTSTR InDestImageFileName, const CRect& InSourceRect, int intFormatTarget);
};

