#pragma once
#include <filesystem>
#include <string>

using Path = std::filesystem::path;

class IResourceRepository
{
public:
	//������ ����� ����� � ��������� �� � ����� � ��������� � ����� ������.
	//���������� ����� ��� �����
	virtual Path AddResource(const Path& target) = 0;

	//������� ������ �� ����� � ���������
	virtual void DeleteResource(const std::string& target) = 0;

	//���������� ���� � ����� � ���������
	virtual Path GetResourcesPath() const = 0;
};