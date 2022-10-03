#include "Beverages.h"
#include "Condiments.h"
#include <iostream>

template <typename Condiment, typename... Args>
auto MakeCondiment(const Args&... args)
{
	return [=](auto&& b) {
		return std::make_unique<Condiment>(std::forward<decltype(b)>(b), args...);
	};
}

template <typename Component, typename Decorator>
auto operator<<(Component&& component, const Decorator& decorate)
{
	return decorate(std::forward<Component>(component));
}

int main()
try
{
	auto milkshake = std::make_unique<Milkshake>(MilkshakeSize::Medium)
		<< MakeCondiment<ChocolateCrumbs>(5);
	std::cout << milkshake->GetDescription() << " costs " << milkshake->GetCost() << std::endl;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;
}