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

#define MAP ft::map<T1, T2>
#define PAIR ft::pair<T1, T2>
#define PERF_VALUE 1000000

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
void	ft_map_mono_test()	
{
//--------------------------------------------------------------------------------------//
//                                       Iterator                                       //
//--------------------------------------------------------------------------------------//
/*
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

	typename MAP::const_iterator start3 = iterator2.cbegin();
	typename MAP::const_iterator end3 = iterator2.cend();
	ft_check_value(start3 != end3, true);
	start3++;
	ft_check_value(start3 != end3, false);
	
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
	*/

//--------------------------------------------------------------------------------------//
//                                      Modifiers                                       //
//--------------------------------------------------------------------------------------//

ft_title("Modifier : ");
MAP map_m;
PAIR p;
p.first = 142; p.second = 42;
//map_m.insert(p);
//ft_check_value(map_m.at(142), 42);

for (int i = 0; i < 100000; i++)
{
	if (i == 50)
		{ p.first = i; p.second = 4200;}
	else
		{p.first = i; p.second = 99;}
	map_m.insert(p);

}



//ft_check_value(map_m.at(50), 4200);
/*
MAP map_m2;

map_m2.insert(map_m.begin(), map_m.end());
ft_check_value(map_m2.size(), static_cast<unsigned long int>(101));
//ft_check_value(map_m2.at(50), 4200);
typename MAP::iterator m2_it = map_m2.begin();
for (int i = 0; i < 50; i++)
	m2_it++;
map_m2.erase(m2_it);
ft_check_value(map_m2[50], 0);
MAP map_m3;
map_m3[50] = 43;
map_m3.swap(map_m2);
ft_check_value(map_m2[50], 43);
std::cout << map_m3.size() << std::endl;
map_m3.erase(map_m3.begin(), map_m3.end());
std::cout << map_m3.size() << std::endl;
ft_check_value(map_m3.size(),static_cast<unsigned long int>(0));
ft_check_value(map_m2[1],0);
*/




//--------------------------------------------------------------------------------------//
//                                      Observers                                       //
//--------------------------------------------------------------------------------------//
	
//--------------------------------------------------------------------------------------//
//                                      Operations                                      //
//--------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------//
//                                      Allocator                                       //
//--------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------//
//                                      Speed Test                                      //
//--------------------------------------------------------------------------------------//
}


#endif