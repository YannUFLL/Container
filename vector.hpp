
#include <memory>

template<typename T, typename A = std::allocator<T> >
class vector_base{
	public : 
		A _alloc;
		T *_v;
		T *_space;
		T *_last; 

	vector_base(const A& a, typename A::size_type n): _alloc(a), v(a.allocate(n)), space(v + n), last(v + n)  
	{}
	~vector_base()
	{
		alloc.deallocate(v, last);
	}
};

template<typename IT, typename T, typename A>
void	uninitialized_fill(IT beg, IT end, const T& x, const A& alloc)
{
	IT p; 
	try {
		for (p = beg; p != end; ++p)
			alloc.construct(p, x);
	}
	catch (std::exception &e)
	{
		for (IT q = beg; q !=p; q++ )
			alloc.destroy(q);
		throw(std::exception);
	}
}

template<typename IT, typename T, typename A>
void	uninitialized_copy(IT beg, IT end, T val, const A& alloc)
{
	IT p; 
	try {
		for (p = beg; p != end; ++p)
			alloc.construct(p, x);
	}
	catch (std::exception &e)
	{
		for (IT q = beg; q !=p; q++ )
			alloc.destroy(q);
		throw(std::exception);
	}
}

template <typename T, typename A = std::allocator<T> >
class vector : public vector_base<T, A>
{
	vector<T,A>(size_type n, const &T val, const A&a ): vector_base<T,A>(a, n )
	{
		uninitialized_fill(_v, _v + n, val, a);
	}
	void destroy_element()
	{
		for (T * p = _v; p != space; p++)
		{
			alloc.destroy(q);
		}
	}
};

template<typename T> void swap(vector_base<T>& a, vector_base<T> &b)
{
	swap(a._alloc, b._alloc);swap(a._v, b._v);swap(a._space,b._swapce);swap(a._last,b._last);
}
