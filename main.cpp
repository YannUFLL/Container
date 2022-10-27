#include <chrono> 
#include <unistd.h>
#include <stdlib.h>
#include "MyChrono.hpp"
#include "vector_test.hpp"
#include "vector.hpp"


template<typename T> 
void	ft_mono_test();

template <typename T>
void	ft_speed_test();

int main()
{
	vector<int> coucou;

	ft_mono_test<int>();
	ft_speed_test<int>();
}