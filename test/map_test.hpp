#ifndef MAP_TEST
#define MAP_TEST

#include <chrono> 
#include <unistd.h>
#include <stdlib.h>
#include "../test/MyChrono.hpp"
#include "../test/vector_test.hpp"
#include "../container/vector.hpp"
#include "../container/map.hpp"
#include <map>
#include "../test/vector_test.hpp"
#include <list>
#include <string>

#define MAP ft::map<T1, T2>
#define PAIR ft::pair<T1, T2>

template <typename T1, typename T2>
void	ft_fulling_map(MAP &map)
{
	std::vector<int> vec;
	for (int i = 0; i <= 1000; i++)
	{
		if (i == 42)
			map[i] = 42;
		else
			map[i] = rand() % 100;
	}
}

void	ft_title(std::string title)
{
	std::cout << std::endl << std::endl << title << std::endl;
}

template <typename T1, typename T2>
void	ft_map_test()	
{
	
//--------------------------------------------------------------------------------------//
//                                     Constructor                                      //
//--------------------------------------------------------------------------------------//
	//Constructeur de copy avec une list en entree 
	std::cout << std::endl << "\e[0;31m		Starting map test \e[0m" << std::endl;
	usleep(2000000);
	ft_title("Constructor : ");
/*
	std::list<ft::pair<const int, int> > lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(ft::pair<const int, int>(i, (lst_size - i)));
	ft::map<T1, T2> mp(lst.begin(), lst.end());
	ft_check_value(mp.size(), static_cast<unsigned long int>(10));
	ft_check_value(mp[2],8 );
	ft::map<T1, T2> mp2;
	ft_check_value(mp2.size(), static_cast<unsigned long int>(0));

	ft::map<T1, T2> mp3(mp);
	ft_check_value(mp3[2],8 );*/
//--------------------------------------------------------------------------------------//
//                                       Iterator                                       //
//--------------------------------------------------------------------------------------//


	ft_title("Iterator : ");
	MAP iterator;
	typename MAP::iterator start = iterator.begin();
	typename MAP::iterator end = iterator.end();
	ft_check_value(start == end, true);
	ft_fulling_map(iterator);
	typename MAP::iterator start2 = iterator.begin();
	typename MAP::iterator end2 = iterator.end();
	ft_check_value(start2 == end2, false);
	for (int i = 0; i < 1000; i++)
		start2++;
	end2--;
	ft_check_value(start2 == end2, true);
	ft_check_value(start2->second, iterator[1000]);
	for (int i = 0; i < 1000; i++)
		--start2;
	ft_check_value(start2->second, iterator[0]);
	typename MAP::reverse_iterator rstart = iterator.rbegin();
	typename MAP::reverse_iterator rend ;
	rend = iterator.rend();
	(void)rstart;
	rend--;
	ft_check_value(rend->second, iterator[0]);
	rend--;
	ft_check_value(rend->second, iterator[1]);
	ft_check_value(rstart->second, iterator[1000]);

	MAP iterator2;
	typename MAP::reverse_iterator rstart2 = iterator2.rbegin();
	typename MAP::reverse_iterator rend2 = iterator2.rend();
	ft_check_value(rstart2 == rend2,true);
	iterator2[1] = 42;
 	rstart2 = iterator2.rbegin();
	rend2 = iterator2.rend();
	ft_check_value(rstart2 != rend2,true);
	rstart2++;
	rstart2--;
	rstart2++;
	ft_check_value(rstart2 != rend2,false);
/*
	typename MAP::const_iterator start3 = iterator2.begin();
	typename MAP::const_iterator end3 = iterator2.end();
	ft_check_value(start3 != end3, true);
	start3++;
	ft_check_value(start3 != end3, false);*/

	iterator.clear();
	start = iterator.begin();
	end = iterator.end();
	ft_check_value((start == end), true);

//--------------------------------------------------------------------------------------//
//                                       Capacity                                       //
//--------------------------------------------------------------------------------------//

	ft_title("Capacity : ");
	MAP size;
	ft_check_value(size.size(),static_cast<unsigned long int>(0));
	ft_check_value(size.empty(),true);
	for (int i = 0; i< 1452; i++)
	{
		size[i] = 42;
	}
	ft_check_value(size.empty(),false);
	ft_check_value(size.size(),static_cast<unsigned long int>(1452));
	
//--------------------------------------------------------------------------------------//
//                                    Element Access                                    //
//--------------------------------------------------------------------------------------//

	ft_title("Element Access : ");
	MAP map_ea;
	map_ea[1] = 42;
	ft_check_value(map_ea[1], 42);
	try
	{
		map_ea.at(2);
	}
	catch (std::exception &e)
	{
		ft_check_value(1, 1);
	}
	ft_check_value(map_ea.at(1), 42);
	map_ea[1] = 84;
	ft_check_value(map_ea.at(1), 84);
	ft_fulling_map(map_ea);
	ft_check_value(map_ea.at(42), 42);
	

//--------------------------------------------------------------------------------------//
//                                      Modifiers                                       //
//--------------------------------------------------------------------------------------//


ft_title("Modifier : ");
MAP map_m;
PAIR p;
p.first = 142; p.second = 42;
map_m.insert(p);
ft_check_value(map_m.at(142), 42);

for (int i = 0; i <10000 ; i++)
{
	if (i == 50)
		{ p.first = i; p.second = 4200;}
	else
		{p.first = i; p.second = 99;}
	map_m.insert(p);

}
ft_check_value(map_m.at(50), 4200);
MAP map_m2;

map_m2.insert(map_m.begin(), map_m.end());
ft_check_value(map_m2.size(), static_cast<unsigned long int>(10000));
ft_check_value(map_m2.at(50), 4200);
typename MAP::iterator m2_it = map_m2.begin();

for (int i = 0; i < 4; i++)
	m2_it++;

map_m2.erase(m2_it);
ft_check_value(map_m2[4], 0);
MAP map_m3;
map_m3[50] = 43;
map_m3.swap(map_m2);
ft_check_value(map_m2[50], 43);
map_m3.erase(map_m3.begin(), map_m3.end());
ft_check_value(map_m3.size(),static_cast<unsigned long int>(0));
ft_check_value(map_m2[1],0);


MAP map_m4;
try
{
	map_m4.at(42);
}
catch(const std::exception& e)
{
	ft_check_value(1,1);
}
	ft_check_value(map_m4.size(),static_cast<unsigned long int>(0));
	map_m4.clear();
	map_m4.clear();

//--------------------------------------------------------------------------------------//
//                                      Operations                                       //
//--------------------------------------------------------------------------------------//
ft_title("Operations : ");
MAP map_ope;
ft_check_value(map_ope.count(42), static_cast<unsigned long int>(0));
map_ope[42] = 42;
map_ope[42] = 43;
map_ope[42] = 44;
ft_check_value(map_ope.count(42), static_cast<unsigned long int>(1));
map_ope[1] = 42;
map_ope[2] = 42;
map_ope[3] = 42;
map_ope[4] = 42;
map_ope[5] = 42;
map_ope[8] = 42;
typename MAP::iterator it_ob = map_ope.find(3);
it_ob++;
ft_check_value(it_ob->first, 4);
it_ob = map_ope.find(100000);
ft_check_value(it_ob, map_ope.end());
it_ob = map_ope.lower_bound(2);
ft_check_value(it_ob->first, 2);
it_ob = map_ope.lower_bound(6);
ft_check_value(it_ob->first, 8);
it_ob = map_ope.upper_bound(9);
ft_check_value(it_ob, (--map_ope.end()));
it_ob = map_ope.upper_bound(5);
ft_check_value(it_ob->first, 8);
/*std::pair<typename MAP::iterator, typename MAP::iterator> pair = map_ope.equal_range(5);
ft_check_value(pair.first->first, 5);
ft_check_value(pair.second->first, 8);*/


//--------------------------------------------------------------------------------------//
//                                      Operator                                        //
//--------------------------------------------------------------------------------------//
ft_title("Operator : ");

MAP map_op;
map_op[0] = 5;
map_op[1] = 42;
map_op[2] = 43;

MAP map_op2;
map_op2[0] = 5;
map_op2[1] = 42;
map_op2[2] = 43;

ft_check_value(map_op == map_op2, true);
ft_check_value(map_op != map_op2, false);
map_op2[4] = 43;
ft_check_value(map_op == map_op2, false);
ft_check_value(map_op != map_op2, true);
map_op2.erase(4);
ft_check_value(map_op == map_op2, true);
map_op2[2] = 44;
ft_check_value(map_op == map_op2, false);
map_op2[2] = 43;


ft_check_value(map_op <= map_op2, true);
ft_check_value(map_op >= map_op2, true);
ft_check_value(map_op < map_op2, false);
ft_check_value(map_op > map_op2, false);
ft_check_value(map_op == map_op2, true);
map_op.clear();
map_op = map_op2;
map_op2.clear();
ft_check_value(map_op == map_op2, false);


//--------------------------------------------------------------------------------------//
//                                      Allocator                                       //
//--------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------//
//                                      Speed Test                                      //
//--------------------------------------------------------------------------------------//
	ft_title("Speed Test : ");
	std::cout << std::endl;
	MAP map_s1;
	MyChrono chrono;
	chrono.begin();
	for (int i = 0; i < PERF_VALUE; i++)
		map_s1[i];
	chrono.end();
	chrono.print_time(STRING(time insert PERF_VALUE elements : ));

	chrono.begin();
	for (int i = 0; i < PERF_VALUE; i++)
		map_s1.erase(i);
	chrono.end();
	chrono.print_time(STRING(time erase PERF_VALUE elements : ));

	chrono.begin();
	for (int i = 0; i < PERF_VALUE; i++)
	map_s1[rand()] = rand();
	chrono.end();
	chrono.print_time(STRING(time insert random PERF_VALUE elements : ));
		
	chrono.begin();
	map_s1.clear();
	chrono.end();
	chrono.print_time(STRING(time clear map random PERF_VALUE elements : ));

}


#endif