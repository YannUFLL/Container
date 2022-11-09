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

/*
int main()
{
	ft::vector<int> a(6,42);	
	ft::vector<int> b(6,88);	
	b.reserve(100);
	ft::vector<int>::iterator start = b.begin()+ 2;
	ft::vector<int>::iterator end =	b.begin()+ 2;
	(void)start;
	
	b.erase(start, end);
	for (int i = 0; i < 12;  ++i)
	{
		std::cout << b[i] << std::endl;
	}
}*/



int main()
{
	ft_mono_test<int>();
	ft_speed_test<int>();
}