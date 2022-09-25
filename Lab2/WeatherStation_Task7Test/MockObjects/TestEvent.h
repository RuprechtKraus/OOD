#pragma once

enum TestEvent : unsigned short
{
	TEST_EVENT_ONE = 0b01,
	TEST_EVENT_TWO = 0b10
};

constexpr TestEvent operator~(TestEvent options)
{
	return static_cast<TestEvent>(~static_cast<int>(options));
}

constexpr TestEvent operator|(TestEvent left, TestEvent right)
{
	return static_cast<TestEvent>(static_cast<int>(left) | static_cast<int>(right));
}

constexpr TestEvent operator|=(TestEvent& left, TestEvent right)
{
	left = left | right;
	return left;
}

constexpr TestEvent operator&(TestEvent left, TestEvent right)
{
	return static_cast<TestEvent>(static_cast<int>(left) & static_cast<int>(right));
}

constexpr TestEvent operator&=(TestEvent& left, TestEvent right)
{
	left = left & right;
	return left;
}