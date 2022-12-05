/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_test.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 23:34:42 by ydumaine          #+#    #+#             */
/*   Updated: 2022/12/05 11:11:29 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TEST
#define VECTOR_TEST

#include "test.hpp"
#include <vector>
#include "../container/vector.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <typeinfo>
#include <iomanip>
#include "MyChrono.hpp"


#define COMPARE_VECTORS(vector, my_vector) ft_compare_vector(vector, my_vector, #vector)
#define INFO(vector, msg) ft_info_vector(vector, msg)
#define PERF_VALUE 1000000 // ONE MILLION

/*
DIDN'T WORK I DON'T KNOW WHY 
#define STRING(a) #a
THE ONE BELLOW WORK FINE
*/

#define STR(a) #a
#define STRING(a) STR(a) 

typedef struct s_test
{
	int a;
	int b[1000];
	std::string c;
} test_struct;


void	ok(void);
void	ok(int i);
void	fa(void);
void	fa(int i);
void	title(std::string name);
void	ft_wait();

template<typename T>
void	ft_check_value(T value, T control, bool endl = 0)
{
	usleep(50000);
	if (endl == 1)
	{	
		if (value == control)
			std::cout << "\u2705" << std	::endl;
		else 
			std::cout << "\u274c" << std::endl;
	}
	else
	{
		if (value == control)
			std::cout << "\u2705";
		else 
			std::cout << "\u274c";
	}
}

template<typename T>
void	print_data(T data, std::string title)
{
	std::cout << title ;
	std::cout << data << std::endl ;
}

template<typename T>
void	ft_compare_vector(VEC<T> vector, MVEC<T> my_vector, std::string name)
{
	title(name);
	typename VEC<T>::const_iterator it_vec;
	typename MVEC<T>::const_iterator it_myvec;
	if (vector.size() != my_vector.size())
		fa();
	else 
		ok();
	if (vector.capacity() != my_vector.capacity())
		fa();
	else
		ok();
	it_myvec = my_vector.begin(); 
	bool result = true;  
	for (it_vec = vector.begin(); it_vec != vector.end(); it_vec++)
	{
		if (*it_vec != *it_myvec)
		{
			result = false; 
			break;
		}
		it_myvec++;
	}
	if (result == false)
		fa(1);
	else
		ok(1);
}

template<typename T>
void	ft_info_vector(T const &vector, std::string name)
{
	std::cout <<"\e[0;34m" << name << "\e[0m"<< std::endl;
	std::cout << std::setw(20) << std::left << "Size";
	std::cout << vector.size() << std::endl;
	std::cout << std::setw(20) << std::left << "Capacity";
	std::cout << vector.capacity() << std::endl;
	std::cout << std::setw(20) << std::left << "Content : ";
	if (vector.begin() == vector.end())
		std::cout << "empty " << std::endl;
	for (typename T::const_iterator it_vec = vector.begin(); it_vec != vector.end(); it_vec++)
	{
		std::cout << *it_vec << ";"; 
	}
	std::cout << std::endl << std::endl ;
}



template<typename T> 
void	ft_fill_vector(VEC<T> &v)
{
	for (int i = 0; i <= 100; i++)
		v.push_back(i); 
}


template<typename T> 
void	ft_vector_test()
{
//--------------------------------------------------------------------------------------//
//                                     Constructor                                      //
//--------------------------------------------------------------------------------------//

	std::cout << std::endl << "\e[0;31m		Starting vector test \e[0m" << std::endl << std::endl;
	usleep(1000000);
	std::cout << std::endl << "\e[0;33mStarting test... PHASE 1 'constructor' :\e[0m" << std::endl;
	MVEC<T> my_default_constructor; 
	INFO(my_default_constructor, "Default constructor : ");

	MVEC<T> my_fill_constructor(10, 42);
	INFO(my_fill_constructor, "Fill constructor : ");
	int a[] = {1,4,5,9,4,5,1,6,1,6,1,4,7,9,3,154845,1548894};
	MVEC<T> my_range_constructor(&a[0], &a[16]);
	INFO(my_range_constructor, "Range constructor : ");

	MVEC<T> my_copy_constructor(my_fill_constructor);
	INFO(my_copy_constructor, "Copy constructor : ");

	MVEC<T> const const_my_default_constructor; 
	INFO(const_my_default_constructor, "Const default constructor : ");
	MVEC<T> const const_my_fill_constructor(10, 42);
	INFO(const_my_fill_constructor, "Const fill constructor : ");

	MVEC<T> const const_my_range_constructor(&a[0], &a[16]);
	INFO(const_my_range_constructor, "Const range constructor");

	MVEC<T> const const_my_copy_constructor(my_default_constructor);
	INFO(const_my_copy_constructor, "Const copy constructor");

	MVEC<T> to_assign;
	MVEC<T> to_copy;
	ft_fill_vector(to_copy);
	to_assign = to_copy;
	ft_compare_vector(to_copy, to_assign, "Assignation operator");
	ft_wait();
	
//--------------------------------------------------------------------------------------//
//                                       Iterator                                       //
//--------------------------------------------------------------------------------------//

	
	std::cout << std::endl << std::endl << std::endl << "\e[0;33mStarting test... PHASE 2, 'iterator' :\e[0m" << std::endl ;
	typename MVEC<T>::iterator my_it;
	MVEC<T> my_iterator_vector;	
	ft_fill_vector(my_iterator_vector);
	my_it = my_iterator_vector.begin();
	std::cout << "it = v.begin() *it = 42 and it = v.end() *(--it) = 42 " << std::endl;
	std::cout << "Result : " << std::endl;
	*my_it = 42;
	my_it = my_iterator_vector.end();
	*(--my_it) = 42;
	typename MVEC<T>::reverse_iterator my_rit;
	INFO(my_iterator_vector, "Iterator : ");
	my_rit = my_iterator_vector.rbegin();
	*(my_rit) = 84;
	my_rit = my_iterator_vector.rend();
	*(--my_rit) = 18;
	std::cout << "it = v.rbegin() *it = 84 and it = v.rend() *(--it) = 18 " << std::endl;
	std::cout << "Result : " << std::endl;
	INFO(my_iterator_vector, "Reverse iterator : ");
	my_it = my_iterator_vector.begin();
	std::cout << "Value *(1 + my_it) : " <<  *(1 + my_it) << std::endl; 
	std::cout <<  "Value iterator[10] must be equal to 10 : " << my_it[10] << std::endl;
	std::cout <<  "Value iterator[10] must be equal to 10 : " << my_it[10] << std::endl;
	my_it = my_iterator_vector.end();
	

	typename MVEC<T>::const_iterator	my_cit = my_iterator_vector.end() ;
	std::cout << "Operator != with iterator and const iterator, must be 0 : " << (my_it != my_cit) << std::endl;
	my_cit += 5;
	INFO(my_iterator_vector, "iterator constant");

	typename MVEC<T>::iterator my_it2(my_iterator_vector.begin() + 1);
	std::cout << "Dereferenced Value of an iterator begin + 1 : " << *my_it2 << std::endl;
	typename MVEC<T>::reverse_iterator my_rit2(my_it2);
	std::cout << "Dereferenced value of a reverse iterator set with the previous iterator : " << *my_rit2 << std::endl;
	std::cout << "Value of my_rit2[2] : " << my_rit2[-2] << std::endl;
	my_rit2 = my_iterator_vector.rbegin();
	std::cout << "Value of my_rit2 : " << *(my_rit2) << std::endl;
	std::cout << "my_rit2 = rbegin(), value of my_rit2[2] " << my_rit2[10] << std::endl;
	typename MVEC<T>::const_reverse_iterator my_rit3(my_iterator_vector.rbegin() + 3);
	std::cout << "Value of my_rit2 - my_rit3 : " << my_rit3 - my_rit2 << std::endl;
	ft_wait();
	

//--------------------------------------------------------------------------------------//
//                                       Capacity                                       //
//--------------------------------------------------------------------------------------//

	
	std::cout << std::endl << std::endl << std::endl << "\e[0;33mStarting test... PHASE 3, 'Capacity' :\e[0m" << std::endl ;

	MVEC<T> my_resize;
	my_resize.resize(50000);
	print_data(my_resize.size(), "resize of an empty vector to 50000, size value : ");
	print_data(my_resize.capacity(), "capacity : ");
	print_data(my_resize.empty(), "value bool empty (should not be empty) : ");
	my_resize.clear();
	my_resize.shrink_to_fit();
	my_resize.push_back(42);	
	my_resize.push_back(43);	
	my_resize.push_back(44);	
	my_resize.reserve(100);
	INFO(my_resize, "vector 42;43;44 after reserve of 100 elements : "); 
	print_data(my_resize.capacity(), "new capacity after reserve for a capacity of 100000 : ");

	my_resize.shrink_to_fit();
	print_data(my_resize.capacity(), "new capacity after reserve for a shrink to fit: ");

	ft_wait();
	
//--------------------------------------------------------------------------------------//
//                                    Element access                                    //
//--------------------------------------------------------------------------------------//
	
	std::cout << std::endl << std::endl << std::endl << "\e[0;33mStarting test... PHASE 4, 'Element access' :\e[0m" << std::endl ;
	VEC<T> element_access; 
	ft_fill_vector(element_access);
	INFO(element_access, "Elements du vecteur avant test 'Element access' : "); 

	print_data(element_access[2], "Element of index 2 : "); 
	print_data(element_access.at(2), "Element of at 2 : "); 
	print_data(element_access.front(), "Element returned by front() : "); 
	print_data(element_access.back(), "Element returned by back() : "); 
	print_data(element_access.data(), "Element returned by data : "); 
	ft_wait();
	
//--------------------------------------------------------------------------------------//
//                                       Modifier                                       //
//--------------------------------------------------------------------------------------//


	std::cout << std::endl << std::endl << std::endl << "\e[0;33mStarting test... PHASE 5, 'Modifier' :\e[0m" << std::endl ;
	VEC<T> vec_m;
	vec_m.push_back(1001);
	vec_m.push_back(1002);
	vec_m.push_back(1003);

	INFO(my_range_constructor, "Element of the vector before test 'modifier' : "); 
	int b[] = {42,43,44};
	my_range_constructor.assign(&b[0], &b[2]);
	INFO(my_range_constructor, "After assign : "); 
	my_range_constructor.push_back(18); 
	INFO(my_range_constructor, "After push back of 18 : "); 
	my_range_constructor.pop_back(); 
	INFO(my_range_constructor, "After pob back : "); 
	my_range_constructor.insert(my_range_constructor.begin(), 118); 
	INFO(my_range_constructor, "After insert of 118 in position 0 : "); 
	my_range_constructor.erase(my_range_constructor.begin()); 
	INFO(my_range_constructor, "After erase of 118 in position 0 : "); 
	my_range_constructor.insert(my_range_constructor.begin() + 1, 4, 44); 
	INFO(my_range_constructor, "After insert of val 44 four time at the middle: "); 
	my_range_constructor.shrink_to_fit();
	my_range_constructor.insert(my_range_constructor.begin() + 1,10, 88); 
	INFO(my_range_constructor, "After shrint to fit and insert fill val 88 ten times, in position 1 : "); 
	my_range_constructor.insert(my_range_constructor.begin() + 1, vec_m.begin(), vec_m.end()); 
	INFO(my_range_constructor, "insert with iterator of vector 1001,1002,1003  in position 1 : "); 
	my_range_constructor.erase(my_range_constructor.begin() + 1, my_range_constructor.begin() + 4); 
	INFO(my_range_constructor, "After erase of 1001,1002,1003  in position 1 : "); 
	my_range_constructor.insert(my_range_constructor.begin() + 1, vec_m.begin(), vec_m.end()); 
	INFO(my_range_constructor, "insert with iterator of vector 1001,1002,1003  in position 1 with no reallocation because enought capacity : "); 
	VEC<T> swap;
	ft_fill_vector(swap);
	my_range_constructor.swap(swap); 
	INFO(my_range_constructor, "After swap with other vector : "); 
	my_range_constructor.clear();
	INFO(my_range_constructor, "After clear : "); 
	std::cout << "insert 1 element in position 0, return value must be 4200 : " <<  *(my_range_constructor.insert(my_range_constructor.begin(), 4200)) << std::endl; 

	ft_wait();
	
//--------------------------------------------------------------------------------------//
//                                 Comparison operator                                  //
//--------------------------------------------------------------------------------------//
	
	std::cout << std::endl << std::endl << std::endl << "\e[0;33mStarting test... PHASE 6, 'comparison operator' :\e[0m" << std::endl ;
	VEC<T> test;
	VEC<T> test2;
	ft_check_value(test == test2, true);
	test2.push_back(10);
	ft_check_value(test == test2, false);
	ft_check_value(test != test2, true);
	ft_check_value(test <= test2, true);
	test.push_back(11);
	ft_check_value(test <= test2, false);
	test2.push_back(12);
	ft_check_value(test <= test2, false);
	test2.clear();
	test.clear();
	for (int i = 0; i <= 100; i++)
	{
		test.push_back(i);
		test2.push_back(i);
	}
	test.push_back(-42);
	ft_check_value(test <= test2, false);
	std::cout << std::endl;
	std::cout << std::endl;
	ft_wait();
	

//--------------------------------------------------------------------------------------//
//                                      Speed test                                      //
//--------------------------------------------------------------------------------------//

	std::cout << std::endl <<  "\e[0;33mStarting test... PHASE 7, 'Speed test' :\e[0m" << std::endl ;
	VEC<T> vector;
	MyChrono chrono;
	chrono.begin();
	for (int i = 0; i < PERF_VALUE; i++)
		vector.push_back(i);
	chrono.end();
	chrono.print_time(STRING(Time for push_back PERF_VALUE elements in a empty vector : ));

	chrono.begin();
	VEC<T> vector2(PERF_VALUE, 42);
	chrono.end();
	chrono.print_time(STRING(Filling time using fill constructor for PERF_VALUE  : ));

	chrono.begin();
	VEC<T> vector3(vector2.begin(), vector2.end());
	chrono.end();
	chrono.print_time(STRING(Constructing time by iterator for PERF_VALUE elements  : ));

	typename VEC<T>::iterator middle = vector2.begin() + (vector2.size() / 2);
	chrono.begin();
	vector2.insert(middle, vector.begin(), vector.end());
	chrono.end();
	chrono.print_time(STRING(Filling time by insering a vector of PERF_VALUE elements in the middle of a vector of PERF_VALUE elements : ));

	chrono.begin();
	vector2.resize(PERF_VALUE * 10 );
	chrono.end();
	chrono.print_time(STRING(Time for a resize of (PERF_VALUE  * 10)  : ));
	
	middle = vector3.begin() + (vector3.size() / 2);
	chrono.begin();
	vector3.erase(middle);
	chrono.end();
	chrono.print_time("Time for suppress a element in the middle of the vector :");

	chrono.begin();
	vector2.clear();
	chrono.end();
	chrono.print_time(STRING(Time for a clear of (PERF_VALUE * 10) elements : ));
	
}

//--------------------------------------------------------------------------------------//
//               Test for comparison std::vector and ft::vector : Usless                //
//--------------------------------------------------------------------------------------//


template<typename T> 
void	ft_dual_test()
{
	
	VEC<T> default_constructor; 
	MVEC<T> my_default_constructor; 
	COMPARE_VECTORS(default_constructor, my_default_constructor);

	VEC<T> fill_constructor(10, 42);
	MVEC<T> my_fill_constructor(10, 42);
	COMPARE_VECTORS(fill_constructor, my_fill_constructor);

	int a[] = {1,4,5,9,4,5,1,6,1,6,1,4,7,9,3,154845,1548894};
	VEC<T> range_constructor(&a[0],&a[16]);
	MVEC<T> my_range_constructor(&a[0], &a[16]);
	COMPARE_VECTORS(range_constructor, my_range_constructor);

	VEC<T> copy_constructor(default_constructor);
	MVEC<T> my_copy_constructor(default_constructor);
	COMPARE_VECTORS(range_constructor, my_range_constructor);

	VEC<T> const const_default_constructor; 
	MVEC<T> const const_my_default_constructor; 
	COMPARE_VECTORS(const_default_constructor, const_my_default_constructor);
	

	VEC<T> const const_fill_constructor(10, 42);
	MVEC<T> const const_my_fill_constructor(10, 42);
	COMPARE_VECTORS(const_fill_constructor, const_my_fill_constructor);

	VEC<T> const const_range_constructor;
	MVEC<T> const const_my_range_constructor;
	COMPARE_VECTORS(const_range_constructor, const_my_range_constructor);

	VEC<T> const const_copy_constructor(default_constructor);
	MVEC<T> const const_my_copy_constructor(default_constructor);
	COMPARE_VECTORS(const_copy_constructor, const_my_copy_constructor);	

	MVEC<T> to_assign;
	MVEC<T> to_copy;
	ft_fill_vector(to_copy);
	to_assign = to_copy;
	ft_compare_vector(to_copy, to_assign, "Assignation operator");

	typename VEC<T>::iterator it;
	typename MVEC<T>::iterator my_it;
	VEC<T> iterator_vector;
	VEC<T> my_iterator_vector;
	ft_fill_vector(iterator_vector);
	ft_fill_vector(my_iterator_vector);
	it = iterator_vector.begin();
	my_it = my_iterator_vector.begin();
	*it = 42;
	*my_it = 42;
	it = iterator_vector.end();
	my_it = my_iterator_vector.end();
	*(--it) = 42;
	*(--my_it) = 42;
	typename VEC<T>::reverse_iterator rit;
	typename MVEC<T>::reverse_iterator my_rit;
	COMPARE_VECTORS(iterator_vector, my_iterator_vector);
	rit = iterator_vector.rbegin();
	my_rit = my_iterator_vector.rbegin();
	*(rit) = 84;
	*(my_rit) = 84;
	rit = iterator_vector.rend();
	my_rit = my_iterator_vector.rend();
	*(--rit) = 84;
	*(--my_rit) = 84;
	COMPARE_VECTORS(iterator_vector, my_iterator_vector);	

	typename VEC<T>::const_iterator	cit = iterator_vector.cbegin();
	typename MVEC<T>::const_iterator	my_cit = my_iterator_vector.cbegin();
	cit += 5;  
	my_cit += 5;
	if (*cit != *my_cit)
		{ title("const iterator  ") ; fa(1) ;}
	else 
		{ title("const iterator  ") ; ok(1) ;}

	VEC<T> size;
	MVEC<T> my_size;
	if (size.size() != my_size.size())
		{ title("Size") ; fa() ;}
	else 
		{ title("Size") ; ok() ;}
	VEC<T> size2(21474, 10);
	MVEC<T> my_size2(21474, 10);
	if (size2.size() != my_size2.size())
		{ fa(1) ;}
	else 
		{ ok(1) ;}

	MVEC<T> my_resize;
	my_resize.resize(50000);
	INFO(my_resize, "RESIZE OF 10000");

}

#endif
