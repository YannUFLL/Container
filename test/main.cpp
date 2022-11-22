#include <chrono> 
#include <unistd.h>
#include <stdlib.h>
#include "../test/MyChrono.hpp"
#include "../test/vector_test.hpp"
#include "../container/vector.hpp"
#include "../container/map.hpp"
#include <map>


template<typename T> 
void	ft_vector_mono_test();

template <typename T>
void	ft_vector_speed_test();

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
		ft::cout << b[i] << ft::endl;
	}
}*/

void	ft_print_element(int i, ft::map<int, int> &test)
{
	for (int j = 0;j < i; j++)
		std::cout << test[j] << std::endl;

}
int main()
{
	ft::map<int, int> test;
	test[42] = 42;
	test[43] = 42;
	test[10] = 1;
	test[52] = 35;
	test[34] = 35;
	ft::pair<int, int> pair;
	pair.first = 1042;
	pair.second = 2042;
	test.insert(pair);
	ft::map<int, int>::iterator it;
	it = test.end();
	--it;
	std::cout << it->first << std::endl;
	std::cout << it->first << std::endl;
	}