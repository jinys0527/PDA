#include "BlackBoard.h"

void BlackBoard::SetVaule(const std::string& key, const BBValue& value)
{
	m_Data[key] = value;
}
