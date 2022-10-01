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
{
	auto greenTea = std::make_unique<GreenTea>() << MakeCondiment<Lemon>(6) << MakeCondiment<CoconutFlakes>(10);
	std::cout << greenTea->GetDescription() << " costs " << greenTea->GetCost() << std::endl;
}