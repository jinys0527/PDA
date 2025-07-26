#pragma once

#include "d2d1helper.h"
#include <string>
#include <vector>

struct Frame
{
	D2D1_RECT_U m_SrcRect;
	float		m_Duration;

	float Width() const { return (float)m_SrcRect.right - m_SrcRect.left; }
	float Height() const { return (float)m_SrcRect.bottom - m_SrcRect.top; }

	D2D1_RECT_F ToRectF() const
	{
		return D2D1::RectF(
			static_cast<float>(m_SrcRect.left),
			static_cast<float>(m_SrcRect.top),
			static_cast<float>(m_SrcRect.right),
			static_cast<float>(m_SrcRect.bottom)
		);
	}
};


struct Tag
{
	std::string m_Name;
	int m_From;
	int m_To;
	std::string m_Direction;
};

class AnimationClip
{
public:
	AnimationClip() = default;
	~AnimationClip() = default;

	void AddFrame(const Frame& frame)
	{
		m_Frames.emplace_back(frame);
		m_TotalDuration += frame.m_Duration;
	}

	void SetTextureKey(std::wstring key)
	{
		m_TextureKey = key;
	}
	Frame& GetFrame(int index) { return m_Frames[index]; }

	const std::vector<Frame>& GetFrames() const { return m_Frames; }
	float GetTotalDuration() const { return m_TotalDuration; }
	const std::wstring GetTextureKey() const { return m_TextureKey; }

private:
	std::vector<Frame> m_Frames;
	float m_TotalDuration = 0.f;
	std::wstring m_TextureKey;
};

