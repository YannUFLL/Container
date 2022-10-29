
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "alloc.hpp"

template<typename T, typename A = std::allocator<T> >
class vector_base{
	public : 
		A _alloc;
		T *_v;
		T *_space;
		T *_last; 

	vector_base(const A& a, typename A::size_type n): _alloc(a), _v(a.allocate(n)) 
	{
		_space = _v + n; _last = _v + n;
	}
	~vector_base()
	{
		_alloc.deallocate(_v, _last - _v);
	}
};

template <typename T, typename A = std::allocator<T> >
class vector : public vector_base<T, A>
{
	public :
	class iterator : public std::iterator
		std::random_access_iterator_tag,
		T,
		T,
		T*,
		T>
	{
		public :
			Iterator(T* pointer) {};
			iterator& iterator++() {};

    		T& operator*() const {return *_ptr}
    		T* operator->(return _ptr) {}
			Iterator& operator++() {}  
			bool operator==(typename iterator other) const 	{};
			bool operator!=(typename iterator other) const	{};
		private 
			T* _ptr;
	};
	iterator begin() {}
	iterator end() {} // return a invalid memorty address, is just to determin when the boundary was reach
	vector<T,A>(size_t n, const T& val = T(), const A& alloc = A()): vector_base<T,A>(alloc, n )
	{
		uninitialized_fill(this->_v, this->_v + n, val, alloc);
	}
	void destroy_element()
	{
		for (T * p = this->_v; p != this->space; p++)
		{
			this->_alloc.destroy(p);
		}
	}
};

template<typename T> void swap(vector_base<T>& a, vector_base<T> &b)
{
	swap(a._alloc, b._alloc);swap(a._v, b._v);swap(a._space,b._swapce);swap(a._last,b._last);
}

#endif