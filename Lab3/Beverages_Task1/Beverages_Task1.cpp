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
	auto beverage = std::make_unique<Coffee>() 
		<< MakeCondiment<Liquor>(LiquorType::Nut) 
		<< MakeCondiment<Liquor>(LiquorType::Chocolate)
		<< MakeCondiment<IceCubes>(2, IceCubeType::Dry);
	std::cout << beverage->GetDescription() << " costs " << beverage->GetCost() << std::endl;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;
}