#pragma once
#include <functional>
#include <exception>

// please cache it
struct Vector2;
using Area = std::vector<Vector2>;

struct PositionInfo
{
	size_t x = 0, y = 0;
	Area* area = 0;
};
struct Vector2 
{
	size_t x = 0, y = 0;

	operator PositionInfo(void) const
	{
		return { .x = x, .y = y };
	}

	bool operator==(const Vector2& other) const
	{
		return other.x == x && other.y == y;
	};
};

struct Vector2i
{
	long x = 0, y = 0;

	operator PositionInfo(void) const
	{
		return { .x = (size_t)x, .y = (size_t)y };
	}
};

template <>
struct std::hash<Vector2> 
{
	_NODISCARD size_t operator()(const Vector2& vec) const noexcept 
	{
		return vec.x ^ vec.y;
	}
};

__forceinline Vector2 make_step(const PositionInfo& from, Vector2i dir)
{
	return { .x = from.x + dir.x, .y = from.y + dir.y};
}

struct GameNotInitialized : std::exception {};

#define RUNTIME_CHECKS

#ifdef RUNTIME_CHECKS
#define GC_ASSERT() if(!(gc && gc->initialized)) throw GameNotInitialized()
#else
#define GC_ASSERT() do {} while(0)
#endif
