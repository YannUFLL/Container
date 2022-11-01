
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "alloc.hpp"

template<typename T, typename Alloc = std::allocator<T> >
class vector_base{
	public : 
	typedef T value_type;
	typedef T* pointer;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef std::size_t size_type;

		allocator_type _alloc;
		pointer _v;
		pointer _space;
		pointer _last;

	vector_base(const allocator_type &a ): _alloc(a), _v(NULL)  
	{
	}
	vector_base(const allocator_type& a, size_type n): _alloc(a), _v(_alloc.allocate(n)) {

		_space = _v + n; _last = _v + n;
	}
	~vector_base()
	{
		_alloc.deallocate(_v, _last - _v);
	}
};

template <typename T, typename Alloc = std::allocator<T> >
class vector : public vector_base<T, Alloc>
{
	typedef T value_type;
	typedef T* pointer;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef std::size_t size_type;

	public :
	class iterator : public std::iterator<
		std::random_access_iterator_tag,
		T,
		T,
		T*,
		T>
	{
		public :
			iterator(pointer ptr) {this->_ptr = ptr;}
    		reference operator*() const {return *_ptr;}
    		pointer operator->() {return _ptr;}
			iterator& operator++() {_ptr++; return(*this);} 
			iterator& operator++(int) {iterator temp = *this; ++(*this); return(temp);} 
			bool operator==(const iterator &a) const 	
			{
				return (a._ptr == this->_ptr);
			}
			bool operator!=(const iterator &a) const 	
			{
				return (a._ptr != this->_ptr);
			}
		private : 
			pointer _ptr;
	};
	iterator begin() {return(iterator(this->_v)); }
	iterator end() {return(iterator(this->_space));} // return a invalid memorty address, is just to determin when the boundary was reach

	explicit vector(const allocator_type& alloc = allocator_type()): vector_base<T,Alloc>(alloc, 0) {}

	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): vector_base<T,Alloc>(alloc, n )
	{
		uninitialized_fill<T*,T,Alloc>(this->_v, (this->_v + n), val, this->_alloc);
	}

	template <typename InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type()): vector_base<T,Alloc>(alloc, 0)
	{
		size_type n;
		for (InputIterator ptr = first; ptr != last; ptr++)
			n++;
		this->_alloc.allocate(n);
		uninitialized_copy(first, last, this->_v, this->_alloc );
	}

	vector(const vector& x): vector_base<T,Alloc>(x._alloc, x.size()) 
	{
		uninitialized_copy(x.begin(), x.end(), this->_v, this->_alloc);
	}

	~vector()	{destroy_element();this->~vector_base<T>();}	
	void destroy_element()
	{
		for (pointer p = this->_v; p != this->_space; p++)
		{
			this->_alloc.destroy(p);
		}
	}
	/* CAPACITY */
	size_type size() const {return size_type(end() - begin());}
	size_type maxsize() const {return (static_cast<size_type>(std::numeric_limits<size_type>::max()));}
	size_type capacity() {return (this->_last - this->_v);}
	void	resize(size_type n, value_type val = value_type())
	{
		reallocate(n,val);
	}
	void	reserve(size_type n) 
	{
		if (n > this->maxsize)
			throw (std::length_error("vector::reserve"));
		if (n > this->capacity())
		{
			reallocate(n);
		}
	}
	bool empty() {return(this->_v == this->_space - 1);}
	private : 
		void	reallocate(size_type n)
		{
			size_type nbr_elements = this->size();
			pointer ptr = this->_alloc.allocate(n);
			uninitialized_copy(this->begin(), this->end(), ptr, this->_alloc);
			this->~vector();
			this->_v = ptr; 
			this->_space = ptr + nbr_elements; 
			this->_last = ptr + n;
		}
		void	reallocate(size_type n, value_type val)
		{
			size_type nbr_elements = this->size();
			pointer ptr = this->_alloc.allocate(n);
			uninitialized_copy(ptr, ptr + this->size(), this->_v, this->_alloc);
			uninitialized_fill(ptr + this->size(), ptr + n, val, this->_alloc);
			this->~vector();
			this->_v = ptr; 
			this->_space = ptr + nbr_elements; 
			this->_last = ptr + n;
		}
};

template<typename T> void swap(vector_base<T>& a, vector_base<T> &b)
{
	swap(a._alloc, b._alloc);swap(a._v, b._v);swap(a._space,b._space);swap(a._last,b._last);
}

#endif