#pragma once
#include <cstdint>

class ICryptographer
{
public:
	virtual uint8_t Encrypt(uint8_t byte) const = 0;
	virtual uint8_t Decrypt(uint8_t byte) const = 0;
	virtual ~ICryptographer() = default;
};