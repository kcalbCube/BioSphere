#pragma once
#include "map.h"
#include "level_atoms.h"
#include <ranges>
#include <map>

template<size_t XSize, size_t YSize>
void generateMap(Map& map, std::string sourceData[YSize], std::string sourceAreaData[YSize])
{
	map.sizeX = XSize;
	map.sizeY = YSize;
	map.createMapArrays();

	std::map<int, Area> areas;

	for(size_t y = 0; y < YSize; ++y)
		for (size_t x = 0; x < XSize; ++x)
		{
			switch (sourceData[y][x])
			{
			case ' ':
				break;
			case '#':
				gc->createAtom<Wall>(x, y);
				break;
			}
			areas[sourceAreaData[y][x]].push_back({ x, y });
		}

	for (Area& area_ : areas | std::ranges::views::values)
	{
		auto area = map.areas.emplace_back(area_);
		for (Vector2 vec : area)
			map.xy2area[vec] = &*std::find(map.areas.begin(), map.areas.end(), area_);
	}
}
// TODO: remove this testing shit
namespace levels
{
	std::string test[] = {
		"#############",
		"#       ##  #",
		"#           #",
		"#############"
	};

	std::string test_a[] = {
		"1111111112222",
		"1111111112222",
		"1111111112222",
		"1111111112222"
	};

	
}