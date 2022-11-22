#include <chrono> 
#include <unistd.h>
#include <stdlib.h>
#include "../test/MyChrono.hpp"
#include "../test/vector_test.hpp"
#include "../test/map_test.hpp"
#include "../container/vector.hpp"
#include "../container/map.hpp"
#include <map>


template<typename T> 
void	ft_vector_mono_test();

template <typename T>
void	ft_vector_speed_test();

int main()
{
	ft_map_mono_test<int, int>();
}