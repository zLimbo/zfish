#ifndef __PRINT_H__
#define __PRINT_H__

#include <iostream>
#include <string>
#include <vector>

namespace zl
{

	enum COLOR
	{
		BLACE = 30,
		RED,
		GREEN,
		YELLO,
		BLUE,
		FUCHSIA,
		ULTRAMARINE,
		WHITE
	};

	template <typename T>
	inline void print(const T x)
	{
		std::cout << x << std::endl;
	}

	template <typename T>
	inline void print(const std::vector<T> v)
	{
		for (const T &x : v)
			std::cout << x << " ";
		std::cout << std::endl;
	}

	template <typename T, typename... Args>
	inline void print(const T x, Args... args)
	{
		std::cout << x << " ";
		print(args...);
	}

	template <typename... Args>
	inline void print(COLOR color, Args... args)
	{
		std::cout << "\033[1;" << color << "m";
		print(args...);
		std::cout << "\033[0m";
	}

} // zl
#endif //__PRINT_H__
