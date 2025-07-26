#ifndef PCH_H
#define PCH_H

#include "framework.h"
#define _CRTDBG_MAP_ALLOC
#include <windows.h>

// COM 및 DirectX 인터페이스
#include <wrl/client.h>              // ComPtr
#include <d3d11.h>                   // Direct3D 11
#include <dxgi1_6.h>                 // DXGI 1.6 (Windows 10 이상 최신 스왑체인)
#include <d2d1_3.h>                  // Direct2D 1.3 (ID2D1Factory4)
#include <d2d1_3helper.h>            // D2D1::Helper 클래스들
#include <dwrite_3.h>                // DirectWrite (최신 텍스트 엔진)
#include <wincodec.h>                // WIC (이미지 로딩)

#include <stdio.h>
#include <stdexcept>

namespace DX
{
	class com_exception : public std::exception
	{
	public:
		com_exception(HRESULT hr) : result(hr) {}

		const char* what() const noexcept override
		{
			static char s_str[64] = {};
			sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
			return s_str;
		}

	private:
		HRESULT result;
	};

	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			throw com_exception(hr);
		}
	}
}

#endif