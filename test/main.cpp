#include <chrono> 
#include <unistd.h>
#include <stdlib.h>
#include "../test/MyChrono.hpp"
#include "../test/vector_test.hpp"
#include "../container/vector.hpp"
#include "../container/map.hpp"


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

void	ft_print_element(int i, ft::map<int, int> &test)
{
	for (int j = 0;j < i; j++)
		std::cout << test[j] << std::endl;

}

int main()
{
	ft::map<int,int> test;
	test[1] = 101;
	test[2] = 102;
	test[3] = 103;
	test[4] = 104;
	test[5] = 105;
	test.erase(5);
	test.erase(4);
	test.erase(3);
	test.erase(2);
	test.erase(1);
	std::cout << std::endl << std::endl;
	test.erase(1);
	std::cout << test[1] << std::endl;
}