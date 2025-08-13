#include "pch.h"
#include <iostream>
#include "GameManager.h"

GameManager::GameManager(EventDispatcher& eventDispatcher) : m_EventDispatcher(eventDispatcher)
{
	m_EventDispatcher.AddListener(EventType::OnPlayerHpChanged, this);
	m_EventDispatcher.AddListener(EventType::OnPlayerDeath, this);
	m_EventDispatcher.AddListener(EventType::OnScoreChange, this);
	m_EventDispatcher.AddListener(EventType::OnBossScene, this);
}

GameManager::~GameManager()
{
}

void GameManager::Reset()
{
	m_EventDispatcher.RemoveListener(EventType::OnPlayerHpChanged, this);
	m_EventDispatcher.RemoveListener(EventType::OnPlayerDeath, this);
	m_EventDispatcher.RemoveListener(EventType::OnScoreChange, this);
	m_EventDispatcher.RemoveListener(EventType::OnBossScene, this);
}

void GameManager::OnEvent(EventType type, const void* data)
{
	switch (type)
	{
	case EventType::OnPlayerHpChanged:
		m_forhitHp = (int)data;
		if (m_forhitHp < m_prevHp)
		{
			m_scrollSpeed = 0;
			m_hitCount++;
		}
		m_prevHp = m_forhitHp;
		break;
	case EventType::OnPlayerDeath:

		break;
	case EventType::OnScoreChange:
		
		break;
	}
}