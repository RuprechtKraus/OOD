#pragma once
#include <iostream>
#include <memory>

class IOutputStream
{
public:
	// ���������� � ����� ������ ����
	// ����������� ���������� std::ios_base::failure � ������ ������
	virtual void WriteByte(uint8_t data) = 0;

	// ���������� � ����� ���� ������ �������� size ����,
	// ��������������� �� ������ srcData,
	// � ������ ������ ����������� ���������� std::ios_base::failure
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

	virtual ~IOutputStream() = default;
};

using OutputStreamPtr = std::unique_ptr<IOutputStream>;