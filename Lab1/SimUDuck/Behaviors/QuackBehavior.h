#pragma once
#include <functional>
#include <iostream>

using QuackBehavior = std::function<void()>;

inline void NormalQuack()
{
	std::cout << "Quack Quack!!!" << std::endl;
}

inline void SqueakQuack()
{
	std::cout << "Squeak!!!" << std::endl;
}