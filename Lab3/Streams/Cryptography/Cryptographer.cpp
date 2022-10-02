#include "Cryptographer.h"
#include <algorithm>
#include <random>
#include <ranges>

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
	std::ranges::generate(m_lookupTable, [i = 0]() mutable { return i++; });
	std::ranges::shuffle(m_lookupTable, g);
}