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
	std::vector<int> a(6,42);	
	std::vector<int> b(6,88);	
	b.reserve(100);
	std::vector<int>::iterator z = b.insert(b.begin() + 2, a.begin(),a.end());
	for (int i = 0; i < 12;  ++i)
	{
		std::cout << b[i] << std::endl;
	}
}


/*
int main()
{
	ft_mono_test<int>();
	ft_speed_test<int>();
}*/