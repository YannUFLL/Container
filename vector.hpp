

template<typename T, typename A = std::allocato<T>
{
	private : 
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
}

template<typename IT, typename T>
void	uninitialized_fill(IT beg, IT end, const T& x)
{
	IT p; 
	try {
		for (p = beg; p != end; ++p)
			alloc.construct(p, x)
	}
	catch (std::exception &e)
	{
		for (IT q = beg; q !=p; q++ )
			alloc.destroy(q);
		throw(std::exception);
	}
}

template <typename T, typename A = std::alocator<T>>
private : private vector_base<T, A>
{
	void destroy_element()
}