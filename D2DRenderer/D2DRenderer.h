#pragma once

#include <wrl/client.h>
#include <d2d1helper.h>
#include <vector>
#include "RenderData.h"
#include <iostream>
using namespace Microsoft::WRL;


class TransformComponent;
class CameraObject;

class D2DRenderer
{
public:
	D2DRenderer() = default;
	~D2DRenderer() { std::cout << "D2DRenderer destroyed\n"; UnInitialize(); }

	void Initialize(HWND hwnd);

	void UnInitialize();

	void Resize(int width, int height);

	void DrawLine(float x1, float y1, float x2, float y2, const D2D1::ColorF& color);

	void DrawCircle(float x, float y, float radius, const D2D1::ColorF& color);

	void DrawRectangle(float left, float top, float right, float bottom, const D2D1::ColorF& color);

	void DrawBitmap(ID2D1Bitmap1* bitmap, D2D1_RECT_F dest);

	void DrawBitmap(ID2D1Bitmap1* bitmap, D2D1_RECT_F destRect, D2D1_RECT_F srcRect, float opacity = 1.0f);

	void DrawBitmap(ID2D1Bitmap1* bitmap, D2D1_RECT_F dest, TransformComponent* trans, D2D1::Matrix3x2F viewTM);

	template<typename T>
	void LogComObjectRefCount(T* comObject, const char* name)
	{
		if (!comObject)
		{
			std::cout << name << " is nullptr\n";
			return;
		}

		ULONG refCount = 0;
		__try
		{
			refCount = comObject->AddRef();
			refCount = comObject->Release();
			std::cout << name << " RefCount = " << refCount << "\n";
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			std::cout << "[Exception] Access violation when calling AddRef/Release on " << name << "\n";
		}
	}

	void LogInternalComStates();

	void DrawMessage(const wchar_t* text, float left, float top, float width, float height, const D2D1::ColorF& color);


	void Draw(std::vector<RenderInfo>& renderInfo);
	void DrawInternal(std::vector<RenderInfo>& renderInfo, D2D1::Matrix3x2F cameraMatrix);

	Math::Vector2F CalcAnchorOffset(const Math::Vector2F& parentSize,
		const Anchor& anchor,
		const Math::Vector2F& anchoredPosition,
		const Math::Vector2F& sizeDelta,
		const Math::Vector2F& pivot);

	void SetTransform(const D2D1_MATRIX_3X2_F tm);

	// Set the target bitmap for D2D rendering
	void SetTarget()
	{
		m_d2dContext->SetTarget(m_targetBitmap.Get());
	}

	void RenderBegin();

	void RenderEnd(bool bPresent = true);

	void Present();

	void CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1*& outBitmap);

	ID3D11Device* GetD3DDevice() const { return m_d3dDevice.Get(); }

	ID3D11DeviceContext* GetD3DContext() const { return m_d3dContext.Get(); }

	ID2D1DeviceContext7* GetD2DContext() const { return m_d2dContext.Get(); }

	ID3D11RenderTargetView* GetD3DRenderTargetView() const { return m_d3dRenderTargetView.Get(); }

	void SetCamera(CameraObject* camera) { m_Camera = camera; }

private:
	void CreateDeviceAndSwapChain(HWND hwnd);

	void CreateRenderTargets();

	void CreateWriteResource();

	void ReleaseRenderTargets();

private:
	HWND m_hwnd = nullptr;

	CameraObject* m_Camera;

	ComPtr<ID3D11Device>			m_d3dDevice;
	ComPtr<IDXGISwapChain1>			m_swapChain;

	ComPtr<ID3D11DeviceContext>		m_d3dContext;
	ComPtr<ID3D11RenderTargetView>	m_d3dRenderTargetView;

	ComPtr<ID2D1Bitmap1>			m_targetBitmap;
	ComPtr<ID2D1SolidColorBrush>	m_brush;
	ComPtr<ID2D1SolidColorBrush>	m_textBrush;
	ComPtr<IDWriteTextFormat>		m_textFormat;

	ComPtr<ID2D1Device7>			m_d2dDevice;
	ComPtr<ID2D1DeviceContext7>		m_d2dContext;

	ComPtr<IWICImagingFactory>		m_wicFactory;
};