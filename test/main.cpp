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
	/*
	ft::map<int, int> test;
	test[42] = 42;
	test[42] = 42;
	test.erase(42);
	test.erase(42);
	*/
	ft::map<int,int> test;
	std::vector<int> number;
	std::srand(2);
	int nbr = 100;
	for (int i = 0; i <= nbr; i++)
		number.push_back(rand() % 100);
	std::vector<int>::iterator it;
	it = number.begin();
	for (int i = 0; i <= nbr; i++)
	{
		std::cout << "index : " << i << "  number : " << number[i] << std::endl; 
	}
	for (int i = 0; i <= nbr; i++)
	{
		test[*it] = 42;
		it++;
	}
	it = number.begin();
	std::cout << std::endl << "lancement des test d'affichage : " << std::endl;
	for (int i = 0; i <= nbr; i++)
	{
		std::cout << "valeur : test[" << *it << "] = " << test[*it] << std::endl;
		std::cout << "supression... : test[" << *it << "]" << std::endl;
		test.erase(*it);
		it++;
	}
	it = number.begin();
	for (int i = 0; i <= nbr; i++)
	{
		std::cout << test[*it] << std::endl;
		it++;
	}
}