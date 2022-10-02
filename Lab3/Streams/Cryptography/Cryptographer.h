#pragma once
#include "ICryptographer.h"
#include <array>

class Cryptographer : public ICryptographer
{
public:
	Cryptographer(int key);

	uint8_t Encrypt(uint8_t byte) const override;
	uint8_t Decrypt(uint8_t byte) const override;

private:
	void InitializeLookupTable();

	std::array<uint8_t, 256> m_lookupTable{};
	int m_key;
};