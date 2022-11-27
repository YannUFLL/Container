#include "vector_test.hpp"


void	ok(void)
{	
	std::cout << "\u2705" ;  
}

void	ok(int i)
{	
	(void)(i);
	std::cout << "\u2705" << std::endl ;
}

void	fa(void)
{	
	std::cout << "\u274c" ;
}

void	fa(int i)
{	
	(void)(i);
	std::cout << "\u274c" << std::endl ;
}

void	title(std::string name)
{
	std::cout << std::setw(40) << std::left << name ;
}

void ft_wait()
{
	std::cout << "Please press any key to continue... " << std::endl;
	system("read");
		for (int i = 0; i < 100; i++)
		std::cout << std::endl;
}