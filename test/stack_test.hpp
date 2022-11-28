/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:39:11 by ydumaine          #+#    #+#             */
/*   Updated: 2022/11/28 13:23:23 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_TEST
#define STACK_TEST

#include <chrono> 
#include <unistd.h>
#include <stdlib.h>
#include "../test/MyChrono.hpp"
#include "../test/vector_test.hpp"
#include "../container/vector.hpp"
#include "../container/map.hpp"
#include <map>
#include "../test/vector_test.hpp"

#define STACK ft::stack<T>

template<typename T>
void	ft_stack_test()
{
	std::cout << std::endl << "\e[0;31m		Starting stack test \e[0m" << std::endl << std::endl;
	usleep(1000000);
	STACK s;
	s.push(15);
	ft_check_value(s.top(), 15);
	s.push(30);
	ft_check_value(s.top(), 30);
	s.push(1);
	ft_check_value(s.top(), 1);
	ft_check_value(s.size(), static_cast<unsigned long int>(3));
	s.pop();
	s.pop();
	s.pop();
	ft_check_value(s.size(),static_cast<unsigned long int>(0));
	STACK s2;
	s.push(15);
	s2.push(15);
	s.push(30);
	s2.push(30);
	s.push(42);
	s2.push(42);
	ft_check_value((s2 == s), true);
	
}

#endif


