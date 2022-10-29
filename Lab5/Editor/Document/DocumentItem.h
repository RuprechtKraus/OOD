#pragma once
#include "Elements/IImage.h"
#include "Elements/IParagraph.h"
#include <memory>
#include <variant>

class ConstDocumentItem
{
public:
	ConstDocumentItem(const std::variant<
		std::shared_ptr<IImage>,
		std::shared_ptr<IParagraph>>& item);

	// ���������� ��������� �� ����������� �����������, ���� nullptr,
	// ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage() const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph() const;
	virtual ~ConstDocumentItem() = default;

private:
	std::variant<std::shared_ptr<IImage>, std::shared_ptr<IParagraph>> m_item;
};

class DocumentItem : public ConstDocumentItem
{
public:
	DocumentItem(const std::variant<
		std::shared_ptr<IImage>,
		std::shared_ptr<IParagraph>>& item);

	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<IImage> GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<IParagraph> GetParagraph();
};
