/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:42:30 by ydumaine          #+#    #+#             */
/*   Updated: 2022/11/28 13:02:03 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono> 
#include <unistd.h>
#include <stdlib.h>
#include "../test/MyChrono.hpp"
#include "../test/vector_test.hpp"
#include "../test/map_test.hpp"
#include "../container/vector.hpp"
#include "../container/map.hpp"
#include "../container/stack.hpp"
#include "stack_test.hpp"
#include <map>

template<typename T> 
void	ft_vector_test();


int main()
{
	for (int i = 0; i < 100; i++)
		std::cout << std::endl;
	ft_vector_test<int>();
	std::cout << "Please press any key to start map test... " << std::endl;
	system("read");
	for (int i = 0; i < 100; i++)
		std::cout << std::endl;
	ft_map_test<int, int>();
	std::cout << "Please press any key to start stack test... " << std::endl;
	system("read");
	ft_stack_test<int>();
}