#pragma once
#include "gamecontroller.h"
#include "client.h"
#include "atom.h"
#include "utils.h"
#include <ranges>

constexpr auto g_renderMaxX = 24;
constexpr auto g_renderMaxY = 12;

std::string render(ClientMob& client)
{
	GC_ASSERT();
	auto torender = gc->map.locateInArea(gc->map.locateArea(client));
	std::erase_if(torender, [](auto* atom) -> bool
		{
			return (atom->pi.x > g_renderMaxX) || (atom->pi.y > g_renderMaxY);
		});
	char buffer[g_renderMaxX][g_renderMaxY];
	memset(buffer, ' ', g_renderMaxX * g_renderMaxY);
	/*
	for (auto&& c : buffer)
		std::ranges::fill_n(c, g_renderMaxX, ' ');
	*/

	size_t startX = UINT32_MAX;
	for (auto* atom : torender)
	{
		startX = std::min(startX, atom->pi.x);
		buffer[atom->pi.x][atom->pi.y] = atom->render();
	}

	std::string result;
	for (size_t y = 0; y < g_renderMaxY; ++y)
	{
		for (size_t x = startX; x < std::size(buffer[y]) + startX; ++x)
			result.push_back(buffer[x][y]);
		result.push_back('\n');
	}
	return result;
}