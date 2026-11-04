#include "pch.h"
#include "ConvertImageFile.h"
#include <vector>

bool ConvertImageFile::ConvertImagExtension(LPCTSTR InSourceImageFileName, LPCTSTR InDestImageFileName, 
    const CRect& InSourceRect, int intFormatTarget)
{
    //(0: jpg, 1 : jpeg, 2 : png, 3 : bmp, 4 : gif);
    bool res = true;
    if (intFormatTarget == 0)
    {
        if (!MakeConvertedImage(InSourceImageFileName, InDestImageFileName, InSourceRect, Gdiplus::ImageFormatJPEG))
        {
            res = false;
        }
    }
    else if (intFormatTarget == 1)
    {
        if (!MakeConvertedImage(InSourceImageFileName, InDestImageFileName, InSourceRect, Gdiplus::ImageFormatJPEG))
        {
            res = false;
        }
    }
    else if (intFormatTarget == 2)
    {
        if (!MakeConvertedImage(InSourceImageFileName, InDestImageFileName, InSourceRect, Gdiplus::ImageFormatPNG))
        {
            res = false;
        }
    }
    else if(intFormatTarget == 3)
    {
        if (!MakeConvertedImage(InSourceImageFileName, InDestImageFileName, InSourceRect, Gdiplus::ImageFormatBMP))
        {
            res = false;
        }
    }
    else
    {
        if (!MakeConvertedImage(InSourceImageFileName, InDestImageFileName, InSourceRect, Gdiplus::ImageFormatGIF))
        {
            res = false;
        }
    }
    return res;
}

//https://blog.naver.com/kzh8055/140100162253 참조
BOOL ConvertImageFile::MakeConvertedImage(LPCTSTR InSourceImageFileName, LPCTSTR InDestImageFileName,
    const CRect& InSourceRect, REFGUID InImageFormatToMake)
{
    CImage    TempSourceImage;
    CImage    TempDestImage;

    TempSourceImage.Load(InSourceImageFileName);
    CDC* pSourceDC = CDC::FromHandle(TempSourceImage.GetDC());

    int BitPerPixel = pSourceDC->GetDeviceCaps(BITSPIXEL);
    TempDestImage.Create(InSourceRect.Width(), InSourceRect.Height(), BitPerPixel);
    CDC* pDestDC = CDC::FromHandle(TempDestImage.GetDC());

    if (!pSourceDC || !pDestDC)
    {
        return FALSE;
    }

    pDestDC->BitBlt(0, 0, InSourceRect.Width(), InSourceRect.Height(),
        pSourceDC, InSourceRect.left, InSourceRect.top, SRCCOPY);

    TempDestImage.ReleaseDC();
    TempSourceImage.ReleaseDC();

    // 저장할 파일 포맷
    TempDestImage.Save(InDestImageFileName, InImageFormatToMake);

    return TRUE;
}

