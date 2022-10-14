#pragma once
#include "Canvas/ICanvas.h"
#include "gmock/gmock.h"

class MockCanvas : public ICanvas
{
public:
	MOCK_METHOD(void, SetColor, (Color color), (override));
	MOCK_METHOD(void, DrawLine, (const Point& from, const Point& to), (override));
	MOCK_METHOD(void, DrawEllipse, (const Point& topLeft, int width, int height));
};