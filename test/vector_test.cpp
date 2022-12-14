/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 23:34:38 by ydumaine          #+#    #+#             */
/*   Updated: 2022/12/04 23:42:22 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_test.hpp"
#include "test.hpp"


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
	#if SLOWMODE
	std::cout << std::endl << std::endl;
	std::cout << "Please press any key to continue... " << std::endl;
	system("read");
		for (int i = 0; i < 100; i++)
		std::cout << std::endl;
	#endif
}