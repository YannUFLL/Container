#ifndef ALLOC_HPP
#define ALLOC_HPP

#include <new>


template<typename IT, typename T, typename A>
void	uninitialized_fill(IT beg, IT end, const T& val, A& alloc)
{
	IT p;
	try {
		for (p = beg; p != end; ++p)
			alloc.construct(p, val);
	}
	catch (std::exception &e)
	{
		for (IT q = beg; q !=p; q++ )
			static_cast<A&>(alloc).destroy(q);
		throw;
	}
}

template<typename INPUT_IT, typename IT, typename A>
void	uninitialized_copy(INPUT_IT beg, INPUT_IT end, IT &val, A& alloc)
{
	INPUT_IT p;
	IT ptr = val;
	try {
		for (p = beg; p != end; ++p, ++ptr)
			alloc.construct(p, *ptr);
	}
	catch (std::exception &e)
	{
		for (INPUT_IT q = beg; q !=p; q++ )
			alloc.destroy(q);
		throw;
	}
}

#endif