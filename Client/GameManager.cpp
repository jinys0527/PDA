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
		m_playerHp = (int)data;
		if (m_playerHp < m_prevHp)
		{
			m_scrollSpeed = 0;
			m_hitCount++;
		}
		m_prevHp = m_playerHp;
		break;
	case EventType::OnPlayerDeath:

		break;
	case EventType::OnScoreChange:
		
		break;
	}
}
