#ifndef VECTOR_TEST
#define VECTOR_TEST

#include <vector>
#include "../container/vector.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <unistd.h>
#include <typeinfo>
#include "MyChrono.hpp"

#define VEC ft::vector
#define	MVEC ft::vector
#define COMPARE_VECTORS(vector, my_vector) ft_compare_vector(vector, my_vector, #vector)
#define INFO(vector, msg) ft_info_vector(vector, msg)
#define PERF_VALUE 10000

/*
NE MARCHE PAS je sais pas pourquoi
#define STRING(a) #a
CELUI DU DESSOUS MARCHE BIEN
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
void	ft_info_vector(T &vector, std::string name)
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
	*my_it = 42;
	my_it = my_iterator_vector.end();
	*(--my_it) = 42;
	typename MVEC<T>::reverse_iterator my_rit;
	INFO(my_iterator_vector, "Iterator : ");
	my_rit = my_iterator_vector.rbegin();
	*(my_rit) = 84;
	my_rit = my_iterator_vector.rend();
	*(--my_rit) = 84;
	INFO(my_iterator_vector, "Reverse iterator : ");
	

	typename MVEC<T>::const_iterator	my_cit = my_iterator_vector.cbegin();
	my_cit += 5;
	INFO(my_iterator_vector, "iterator constant");
	ft_wait();
	

//--------------------------------------------------------------------------------------//
//                                       Capacity                                       //
//--------------------------------------------------------------------------------------//

	
	std::cout << std::endl << std::endl << std::endl << "\e[0;33mStarting test... PHASE 3, 'Capacity' :\e[0m" << std::endl ;

	MVEC<T> my_resize;
	my_resize.resize(50000);
	print_data(my_resize.size(), "resize of an empty vector to 50000, size value : ");
	print_data(my_resize.capacity(), "capacity : ");
	print_data(my_resize.empty(), "is empyt : ");
	
	my_resize.reserve(100000);
	print_data(my_resize.capacity(), "new capacity after reserve for a capacity of 100000 : ");

	my_resize.shrink_to_fit();
	print_data(my_resize.capacity(), "new capacity after reserve for a shrink to fit: ");

	std::cout << std::endl << std::endl << std::endl;
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
	INFO(my_range_constructor, "Element of the vector before test 'modifier' : "); 
	int b[] = {42,43,44};
	my_range_constructor.assign(&b[0], &b[2]);
	INFO(my_range_constructor, "After assign : "); 
	my_range_constructor.push_back(18); 
	INFO(my_range_constructor, "After push back of 18 : "); 
	my_range_constructor.pop_back(); 
	INFO(my_range_constructor, "After pob back : "); 
	my_range_constructor.insert(my_range_constructor.begin(), 118); 
	INFO(my_range_constructor, "After insert of 118 in position 1 : "); 
	my_range_constructor.erase(my_range_constructor.begin()); 
	INFO(my_range_constructor, "After erase of 118 in position 1 : "); 
	VEC<T> swap;
	ft_fill_vector(swap);
	my_range_constructor.swap(swap); 
	INFO(my_range_constructor, "After swap with other vector : "); 
	my_range_constructor.clear();
	INFO(my_range_constructor, "After clear : "); 
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
	chrono.print_time(STRING(Temps de remplissage pour PERF_VALUE  : ));

	chrono.begin();
	VEC<T> vector2(PERF_VALUE, 42);
	chrono.end();
	chrono.print_time(STRING(Temps de construction pour PERF_VALUE  : ));

	chrono.begin();
	VEC<T> vector3(vector2.begin(), vector2.end());
	chrono.end();
	chrono.print_time(STRING(Temps de construction pour via iterateur de vecteur pour  PERF_VALUE  : ));

	typename VEC<T>::iterator middle = vector2.begin() + (vector2.size() / 2);
	chrono.begin();
	vector2.insert(middle, vector.begin(), vector.end());
	chrono.end();
	chrono.print_time(STRING(Temps de remplissage par insertion au milieu d un vecteur : ));

	chrono.begin();
	vector2.resize(PERF_VALUE * 10 );
	chrono.end();
	chrono.print_time(STRING(Temps de traitement d un resize de (PERF_VALUE  * 10)  : ));
	middle = vector3.begin() + (vector3.size() / 2);

	chrono.begin();
	vector3.erase(middle);
	chrono.end();
	chrono.print_time("Temps de suppresionn d'un element au milieu : ");

	chrono.begin();
	vector2.clear();
	chrono.end();
	chrono.print_time(STRING(Temps de traitement d un clear sur un vecteur de  (PERF_VALUE * 10) :  ));
	
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
