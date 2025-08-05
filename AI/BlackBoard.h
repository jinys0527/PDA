#pragma once
#include <string>
#include <unordered_map>
#include <variant>
#include <optional>


// �ൿƮ�� ������ �����ϴ� ������ �����
// AI�� �Ǵ��ϰų� �ൿ�� �� �����ϴ� ��� ����, ����, �������� ����
class BlackBoard
{
public:
	using BBValue = std::variant<int, float, bool, std::string>;

public:

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

private:
	std::unordered_map<std::string, BBValue> m_Data;

};

