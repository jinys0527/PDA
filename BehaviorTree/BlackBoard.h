#pragma once
#include <string>
#include <unordered_map>
#include <optional>
#include <memory>
#include <variant>
#include "SoundManager.h"


class Telegraph;
class GameObject;

// �ൿƮ�� ������ �����ϴ� ������ �����
// AI�� �Ǵ��ϰų� �ൿ�� �� �����ϴ� ��� ����, ����, �������� ����
class BlackBoard
{
public:
	using BBValue = std::variant
        <
        int, 
        float,
        bool, 
        std::string, 
        std::vector<std::string>,
        std::vector<std::shared_ptr<Telegraph>>,
        std::vector<std::shared_ptr<GameObject>>,
        std::unordered_map<std::string, std::shared_ptr<GameObject>>,
        std::unordered_map<std::string, std::vector<int>>,
        std::vector<int>
        >;

public:

    BlackBoard(SoundManager& soundmanager) : m_SoundManager(soundmanager) {}

	void SetValue(const std::string& key, const BBValue& value);

    // ������ Ȯ��
    template<typename T>
    std::optional<T> GetValue(const std::string& key) const {
        auto it = m_Data.find(key);
        if (it == m_Data.end()) return std::nullopt;

        if (auto val = std::get_if<T>(&(it->second))) {
            return *val;
        }
        return std::nullopt;
    }


    // ������ ���� ����
    bool HasKey(const std::string& key) const;
    SoundManager& GetSoundManager() { return m_SoundManager; }

protected:
	std::unordered_map<std::string, BBValue> m_Data;
    SoundManager& m_SoundManager;

};

