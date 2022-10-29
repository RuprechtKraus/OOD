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

	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	std::shared_ptr<const IImage> GetImage() const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
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

	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph();
};
