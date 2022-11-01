#ifndef ALLOC_HPP
#define ALLOC_HPP


template<typename IT, typename T, typename A>
void	uninitialized_fill(IT beg, IT end, const T& val, A& alloc)
{
	IT p;
	std::allocator<T> test;
	try {
		for (p = beg; p != end; ++p)
			test.construct(p, val);
	}
	catch (std::exception &e)
	{
		for (IT q = beg; q !=p; q++ )
			static_cast<A&>(alloc).destroy(q);
		throw(std::exception());
	}
}

template<typename IT, typename A>
void	uninitialized_copy(IT &beg, IT &end, IT &val, A& alloc)
{
	IT p; 
	try {
		for (p = beg; p != end; ++p, ++val)
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