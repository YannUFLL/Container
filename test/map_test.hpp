#ifndef MAP_TEST
#define MAP_TEST

#include <chrono> 
#include <unistd.h>
#include <stdlib.h>
#include "../test/MyChrono.hpp"
#include "../test/vector_test.hpp"
#include "../container/vector.hpp"
#include "../container/map.hpp"
#include <map>
#include "../test/vector_test.hpp"

#define MAP ft::map<T1, T2>
#define PERF_VALUE 1000000

template <typename T1, typename T2>
void	ft_map_mono_test()	
{
//--------------------------------------------------------------------------------------//
//                                       Capacity                                       //
//--------------------------------------------------------------------------------------//
	std::cout << "size function : " << std::endl;
	MAP size;
	ft_check_value(size.size(),static_cast<unsigned long int>(0));
	for (int i = 0; i< 1452; i++)
	{
		size[i] = 42;
	}
	ft_check_value(size.size(),static_cast<unsigned long int>(1452));
}

#endif