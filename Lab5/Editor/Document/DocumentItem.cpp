#include "DocumentItem.h"

ConstDocumentItem::ConstDocumentItem(const std::variant<
	std::shared_ptr<IImage>,
	std::shared_ptr<IParagraph>>& item)
	: m_item(item)
{
}

std::shared_ptr<const IImage> ConstDocumentItem::GetImage() const
{
	if (auto* ptr = std::get_if<std::shared_ptr<IImage>>(&m_item))
	{
		return *ptr;
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<const IParagraph> ConstDocumentItem::GetParagraph() const
{
	if (auto* ptr = std::get_if<std::shared_ptr<IParagraph>>(&m_item))
	{
		return *ptr;
	}
	else
	{
		return nullptr;
	}
}

DocumentItem::DocumentItem(const std::variant<
	std::shared_ptr<IImage>,
	std::shared_ptr<IParagraph>>& item)
	: ConstDocumentItem(item)
{
}

std::shared_ptr<IImage> DocumentItem::GetImage()
{
	return std::const_pointer_cast<IImage>(ConstDocumentItem::GetImage());
}

std::shared_ptr<IParagraph> DocumentItem::GetParagraph()
{
	return std::const_pointer_cast<IParagraph>(ConstDocumentItem::GetParagraph());
}