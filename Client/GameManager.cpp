#include "pch.h"
#include <iostream>
#include "GameManager.h"

GameManager::GameManager(EventDispatcher& eventDispatcher) : m_EventDispatcher(eventDispatcher)
{
	m_EventDispatcher.AddListener(EventType::OnPlayerHit, this);
	m_EventDispatcher.AddListener(EventType::OnPlayerDeath, this);
	m_EventDispatcher.AddListener(EventType::OnScoreChange, this);
	m_EventDispatcher.AddListener(EventType::OnBossScene, this);
}

GameManager::~GameManager()
{

}

void GameManager::OnEvent(EventType type, const void* data)
{
	switch (type)
	{
	case EventType::OnPlayerHit:
		std::cout << "¸ÂÀ½" << std::endl;
		if ((int)data < m_playerHp)
			m_hitCount++;
		m_playerHp = (int)data;
		break;
	case EventType::OnPlayerDeath:

		break;
	case EventType::OnScoreChange:
		
		break;
	}
}

void GameManager::Reset()
{
	m_EventDispatcher.RemoveListener(EventType::OnPlayerHit, this);
	m_EventDispatcher.RemoveListener(EventType::OnPlayerDeath, this);
	m_EventDispatcher.RemoveListener(EventType::OnScoreChange, this);
	m_EventDispatcher.RemoveListener(EventType::OnBossScene, this);
}
