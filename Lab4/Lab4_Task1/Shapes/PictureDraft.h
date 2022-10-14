#pragma once
#include "Shape.h"
#include "boost/iterator/indirect_iterator.hpp"
#include <memory>
#include <vector>

class PictureDraft
{

public:
	using Storage = std::vector<std::unique_ptr<Shape>>;
	using ConstIterator = boost::indirect_iterator<Storage::const_iterator, const Shape&>;

	PictureDraft() = default;

	PictureDraft(PictureDraft&&) = default;
	PictureDraft& operator=(PictureDraft&&) = default;

	PictureDraft(const PictureDraft&) = delete;
	PictureDraft& operator=(const PictureDraft&) = delete;

	void AddShape(std::unique_ptr<Shape>&& shape);
	bool IsEmpty() const;

	ConstIterator begin() const;
	ConstIterator end() const;

private:
	Storage m_shapes;
};

inline PictureDraft::ConstIterator begin(const PictureDraft& draft)
{
	return draft.begin();
}

inline PictureDraft::ConstIterator end(const PictureDraft& draft)
{
	return draft.end();
}