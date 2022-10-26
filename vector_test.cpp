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