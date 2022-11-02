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
	std::vector<int> coucou(10,42);
	std::vector<int>::iterator it1 = coucou.begin();
	std::vector<int>::iterator it2 = coucou.end();
	if (it1 < it2)
		std::cout << "OUI" << std::endl;
	
}


/*
int main()
{
	ft_mono_test<int>();
	ft_speed_test<int>();
}*/