#include "Cryptographer.h"
#include <algorithm>
#include <random>
#include <numeric>

Cryptographer::Cryptographer(int key)
	: m_key(key)
{
	InitializeLookupTable();
}

uint8_t Cryptographer::Encrypt(uint8_t byte) const
{
	return m_lookupTable[byte];
}

uint8_t Cryptographer::Decrypt(uint8_t byte) const
{
	for (int i = 0; i < 256; i++)
	{
		if (m_lookupTable[i] == byte)
		{
			return i;
		}
	}
}

void Cryptographer::InitializeLookupTable()
{
	std::mt19937 g(m_key);
	std::iota(m_lookupTable.begin(), m_lookupTable.end(), 0);
	std::ranges::shuffle(m_lookupTable, g);
}