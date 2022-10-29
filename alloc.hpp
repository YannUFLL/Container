#ifndef ALLOC_HPP
#define ALLOC_HPP

#include "vector.hpp"

template<typename T, typename A>
void	uninitialized_fill(typename vector<T>::iterator beg, typename vector<T>::iterator end, const T& val, const A& alloc)
{
	typename vector<T>::iterator p;
	try {
		for (p = beg; p != end; ++p)
			alloc.construct((&*p), val);
	}
	catch (std::exception &e)
	{
		for (typename vector<T>::iterator q = beg; q !=p; q++ )
			alloc.destroy(q);
		throw(std::exception());
	}
}

template<typename T, typename A>
void	uninitialized_copy(typename vector<T>::iterator beg, typename vector<T>::iterator end, T val, const A& alloc)
{
	typename vector<T>::iterator p; 
	try {
		for (p = beg; p != end; ++p)
			alloc.construct(p, val);
	}
	catch (std::exception &e)
	{
		for (IT q = beg; q !=p; q++ )
			alloc.destroy(q);
		throw(std::exception());
	}
}

#endif